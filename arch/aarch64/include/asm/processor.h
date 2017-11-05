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

/**
 * @author Stefan Lankes
 * @file arch/arm64/include/asm/processor.h
 * @brief CPU-specific functions
 *
 * This file contains structures and functions related to CPU-specific assembler commands.
 */

#ifndef __ARCH_PROCESSOR_H__
#define __ARCH_PROCESSOR_H__

#include <hermit/stddef.h>
#include <asm/irqflags.h>

#ifdef __cplusplus
extern "C" {
#endif

// determine the cpu features
int cpu_detection(void);

/** @brife Get thread local storage
 *
 * Helper function to get the TLS of the current task
 */
static inline size_t get_tls(void) {
	uint64_t addr;
	asm volatile(
		"mrs %0, tpidr_el0"
		: "+r"(addr)
		:
		: );
	return addr;
}

/** @brief Set thread local storage
 *
 * Helper function to set the TLS of the current task
 */
static inline void set_tls(size_t addr) {
	asm volatile(
		"msr tpidr_el0, %0"
		: "=r"(addr)
		:
		: );
}

/** @brief Read id_aa64mmfr0_el1 register
 * @return id_aa64mmfr0_el1's value
 */
static inline size_t read_id_aa64mmfr0_el1(void) {
        size_t val;
        asm volatile("mrs %0, id_aa64mmfr0_el1" : "=r"(val) :: "memory");
        return val;
}

/** @brief Read sctlr_el1 register
 * @return sctlr_el1's value
 */
static inline size_t read_sctlr_el1(void) {
        size_t val;
        asm volatile("mrs %0, sctlr_el1" : "=r"(val) :: "memory");
        return val;
}

/** @brief Write a value into sctlr_el1 register
 * @param val The value you want to write into sctlr_el1
 */
static inline void write_sctlr_el1(size_t val) {
	asm volatile("msr sctlr_el1, %0" :: "r"(val) : "memory");
}

/** @brief Read tcr_el1 register
 * @return tcr_el1's value
 */
static inline size_t read_tcr_el1(void) {
        size_t val;
        asm volatile("mrs %0, tcr_el1" : "=r"(val) :: "memory");
        return val;
}

/** @brief Write a value into tcr_el1 register
 * @param val The value you want to write into tcr_el1
 */
static inline void write_tcr_el1(size_t val) {
	asm volatile("msr tcr_el1, %0" :: "r"(val) : "memory");
}

/** @brief Read mair_el1 register
 * @return mair_el1's value
 */
static inline size_t read_mair_el1(void) {
        size_t val;
        asm volatile("mrs %0, mair_el1" : "=r"(val) :: "memory");
        return val;
}

/** @brief Write a value into mair_el1 register
 * @param val The value you want to write into mair_el1
 */
static inline void write_mair_el1(size_t val) {
	asm volatile("msr mair_el1, %0" :: "r"(val) : "memory");
}

/** @brief Read ttbr0_el1 register
 * @return ttbr0_el1's value
 */
static inline size_t read_ttbr0_el1(void) {
        size_t val;
        asm volatile("mrs %0, ttbr0_el1" : "=r"(val) :: "memory");
        return val;
}

/** @brief Write a value into ttbr0_el1 register
 * @param val The value you want to write into ttbr0_el1
 */
static inline void write_ttbr0_el1(size_t val) {
	asm volatile("msr ttbr0_el1, %0" :: "r"(val) : "memory");
}

/** @brief Read ttbr1_el1 register
 * @return ttbr1_el1's value
 */
static inline size_t read_ttbr1_el1(void) {
        size_t val;
        asm volatile("mrs %0, ttbr1_el1" : "=r"(val) :: "memory");
        return val;
}

/** @brief Write a value into ttbr1_el1 register
 * @param val The value you want to write into ttbr1_el1
 */
static inline void write_ttbr1_el1(size_t val) {
	asm volatile("msr ttbr1_el1, %0" :: "r"(val) : "memory");
}

/** @brief Read far_el1 register
 * @return faulting virtual address
 */
static inline size_t read_far_el1(void) {
        size_t val = 0;
        asm volatile("mrs %0, far_el1" : "=r"(val) :: "memory");
        return val;
}

/** @brief Read out time stamp counter
 *
 * The rdtsc instruction puts a 64 bit time stamp value
 * into EDX:EAX.
 *
 * @return The 64 bit time stamp value
 */
inline static uint64_t rdtsc(void) { return 0; }

inline static uint64_t get_rdtsc(void) { return rdtsc(); }


/** @brief: print current pstate
 */
void dump_pstate(void);

/// A one-instruction-do-nothing
#define NOP
/// The PAUSE instruction provides a hint to the processor that the code sequence is a spin-wait loop.
#define PAUSE
/// The HALT instruction stops the processor until the next interrupt arrives
#define HALT

/** @brief Flush Translation Lookaside Buffer
 */
static inline void tlb_flush(uint8_t with_ipi)
{
	asm volatile(
 		"tlbi all\n\t"
		"isb"
 		:
 		:
 		: "memory"
 	);

#if MAX_CORES > 1
	if (with_ipi)
		ipi_tlb_flush();
#endif
}

/** @brief Flush a specific page entry in TLB
 * @param addr The (virtual) address of the page to flush
 */
 static inline void tlb_flush_one_page(size_t addr, uint8_t with_ipi)
 {
 	asm volatile(
 		"tlbi vaae1, %0 \n\t"
		"isb"
 		:
 		: "r" (addr)
 		: "memory"
 	);

 	#if MAX_CORES > 1
 		if (with_ipi)
 			ipi_tlb_flush();
 	#endif
 }

/// Force strict CPU ordering, serializes load and store operations.
static inline void mb(void) { asm volatile ("dmb sy" : : : "memory"); }
/// Force strict CPU ordering, serializes load operations.
static inline void rmb(void) { asm volatile ("dmb ld" : : : "memory"); }
/// Force strict CPU ordering, serializes store operations.
static inline void wmb(void) { asm volatile ("dmb st" : : : "memory"); }

static inline size_t msb(size_t i) {
	size_t ret, tmp = 63;

	if (!i)
		return (sizeof(size_t)*8);
	asm volatile (
		"clz %0, %1\n\t"
		"sub %0, %2, %0"
	 	: "=r"(ret)
	 	: "r"(i), "r"(tmp)
	 	: "cc");

	return ret;
}

/** @brief Init several subsystems
 *
 * This function calls the initialization procedures for:
 * - GDT
 * - APIC
 * - PCI [if configured]
 *
 * @return 0 in any case
 */
inline static int system_init(void)
{
	//cpu_detection();

	return 0;
}

/** @brief Detect and read out CPU frequency
 *
 * @return The CPU frequency in MHz
 */
uint32_t detect_cpu_frequency(void);

/** @brief Read out CPU frequency if detected before
 *
 * If you did not issue the detect_cpu_frequency() function before,
 * this function will call it implicitly.
 *
 * @return The CPU frequency in MHz
 */
uint32_t get_cpu_frequency(void);

/** @brief Busywait an microseconds interval of time
 * @param usecs The time to wait in microseconds
 */
static inline void udelay(uint32_t usecs) {}

/// Register a task's TSS at GDT
void register_task(void);

/** @brief System calibration
 *
 * This procedure will detect the CPU frequency and calibrate the APIC timer.
 *
 * @return 0 in any case.
 */
static inline int system_calibration(void) {return 0;}

#ifdef __cplusplus
}
#endif

#endif
