/*
 * Copyright (c) 2018, Stefan Lankes, RWTH Aachen University
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

#ifdef __aarch64__

#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <fcntl.h>
#include <sched.h>
#include <signal.h>
#include <limits.h>
#include <pthread.h>
#include <semaphore.h>
#include <elf.h>
#include <err.h>
#include <poll.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/eventfd.h>
#include <linux/const.h>
#include <linux/kvm.h>

#include "uhyve.h"

static bool cap_irqfd = false;

extern int kvm, vmfd, netfd, efd;
extern uint8_t* mboot;
extern __thread struct kvm_run *run;
extern __thread int vcpufd;
extern __thread uint32_t cpuid;

void print_registers(void)
{
}

void timer_handler(int signum)
{
	err(1, "Checkpointing is currently not supported!");
}

void restore_cpu_state(void)
{
	err(1, "Checkpointing is currently not supported!");
}

void save_cpu_state(void)
{
	err(1, "Checkpointing is currently not supported!");	
}

int load_checkpoint(uint8_t* mem, char* path)
{
	err(1, "Checkpointing is currently not supported!");
}

void init_cpu_state(uint64_t elf_entry)
{
	struct kvm_mp_state mp_state = { KVM_MP_STATE_RUNNABLE };
	struct kvm_regs regs = {
		.sp_el1 = 0x205,
		.elr_el1 = elf_entry,   // entry point to HermitCore
	};

	// be sure that the multiprocessor is runable
	kvm_ioctl(vcpufd, KVM_SET_MP_STATE, &mp_state);

	/* Setup registers and memory. */
	kvm_ioctl(vcpufd, KVM_SET_REGS, &regs);

	// only one core is able to enter startup code
	// => the wait for the predecessor core
	while (*((volatile uint32_t*) (mboot + 0x20)) < cpuid)
		pthread_yield();
	*((volatile uint32_t*) (mboot + 0x30)) = cpuid;
}

void init_irq_chip(void)
{
	kvm_ioctl(vmfd, KVM_CREATE_IRQCHIP, NULL);

	cap_irqfd = kvm_ioctl(vmfd, KVM_CHECK_EXTENSION, KVM_CAP_IRQFD) <= 0 ? false : true;
        if (!cap_irqfd)
                err(1, "the support of KVM_CAP_IRQFD is curently required");
}
#endif
