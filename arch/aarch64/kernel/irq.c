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

#define IRQ_TYPE_LEVEL		0x0
#define IRQ_TYPE_EDGE		0x1

static size_t gicd_base = GICD_BASE;
static size_t gicc_base = GICC_BASE;
static unsigned char cpu_targets[MAX_CORES] = {[0 ... MAX_CORES-1] = 0};

static inline uint32_t gicd_read(size_t off)
{
	return *((uint32_t*)(gicd_base + off));
}

static inline void gicd_write(size_t off, uint32_t value)
{
	*((uint32_t*)(gicd_base + off)) = value;
}

static inline uint32_t gicd_read_reg(size_t off, uint32_t reg)
{
	return *((uint32_t*)(gicd_base + off + reg));
}

static inline void gicd_write_reg(size_t off, uint32_t reg, uint32_t value)
{
	*((uint32_t*)(gicd_base + off + reg)) = value;
}

static inline void gicd_write_reg_grp(uint32_t reg, uint32_t irq, uint8_t value)
{
    uint32_t offset = reg + (irq / 32) * 4;
    uint32_t shift = irq % 32;
    uint32_t old = gicd_read(offset);

    old &= ~(1 << shift);
    old |= value << shift;

    *((uint32_t*)(gicd_base + offset)) = old;
}

static inline uint8_t gicd_read_reg_grp(uint32_t reg, uint32_t irq)
{
	uint32_t offset = reg + (irq / 32) * 4;
	uint32_t mask = 1 << (irq % 32);

    return (*((uint32_t*)(gicd_base + offset))) & mask ? 1 : 0;
}

static inline uint32_t gicc_read(size_t off)
{
	return *((uint32_t*)(gicc_base + off));
}

static inline void gicc_write(size_t off, uint32_t value)
{
	*((uint32_t*)(gicc_base + off)) = value;
}

void set_irq_type(uint32_t id, uint32_t type)
{
	gicd_write_reg_grp(GICD_ICFGR, id, 1);
}

int irq_init(void)
{
	int smp_idx = 0;
	uint64_t ctlr;
	unsigned char my_mask = 0;

	LOG_INFO("Enable interrupt handling\n");

	for (int i = 16; i < 32; i++) { /* check PPIs target */
		my_mask = gicd_read_reg_grp(GICD_ITARGETSR, i);
		if (my_mask) {
			cpu_targets[smp_idx] = my_mask;
			break;
		}
	}

	if (!my_mask) {
		LOG_INFO("Assuming uniprocessor\n");
		cpu_targets[smp_idx] = 0;
	}

	/* set priority mask register for CPU */
	for (int i = 0; i < 32; i += 4) {
		gicc_write(GICC_PMR, 0xf0);
	}

	/* enable CPU interface */
	ctlr = gicc_read(GICC_CTLR);
	ctlr |= 1;
	gicc_write(GICC_CTLR, ctlr);

	LOG_INFO("CPU interface enabled.\n");

	/* Disable the distributor before going further */
	ctlr = gicd_read(GICD_CTLR);
	ctlr = ctlr & ~1;
	gicd_write(GICD_CTLR, ctlr);

	uint32_t int_nr = ((gicd_read(GICD_TYPER) & 0x1f)+1)*32;
	LOG_INFO("Number of supported interrupts %d\n", int_nr);

	/* set all SPIs to level-sensitive at the start */
	for (uint32_t i = 32; i<int_nr; i+=16)
		gicd_write_reg(GICD_ICFGR, i / 4, 0);

	if (my_mask) {
		my_mask |= my_mask << 8;  /* duplicate pattern (x2) */
		my_mask |= my_mask << 16; /* duplicate pattern (x4) */
	}

	/* set priority */
	for (uint32_t i=32; i<int_nr; i+=4) {
		if (my_mask) {
			gicd_write_reg(GICD_ITARGETSR, i, my_mask);
		}

		gicd_write_reg(GICD_IPRIORITYR, i, 0xc0c0c0c0);
	}

	/* disable all Shared Peripheral Interrupts (SPI) */
	for (uint32_t i=32; i<int_nr; i+=32)
		gicd_write_reg(GICD_ICENABLER, i / 8, 0xffffffff);

	/* disable all Private Peripheral Interrupts (PPI) interrupts */
	gicd_write_reg(GICD_ICENABLER, 0, 0xffff0000);

	/* enable all Software Generated Interrupts (SGI) interrupts */
	gicd_write_reg(GICD_ISENABLER, 0, 0x0000ffff);

	/* set priority on SGI/PPI (at least bits [7:4] must be implemented) */
	for (uint32_t i=0; i<32; i+=4)
		gicd_write_reg(GICD_IPRIORITYR, i, 0xc0c0c0c0);

	/* enable distributor interface */
	ctlr |= 1;
	gicd_write(GICD_CTLR, ctlr);

	set_irq_type(16+11, IRQ_TYPE_EDGE);

	return 0;
}

int enable_dynticks(void)
{
	return 0;
}

int irq_handler(void)
{
    uint32_t esr = read_esr_el1();
    uint32_t ec = esr >> 24;
    uint32_t iss = esr & 0xFFFFFF;

	kputs("receive interrupt\n");
	/* data abort from lower or current level */
    if (ec == 0b100100 || ec == 0b100101) {
		/* check if value in far_el1 is valid */
		if (!(iss & (1 << 10))) {
			/* read far_el1 register, which holds the faulting virtual address */
            uint64_t far = read_far_el1();
			//page_fault_handler(far);
		} else {
			kputs("Could not handle data abort: address in far_el1 invalid\n");
		}
    }

	return 0;
}
