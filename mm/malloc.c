/*
 * Copyright (c) 2014, Steffen Vogel, RWTH Aachen University
 *                     All rights reserved.
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
 * @author Steffen Vogel <steffen.vogel@rwth-aachen.de>
 */

#include <hermit/stdio.h>
#include <hermit/malloc.h>
#include <hermit/spinlock.h>
#include <hermit/memory.h>
#include <hermit/logging.h>
#include <asm/page.h>

/// A linked list for each binary size exponent
static buddy_t* buddy_lists[BUDDY_LISTS] = { [0 ... BUDDY_LISTS-1] = NULL };

extern spinlock_irqsave_t hermit_mm_lock;

/** @brief Check if larger free buddies are available */
static inline int buddy_large_avail(uint8_t exp)
{
	while ((exp<BUDDY_MAX) && !buddy_lists[exp-BUDDY_MIN])
		exp++;

	return exp != BUDDY_MAX;
}

/** @brief Calculate the required buddy size */
static inline int buddy_exp(size_t sz)
{
	int exp;
	for (exp=0; sz>(1<<exp); exp++);

	if (exp > BUDDY_MAX)
		exp = 0;
	if (exp < BUDDY_MIN)
		exp = BUDDY_MIN;

	return exp;
}

/** @brief Get a free buddy by potentially splitting a larger one */
static buddy_t* buddy_get(int exp)
{
	spinlock_irqsave_lock(&hermit_mm_lock);
	buddy_t** list = &buddy_lists[exp-BUDDY_MIN];
	buddy_t* buddy = *list;
	buddy_t* split;

	if (buddy)
		// there is already a free buddy =>
		// we remove it from the list
		*list = buddy->next;
	else if ((exp >= BUDDY_ALLOC) && !buddy_large_avail(exp))
		// theres no free buddy larger than exp =>
		// we can allocate new memory
		buddy = (buddy_t*) palloc(1<<exp, VMA_HEAP|VMA_CACHEABLE);
	else {
		// we recursivly request a larger buddy...
		buddy = buddy_get(exp+1);
		if (BUILTIN_EXPECT(!buddy, 0))
			goto out;

		// ... and split it, by putting the second half back to the list
		split = (buddy_t*) ((size_t) buddy + (1<<exp));
		split->next = *list;
		*list = split;
	}

out:
	spinlock_irqsave_unlock(&hermit_mm_lock);

	return buddy;
}

/** @brief Put a buddy back to its free list
 *
 * TODO: merge adjacent buddies (memory compaction)
 */
static void buddy_put(buddy_t* buddy)
{
	spinlock_irqsave_lock(&hermit_mm_lock);
	buddy_t** list = &buddy_lists[buddy->prefix.exponent-BUDDY_MIN];
	buddy->next = *list;
	*list = buddy;
	spinlock_irqsave_unlock(&hermit_mm_lock);
}

void buddy_dump(void)
{
	size_t free = 0;
	int i;

	for (i=0; i<BUDDY_LISTS; i++) {
		buddy_t* buddy;
		int exp = i+BUDDY_MIN;

		if (buddy_lists[i])
			LOG_INFO("buddy_list[%u] (exp=%u, size=%lu bytes):\n", i, exp, 1<<exp);

		for (buddy=buddy_lists[i]; buddy; buddy=buddy->next) {
			LOG_INFO("  %p -> %p \n", buddy, buddy->next);
			free += 1<<exp;
		}
	}
	LOG_INFO("free buddies: %lu bytes\n", free);
}

void* create_stack(size_t sz)
{
	LOG_DEBUG("create_stack(0x%zx)\n", sz);
	kputs("create_stack(");
	print_hex(sz);
	kputs(")\n");

	if (BUILTIN_EXPECT(!sz, 0))
		return NULL;

	return (void*) kmalloc(sz);
}

int destroy_stack(void* viraddr, size_t sz)
{
	LOG_DEBUG("destroy_stack(0x%zx) (size 0x%zx)\n", viraddr, sz);
	kputs("destroy_stack(");
	print_hex(viraddr);
	kputs(") (size ");
	print_hex(sz);
	kputs(")\n");

	if (BUILTIN_EXPECT(!viraddr, 0))
		return -EINVAL;
	if (BUILTIN_EXPECT(!sz, 0))
		return -EINVAL;

	kfree(viraddr);
	return 0;
}
