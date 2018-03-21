/*
 * Copyright (c) 2017, Stefan Lankes, RWTH Aachen University
 *               2014, Steffen Vogel, RWTH Aachen University
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
 * @file arch/arm64/include/asm/page.h
 * @brief Paging related functions
 *
 * This file contains the several functions to manage the page tables
 */

#include <hermit/stddef.h>
#include <hermit/stdlib.h>
#include <asm/processor.h>

#ifndef __PAGE_H__
#define __PAGE_H__

/// Page offset bits
#define PAGE_BITS		12
#define PAGE_2M_BITS		21
/// The size of a single page in bytes
#define PAGE_SIZE		( 1L << PAGE_BITS)
#define PAGE_MASK		((~0L) << PAGE_BITS)
#define PAGE_2M_MASK		((~0L) << PAGE_2M_BITS)

/// Total operand width in bits
#define BITS			64
/// Physical address width (maximum value)
#define PHYS_BITS		48
/// Linear/virtual address width
#define VIRT_BITS		48
/// Page map bits
#define PAGE_MAP_BITS		9
/// Number of page map indirections
#define PAGE_LEVELS		4

/// The number of entries in a page map table
#define PAGE_MAP_ENTRIES	       (1L << PAGE_MAP_BITS)

/// Align to next page
#define PAGE_CEIL(addr)        (((addr) + PAGE_SIZE - 1) & PAGE_MASK)
/// Align to page
#define PAGE_FLOOR(addr)         ( (addr)                  & PAGE_MASK)

/// Align to next 2M boundary
#define PAGE_2M_CEIL(addr)	(((addr) + (1L << 21) - 1) & ((~0L) << 21))
/// Align to 2M boundary
#define PAGE_2M_FLOOR(addr)	( (addr)                   & ((~0L) << 21))
// Align the kernel end
#define KERNEL_END_CEIL(addr)	(((addr) + (16L << 10)) & ~0xFFFF)

/// Page is present
#define PG_PRESENT		(1UL << 0)
/// Page is read- and writable
#define PG_RW			(1UL << 1)
/// Page is addressable from userspace
#define PG_USER			(1UL << 2)
/// Page write through is activated
#define PG_PWT			(1UL << 3)
/// Page cache is disabled
#define PG_PCD			(1UL << 4)
/// Page was recently accessed (set by CPU)
#define PG_ACCESSED		(1UL << 5)
/// Page is dirty due to recent write-access (set by CPU)
#define PG_DIRTY		(1UL << 6)
/// Huge page: 4MB (or 2MB, 1GB)
#define PG_PSE			(1UL << 7)
/// Page attribute table
#define PG_PAT			PG_PSE

#define PG_DEVICE		(1UL << 8)
#define PG_NX			0
#define PG_GLOBAL		0

/// This table is a self-reference and should skipped by page_map_copy()
#define PG_SELF			(1UL << 63)

#define PT_PT			0x713UL
#define PT_MEM			0x713UL
#define PT_MEM_CD		0x70FUL
#define PT_DEVICE		0x707UL

#define PT_SELF			(1UL << 55)
#define PT_AF			(1UL << 10)	/* Access Flag */
#define PT_CONTIG		(1UL << 52)	/* Contiguous bit */
#define PT_S			(3UL << 8)
#define PT_PXN			(1UL << 53)
#define PT_UXN			(1UL << 54)

/** @brief Converts a virtual address to a physical
 *
 * A non mapped virtual address causes a pagefault!
 *
 * @param addr Virtual address to convert
 * @return physical address
 */
size_t virt_to_phys(size_t vir);

/** @brief Initialize paging subsystem
 *
 * This function uses the existing bootstrap page tables (boot_{pgd, pgt})
 * to map required regions (video memory, kernel, etc..).
 * Before calling page_init(), the bootstrap tables contain a simple identity
 * paging. Which is replaced by more specific mappings.
 */
int page_init(void);

/** @brief Map a continuous region of pages
 *
 * @param viraddr Desired virtual address
 * @param phyaddr Physical address to map from
 * @param npages The region's size in number of pages
 * @param bits Further page flags
 * @param do_ipi if set, inform via IPI all other cores
 * @return
 */
int __page_map(size_t viraddr, size_t phyaddr, size_t npages, size_t bits);

/** @brief Map a continuous region of pages
 *
 * @param viraddr Desired virtual address
 * @param phyaddr Physical address to map from
 * @param npages The region's size in number of pages
 * @param bits Further page flags
 * @return
 */
static inline int page_map(size_t viraddr, size_t phyaddr, size_t npages, size_t bits)
{
	return __page_map(viraddr, phyaddr, npages, bits);
}

/** @brief Unmap a continuous region of pages
 *
 * @param viraddr The virtual start address
 * @param npages The range's size in pages
 * @return
 */
int page_unmap(size_t viraddr, size_t npages);

/** @brief Change the page permission in the page tables of the current task
 *
 * Applies given flags noted in the 'flags' parameter to
 * the range denoted by virtual start and end addresses.
 *
 * @param start Range's virtual start address
 * @param end Range's virtual end address
 * @param flags flags to apply
 *
 * @return
 * - 0 on success
 * - -EINVAL (-22) on failure.
 */
int page_set_flags(size_t viraddr, uint32_t npages, int flags);

/** @brief Handler to map on demand pages for the heap
 *
 * @return
 * - 0 on success
 * - -EINVAL (-22) on failure.
 */
int page_fault_handler(size_t viraddr);

/** @brief Flush Translation Lookaside Buffer
 */
static inline void tlb_flush(void)
{
	asm volatile(
		"dsb ishst\n\t"         // ensure write has completed
		"tlbi vmalle1is\n\t"    // invalidate all TLB entries
		"dsb ish\n\t"           // ensure completion of TLB invalidation
		"isb"                   // synchronize context
		:
		:
		: "memory"
	);
}

/** @brief Flush a specific page entry in TLB
 * @param addr The (virtual) address of the page to flush
 */
static inline void tlb_flush_one_page(size_t addr)
{
	addr = addr >> PAGE_BITS;

	asm volatile(
		"dsb ishst\n\t"         // ensure write has completed
		"tlbi vale1is, %0 \n\t"
		"dsb ish\n\t"           // ensure completion of TLB invalidation
		"isb"                   // synchronize context
                :
		: "r"(addr)
		: "memory"
	);
}

/** @brief Flush a range of page entries in TLB
 * @param addr The (virtual) start address
 * @param end The (virtual) end address
 */
static inline void tlb_flush_range(size_t start, size_t end)
{
	if ((end - start) > (1024ULL << PAGE_BITS)) {
		tlb_flush();
		return;
	}

	start = start >> PAGE_BITS;
	end = end >> PAGE_BITS;

	asm volatile ("dsb ishst" ::: "memory");
	for (size_t addr = start; addr < end; addr++)
		asm("tlbi vaae1is, %0" :: "r"(addr));
	asm volatile ("dsb ish" ::: "memory");
	asm volatile ("isb" ::: "memory");
}

#endif
