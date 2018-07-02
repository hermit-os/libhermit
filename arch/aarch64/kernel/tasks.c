/*
 * Copyright (c) 2017, Stefan Lankes, RWTH Aachen University
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the name of the University nor the names of its contributors
 *      may be used to endorse or promote products derived from this
 *      software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <hermit/stdio.h>
#include <hermit/stdlib.h>
#include <hermit/tasks.h>
#include <hermit/errno.h>
#include <hermit/logging.h>
#include <hermit/string.h>

extern int smp_main(void);

/*
 * Note that linker symbols are not variables, they have no memory allocated for
 * maintaining a value, rather their address is their value.
 */
extern const void tls_start;
extern const void tls_end;
extern const void tdata_end;

extern atomic_int32_t cpu_online;
extern atomic_int32_t current_boot_id;

typedef union dtv
{
	size_t counter;
	struct {
		void *val;
		uint8_t is_static;
	} pointer;
} dtv_t;

typedef struct {
	dtv_t *dtv;	/* dtv */
	void *privat;	/* private */
} thread_block_t;

static int init_tls(void)
{
	task_t* curr_task = per_core(current_task);

	// do we have a thread local storage?
	if (((size_t) &tls_end - (size_t) &tls_start) > 0) {
		size_t tdata_size = (size_t) &tdata_end - (size_t) &tls_start;

		curr_task->tls_addr = (size_t) &tls_start;
		curr_task->tls_size = (size_t) &tls_end - (size_t) &tls_start;

		thread_block_t* tcb = (thread_block_t*) kmalloc(curr_task->tls_size+sizeof(thread_block_t));
		if (BUILTIN_EXPECT(!tcb, 0)) {
			LOG_ERROR("load_task: heap is missing!\n");
			return -ENOMEM;
		}

		memset((void*) tcb, 0x00, curr_task->tls_size+sizeof(thread_block_t));
		tcb->dtv = (dtv_t*) &tcb[1];
		memcpy((char*) tcb->dtv, (void*) curr_task->tls_addr, tdata_size);

		set_tpidr((size_t) tcb);
		LOG_INFO("TLS of task %d on core %d starts at 0x%zx (tls size 0x%zx)\n", curr_task->id, CORE_ID, get_tpidr(), curr_task->tls_size);
	} else set_tpidr(0); // no TLS => clear tpidr_el0 register

	return 0;
}

void destroy_tls(void)
{
	size_t tpidr = get_tpidr();
	if (tpidr)
		kfree((void*)tpidr);
}

static int thread_entry(void* arg, size_t ep)
{

	if (init_tls())
		return -ENOMEM;

	//vma_dump();

	entry_point_t call_ep = (entry_point_t) ep;
	call_ep(arg);
	/* After finishing the task, we will return here and call the
	   cleanup function, which calls the scheduler */
	leave_kernel_task();

	return 0;
}

size_t* get_current_stack(void)
{
	task_t* curr_task = per_core(current_task);
	size_t stptr = (size_t) curr_task->stack;

	if (curr_task->status == TASK_IDLE)
		stptr += KERNEL_STACK_SIZE - 0x10;
	else
		stptr = (stptr + DEFAULT_STACK_SIZE - sizeof(size_t)) & ~0x1F;

	//set_tss(stptr, (size_t) curr_task->ist_addr + KERNEL_STACK_SIZE - 0x10);

	return curr_task->last_stack_pointer;
}

int create_default_frame(task_t* task, entry_point_t ep, void* arg, uint32_t core_id)
{
	size_t *stack;
	struct state *stptr;
	size_t state_size;

	if (BUILTIN_EXPECT(!task, 0))
		return -EINVAL;

	if (BUILTIN_EXPECT(!task->stack, 0))
		return -EINVAL;

	LOG_INFO("Task %d uses memory region [%p - %p] as stack\n", task->id, task->stack, (char*) task->stack + DEFAULT_STACK_SIZE - 1);
	LOG_INFO("Task %d uses memory region [%p - %p] as IST1\n", task->id, task->ist_addr, (char*) task->ist_addr + KERNEL_STACK_SIZE - 1);

	memset(task->stack, 0xCD, DEFAULT_STACK_SIZE);

	/* The difference between setting up a task for SW-task-switching
	 * and not for HW-task-switching is setting up a stack and not a TSS.
	 * This is the stack which will be activated and popped off for iret later.
	 */
	stack = (size_t*) (((size_t) task->stack + DEFAULT_STACK_SIZE - sizeof(size_t)) & ~0x1F);	// => stack is 32byte aligned

	/* Only marker for debugging purposes, ... */
	*stack-- = 0xDEADBEEF;
	*stack-- = 0xDEADBEEF;

	/* Next bunch on the stack is the initial register state.
	 * The stack must look like the stack of a task which was
	 * scheduled away previously. */
	state_size = sizeof(struct state);
	stack = (size_t*) ((size_t) stack - state_size);

	stptr = (struct state *) stack;
	memset(stptr, 0x00, state_size);
	//stptr->sp = (size_t)stack + state_size;
	/* the first-function-to-be-called's arguments, ... */
	stptr->x0 = (size_t) arg;

	/* The procedure link register needs to hold the address of the
	 * first function to be called when returning from switch_context. */
	stptr->elr_el1 = (size_t)thread_entry;
	stptr->x1 = (size_t)ep; // use second argument to transfer the entry point

	/* Zero the condition flags. */
	stptr->spsr_el1 = 0x205;

	/* Set the task's stack pointer entry to the stack we have crafted right now. */
	task->last_stack_pointer = (size_t*)stack;

	return 0;
}

#if MAX_CORES > 1
int smp_start(void)
{
	int32_t core_id = atomic_int32_read(&current_boot_id);

	LOG_INFO("Try to initialize processor (local id %d)\n", core_id);

	cpu_detection();

	atomic_int32_inc(&cpu_online);

	irq_enable();

	return smp_main();
}
#endif

int is_proxy(void)
{
	return 0;
}

void wait_for_task(void)
{
	HALT;
}

void wakeup_core(uint32_t core_id)
{
	// Currently not required...
}

void shutdown_system(void)
{
	LOG_INFO("Try to shutdown system\n");

	atomic_int32_dec(&cpu_online);
	while(1) {
		HALT;
	}
}

extern uint32_t uhyve;
const int32_t is_uhyve(void)
{
	return (uhyve != 0);
}
