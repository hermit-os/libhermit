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

#ifndef __ARCH_STRING_H__
#define __ARCH_STRING_H__

/**
 * @author Stefan Lankes
 * @file include/hermit/string.h
 * @brief Definition of basic string and memory opeations
 */

#include <hermit/stddef.h>
#include <asm/string.h>

#ifdef __cplusplus
extern "C" {
#endif

#if HAVE_ARCH_MEMCPY
void *aarch64_memcpy(void *dest, const void *src, size_t count);

#define memcpy(dest, src, count) aarch64_memcpy((dest), (src), (count))
#endif

#if HAVE_ARCH_MEMSET
void *aarch64_memset(void *dest, int val, size_t count);

#define memset(dest, val, count) aarch64_memset((dest), (val), (count))
#endif

#if HAVE_ARCH_MEMCMP
int aarch64_memcmp(const void *s1, const void *s2, size_t n);

#define memcmp(s1, s2, n) aarch64_memcmp((s1), (s2), (n))
#endif

#if HAVE_ARCH_STRLEN
size_t aarch64_strlen(const char *str);

#define strlen(str) aarch64_strlen((str))
#endif

#if HAVE_ARCH_STRNCPY
char *aarch64_strncpy(char *dest, const char *src, size_t n);

#define strncpy(dest, src, n) aarch64_strncpy((dest), (src), (n))
#endif

#if HAVE_ARCH_STRCPY
char *aarch64_strcpy(char *dest, const char *src);

#define strcpy(dest, src) aarch64_strcpy((dest), (src))
#endif

#if HAVE_ARCH_STRCMP
int arm64_strcmp(const char *s1, const char *s2);

#define strcmp(s1, s2) arm64_strcmp((s1), (s2))
#endif

#if HAVE_ARCH_STRNCMP
int arm64_strncmp(const char *s1, const char *s2, size_t n);

#define strncmp(s1, s2) arm64_strncmp((s1), (s2), (n))
#endif

#ifdef __cplusplus
}
#endif

#endif
