/*
 * Copyright (c) 2014-2018, Stefan Lankes, RWTH Aachen University
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

#include <hermit/stdlib.h>
#include <hermit/stdio.h>
#include <hermit/logging.h>
#include <hermit/errno.h>
#include <hermit/tasks.h>
#include <hermit/spinlock.h>
#include <asm/processor.h>
#include <asm/page.h>
#include <asm/irq.h>

/* GIC related constants */
#define GICR_BASE			0

/* GIC Distributor interface register offsets that are common to GICv3 & GICv2 */
#define GICD_CTLR			0x0
#define GICD_TYPER			0x4
#define GICD_IIDR			0x8
#define GICD_IGROUPR			0x80
#define GICD_ISENABLER			0x100
#define GICD_ICENABLER			0x180
#define GICD_ISPENDR			0x200
#define GICD_ICPENDR			0x280
#define GICD_ISACTIVER			0x300
#define GICD_ICACTIVER			0x380
#define GICD_IPRIORITYR			0x400
#define GICD_ITARGETSR			0x800
#define GICD_ICFGR			0xc00
#define GICD_NSACR			0xe00
#define GICD_SGIR			0xF00

#define GICD_CTLR_ENABLEGRP0		(1 << 0)
#define GICD_CTLR_ENABLEGRP1		(1 << 1)

/* Physical CPU Interface registers */
#define GICC_CTLR			0x0
#define GICC_PMR			0x4
#define GICC_BPR			0x8
#define GICC_IAR			0xC
#define GICC_EOIR			0x10
#define GICC_RPR			0x14
#define GICC_HPPIR			0x18
#define GICC_AHPPIR			0x28
#define GICC_IIDR			0xFC
#define GICC_DIR			0x1000
#define GICC_PRIODROP			GICC_EOIR

#define GICC_CTLR_ENABLEGRP0		(1 << 0)
#define GICC_CTLR_ENABLEGRP1		(1 << 1)
#define GICC_CTLR_FIQEN			(1 << 3)
#define GICC_CTLR_ACKCTL		(1 << 2)

#define MAX_HANDLERS			256
#define RESCHED_INT			1

/** @brief IRQ handle pointers
*
* This array is actually an array of function pointers. We use
* this to handle custom IRQ handlers for a given IRQ
*/
static irq_handler_t irq_routines[MAX_HANDLERS] = {[0 ... MAX_HANDLERS-1] = NULL};

static spinlock_irqsave_t mask_lock = SPINLOCK_IRQSAVE_INIT;

static size_t gicd_base = GICD_BASE;
static size_t gicc_base = GICC_BASE;
static uint32_t nr_irqs = 0;

static inline uint32_t gicd_read(size_t off)
{
	uint32_t value;
	asm volatile("ldar %w0, [%1]" : "=r"(value) : "r"(gicd_base + off) : "memory");
	return value;
}

static inline void gicd_write(size_t off, uint32_t value)
{
	asm volatile("str %w0, [%1]" : : "rZ" (value), "r" (gicd_base + off) : "memory");
}

static inline uint32_t gicc_read(size_t off)
{
	uint32_t value;
	asm volatile("ldar %w0, [%1]" : "=r"(value) : "r"(gicc_base + off) : "memory");
	return value;
}

static inline void gicc_write(size_t off, uint32_t value)
{
	asm volatile("str %w0, [%1]" : : "rZ" (value), "r" (gicc_base + off) : "memory");
}

static void gicc_enable(void)
{
	// Global enable signalling of interrupt from the cpu interface
	gicc_write(GICC_CTLR, GICC_CTLR_ENABLEGRP0 | GICC_CTLR_ENABLEGRP1 | GICC_CTLR_FIQEN | GICC_CTLR_ACKCTL);
}

static void gicc_disable(void)
{
	// Global disable signalling of interrupt from the cpu interface
	gicc_write(GICC_CTLR, 0);
}

