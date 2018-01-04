/*
 * Copyright (c) 2010, Stefan Lankes, RWTH Aachen University
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
#include <hermit/string.h>
#include <hermit/stdlib.h>
#include <hermit/tasks.h>
#include <hermit/errno.h>
#include <hermit/processor.h>
#include <hermit/logging.h>
#include <asm/gdt.h>
#include <asm/tss.h>
#include <asm/page.h>

// minimal number of GDT entries (for one core)
// a TSS descriptor is twice larger than a code/data descriptor
#define GDT_MIN_ENTRIES	(7+1*2)

gdt_ptr_t		gp;

// currently, our kernel has full access to the ioports
static gdt_entry_t	boot_gdt[GDT_MIN_ENTRIES] = {[0 ... GDT_MIN_ENTRIES-1] = {0, 0, 0, 0, 0, 0}};
static gdt_entry_t*	gdt = boot_gdt;

static tss_t*		boot_tss = NULL;
static tss_t**		task_state_segments = &boot_tss;

/*
 * This is defined in entry.asm. We use this to properly reload
 * the new segment registers
 */
extern void gdt_flush(void);

/*
 * This is defined in entry.asm. We use this to properly replace
 * the current stack
 */
extern void replace_boot_stack(size_t);

extern int32_t boot_processor;
extern atomic_int32_t possible_cpus;
extern atomic_int32_t current_boot_id;

void set_tss(size_t rps0, size_t ist1)
{
	task_state_segments[CORE_ID]->rsp0 = rps0;
	task_state_segments[CORE_ID]->ist1 = ist1;
}

/* Setup a descriptor in the Global Descriptor Table */
void gdt_set_gate(int num, unsigned long base, unsigned long limit,
			  unsigned char access, unsigned char gran)
{
	configure_gdt_entry(gdt+num, base, limit, access, gran);
}

void configure_gdt_entry(gdt_entry_t *dest_entry, unsigned long base, unsigned long limit,
		unsigned char access, unsigned char gran)
{
	/* Setup the descriptor base address */
	dest_entry->base_low = (base & 0xFFFF);
	dest_entry->base_middle = (base >> 16) & 0xFF;
	dest_entry->base_high = (base >> 24) & 0xFF;

	/* Setup the descriptor limits */
	dest_entry->limit_low = (limit & 0xFFFF);
	dest_entry->granularity = ((limit >> 16) & 0x0F);

	/* Finally, set up the granularity and access flags */
	dest_entry->granularity |= (gran & 0xF0);
	dest_entry->access = access;
}

/*
 * This will setup the special GDT
 * pointer, set up the entries in our GDT, and then
 * finally call gdt_flush() in our assembler file in order
 * to tell the processor where the new GDT is and update the
 * new segment registers
 */
void gdt_install(void)
{
	int num = 0;

	/* Setup the GDT pointer and limit */
	gp.limit = (sizeof(gdt_entry_t) * GDT_MIN_ENTRIES) - 1;
	gp.base = (size_t) gdt;

	/* Our NULL descriptor */
	gdt_set_gate(num++, 0, 0, 0, 0);

	/*
	 * The second entry is our Code Segment. The base address
	 * is 0, the limit is 4 GByte, it uses 4KByte granularity,
	 * and is a Code Segment descriptor.
	 */
	gdt_set_gate(num++, 0, 0,
		GDT_FLAG_RING0 | GDT_FLAG_SEGMENT | GDT_FLAG_CODESEG | GDT_FLAG_PRESENT, GDT_FLAG_64_BIT);

	/*
	 * The third entry is our Data Segment. It's EXACTLY the
	 * same as our code segment, but the descriptor type in
	 * this entry's access byte says it's a Data Segment
	 */
	gdt_set_gate(num++, 0, 0,
		GDT_FLAG_RING0 | GDT_FLAG_SEGMENT | GDT_FLAG_DATASEG | GDT_FLAG_PRESENT, GDT_FLAG_64_BIT);

	/*
	 * Create code segment for 32bit user-space applications (ring 3)
	 */
	gdt_set_gate(num++, 0, 0xFFFFFFFF,
		GDT_FLAG_RING3 | GDT_FLAG_SEGMENT | GDT_FLAG_CODESEG | GDT_FLAG_PRESENT, GDT_FLAG_32_BIT | GDT_FLAG_4K_GRAN);

	/*
	 * Create data segment for 32bit user-space applications (ring 3)
	 */
	gdt_set_gate(num++, 0, 0xFFFFFFFF,
		GDT_FLAG_RING3 | GDT_FLAG_SEGMENT | GDT_FLAG_DATASEG | GDT_FLAG_PRESENT, GDT_FLAG_32_BIT | GDT_FLAG_4K_GRAN);

	/*
	 * Create code segment for 64bit user-space applications (ring 3)
	 */
	gdt_set_gate(num++, 0, 0,
		GDT_FLAG_RING3 | GDT_FLAG_SEGMENT | GDT_FLAG_CODESEG | GDT_FLAG_PRESENT, GDT_FLAG_64_BIT);

	/*
	 * Create data segment for 64bit user-space applications (ring 3)
	 */
	gdt_set_gate(num++, 0, 0,
		GDT_FLAG_RING3 | GDT_FLAG_SEGMENT | GDT_FLAG_DATASEG | GDT_FLAG_PRESENT, GDT_FLAG_64_BIT);

	/* Flush out the old GDT and install the new changes! */
	gdt_flush();
}

