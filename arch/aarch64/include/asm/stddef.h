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
 * @file arch/arm64/include/asm/stddef.h
 * @brief Standard datatypes
 *
 * This file contains typedefs for standard datatypes for numerical and character values.
 */

#ifndef __ARCH_STDDEF_H__
#define __ARCH_STDDEF_H__

#ifdef __cplusplus
extern "C" {
#endif

#define per_core(var) (var)

#define set_per_core(var, value) (var = value)

#define KERNEL_SPACE (1ULL << 30)

// A popular type for addresses
typedef unsigned long long size_t;
/// Pointer differences
typedef long long ptrdiff_t;
#ifdef __KERNEL__
typedef long long ssize_t;
typedef long long off_t;
#endif

/// Unsigned 64 bit integer
typedef unsigned long uint64_t;
/// Signed 64 bit integer
typedef long int64_t;
/// Unsigned 32 bit integer
typedef unsigned int uint32_t;
/// Signed 32 bit integer
typedef int int32_t;
/// Unsigned 16 bit integer
typedef unsigned short uint16_t;
/// Signed 16 bit integer
typedef short int16_t;
/// Unsigned 8 bit integer (/char)
typedef unsigned char uint8_t;
/// Signed 8 bit integer (/char)
typedef char int8_t;
/// 16 bit wide char type
typedef unsigned short wchar_t;

#ifndef _WINT_T
#define _WINT_T
typedef wchar_t wint_t;
#endif

/// This defines what the stack looks like after the task context is saved
struct state {
	/// Interrupt number
	uint64_t int_no;
};

typedef struct {
	void	*ss_sp;		/* Stack base or pointer.  */
} stack_t;

static inline const int32_t is_uhyve(void) { return 0; }
static inline const int32_t is_single_kernel(void) { return 1; }
static inline const char* get_cmdline(void) { return 0; }
static inline int init_rcce(void) { return 0; }
static inline void print_status(void) {}

#ifdef __cplusplus
}
#endif

#endif
