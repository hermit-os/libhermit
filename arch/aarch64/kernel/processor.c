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
#include <hermit/spinlock.h>
#include <asm/processor.h>

/*
 * Note that linker symbols are not variables, they have no memory allocated for
 * maintaining a value, rather their address is their value.
 */
extern const void percore_start;
extern const void percore_end0;
extern const void percore_end;

extern uint32_t cpu_freq;
extern atomic_int32_t current_boot_id;

void print_cpu_status(int isle)
{
	static spinlock_t status_lock = SPINLOCK_INIT;

	spinlock_lock(&status_lock);
	LOG_INFO("CPU %d is online, 0x%zx\n", CORE_ID, get_mpidr());
	spinlock_unlock(&status_lock);
}

uint32_t get_cpu_frequency(void)
{
	return cpu_freq;
}

static void init_percore_data(uint32_t core_id)
{
	asm volatile("msr tpidr_el1, %0" :: "r"(core_id * ((size_t) &percore_end0 - (size_t) &percore_start)));

#if 1
	size_t off;
	asm volatile("mrs %0, tpidr_el1" : "=r"(off));
	LOG_INFO("Set tpidr_el1 to 0x%zx\n", off);
#endif
}

int cpu_detection(void)
{
	static uint8_t first_time = 1;
	uint32_t id = atomic_int32_read(&current_boot_id);

	init_percore_data(id);
	set_per_core(__core_id, id);

	if (first_time) {
		LOG_INFO("HermitCore runs in exception level %d\n", get_current_el());
		LOG_INFO("System control register: 0x%x\n", get_sctlr());
	}

#if 0
	uint32_t value = 0;

	LOG_INFO("Enable performance counter\n");

	/* Enable Performance Counter */
	asm volatile("mrs %0, pmcr_el0" : "=r" (value));
	value |= ARMV8_PMCR_E; /* Enable */
	value |= ARMV8_PMCR_C; /* Cycle counter reset */
	value |= ARMV8_PMCR_P; /* Reset all counters */
	asm volatile("msr pmcr_el0, %0" : : "r" (value));

	/* Enable cycle counter register */
	asm volatile("mrs %0, pmcntenset_el0" : "=r" (value));
	value |= ARMV8_PMCNTENSET_EL0_EN;
	asm volatile("msr pmcntenset_el0, %0" : : "r" (value));
#endif

	first_time = 0;

	return 0;
}
