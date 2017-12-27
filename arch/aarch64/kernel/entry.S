/*
 * Copyright (c) 2017, Stefan Lankes, RWTH Aachen University, Germany
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

.align 8
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
  /* Enable I caching */
  mrs x0, sctlr_el1
  orr x0, x0, #(1 << 12)
  msr sctlr_el1, x0

  /* Select sp_el0 as stack pointer */
  //msr  spsel, #0

  /* Set exception table */
  ldr x0, =vector_table_el1
  msr vbar_el1, x0

  /* Pointer to stack base  */
  ldr x1, =(boot_stack+KERNEL_STACK_SIZE-0xF)
  mov sp, x1

  /* Return current exception level */
  bl koutput_init
  mrs x0, CurrentEl
  sub x0, x0, #3
  //msr DAIFClr, #0b1111
  //mrs x0, DAIF
  //mrs x0, hcr_el2
  bl print_hex_return;

  /* Test floating point */
  //fmov d0, #5.0
  //fmov d1, #2.0
  //fdiv d0, d0, d1
  //fmov x0, d0
  //mrs x0, fpcr
  //mrs x0, fpsr
  //bl print_hex_return

  /* Test core ID */
  mrs x0, mpidr_el1
  bl print_hex_return

//   /* Enter user space */
//   ldr x0, =el0_return
//   msr elr_el1, x0
//   eret
// el0_return:
//
//   /* Return current exception level */
//   mrs x0, CurrentEl
//   sub x0, x0, #3
//   bl irq_handler

  bl hermit_main

  /* halt */
halt:
  wfe
  b halt

.global switch_context
.balign 16
switch_context:
  stp x29, x30, [sp, #-16]!
  stp x27, x28, [sp, #-16]!
  stp x25, x26, [sp, #-16]!
  stp x23, x24, [sp, #-16]!
  stp x21, x22, [sp, #-16]!
  stp x19, x20, [sp, #-16]!
  stp x17, x18, [sp, #-16]!
  stp x15, x16, [sp, #-16]!
  stp x13, x14, [sp, #-16]!
  stp x11, x12, [sp, #-16]!
  stp x9, x10, [sp, #-16]!
  stp x7, x8, [sp, #-16]!
  stp x5, x6, [sp, #-16]!
  stp x3, x4, [sp, #-16]!
  stp x1, x2, [sp, #-16]!
  mrs x1, tpidr_el0
  stp x1, x0, [sp, #-16]!
  mrs x1, tpidrro_el0
  mrs x2, nzcv
  stp x1, x2, [sp, #-16]!

  mov x1, sp
  str x1, [x0]				/* store old sp */
  bl get_current_stack		/* get new sp   */
  mov sp, x0

  /* call cleanup code */
  bl finish_task_switch

  ldp x0, x1, [sp], #16
  msr tpidrro_el0, x0
  msr nzcv, x1
  ldp x1, x0, [sp], #16
  msr tpidr_el0, x1
  ldp x1, x2, [sp], #16
  ldp x3, x4, [sp], #16
  ldp x5, x6, [sp], #16
  ldp x7, x8, [sp], #16
  ldp x9, x10, [sp], #16
  ldp x11, x12, [sp], #16
  ldp x13, x14, [sp], #16
  ldp x15, x16, [sp], #16
  ldp x17, x18, [sp], #16
  ldp x19, x20, [sp], #16
  ldp x21, x22, [sp], #16
  ldp x23, x24, [sp], #16
  ldp x25, x26, [sp], #16
  ldp x27, x28, [sp], #16
  ldp x29, x30, [sp], #16

  ret


.global trigger_interrupt
trigger_interrupt:
  svc #128
  ret


asm_irq_handler:
  /* Save caller-saved registers according to Procedure Call Standard */
  stp x17, x18, [sp, #-16]!
  stp x15, x16, [sp, #-16]!
  stp x13, x14, [sp, #-16]!
  stp x11, x12, [sp, #-16]!
  stp x9, x10, [sp, #-16]!
  stp x7, x8, [sp, #-16]!
  stp x5, x6, [sp, #-16]!
  stp x3, x4, [sp, #-16]!
  stp x1, x2, [sp, #-16]!
  stp x0, x1, [sp, #-16]!

  bl irq_handler

  /* Restore caller-saved registers */
  ldp x0, x1, [sp], #16
  ldp x1, x2, [sp], #16
  ldp x3, x4, [sp], #16
  ldp x5, x6, [sp], #16
  ldp x7, x8, [sp], #16
  ldp x9, x10, [sp], #16
  ldp x11, x12, [sp], #16
  ldp x13, x14, [sp], #16
  ldp x15, x16, [sp], #16
  ldp x17, x18, [sp], #16

  eret


// Exception vector table
// No nested implementation yet
.balign 0x800
vector_table_el1:
/* Current exception level, sp_el0 */
curr_el_sp0_sync:
  bl irq_handler

.balign 0x80
curr_el_sp0_irq:
  bl irq_handler

.balign 0x80
curr_el_sp0_fiq:
  bl irq_handler

.balign 0x80
curr_el_sp0_serror:
  bl irq_handler

/* Current exception level, sp_elx */
.balign 0x80
curr_el_spx_sync:
  bl irq_handler

.balign 0x80
curr_el_spx_irq:
  bl irq_handler

.balign 0x80
curr_el_spx_fiq:
  bl irq_handler

.balign 0x80
curr_el_spx_serror:
  bl irq_handler

/* Lower exception level, coming from AArch64 */
.balign 0x80
lower_el_aarch64_sync:
  bl irq_handler

.balign 0x80
lower_el_aarch64_irq:
  bl irq_handler

.balign 0x80
lower_el_aarch64_fiq:
  bl irq_handler

.balign 0x80
lower_el_aarch64_serror:
  bl irq_handler

/* Lower exception level, coming from AArch32 */
.balign 0x80
lower_el_aarch32_sync:
  bl irq_handler

.balign 0x80
lower_el_aarch32_irq:
  bl irq_handler

.balign 0x80
lower_el_aarch32_fiq:
  bl irq_handler

.balign 0x80
lower_el_aarch32_serror:
  bl irq_handler


.section .data
.global boot_stack
boot_stack: .skip (MAX_CORES*KERNEL_STACK_SIZE)
.global boot_ist
boot_ist: .skip KERNEL_STACK_SIZE
.global msg
msg: .ascii "\n"