/*
 * Create TSS for the current core (we use these segments for task switching)
 */
void tss_init(tid_t id /* => current task id */)
{
	int32_t no_cpus = atomic_int32_read(&possible_cpus);
	int32_t core_id = atomic_int32_read(&current_boot_id);

	LOG_INFO("Initialize TSS for task %d on core %d, possible cores %d\n",
		id, core_id, no_cpus);

	if ((task_state_segments == &boot_tss) && (no_cpus > 1))
	{
		task_state_segments = (tss_t**) kmalloc(sizeof(tss_t*)*no_cpus);
		if (BUILTIN_EXPECT(!task_state_segments, 0)) {
			LOG_ERROR("Unable to allocate array for the task state segments\n");
			goto oom;
		}

		memset(task_state_segments, 0x00, sizeof(tss_t*)*no_cpus);
		task_state_segments[0] = boot_tss;
	}

	if ((gdt == boot_gdt) && (no_cpus > 1))
	{
		gdt = (gdt_entry_t*) kmalloc(sizeof(gdt_entry_t)*(7+no_cpus*2));
		if (BUILTIN_EXPECT(!gdt, 0)) {
			LOG_ERROR("Unable to allocate GDT\n");
			goto oom;
		}

		memset(gdt, 0x00, sizeof(gdt_entry_t)*(7+no_cpus*2));
		memcpy(gdt, &boot_gdt, sizeof(gdt_entry_t)*GDT_MIN_ENTRIES);

		gp.limit = (sizeof(gdt_entry_t) * (7+no_cpus*2)) - 1;
		gp.base = (size_t) gdt;
	}

	tss_t* tss = (tss_t*) kmalloc(sizeof(tss_t));
	if (BUILTIN_EXPECT(!tss, 0)) {
		LOG_ERROR("Unable to allocate task state segment\n");
		goto oom;
	}

	memset(tss, 0x00, sizeof(tss_t));

	size_t rsp0 = (size_t) create_stack(KERNEL_STACK_SIZE);
	if (BUILTIN_EXPECT(!rsp0, 0)) {
		LOG_ERROR("Unable to allocate stack for the idle task %d\n", id);
		goto oom;
	}
	tss->rsp0 = rsp0 + KERNEL_STACK_SIZE - 0x10;

	size_t ist1 = (size_t) create_stack(KERNEL_STACK_SIZE);
	if (BUILTIN_EXPECT(!ist1, 0)) {
		LOG_ERROR("Unable to allocate ist1 for the idle task %d\n", id);
		goto oom;
	}
	tss->ist1 = (size_t) ist1 + KERNEL_STACK_SIZE - 0x10;

	tss->ist2 = (size_t) create_stack(KERNEL_STACK_SIZE) + KERNEL_STACK_SIZE - 0x10;
	if (BUILTIN_EXPECT(!tss->ist2, 0)) {
		LOG_ERROR("Unable to allocate ist2 for the idle task %d\n", id);
		goto oom;
	}

	tss->ist3 = (size_t) create_stack(KERNEL_STACK_SIZE) + KERNEL_STACK_SIZE - 0x10;
	if (BUILTIN_EXPECT(!tss->ist3, 0)) {
		LOG_ERROR("Unable to allocate ist3 for the idle task %d\n", id);
		goto oom;
	}

	tss->ist4 = (size_t) create_stack(KERNEL_STACK_SIZE) + KERNEL_STACK_SIZE - 0x10;
	if (BUILTIN_EXPECT(!tss->ist4, 0)) {
		LOG_ERROR("Unable to allocate ist4 for the idle task %d\n", id);
		goto oom;
	}

	task_state_segments[core_id] = tss;
	gdt_set_gate(7+core_id*2, (unsigned long) tss,
		sizeof(tss_t), GDT_FLAG_PRESENT | GDT_FLAG_TSS | GDT_FLAG_RING0, 0);

	// set stack in our task table
	set_boot_stack(id, rsp0, ist1);

	// replace the stack pointer
	replace_boot_stack(rsp0);

	gdt_flush();
	reset_fsgs(core_id);

	return;

oom:
	while(1) { HALT; }
}
