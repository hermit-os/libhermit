/*
 * Copyright (c) 2010-2018, Stefan Lankes, RWTH Aachen University
 *               2014,      Steffen Vogel, RWTH Aachen University
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
 * This is a 32/64 bit portable paging implementation for the x86 architecture
 * using self-referenced page tables	i.
 * See http://www.noteblok.net/2014/06/14/bachelor/ for a detailed description.
 *
 * @author Steffen Vogel <steffen.vogel@rwth-aachen.de>
 */

#include <hermit/stdio.h>
#include <hermit/memory.h>
#include <hermit/errno.h>
#include <hermit/string.h>
#include <hermit/spinlock.h>
#include <hermit/tasks.h>
#include <hermit/logging.h>

#include <asm/irq.h>
#include <asm/page.h>
#include <asm/uhyve.h>

typedef struct {
	uint64_t rip;
	uint64_t addr;
	int success;
} __attribute__ ((packed)) uhyve_pfault_t;

/* Note that linker symbols are not variables, they have no memory
 * allocated for maintaining a value, rather their address is their value. */
extern const void kernel_start;

extern size_t l0_pgtable;

/** Single-address space operating system => one lock for all tasks */
static spinlock_irqsave_t page_lock = SPINLOCK_IRQSAVE_INIT;

/** A self-reference enables direct access to all page tables */
static size_t* const self[PAGE_LEVELS] = {
	(size_t *) 0x0000FF8000000000ULL,
	(size_t *) 0x0000FFFFC0000000ULL,
	(size_t *) 0x0000FFFFFFE00000ULL,
	(size_t *) 0x0000FFFFFFFFF000ULL
};

static uint8_t expect_zeroed_pages = 0;

size_t virt_to_phys(size_t addr)
{
	size_t vpn   = addr >> PAGE_BITS;	// virtual page number
	size_t entry = self[0][vpn];		// page table entry
	size_t off   = addr  & ~PAGE_MASK;	// offset within page
	size_t phy   = entry &  PAGE_MASK;	// physical page frame number

	return (phy | off) & ((1ULL << VIRT_BITS) - 1);
}

/*
 * get memory page size
 */
int getpagesize(void)
{
	return PAGE_SIZE;
}

//TODO: code is missing
int page_set_flags(size_t viraddr, uint32_t npages, int flags)
{
	return -EINVAL;
}