static void gicd_enable(void)
{
	// Global enable forwarding interrupts from distributor to cpu interface
	gicd_write(GICD_CTLR, GICD_CTLR_ENABLEGRP0 | GICD_CTLR_ENABLEGRP1);
}

static void gicd_disable(void)
{
	// Global disable forwarding interrupts from distributor to cpu interface
	gicd_write(GICD_CTLR, 0);
}

static void gicc_set_priority(uint32_t priority)
{
	gicc_write(GICC_PMR, priority & 0xFF);
}

static void gic_set_enable(uint32_t vector, uint8_t enable)
{
	if (enable) {
		uint32_t regoff = GICD_ISENABLER + 4 * (vector / 32);
		gicd_write(regoff, gicd_read(regoff) | (1 << (vector % 32)));
	} else {
		uint32_t regoff = GICD_ICENABLER + 4 * (vector / 32);
		gicd_write(regoff, gicd_read(regoff) | (1 << (vector % 32)));
	}
}

static int unmask_interrupt(uint32_t vector)
{
	if (vector >= nr_irqs)
		return -EINVAL;

	spinlock_irqsave_lock(&mask_lock);
	gic_set_enable(vector, 1);
	spinlock_irqsave_unlock(&mask_lock);

	return 0;
}

static int mask_interrupt(uint32_t vector)
{
	if (vector >= nr_irqs)
		return -EINVAL;

	spinlock_irqsave_lock(&mask_lock);
	gic_set_enable(vector, 0);
	spinlock_irqsave_unlock(&mask_lock);

	return 0;
}

/* This installs a custom IRQ handler for the given IRQ */
int irq_install_handler(unsigned int irq, irq_handler_t handler)
{
	if (irq >= MAX_HANDLERS)
		return -EINVAL;

	irq_routines[irq] = handler;
	
	unmask_interrupt(irq);

	return 0;
}

/* This clears the handler for a given IRQ */
int irq_uninstall_handler(unsigned int irq)
{
	if (irq >= MAX_HANDLERS)
		return -EINVAL;

	irq_routines[irq] = NULL;

	mask_interrupt(irq);

	return 0;
}

int irq_post_init(void)
{
	int ret;

	LOG_INFO("Enable interrupt handling\n");

	ret = vma_add(GICD_BASE, GICD_BASE+GIC_SIZE, VMA_READ|VMA_WRITE);
	if (BUILTIN_EXPECT(ret, 0))
		goto oom;

	ret = page_map(gicd_base, GICD_BASE, GIC_SIZE >> PAGE_BITS, PG_GLOBAL|PG_RW|PG_DEVICE);
        if (BUILTIN_EXPECT(ret, 0))
                goto oom;

	LOG_INFO("Map gicd 0x%zx at 0x%zx\n", GICD_BASE, gicd_base);
	LOG_INFO("Map gicc 0x%zx at 0x%zx\n", GICC_BASE, gicc_base);

	gicc_disable();
	gicd_disable();

	nr_irqs = ((gicd_read(GICD_TYPER) & 0x1f) + 1) * 32;
	LOG_INFO("Number of supported interrupts %u\n", nr_irqs);

	gicd_write(GICD_ICENABLER, 0xffff0000);
	gicd_write(GICD_ISENABLER, 0x0000ffff);
	gicd_write(GICD_ICPENDR, 0xffffffff);
	gicd_write(GICD_IGROUPR, 0);

	for (uint32_t i = 0; i < 32 / 4; i++) {
		gicd_write(GICD_IPRIORITYR + i * 4, 0x80808080);
	}

	for (uint32_t i = 32/16; i < nr_irqs / 16; i++) {
		gicd_write(GICD_NSACR + i * 4, 0xffffffff);
	}

	for (uint32_t i = 32/32; i < nr_irqs / 32; i++) {
		gicd_write(GICD_ICENABLER + i * 4, 0xffffffff);
		gicd_write(GICD_ICPENDR + i * 4, 0xffffffff);
		gicd_write(GICD_IGROUPR + i * 4, 0);
	}

	for (uint32_t i = 32/4; i < nr_irqs / 4; i++) {
		gicd_write(GICD_ITARGETSR + i * 4, 0);
		gicd_write(GICD_IPRIORITYR + i * 4, 0x80808080);
	}

	gicd_enable();

	gicc_set_priority(0xF0);
	gicc_enable();

	unmask_interrupt(RESCHED_INT);

	return 0;

oom:
	LOG_ERROR("Failed to intialize interrupt controller\n");

	return ret;
}

