/*
 * Copyright (c) 2010, Stefan Lankes, RWTH Aachen University
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

#ifndef __STDDEF_H__
#define __STDDEF_H__

/**
 * @author Stefan Lankes
 * @file include/hermit/stddef.h
 * @brief Definition of basic data types
 */

#include <hermit/config.h>
#include <asm/stddef.h>
#include <asm/irqflags.h>

#ifdef __cplusplus
extern "C" {
#endif

// size of the whole application
extern const size_t image_size;

#define TIMER_FREQ	100 /* in HZ */
#define CLOCK_TICK_RATE	1193182 /* 8254 chip's internal oscillator frequency */
#define CACHE_LINE	64
#define HEAP_START	(PAGE_2M_CEIL((size_t)&kernel_start + image_size) + 4*PAGE_SIZE)
#define HEAP_SIZE	(1ULL << 32)
#define KMSG_SIZE	0x1000
#define INT_SYSCALL	0x80
#define MAILBOX_SIZE	128
//#define WITH_PCI_IDS

#define BYTE_ORDER             LITTLE_ENDIAN

#define DYNAMIC_TICKS

#define UHYVE_PORT_WRITE	0x499
#define UHYVE_PORT_OPEN		0x500
#define UHYVE_PORT_CLOSE	0x501
#define UHYVE_PORT_READ		0x502
#define UHYVE_PORT_EXIT		0x503
#define UHYVE_PORT_LSEEK	0x504

// InfiniBand uhyve port IDs
#define UHYVE_PORT_IBV_WC_STATUS_STR            0x510
#define UHYVE_PORT_IBV_RATE_TO_MULT             0x511
#define UHYVE_PORT_MULT_TO_IBV_RATE             0x512
#define UHYVE_PORT_IBV_RATE_TO_MBPS             0x513
#define UHYVE_PORT_MBPS_TO_IBV_RATE             0x514
#define UHYVE_PORT_VERBS_GET_CTX                0x528
#define UHYVE_PORT_IBV_GET_DEVICE_LIST          0x529
#define UHYVE_PORT_IBV_FREE_DEVICE_LIST         0x52A
#define UHYVE_PORT_IBV_GET_DEVICE_NAME          0x52B
#define UHYVE_PORT_IBV_GET_DEVICE_GUID          0x52C
#define UHYVE_PORT_IBV_OPEN_DEVICE              0x52D
#define UHYVE_PORT_IBV_CLOSE_DEVICE             0x52E
#define UHYVE_PORT_IBV_GET_ASYNC_EVENT          0x52F
#define UHYVE_PORT_IBV_ACK_ASYNC_EVENT          0x530
#define UHYVE_PORT_IBV_QUERY_DEVICE             0x531
#define UHYVE_PORT_IBV_QUERY_PORT               0x532
#define UHYVE_PORT____IBV_QUERY_PORT            0x533
#define UHYVE_PORT_IBV_QUERY_GID                0x534
#define UHYVE_PORT_IBV_QUERY_PKEY               0x535
#define UHYVE_PORT_IBV_ALLOC_PD                 0x536
#define UHYVE_PORT_IBV_DEALLOC_PD               0x537
#define UHYVE_PORT_IBV_CREATE_FLOW              0x538
#define UHYVE_PORT_IBV_DESTROY_FLOW             0x539
#define UHYVE_PORT_IBV_OPEN_XRCD                0x53A
#define UHYVE_PORT_IBV_CLOSE_XRCD               0x53B
#define UHYVE_PORT_IBV_REG_MR                   0x53C
#define UHYVE_PORT_IBV_REREG_MR                 0x53D
#define UHYVE_PORT_IBV_DEREG_MR                 0x53E
#define UHYVE_PORT_IBV_ALLOC_MW                 0x53F
#define UHYVE_PORT_IBV_DEALLOC_MW               0x540
#define UHYVE_PORT_IBV_INC_RKEY                 0x541
#define UHYVE_PORT_IBV_BIND_MW                  0x542
#define UHYVE_PORT_IBV_CREATE_COMP_CHANNEL      0x543
#define UHYVE_PORT_IBV_DESTROY_COMP_CHANNEL     0x544
#define UHYVE_PORT_IBV_CREATE_CQ                0x545
#define UHYVE_PORT_IBV_RESIZE_CQ                0x547
#define UHYVE_PORT_IBV_DESTROY_CQ               0x548
#define UHYVE_PORT_IBV_GET_CQ_EVENT             0x549
#define UHYVE_PORT_IBV_ACK_CQ_EVENTS            0x54A
#define UHYVE_PORT_IBV_POLL_CQ                  0x54B
#define UHYVE_PORT_IBV_REQ_NOTIFY_CQ            0x54C
#define UHYVE_PORT_IBV_CREATE_SRQ               0x54D
#define UHYVE_PORT_IBV_CREATE_SRQ_EX            0x54E
#define UHYVE_PORT_IBV_MODIFY_SRQ               0x54F
#define UHYVE_PORT_IBV_QUERY_SRQ                0x550
#define UHYVE_PORT_IBV_GET_SRQ_NUM              0x551
#define UHYVE_PORT_IBV_DESTROY_SRQ              0x552
#define UHYVE_PORT_IBV_POST_SRQ_RECV            0x553
#define UHYVE_PORT_IBV_CREATE_QP                0x554
#define UHYVE_PORT_IBV_CREATE_QP_EX             0x555
#define UHYVE_PORT_IBV_QUERY_DEVICE_EX          0x557
#define UHYVE_PORT_IBV_OPEN_QP                  0x558
#define UHYVE_PORT_IBV_MODIFY_QP                0x559
#define UHYVE_PORT_IBV_QUERY_QP                 0x55A
#define UHYVE_PORT_IBV_DESTROY_QP               0x55B
#define UHYVE_PORT_IBV_POST_SEND                0x561
#define UHYVE_PORT_IBV_POST_RECV                0x562
#define UHYVE_PORT_IBV_CREATE_AH                0x563
#define UHYVE_PORT_IBV_INIT_AH_FROM_WC          0x564
#define UHYVE_PORT_IBV_CREATE_AH_FROM_WC        0x565
#define UHYVE_PORT_IBV_DESTROY_AH               0x566
#define UHYVE_PORT_IBV_ATTACH_MCAST             0x567
#define UHYVE_PORT_IBV_DETACH_MCAST             0x568
#define UHYVE_PORT_IBV_FORK_INIT                0x569
#define UHYVE_PORT_IBV_NODE_TYPE_STR            0x56A
#define UHYVE_PORT_IBV_PORT_STATE_STR           0x56B
#define UHYVE_PORT_IBV_EVENT_TYPE_STR           0x56C
#define UHYVE_PORT_IBV_IS_QPT_SUPPORTED         0x56E

// #define UHYVE_PORT_KERNEL_IBV_LOG               0x56F


#define BUILTIN_EXPECT(exp, b)		__builtin_expect((exp), (b))
//#define BUILTIN_EXPECT(exp, b)	(exp)
#define NORETURN			__attribute__((noreturn))

#define NULL 		((void*) 0)

/// represents a task identifier
typedef unsigned int tid_t;

#define DECLARE_PER_CORE(type, name) extern type name __attribute__ ((section (".percore")))
#define DEFINE_PER_CORE(type, name, def_value) type name __attribute__ ((section (".percore"))) = def_value
#define DEFINE_PER_CORE_STATIC(type, name, def_value) static type name __attribute__ ((section (".percore"))) = def_value

/* needed to find the task, which is currently running on this core */
struct task;
DECLARE_PER_CORE(struct task*, current_task);

#if MAX_CORES > 1
/* allows fast access to the core id */
DECLARE_PER_CORE(uint32_t, __core_id);
#define CORE_ID per_core(__core_id)
#else
#define CORE_ID 0
#endif

#ifdef __cplusplus
}
#endif

#endif
