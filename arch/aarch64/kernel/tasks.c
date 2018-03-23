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

#define TLS_ALIGNBITS		5
#define TLS_ALIGNSIZE		(1L << TLS_ALIGNBITS)
#define TSL_ALIGNMASK		((~0L) << TLS_ALIGNBITS)
#define TLS_FLOOR(addr)		((((size_t)addr) + TLS_ALIGNSIZE - 1) & TSL_ALIGNMASK)

/*
 * Note that linker symbols are not variables, they have no memory allocated for
 * maintaining a value, rather their address is their value.
 */
extern const void tls_start;
extern const void tls_end;

extern atomic_int32_t cpu_online;

static char tls[16][DEFAULT_STACK_SIZE];
static int id = 0;

static int init_tls(void)
{
	task_t* curr_task = per_core(current_task);

	// do we have a thread local storage?
	if (((size_t) &tls_end - (size_t) &tls_start) > 0) {
		char* tls_addr = NULL;
		size_t tpidr_el0;

		curr_task->tls_addr = (size_t) &tls_start;
		curr_task->tls_size = (size_t) &tls_end - (size_t) &tls_start;

		//tls_addr = kmalloc(curr_task->tls_size + TLS_ALIGNSIZE + sizeof(size_t));
		tls_addr = tls[id];
		id++;
		if (BUILTIN_EXPECT(!tls_addr, 0)) {
			LOG_ERROR("load_task: heap is missing!\n");
			return -ENOMEM;
		}

		memset(tls_addr, 0x00, TLS_ALIGNSIZE);
		memcpy((void*) TLS_FLOOR(tls_addr), (void*) curr_task->tls_addr, curr_task->tls_size);
		tpidr_el0 = (size_t) TLS_FLOOR(tls_addr) + curr_task->tls_size;
		*((size_t*)tpidr_el0) = tpidr_el0;

		// set tpidr_el0 register to the TLS segment
		set_tls(tpidr_el0);
		//LOG_INFO("TLS of task %d on core %d starts at 0x%zx (size 0x%zx)\n", curr_task->id, CORE_ID, TLS_FLOOR(tls_addr), curr_task->tls_size);
	} else set_tls(0); // no TLS => clear tpidr_el0 register

	return 0;
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

#if 0
extern uint32_t single_kernel;
const int32_t is_single_kernel(void)
{
	return (single_kernel != 0);
}
#endif
