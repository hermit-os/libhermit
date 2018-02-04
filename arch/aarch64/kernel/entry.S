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
 * This is the kernel's entry point, which is derived from Xen's Mini-OS.
 */

#include <hermit/config.h>

#define MAIR(attr, mt)  ((attr) << ((mt) * 8))

#define PAGE_SHIFT	12
#define PAGE_SIZE	(1 << PAGE_SHIFT)
#define PAGE_MASK	(~(PAGE_SIZE-1))

/* Level 1 table, 1GiB per entry */
#define L1_SHIFT	30
#define L1_SIZE		(1 << L1_SHIFT)
#define L1_OFFSET	(L1_SIZE - 1)
#define L1_INVAL	L0_INVAL
#define L1_BLOCK	L0_BLOCK
#define L1_TABLE	L0_TABLE
#define L1_MASK		(~(L1_SIZE-1))

/* Level 2 table, 2MiB per entry */
#define L2_SHIFT	21
#define L2_SIZE		(1 << L2_SHIFT)
#define L2_OFFSET	(L2_SIZE - 1)
#define L2_INVAL	L0_INVAL
#define L2_BLOCK	L0_BLOCK
#define L2_TABLE	L0_TABLE
#define L2_MASK		(~(L2_SIZE-1))

/* Level 3 table, 4KiB per entry */
#define L3_SHIFT            12
#define L3_SIZE             (1 << L3_SHIFT)
#define L3_OFFSET           (L3_SIZE - 1)
#define L3_INVAL            0x0
        /* 0x1 is reserved */
        /* 0x2 also marks an invalid address */
#define L3_PAGE             0x3
#define L3_MASK             (~(L3_SIZE-1))
#define Ln_ENTRIES	(1 << 9)
#define Ln_ADDR_MASK	(Ln_ENTRIES - 1)

#define ATTR_MASK_L	0xfff

#define PT_PT		0x3
#define PT_MEM		0x711
#define TCR_FLAGS	(TCR_IRGN_WBWA | TCR_ORGN_WBWA | TCR_SHARED)

/*
 * Memory types available.
 */
#define MT_DEVICE_nGnRnE    0
#define MT_DEVICE_nGnRE     1
#define MT_DEVICE_GRE       2
#define MT_NORMAL_NC        3
#define MT_NORMAL           4

/*
 * TCR flags
 */
#define TCR_TxSZ(x)     ((((64) - (x)) << 16) | (((64) - (x)) << 0))
#define TCR_IRGN_WBWA   (((1) << 8) | ((1) << 24))
#define TCR_ORGN_WBWA   (((1) << 10) | ((1) << 26))
#define TCR_SHARED      (((3) << 12) | ((3) << 28))
#define TCR_TBI0        ((1) << 37)
#define TCR_TBI1        ((1) << 38)
#define TCR_ASID16      ((1) << 36)
#define TCR_IPS_40BIT   ((2) << 32)
#define TCR_TG1_4K      ((2) << 30)

/* Number of virtual address bits for 4KB page */
#define VA_BITS         39

#define ALIGN   .align 4

#define END(name) \
	.size name, .-name

#define ENDPROC(name) \
	.type name, @function; \
	END(name)

#define ENTRY(name) \
	.globl name; \
	ALIGN; \
	name:

.section .mboot

.global _start
_start:
b start64

