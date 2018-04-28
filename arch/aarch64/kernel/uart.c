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
#include <hermit/stdio.h>
#include <hermit/errno.h>
#include <hermit/string.h>
#include <hermit/ctype.h>
#include <asm/uart.h>

volatile static unsigned int* mmio = NULL;
extern unsigned int uart_mmio;

/* Puts a single character on a serial device */
int uart_putchar(unsigned char c)
{
	if (mmio)
		*mmio = (unsigned int) c;

	return (int) c;
}

/* Uses the routine above to output a string... */
int uart_puts(const char *text)
{
	size_t i, len = strlen(text);

	if (!mmio)
		return 0;

	for (i = 0; i < len; i++)
		uart_putchar(text[i]);

	return len;
}

int uart_early_init(char* cmdline)
{
	if (is_uhyve()) {
		mmio = (unsigned int*) uart_mmio;
	} else {
		// default value of our QEMU configuration
		mmio = (unsigned int*) 0x09000000;
	}

	return 0;
}

int uart_init(void)
{
	if (is_uhyve()) {
		mmio = (unsigned int*) uart_mmio;
	} else {
		mmio = (unsigned int*) 0x09000000;
	}

	return 0;
}
