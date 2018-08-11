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
#include <asm/atomic.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ARMV8_PMCR_E			(1 << 0) /* Enable all counters */
#define ARMV8_PMCR_P			(1 << 1) /* Reset all counters */
#define ARMV8_PMCR_C			(1 << 2) /* Cycle counter reset */

#define ARMV8_PMUSERENR_EN		(1 << 0) /* EL0 access enable */
#define ARMV8_PMUSERENR_CR		(1 << 2) /* Cycle counter read enable */
#define ARMV8_PMUSERENR_ER		(1 << 3) /* Event counter read enable */

#define ARMV8_PMCNTENSET_EL0_EN	(1 << 31) /* Performance Monitors Count Enable Set register */

/* interrupts */
#define INT_PPI_VMAINT			(16+9)
#define INT_PPI_HYP_TIMER		(16+10)
#define INT_PPI_VIRT_TIMER		(16+11)
#define INT_PPI_SPHYS_TIMER		(16+13)
#define INT_PPI_NSPHYS_TIMER	(16+14)

// determine the cpu features
int cpu_detection(void);

inline static int has_hbmem(void) {
	return 0;
}

inline static size_t get_hbmem_base(void) {
	return 0;
}

inline static size_t get_hbmem_size(void) {
	return 0;
}

static inline uint32_t get_isr(void)
{
	uint32_t status;
	asm volatile("mrs %0, isr_el1" : "=r"(status));
	return status;
}

static inline uint32_t get_sctlr(void)
{
	uint32_t status;
	asm volatile("mrs %0, sctlr_el1" : "=r"(status));
	return status;
}

static inline uint64_t get_elr(void)
{
	uint64_t ret;
	asm volatile("mrs %0, elr_el1" : "=r"(ret));
	return ret;
}

/** @brief get the current exception level
 *
 * Helper function to get the current exception level
 *
 */
static inline uint32_t get_current_el(void)
{
	uint32_t curr;
	asm volatile("mrs %0, CurrentEL" : "=r"(curr));
	return (curr>>2) & 0x3;
}

/** @brief Get thread id register */
static inline size_t get_tpidr(void) {
	uint64_t addr;
	asm volatile("mrs %0, tpidr_el0" : "=r"(addr));
	return addr;
}

/** @brief Set thread id  register */
static inline void set_tpidr(size_t addr) {
	asm volatile("msr tpidr_el0, %0" :: "r"(addr));
}

/** @brief Read id_aa64mmfr0_el1 register
 * @return id_aa64mmfr0_el1's value
 */
static inline size_t read_id_aa64mmfr0(void) {
        size_t val;
        asm volatile("mrs %0, id_aa64mmfr0_el1" : "=r"(val) :: "memory");
        return val;
}

/** @brief Read sctlr_el1 register
 * @return sctlr_el1's value
 */
static inline size_t read_sctlr(void) {
        size_t val;
        asm volatile("mrs %0, sctlr_el1" : "=r"(val) :: "memory");
        return val;
}

/** @brief Write a value into sctlr_el1 register
 * @param val The value you want to write into sctlr_el1
 */
static inline void write_sctlr(size_t val) {
	asm volatile("msr sctlr_el1, %0" :: "r"(val) : "memory");
}

/** @brief Read tcr_el1 register
 * @return tcr_el1's value
 */
static inline size_t read_tcr(void) {
        size_t val;
        asm volatile("mrs %0, tcr_el1" : "=r"(val) :: "memory");
        return val;
}

/** @brief Write a value into tcr_el1 register
 * @param val The value you want to write into tcr_el1
 */
static inline void write_tcr(size_t val) {
	asm volatile("msr tcr_el1, %0" :: "r"(val) : "memory");
}

/** @brief Read mair_el1 register
 * @return mair_el1's value
 */
static inline size_t read_mair(void) {
        size_t val;
        asm volatile("mrs %0, mair_el1" : "=r"(val) :: "memory");
        return val;
}

/** @brief Write a value into mair_el1 register
 * @param val The value you want to write into mair_el1
 */
static inline void write_mair(size_t val) {
	asm volatile("msr mair_el1, %0" :: "r"(val) : "memory");
}

/** @brief Read ttbr0_el1 register
 * @return ttbr0_el1's value
 */
static inline size_t get_ttbr0(void) {
        size_t val;
        asm volatile("mrs %0, ttbr0_el1" : "=r"(val) :: "memory");
        return val;
}

/** @brief Write a value into ttbr0_el1 register
 * @param val The value you want to write into ttbr0_el1
 */
static inline void set_ttbr0(size_t val) {
	asm volatile("msr ttbr0_el1, %0" :: "r"(val) : "memory");
}

/** @brief Read ttbr1_el1 register
 * @return ttbr1_el1's value
 */
static inline size_t get_ttbr1(void) {
        size_t val;
        asm volatile("mrs %0, ttbr1_el1" : "=r"(val) :: "memory");
        return val;
}

/** @brief Write a value into ttbr1_el1 register
 * @param val The value you want to write into ttbr1_el1
 */
static inline void set_ttbr1(size_t val) {
	asm volatile("msr ttbr1_el1, %0" :: "r"(val) : "memory");
}

/** @brief Read far_el1 register
 * @return faulting virtual address
 */
static inline size_t read_far(void) {
        size_t val = 0;
        asm volatile("mrs %0, far_el1" : "=r"(val) :: "memory");
        return val;
}

/** @brief Read esr_el1 register
 * @return esr_el1's (Exception Syndrome Register) value
 */
