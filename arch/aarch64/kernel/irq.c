/*
 * Copyright (c) 2014-2017, Stefan Lankes, Daniel Krebs, RWTH Aachen University
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
#include <asm/processor.h>
#include <asm/page.h>

/* GIC related constants */
#define GICD_BASE			0x8000000
#define GICC_BASE			0x8010000
#define GICR_BASE			0

/* GIC Distributor interface register offsets that are common to GICv3 & GICv2 */
#define GICD_CTLR			0x0
#define GICD_TYPER			0x4
#define GICD_IIDR			0x8
#define GICD_IGROUPR		0x80
#define GICD_ISENABLER		0x100
#define GICD_ICENABLER		0x180
#define GICD_ISPENDR		0x200
#define GICD_ICPENDR		0x280
#define GICD_ISACTIVER		0x300
#define GICD_ICACTIVER		0x380
#define GICD_IPRIORITYR		0x400
#define GICD_ICFGR			0xc00
#define GICD_NSACR			0xe00

#define GICD_ITARGETSR		0x800

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
#define GICC_PRIODROP		GICC_EOIR

#define TIMER_IRQ			27

static size_t gicd_base = GICD_BASE;
static size_t gicc_base = GICC_BASE;

static inline uint32_t gicd_read(size_t off)
{
	uint32_t value;
	asm volatile("ldr %0, [%1]" : "=&r"(value) : "r"(gicd_base + off));
    rmb();
	return value;
}

static inline void gicd_write(size_t off, uint32_t value)
{
	asm volatile("str %0, [%1]" :: "r"(value), "r"(gicd_base + off));
    wmb();
}

static inline uint32_t gicd_read_reg(size_t off, uint32_t reg)
{
	uint32_t value;
	asm volatile("ldr %0, [%1]" : "=&r"(value) : "r"(gicd_base + off + reg));
	rmb();
	return value;
}

static inline void gicd_write_reg(size_t off, uint32_t reg, uint32_t value)
{
	asm volatile("str %0, [%1]" :: "r"(value), "r"(gicd_base + off + reg));
	wmb();
}

static inline uint32_t gicc_read(size_t off)
{
	uint32_t value;
	asm volatile("ldr %0, [%1]" : "=&r"(value) : "r"(gicc_base + off));
	rmb();
	return value;
}

static inline void gicc_write(size_t off, uint32_t value)
{
	asm volatile("str %0, [%1]" :: "r"(value), "r"(gicc_base + off));
    wmb();
}

static void gic_enable_interrupts(void)
{
	// Global enable forwarding interrupts from distributor to cpu interface
	uint32_t ctlr = gicd_read(GICD_CTLR);
	ctlr |= 1;
	gicd_write(GICD_CTLR, ctlr);

	// Global enable signalling of interrupt from the cpu interface
	ctlr = gicc_read(GICC_CTLR);
	ctlr |= 1;
	gicc_write(GICC_CTLR, ctlr);
}

static void gic_disable_interrupts(void)
{
	// Global disable signalling of interrupt from the cpu interface
	uint32_t ctlr = gicc_read(GICC_CTLR);
	ctlr = ctlr & ~1;
	gicc_write(GICC_CTLR, ctlr);

	// Global disable forwarding interrupts from distributor to cpu interface
	ctlr = gicd_read(GICD_CTLR);
	ctlr = ctlr & ~1;
	gicd_write(GICD_CTLR, ctlr);
}

static void gic_cpu_set_priority(char priority)
{
    gicc_write(GICC_PMR, priority & 0x000000FF);
}

static void gic_set_priority(int irq_number, unsigned char priority)
{
    uint32_t value = gicd_read_reg(GICD_IPRIORITYR, irq_number >> 2);
    value &= ~(0xff << (8 * (irq_number & 0x3))); // clear old priority
    value |= priority << (8 * (irq_number & 0x3)); // set new priority
    gicd_write_reg(GICD_IPRIORITYR, irq_number >> 2, value);
}

static void gic_route_interrupt(int irq_number, unsigned char cpu_set)
{
    uint32_t value = gicd_read_reg(GICD_ITARGETSR, irq_number >> 2);
    value &= ~(0xff << (8 * (irq_number & 0x3))); // clear old target
    value |= cpu_set << (8 * (irq_number & 0x3)); // set new target
    gicd_write_reg(GICD_ITARGETSR, irq_number >> 2, value);
}

static inline void clear_bit_non_atomic(int nr, volatile void *base)
{
    volatile uint32_t *tmp = base;
    tmp[nr >> 5] &= (unsigned long)~(1 << (nr & 0x1f));
}

static inline void set_bit_non_atomic(int nr, volatile void *base)
{
    volatile uint32_t *tmp = base;
    tmp[nr >> 5] |= (1 << (nr & 0x1f));
}

static void gic_enable_interrupt(int irq_number, unsigned char cpu_set, unsigned char level_sensitive)
{
    int *set_enable_reg;
    void *cfg_reg;

    // set priority
    gic_set_priority(irq_number, 0x0);

    // set target cpus for this interrupt
    gic_route_interrupt(irq_number, cpu_set);

    // set level/edge triggered
    cfg_reg = (void *)gicd_read(GICD_ICFGR);
	LOG_INFO("Found GICD_ICFGR at %p\n", cfg_reg);
    if (level_sensitive) {
        clear_bit_non_atomic((irq_number * 2) + 1, cfg_reg);
    } else {
        set_bit_non_atomic((irq_number * 2) + 1, cfg_reg);
    }
    wmb();

    // enable forwarding interrupt from distributor to cpu interface
    set_enable_reg = (int *)gicd_read(GICD_ISENABLER);
    set_enable_reg[irq_number >> 5] = 1 << (irq_number & 0x1f);
    wmb();
}

int irq_init(void)
{
	LOG_INFO("Enable interrupt handling\n");

	gic_disable_interrupts();
	gic_cpu_set_priority(0xFF);
	gic_enable_interrupts();

	//gic_enable_interrupt(TIMER_IRQ /* interrupt number */, 0x1 /*cpu_set*/, 0x1 /*level_sensitive*/);

	return 0;
}

int enable_dynticks(void)
{
	return 0;
}

int irq_handler(void)
{
	kputs("receive interrupt\n");

    uint32_t esr = read_esr();
    uint32_t ec = esr >> 24;
    uint32_t iss = esr & 0xFFFFFF;

	/* data abort from lower or current level */
    if (ec == 0b100100 || ec == 0b100101) {
		/* check if value in far_el1 is valid */
		if (!(iss & (1 << 10))) {
			/* read far_el1 register, which holds the faulting virtual address */
            uint64_t far = read_far();
			//page_fault_handler(far);
		} else {
			kputs("Could not handle data abort: address in far_el1 invalid\n");
		}
    }

	return 0;
}