void do_sync(void *regs)
{
	uint32_t iar = gicc_read(GICC_IAR);
	uint32_t esr = read_esr();
	uint32_t ec = esr >> 26;
	uint32_t iss = esr & 0xFFFFFF;
	uint64_t pc = get_elr();

        /* data abort from lower or current level */
	if ((ec == 0b100100) || (ec == 0b100101)) {
		/* check if value in far_el1 is valid */
		if (!(iss & (1 << 10))) {
			/* read far_el1 register, which holds the faulting virtual address */
			uint64_t far = read_far();

			if (page_fault_handler(far, pc) == 0)
				return;

			LOG_ERROR("Unable to handle page fault at 0x%llx\n", far);
			LOG_ERROR("Exception return address 0x%llx\n", get_elr());
			LOG_ERROR("Thread ID register 0x%llx\n", get_tpidr());
			LOG_ERROR("Table Base Register 0x%llx\n", get_ttbr0());
			LOG_ERROR("Exception Syndrome Register 0x%lx\n", esr);

			// send EOI
			gicc_write(GICC_EOIR, iar);
			//do_abort();
			sys_exit(-EFAULT);
		} else {
			LOG_ERROR("Unknown exception\n");
		}
	} else if (ec == 0x3c) {
		LOG_ERROR("Trap to debugger, PC=0x%x\n", pc);
	} else {
		LOG_ERROR("Unsupported exception class: 0x%x, PC=0x%x\n", ec, pc);
	}

	sys_exit(-EFAULT);

}

size_t** do_fiq(void *regs)
{
	size_t** ret = NULL;
	uint32_t iar = gicc_read(GICC_IAR);
	uint32_t vector = iar & 0x3ff;

	//LOG_INFO("Receive fiq %d\n", vector);

	if (vector < MAX_HANDLERS && irq_routines[vector]) {
		(irq_routines[vector])(regs);
	} else if (vector != RESCHED_INT) {
		LOG_INFO("Unable to handle fiq %d\n", vector);
	}

	// Check if timers have expired that would unblock tasks
	check_workqueues_in_irqhandler(vector);

	if ((vector == INT_PPI_NSPHYS_TIMER) || (vector == RESCHED_INT)) {
		// a timer interrupt may have caused unblocking of tasks
		ret = scheduler();
	} else if (get_highest_priority() > per_core(current_task)->prio) {
		// there's a ready task with higher priority
		ret = scheduler();
	}

	gicc_write(GICC_EOIR, iar);

	return ret;
}

size_t** do_irq(void *regs)
{
	size_t** ret = NULL;
	uint32_t iar = gicc_read(GICC_IAR);
	uint32_t vector = iar & 0x3ff;

	LOG_INFO("Receive interrupt %d\n", vector);

	// Check if timers have expired that would unblock tasks
	check_workqueues_in_irqhandler(vector);

	if (get_highest_priority() > per_core(current_task)->prio) {
		// there's a ready task with higher priority
		ret = scheduler();
	}

	gicc_write(GICC_EOIR, iar);

	return ret;
}

void do_error(void *regs)
{
	LOG_ERROR("Receive error interrupt\n");

	while (1) {
		HALT;
	}
}

void do_bad_mode(void *regs, int reason)
{
	LOG_ERROR("Receive unhandled exception: %d\n", reason);

	while (1) {
		HALT;
	}
}

void reschedule(void)
{
	// (2 << 24) = Forward the interrupt only to the CPU interface of the PE that requested the interrupt
	gicd_write(GICD_SGIR, (2 << 24) | RESCHED_INT);
}
