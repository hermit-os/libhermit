/*
 * Copyright (c) 2014-2017, Stefan Lankes, Daniel Krebs, RWTH Aachen University
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

#include <hermit/stdlib.h>
#include <asm/processor.h>
#include <asm/page.h>

int irq_init(void)
{
	return 0;
}

int enable_dynticks(void)
{
	return 0;
}

int irq_handler(int int_nr)
{
    uint32_t esr = read_esr_el1();
    uint32_t ec = esr >> 24;
    uint32_t iss = esr & 0xFFFFFF;

	/* data abort from lower or current level */
    if (ec == 0b100100 || ec == 0b100101) {
		/* check if value in far_el1 is valid */
		if (!(iss & (1 << 10))) {
			/* read far_el1 register, which holds the faulting virtual address */
            uint64_t far = read_far_el1();
			//page_fault_handler(far);
		} else {
			kputs("Could not handle data abort: address in far_el1 invalid\n");
		}
    }

	return 0;
}
