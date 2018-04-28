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
 * @file arch/arm64/include/asm/irqflags.h
 * @brief Functions related to IRQ configuration
 *
 * This file contains definitions of inline functions
 * for enabling and disabling exception handling.
 */

#ifndef __ARCH_IRQFLAGS_H__
#define __ARCH_IRQFLAGS_H__

#ifdef __cplusplus
extern "C" {
#endif

#define IRQ_FLAG_F	(1<<6)
#define IRQ_FLAG_I	(1<<7)
#define IRQ_FLAG_A	(1<<8)
#define IRQ_FLAG_D	(1<<9)

inline static uint32_t get_daif(void)
{
	size_t flags;
	asm volatile("mrs %0, daif" : "=r"(flags) :: "memory");
	return flags;
}

/** @brief Determines, if the exception bit mask bits (DAIF) allows exceptions
 *
 * @return
 * - 1 DAIF is cleared and allows exceptions
 * - 0 DAIF is cleared and allows exceptions
 */
inline static uint8_t is_irq_enabled(void)
{
	size_t flags = get_daif();
	if (flags & (IRQ_FLAG_A|IRQ_FLAG_I|IRQ_FLAG_F))
		return 0;
	return 1;
}

/** @brief Disable IRQs
 *
 * This inline function just set the exception bit mask bits
 */
 static inline void irq_disable(void) {
         asm volatile("msr daifset, 0b111" ::: "memory");
 }

/** @brief Enable IRQs
 *
 * This inline function just clear out the exception bit mask bits
 */
static inline void irq_enable(void) {
        asm volatile("msr daifclr, 0b111" ::: "memory");
}

/** @brief Disable IRQs (nested)
 *
 * Disable IRQs when unsure if IRQs were enabled at all.
 * This function together with irq_nested_enable can be used
 * in situations when interrupts shouldn't be activated if they
 * were not activated before calling this function.
 *
 * @return Whether IRQs had been enabled or not before disabling
 */
inline static uint8_t irq_nested_disable(void) {
	uint8_t was_enabled = is_irq_enabled();
	irq_disable();
	return was_enabled;
}

/** @brief Enable IRQs (nested)
 *
 * Can be used in conjunction with irq_nested_disable() to only enable
 * interrupts again if they were enabled before.
 *
 * @param was_enabled Whether IRQs should be enabled or not
 */
inline static void irq_nested_enable(uint8_t was_enabled) {
	if (was_enabled)
		irq_enable();
}

#ifdef __cplusplus
}
#endif

#endif