.align 8
.global boot_processor
boot_processor: .dword 0
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
  /* disable interrupts */
  msr daifset, #0b111

  /* store x5=dtb */
  /*adrp    x1, dtb
  str     x5, [x1, #:lo12:dtb]*/

  /*
   * Disable the MMU. We may have entered the kernel with it on and
   * will need to update the tables later. If this has been set up
   * with anything other than a VA == PA map then this will fail,
   * but in this case the code to find where we are running from
   * would have also failed.
   */
  dsb sy
  mrs x2, sctlr_el1
  bic x2, x2, #0x1
  msr sctlr_el1, x2
  isb

  /* Calculate where we are */
  bl _calc_offset

  /* Setup CPU for turnning the MMU on. */
  bl _setup_cpu

  /* Setup the initial page table. */
  bl _setup_initial_pgtable

  /*
   * Setup the identity mapping
   */
  bl _setup_idmap_pgtable

  /* Load TTBRx */
  msr     ttbr1_el1, x4
  msr     ttbr0_el1, x5
  isb

  /* Set exception table */
  ldr x0, =vector_table
  msr vbar_el1, x0

  /* Turning on MMU */
  dsb sy

  /*
   * Prepare system control register (SCTRL)
   *
   *
   *   UCI     [26] Enables EL0 access in AArch64 for DC CVAU, DC CIVAC,
                    DC CVAC and IC IVAU instructions
   *   EE      [25] Explicit data accesses at EL1 and Stage 1 translation
                    table walks at EL1 & EL0 are little-endian
   *   EOE     [24] Explicit data accesses at EL0 are little-endian
   *   WXN     [19] Regions with write permission are not forced to XN
   *   nTWE    [18] WFE instructions are executed as normal
   *   nTWI    [16] WFI instructions are executed as normal
   *   UCT     [15] Enables EL0 access in AArch64 to the CTR_EL0 register
   *   DZE     [14] Execution of the DC ZVA instruction is allowed at EL0
   *   I       [12] Instruction caches enabled at EL0 and EL1
   *   UMA     [9]  Disable access to the interrupt masks from EL0
   *   SED     [8]  The SETEND instruction is available
   *   ITD     [7]  The IT instruction functionality is available
   *   THEE    [6]  ThumbEE is disabled
   *   CP15BEN [5]  CP15 barrier operations disabled
   *   SA0     [4]  Stack Alignment check for EL0 enabled
   *   SA      [3]  Stack Alignment check enabled
   *   C       [2]  Data and unified enabled
   *   A       [1]  Alignment fault checking disabled
   *   M       [0]  MMU disabled
   */
  ldr x0, =0x34d5d905
  msr sctlr_el1, x0

  ldr     x0, =mmu_on
  br      x0

mmu_on:
  /* Pointer to stack base  */
  ldr x1, =(boot_stack+KERNEL_STACK_SIZE-0xF)
  mov sp, x1

  /* Test core ID */
  mrs x0, mpidr_el1

  bl hermit_main

  /* halt */
halt:
  wfe
  b halt

.section .text

_setup_cpu:
    ic      iallu
    tlbi    vmalle1is
    dsb     ish

    /*
     * Setup memory attribute type tables
     *
     * Memory regioin attributes for LPAE:
     *
     *   n = AttrIndx[2:0]
     *                      n       MAIR
     *   DEVICE_nGnRnE      000     00000000 (0x00)
     *   DEVICE_nGnRE       001     00000100 (0x04)
     *   DEVICE_GRE         010     00001100 (0x0c)
     *   NORMAL_NC          011     01000100 (0x44)
     *   NORMAL             100     11111111 (0xff)
     */
    ldr     x0, =(MAIR(0x00, MT_DEVICE_nGnRnE) | \
                 MAIR(0x04, MT_DEVICE_nGnRE) | \
                 MAIR(0x0c, MT_DEVICE_GRE) | \
                 MAIR(0x44, MT_NORMAL_NC) | \
                 MAIR(0xff, MT_NORMAL))
    msr     mair_el1, x0

    /*
     * Setup translation control register (TCR)
     */
    ldr     x0, =(TCR_TxSZ(VA_BITS) | TCR_ASID16 | TCR_TG1_4K \
                | TCR_FLAGS )
    mrs     x1, ID_AA64MMFR0_EL1
    bfi     x0, x1, #32, #3
    msr     tcr_el1, x0

    /*
     * Enable FP/ASIMD
     */
    mov     x0, #3 << 20
    msr     cpacr_el1, x0

    /*
     * Reset mdscr_el1
     */
    msr     mdscr_el1, xzr

    ret