static inline size_t read_esr(void) {
        size_t val;
        asm volatile("mrs %0, esr_el1" : "=r"(val) :: "memory");
        return val;
}

static inline uint64_t get_cntpct(void)
{
	uint64_t value;
	asm volatile("mrs %0, cntpct_el0" : "=r" (value) :: "memory");
	return value;
}

static inline uint64_t get_mpidr(void)
{
	uint64_t value;
	asm volatile("mrs %0, mpidr_el1" : "=r"(value) :: "memory");
	return value;
}

static inline uint64_t get_cpuactlr(void)
{
	uint64_t value;
	asm volatile("mrs %0, s3_1_c15_c2_0" : "=r"(value) :: "memory");
	return value;
}

static inline uint64_t get_cpuectlr(void)
{
	uint64_t value;
	asm volatile("mrs %0, s3_1_c15_c2_1" : "=r"(value) :: "memory");
	return value;
}

inline static uint64_t get_rdtsc(void) { return get_cntpct(); }

/// A one-instruction-do-nothing
#define NOP	asm volatile ("nop")
/// The PAUSE instruction provides a hint to the processor that the code sequence is a spin-wait loop.
#define PAUSE	asm volatile ("yield")
/// The HALT instruction stops the processor until the next interrupt arrives
#define HALT	asm volatile ("wfi")

/// Force strict CPU ordering, serializes load and store operations.
static inline void mb(void) { asm volatile ("dmb ish" : : : "memory"); }
/// Force strict CPU ordering, serializes load operations.
static inline void rmb(void) { asm volatile ("dmb ishld" : : : "memory"); }
/// Force strict CPU ordering, serializes store operations.
static inline void wmb(void) { asm volatile ("dmb ishst" : : : "memory"); }

/** @brief search the first most significant bit
 *
 * @param i source operand
 * @return
 * - first bit, which is set in the source operand
 * - invalid value, if not bit ist set
 */
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

static inline uint32_t get_cntfrq(void)
{
	uint32_t val;
	asm volatile("mrs %0, cntfrq_el0" : "=r" (val) :: "memory");
	return val;
}

static inline void set_cntfrq(uint32_t value)
{
	asm volatile("msr cntfrq_el0, %0" :: "r"(value) : "memory");
}

static inline uint32_t get_cntkctl(void)
{
	uint32_t value;
	asm volatile("mrs %0, cntkctl_el1" : "=r" (value) :: "memory");
	return value;
}

static inline void set_cntkctl(uint32_t value)
{
	asm volatile("msr cntkctl_el1, %0" :: "r" (value) : "memory");
}

static inline void set_cntp_cval(uint64_t value)
{
	asm volatile("msr cntp_cval_el0, %0" :: "r"(value) : "memory");
}

static inline uint64_t get_cntp_cval(void)
{
	uint64_t value;
	asm volatile("mrs %0, cntp_cval_el0" : "=r" (value) :: "memory");
	return value;
}

static inline void set_cntp_tval(uint64_t value)
{
	asm volatile("msr cntp_tval_el0, %0" :: "r"(value) : "memory");
}

static inline uint64_t get_cntp_tval(void)
{
	uint64_t value;
	asm volatile("mrs %0, cntp_tval_el0" : "=r" (value) :: "memory");
	return value;
}

static inline void set_cntp_ctl(uint32_t value)
{
	asm volatile("msr cntp_ctl_el0, %0" :: "r"(value) : "memory");
}

static inline uint32_t get_cntp_ctl(void)
{
	uint32_t value;
	asm volatile("mrs %0, cntp_ctl_el0" : "=r" (value) :: "memory");
	return value;
}

static inline uint64_t get_cntvct(void)
{
	uint64_t value;
	asm volatile("mrs %0, cntvct_el0" : "=r" (value) :: "memory");
	return value;
}

static inline void set_cntv_cval(uint64_t value)
{
	asm volatile("msr cntv_cval_el0, %0" :: "r"(value) : "memory");
}

static inline uint64_t get_cntv_cval(void)
{
	uint64_t value;
	asm volatile("mrs %0, cntv_cval_el0" : "=r" (value) :: "memory");
	return value;
}

static inline void set_cntv_tval(uint64_t value)
{
	asm volatile("msr cntv_tval_el0, %0" :: "r"(value) : "memory");
}

static inline uint64_t get_cntv_tval(void)
{
	uint64_t value;
	asm volatile("mrs %0, cntv_tval_el0" : "=r" (value) :: "memory");
	return value;
}

static inline void set_cntv_ctl(uint32_t value)
{
	asm volatile("msr cntv_ctl_el0, %0" :: "r"(value) : "memory");
}

static inline uint32_t get_cntv_ctl(void)
{
	uint32_t value;
	asm volatile("mrs %0, cntv_ctl_el0" : "=r" (value) :: "memory");
	return value;
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
	cpu_detection();

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
void udelay(uint32_t usecs);

/// Finalize the GIC initialization
int irq_post_init(void);

/// Sets up the system clock
int timer_calibration(void);

extern atomic_int32_t cpu_online;

/** @brief System calibration
 *
 * This procedure will detect the CPU frequency and calibrate the APIC timer.
 *
 * @return 0 in any case.
 */
static inline int system_calibration(void)
{
	irq_post_init();
	timer_calibration();
	atomic_int32_inc(&cpu_online);
	irq_enable();

	return 0;
}

#ifdef __cplusplus
}
#endif

#endif
