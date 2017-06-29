/*
 * Copyright (c) 017, Stefan Lankes, RWTH Aachen University, Germany
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

/*
 * This is the kernel's entry point. We could either call main here,
 * or we can use this to setup the stack or other nice stuff.
 */

#include <hermit/config.h>

.section .mboot

.global _start
_start:
b start64

.global boot_processor
boot_processor: .dword -1
.global cpu_online
cpu_online: .dword 0
.global possible_cpus
possible_cpus: .dword 0
.global hbmem_base
hbmem_base: .quad 0
.global hbmem_size
hbmem_size: .quad 0
.global isle
isle: .dword -1
.global image_size
image_size: .quad 0
.global possible_isles
possible_isles: .dword 1

start64:
/* Pointer to stack base  */
ldr x1, =stack_top
mov sp, x1
bl hermit_main
b .

.section .data
.global boot_stack
boot_stack: .skip (MAX_CORES*KERNEL_STACK_SIZE)
.global boot_ist
boot_ist: .skip KERNEL_STACK_SIZE