int __page_map(size_t viraddr, size_t phyaddr, size_t npages, size_t bits)
{
	int lvl, ret = -ENOMEM;
	ssize_t vpn = viraddr >> PAGE_BITS;
	ssize_t first[PAGE_LEVELS], last[PAGE_LEVELS];
	size_t page_counter = 0;
	size_t cflags = 0;

	//kprintf("Map %d pages at 0x%zx\n", npages, viraddr);

	/* Calculate index boundaries for page map traversal */
	for (lvl=0; lvl<PAGE_LEVELS; lvl++) {
		first[lvl] = (vpn         ) >> (lvl * PAGE_MAP_BITS);
		last[lvl]  = (vpn+npages-1) >> (lvl * PAGE_MAP_BITS);
	}

	spinlock_irqsave_lock(&page_lock);

	/* Start iterating through the entries
	 * beginning at the root table */
	for (lvl=PAGE_LEVELS-1; lvl>=0; lvl--) {
		for (vpn=first[lvl]; vpn<=last[lvl]; vpn++) {
			if (lvl) {
				if (!self[lvl][vpn]) {
					/* There's no table available which covers the region.
					 * Therefore we need to create a new empty table. */
					size_t phyaddr = get_pages(1);
					if (BUILTIN_EXPECT(!phyaddr, 0))
						goto out;

					/* Reference the new table within its parent */
					self[lvl][vpn] = phyaddr | PT_PT;

					/* Fill new table with zeros */
					//LOG_INFO("Clear new page table at %p for 0x%zx, %d\n", &self[lvl-1][vpn<<PAGE_MAP_BITS], viraddr, lvl-1);
					tlb_flush_range((size_t) (&self[lvl-1][vpn<<PAGE_MAP_BITS]),
						((size_t)(&self[lvl-1][vpn<<PAGE_MAP_BITS]))+PAGE_SIZE);
					memset(&self[lvl-1][vpn<<PAGE_MAP_BITS], 0, PAGE_SIZE);
				}
			} else { /* page table */
				/*if (self[lvl][vpn]) {
					kprintf("Remap address 0x%zx at core %d\n", viraddr, CORE_ID);
				}*/

#if 0
				if ((viraddr & 0xFFFFULL) == 0) {
					if ((ssize_t)npages-(ssize_t)page_counter >= 16)
						cflags = PT_CONTIG;
					else if ((ssize_t)npages-(ssize_t)page_counter < 16)
						cflags = 0;
				}
#endif

				if (bits & PG_DEVICE)
					self[lvl][vpn] = phyaddr | PT_DEVICE | cflags;
				else
					self[lvl][vpn] = phyaddr | PT_MEM | cflags;

				//if (bits & PG_DEVICE)
				//	kprintf("viradd 0x%zx, reference 0x%zx\n", viraddr, self[lvl][vpn]);

				//if (cflags && !(viraddr & 0xFFFFULL))
				//	kprintf("usre PT_CONTIG for 0x%zx, reference 0x%zx\n", viraddr, self[lvl][vpn]);

				page_counter++;
				phyaddr += PAGE_SIZE;
				viraddr += PAGE_SIZE;
			}
		}
	}

	tlb_flush_range(viraddr, viraddr+npages*PAGE_SIZE);

	ret = 0;
out:
	spinlock_irqsave_unlock(&page_lock);

	return ret;
}

int page_unmap(size_t viraddr, size_t npages)
{
	if (BUILTIN_EXPECT(!npages, 0))
		return 0;

	//kprintf("Unmap %d pages at 0x%zx\n", npages, viraddr);

	spinlock_irqsave_lock(&page_lock);

	/* Start iterating through the entries.
	 * Only the PGT entries are removed. Tables remain allocated. */
	size_t vpn, start = viraddr>>PAGE_BITS;
	for (vpn=start; vpn<start+npages; vpn++) {
		self[0][vpn] = 0;
	}

	tlb_flush_range(viraddr, viraddr+npages*PAGE_SIZE);

	spinlock_irqsave_unlock(&page_lock);

	/* This can't fail because we don't make checks here */
	return 0;
}

int page_fault_handler(size_t viraddr, size_t pc)
{
	task_t* task = per_core(current_task);

	int check_pagetables(size_t vaddr)
	{
		int lvl;
		ssize_t vpn = vaddr >> PAGE_BITS;
		ssize_t index[PAGE_LEVELS];

		/* Calculate index boundaries for page map traversal */
		for (lvl=0; lvl<PAGE_LEVELS; lvl++)
			index[lvl] = vpn >> (lvl * PAGE_MAP_BITS);

		/* do we have already a valid entry in the page tables */
		for (lvl=PAGE_LEVELS-1; lvl>=0; lvl--) {
			vpn = index[lvl];

			if (!self[lvl][vpn])
				return 0;
		}

		return 1;
	}

	spinlock_irqsave_lock(&page_lock);

	//:wpage_dump();

	if ((task->heap) && (viraddr >= task->heap->start) && (viraddr < task->heap->end)) {
		/*
		 * do we have a valid page table entry? => flush TLB and return
		 */
		if (check_pagetables(viraddr)) {
			tlb_flush_one_page(viraddr);
			spinlock_irqsave_unlock(&page_lock);
			return 0;
		}

		 // on demand userspace heap mapping
		viraddr &= PAGE_MASK;

		size_t phyaddr = expect_zeroed_pages ? get_zeroed_page() : get_page();
		if (BUILTIN_EXPECT(!phyaddr, 0)) {
			LOG_ERROR("out of memory: task = %u\n", task->id);
			goto default_handler;
		}

		size_t flags = PG_USER|PG_RW;
		int ret = __page_map(viraddr, phyaddr, 1, flags);

		if (BUILTIN_EXPECT(ret, 0)) {
			LOG_ERROR("map_region: could not map %#lx to %#lx, task = %u\n", phyaddr, viraddr, task->id);
			put_page(phyaddr);

			goto default_handler;
		}

		spinlock_irqsave_unlock(&page_lock);

		return 0;
	}

default_handler:
	spinlock_irqsave_unlock(&page_lock);

	/* indicate unrecoverable page fault to the hypervisor */
	uhyve_pfault_t arg = {pc, viraddr, -1};
	/*
	 * In principle, uhyve_send is a function call to the hypervisor.
	 * => It is safe to pass data, which are stored on the stack.
	 */
	uhyve_send(UHYVE_PORT_PFAULT, (unsigned)virt_to_phys((size_t)&arg));

	return -EINVAL;
}