_setup_initial_pgtable:
    ldr     x4, =boot_l1_pgtable
    ldr     x5, =boot_l2_pgtable

    sub     x4, x4, x22             // x4 := paddr (boot_l1_pgtable)
    sub     x5, x5, x22             // x5 := paddr (boot_l2_pgtable)


    /* Clear level-1 boot page table */
    mov     x0, x4
    add     x1, x0, #PAGE_SIZE
1:  stp     xzr, xzr, [x0], #16
    stp     xzr, xzr, [x0], #16
    stp     xzr, xzr, [x0], #16
    stp     xzr, xzr, [x0], #16
    cmp     x0, x1
    b.lo    1b

    /* Clear level-2 boot page table */
    mov     x0, x5
    add     x1, x0, #PAGE_SIZE
1:  stp     xzr, xzr, [x0], #16
    stp     xzr, xzr, [x0], #16
    stp     xzr, xzr, [x0], #16
    stp     xzr, xzr, [x0], #16
    cmp     x0, x1
    b.lo    1b

	/* Clear fixmap page table */
	ldr     x0, =fixmap_pgtable
	add     x1, x0, #PAGE_SIZE
2:  stp     xzr, xzr, [x0], #16
	stp     xzr, xzr, [x0], #16
	stp     xzr, xzr, [x0], #16
	stp     xzr, xzr, [x0], #16
	cmp     x0, x1
	b.lo    2b

    /* Find the size of the kernel */
    ldr     x0, =kernel_start
    ldr     x1, =kernel_end
    sub     x2, x1, x0
    /* Get the number of l2 pages to allocate, rounded down */
    lsr     x2, x2, #L2_SHIFT
    /* Add 4 MiB for any rounding above and the module data */
    add     x2, x2, #2                  // x2 := total number of entries

    /* Find the table index */
    lsr     x3, x0, #L2_SHIFT           // L2_SHIFT = 21
    and     x3, x3, #Ln_ADDR_MASK       // x3 := index of l2 table

    /* Build the L2 block entries */
    sub     x6, x0, x22                 // x6 := paddr(_text)
    lsr     x6, x6, #L2_SHIFT           // L2_SHIFT = 21
    mov     x7, #PT_MEM
