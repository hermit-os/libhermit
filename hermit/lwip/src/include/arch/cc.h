/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 */
#ifndef __ARCH_CC_H__
#define __ARCH_CC_H__

/* Include some files for defining library routines */
#include <hermit/string.h>
//#include <sys/time.h>

/* Define platform endianness */
#ifndef BYTE_ORDER
#define BYTE_ORDER LITTLE_ENDIAN
#endif /* BYTE_ORDER */

/* Define generic types used in lwIP */
typedef uint8_t		u8_t;
typedef int8_t		s8_t;
typedef uint16_t	u16_t;
typedef int16_t		s16_t;
typedef uint32_t	u32_t;
typedef int32_t		s32_t;
typedef uint64_t	u64_t;
typedef int64_t		s64_t;

typedef size_t mem_ptr_t;

/* Define (sn)printf formatters for these lwIP types */
#define X8_F  "02x"
#define U16_F "u"
#define S16_F "d"
#define X16_F "x"
#define U32_F "u"
#define S32_F "d"
#define X32_F "x"
#define SZT_F "zu"

/* Compiler hints for packing structures */
//#define PACK_STRUCT_FIELD(x) x __attribute__((packed))
#define PACK_STRUCT_FIELD(x) x
#define PACK_STRUCT_STRUCT __attribute__((packed))
#define PACK_STRUCT_BEGIN
#define PACK_STRUCT_END

#define MEM_ALIGNMENT 4
#define ETH_PAD_SIZE  2

#define LWIP_CHKSUM_ALGORITHM	2

/* define errno to determine error code */
#define ERRNO
#define errno per_core(current_task)->lwip_err

/* prototypes for printf() and abort() */
#include <hermit/stdio.h>
#include <hermit/stdlib.h>

/* Plaform specific diagnostic output */
#define LWIP_PLATFORM_DIAG(x)	do {kprintf x;} while(0)

#define LWIP_PLATFORM_ASSERT(x) do {kprintf("Assertion \"%s\" failed at line %d in %s\n", \
                                     x, __LINE__, __FILE__); abort();} while(0)

#if NO_SYS
typedef uint32_t sys_prot_t;

static inline sys_prot_t sys_arch_protect(void)
{
	return irq_nested_disable();
}

static inline void sys_arch_unprotect(sys_prot_t pval)
{
	irq_nested_enable(pval);
}
#endif

#endif /* __ARCH_CC_H__ */