// weak symbol is used to detect a Go application
void __attribute__((weak)) runtime_osinit();

typedef size_t page_entry_t;

/** @brief Get the corresponding virtual address to a page map entry */
static inline size_t entry_to_virt(page_entry_t* entry, int level)
{
	size_t addr = (size_t) entry;

	addr <<= (level+1) * PAGE_MAP_BITS;
	addr &= 0x0000FFFFFFFFFFFFULL;

	return addr;
}

/** @brief Get the base address of the child table
 *
 * @param entry The parent entry
 * @return The child entry
 */
static inline page_entry_t* get_child_entry(page_entry_t *entry)
{
	size_t child = (size_t) entry;

	child <<= PAGE_MAP_BITS;
	child &= 0x0000FFFFFFFFFFFFULL;

	return (page_entry_t*) child;
}

/** @brief Get the base address of the parent entry
 *
 * @param entry The child entry
 * @return The parent entry
 */
static inline page_entry_t* get_parent_entry(page_entry_t *entry)
{
	ssize_t parent = (size_t) entry;

	parent >>= PAGE_MAP_BITS;
	parent |= 0x0000FF8000000000ULL; //PAGE_MAP_PGT;
	parent &= ~(sizeof(size_t) - 1); // align to page_entry_t

	return (page_entry_t*) parent;
}

void page_dump(void)
{
	size_t flags = 0;
	size_t start = 0;
	size_t end;

	void print(size_t start, size_t end, size_t flags) {
		size_t size = end - start;

		kprintf("%#018lx-%#018lx %#14x 0x%zx\n", start, end, size, flags);
	}

	void traverse(int level, page_entry_t* entry) {
		page_entry_t* stop = entry + PAGE_MAP_ENTRIES;
		for (; entry != stop; entry++) {
			if (*entry) {
				if (level) { // do "pre-order" traversal
					// TODO: handle "inheritance" of page table flags (see get_page_flags())
					traverse(level-1, get_child_entry(entry));
				} else {
					if (!flags) {
						flags = *entry & 0xFFFF000000000FFFULL;
						start = entry_to_virt(entry, level);
					}
					else if (flags != (*entry & 0xFFFF000000000FFFULL)) {
						end = entry_to_virt(entry, level);
						print(start, end, flags);

						flags = *entry & 0xFFFF000000000FFFULL;
						start = end;
					}
				}
			}
			else if (flags) {
				end = entry_to_virt(entry, level);
				print(start, end, flags);
				flags = 0;
			}
		}
	}

	kprintf("%-18s-%18s %14s %-6s\n", "start", "end", "size", "flags"); // header

	traverse(PAGE_LEVELS-1, (page_entry_t*) 0x0000FFFFFFFFF000ULL);

	if (flags) // workaround to print last mapping
		print(start, 0L, flags);
}

int page_init(void)
{
	// do we have Go application? => weak symbol isn't zeroe
	// => Go expect zeroed pages => set zeroed_pages to true
	if (runtime_osinit) {
		expect_zeroed_pages = 1;
		LOG_INFO("Detect Go runtime! Consequently, HermitCore zeroed heap.\n");
	}

	return 0;
}