1:  orr     x7, x7, x6, lsl #L2_SHIFT   // x7 := l2 pgtbl entry content

    /* Store the entry */
    str     x7, [x5, x3, lsl #3]

    /* Clear the address bits */
    and     x7, x7, #ATTR_MASK_L

    sub     x2, x2, #1
    add     x3, x3, #1
    add     x6, x6, #1
    cbnz    x2, 1b

    /* Link the l1 -> l2 table */
    /* Find the table index */
    lsr     x3, x0, #L1_SHIFT           // L1_SHIFT = 30
    and     x3, x3, #Ln_ADDR_MASK       // x3 := index of l1 table


    /* Build the L1 page table entry */
    ldr     x7, =PT_PT
    lsr     x9, x5, #12
    orr     x7, x7, x9, lsl #12

    /* Store the entry */
    str     x7, [x4, x3, lsl #3]

	/* Find the table index of the uart device */
	mov     x0, 0x09000000  /* default address of QEMU */
	mov		x2, 1	/* only one entry required */
	ldr     x5, =fixmap_pgtable

	/* Build the L2 block entries */
    sub     x6, x0, x22                 // x6 := paddr(_text)
    lsr     x6, x6, #L2_SHIFT           // L2_SHIFT = 21
    mov     x7, #PT_MEM
1:  orr     x7, x7, x6, lsl #L2_SHIFT   // x7 := l2 pgtbl entry content

    /* Store the entry */
    str     x7, [x5, x3, lsl #3]

    /* Clear the address bits */
    and     x7, x7, #ATTR_MASK_L

    sub     x2, x2, #1
    add     x3, x3, #1
    add     x6, x6, #1
    cbnz    x2, 1b

    /* Link the l1 -> l2 table */
    /* Find the table index */
    lsr     x3, x0, #L1_SHIFT           // L1_SHIFT = 30
    and     x3, x3, #Ln_ADDR_MASK       // x3 := index of l1 table


    /* Build the L1 page table entry */
    ldr     x7, =PT_PT
    lsr     x9, x5, #12
    orr     x7, x7, x9, lsl #12

    /* Store the entry */
    str     x7, [x4, x3, lsl #3]

    ret

_calc_offset:
    ldr     x22, =_start             // x0 := vaddr(_start)
    adr     x21, _start              // x21 := paddr(_start)
    sub     x22, x22, x21            // x22 := phys-offset (vaddr - paddr)
    ret

_setup_idmap_pgtable:
    ldr     x5, =idmap_pgtable
    sub     x5, x5, x22             // x5 := paddr(idmap_pgtable)

    /* Clear identity mapping page table */
    mov     x0, x5
    add     x1, x0, #PAGE_SIZE
1:  stp     xzr, xzr, [x0], #16
    stp     xzr, xzr, [x0], #16
    stp     xzr, xzr, [x0], #16
    stp     xzr, xzr, [x0], #16
    cmp     x0, x1
    b.lo    1b

    /* Create the VA = PA map */
    ldr     x6, =kernel_start           // x0 := vaddr(kernel_start)
    sub     x6, x6, x22                 // x0 := paddr(kernel_start)

    /* Find the table index */
    lsr     x0, x6, #L1_SHIFT
    and     x0, x0, #Ln_ADDR_MASK       // x0 := index of l1 table

    /* Build the L1 block entry */
    ldr     x1, =PT_MEM
    lsr     x2, x6, #L1_SHIFT
    orr     x1, x1, x2, lsl #L1_SHIFT

    /* Store the entry */
    str     x1, [x5, x0, lsl #3]

	/* Create the VA = PA map */
    mov     x6, 0x09000000              // x0 := vaddr(0x09000000)
    sub     x6, x6, x22                 // x0 := paddr(0x09000000)

    /* Find the table index */
    lsr     x0, x6, #L1_SHIFT
    and     x0, x0, #Ln_ADDR_MASK       // x0 := index of l1 table

    /* Build the L1 block entry */
    ldr     x1, =PT_MEM
    lsr     x2, x6, #L1_SHIFT
    orr     x1, x1, x2, lsl #L1_SHIFT

    /* Store the entry */
    str     x1, [x5, x0, lsl #3]

    ret

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

/*
 * There are no PUSH/POP instruction in ARMv8.
 * Use STR and LDR for stack accesses.
 */
.macro push, xreg
str     \xreg, [sp, #-8]!
.endm

.macro pop, xreg
ldr     \xreg, [sp], #8
.endm

.macro trap_entry, el
      sub     sp, sp, #32             // room for LR, SP, SPSR, ELR
      push    x29
      push    x28
      push    x27
      push    x26
      push    x25
      push    x24
      push    x23
      push    x22
      push    x21
      push    x20
      push    x19
      push    x18
      push    x17
      push    x16
      push    x15
      push    x14
      push    x13
      push    x12
      push    x11
      push    x10
      push    x9
      push    x8
      push    x7
      push    x6
      push    x5
      push    x4
      push    x3
      push    x2
      push    x1
      push    x0
.if     \el == 0
      mrs     x21, sp_el0
.else
      add     x21, sp, #272
.endif
      mrs     x22, elr_el1
      mrs     x23, spsr_el1
      stp     x30, x21, [sp, #240]
      stp     x22, x23, [sp, #256]
.endm

.macro trap_exit, el
      ldp     x21, x22, [sp, #256]    // load ELR, SPSR
.if     \el == 0
      ldr     x23, [sp, #248]         // load return stack pointer
.endif
      pop     x0
      pop     x1
      pop     x2
      pop     x3
      pop     x4
      pop     x5
      pop     x6
      pop     x7
      pop     x8
      pop     x9
      msr     elr_el1, x21            // set up the return data
      msr     spsr_el1, x22
.if     \el == 0
      msr     sp_el0, x23
.endif
      pop     x10
      pop     x11
      pop     x12
      pop     x13
      pop     x14
      pop     x15
      pop     x16
      pop     x17
      pop     x18
      pop     x19
      pop     x20
      pop     x21
      pop     x22
      pop     x23
      pop     x24
      pop     x25
      pop     x26
      pop     x27
      pop     x28
      pop     x29
	  ldr     x30, [sp], #32
.endm


/*
 * SYNC & IRQ exception handler.
 */
.align 6
el1_sync:
      trap_entry 1
      mov     x0, sp
      bl      do_sync
      trap_exit 1
      eret
ENDPROC(el1_sync)

.align 6
el1_irq:
      trap_entry 1
      mov     x0, sp
      bl      do_irq
      trap_exit 1
      eret
ENDPROC(el1_irq)

.align 6
el0_sync:
      trap_entry 0
      mov     x0, sp
      bl      do_sync
      trap_exit 0
      eret
ENDPROC(el0_sync)

.align 6
el0_irq:
      trap_entry 0
      mov     x0, sp
      bl      do_irq
      trap_exit 0
      eret
ENDPROC(el0_irq)

/*
 * Bad Abort numbers
 */
#define BAD_SYNC    0
#define BAD_IRQ     1
#define BAD_FIQ     2
#define BAD_ERROR   3

/*
 * Exception vector entry
 */
.macro ventry label
.align  7
b       \label
.endm

.macro invalid, reason
mov     x0, sp
mov     x1, #\reason
b       do_bad_mode
.endm

el0_sync_invalid:
   invalid BAD_SYNC
ENDPROC(el0_sync_invalid)

el0_irq_invalid:
   invalid BAD_IRQ
ENDPROC(el0_irq_invalid)

el0_fiq_invalid:
   invalid BAD_FIQ
ENDPROC(el0_fiq_invalid)

el0_error_invalid:
   invalid BAD_ERROR
ENDPROC(el0_error_invalid)

el1_sync_invalid:
   invalid BAD_SYNC
ENDPROC(el1_sync_invalid)

el1_irq_invalid:
   invalid BAD_IRQ
ENDPROC(el1_irq_invalid)

el1_fiq_invalid:
   invalid BAD_FIQ
ENDPROC(el1_fiq_invalid)

el1_error_invalid:
   invalid BAD_ERROR
ENDPROC(el1_error_invalid)

.align  11
ENTRY(vector_table)
/* Current EL with SP0 */
ventry el1_sync_invalid         // Synchronous EL1t
ventry el1_irq_invalid          // IRQ EL1t
ventry el1_fiq_invalid          // FIQ EL1t
ventry el1_error_invalid        // Error EL1t

/* Current EL with SPx */
ventry el1_sync                 // Synchronous EL1h
ventry el1_irq                  // IRQ EL1h
ventry el1_fiq_invalid          // FIQ EL1h
ventry el1_error_invalid        // Error EL1h

/* Lower EL using AArch64 */
ventry el0_sync                 // Synchronous 64-bit EL0
ventry el0_irq                  // IRQ 64-bit EL0
ventry el0_fiq_invalid          // FIQ 64-bit EL0
ventry el0_error_invalid        // Error 64-bit EL0

/* Lower EL using AArch32 */
ventry el0_sync_invalid         // Synchronous 32-bit EL0
ventry el0_irq_invalid          // IRQ 32-bit EL0
ventry el0_fiq_invalid          // FIQ 32-bit EL0
ventry el0_error_invalid        // Error 32-bit EL0
END(vector_table)

.section .data
.global boot_stack
.balign 0x10
boot_stack: .skip KERNEL_STACK_SIZE
.global boot_ist
boot_ist: .skip KERNEL_STACK_SIZE


.global boot_l1_pgtable, boot_l2_pgtable, fixmap_pgtable
.align 12 // 4KiB aligned
boot_l1_pgtable:
  .space PAGE_SIZE
boot_l2_pgtable:
  .space PAGE_SIZE
fixmap_pgtable:
  .space PAGE_SIZE
idmap_pgtable:
  .space PAGE_SIZE
