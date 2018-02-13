/*
 * Copyright (c) 2010, Stefan Lankes,   RWTH Aachen University
 * Copyright (c) 2018, Annika Wierichs, RWTH Aachen University
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

// KVM I/O ports corresponding to verbs API functions
#define UHYVE_PORT_SET_IB_POOL_ADDR             0x610
#define UHYVE_PORT_IBV_WC_STATUS_STR            0x611
#define UHYVE_PORT_IBV_RATE_TO_MULT             0x612
#define UHYVE_PORT_MULT_TO_IBV_RATE             0x613
#define UHYVE_PORT_IBV_RATE_TO_MBPS             0x614
#define UHYVE_PORT_MBPS_TO_IBV_RATE             0x615
#define UHYVE_PORT_IBV_CQ_EX_TO_CQ              0x616
#define UHYVE_PORT_IBV_START_POLL               0x617
#define UHYVE_PORT_IBV_NEXT_POLL                0x618
#define UHYVE_PORT_IBV_END_POLL                 0x619
#define UHYVE_PORT_IBV_WC_READ_OPCODE           0x61A
#define UHYVE_PORT_IBV_WC_READ_VENDOR_ERR       0x61B
#define UHYVE_PORT_IBV_WC_READ_BYTE_LEN         0x61C
#define UHYVE_PORT_IBV_WC_READ_IMM_DATA         0x61D
#define UHYVE_PORT_IBV_WC_READ_INVALIDATED_RKEY 0x61E
#define UHYVE_PORT_IBV_WC_READ_QP_NUM           0x61F
#define UHYVE_PORT_IBV_WC_READ_SRC_QP           0x620
#define UHYVE_PORT_IBV_WC_READ_WC_FLAGS         0x621
#define UHYVE_PORT_IBV_WC_READ_SLID             0x622
#define UHYVE_PORT_IBV_WC_READ_SL               0x623
#define UHYVE_PORT_IBV_WC_READ_DLID_PATH_BITS   0x624
#define UHYVE_PORT_IBV_WC_READ_COMPLETION_TS    0x625
#define UHYVE_PORT_IBV_WC_READ_CVLAN            0x626
#define UHYVE_PORT_IBV_WC_READ_FLOW_TAG         0x627
#define UHYVE_PORT_IBV_POST_WQ_RECV             0x628
#define UHYVE_PORT_IBV_GET_DEVICE_LIST          0x629
#define UHYVE_PORT_IBV_FREE_DEVICE_LIST         0x62A
#define UHYVE_PORT_IBV_GET_DEVICE_NAME          0x62B
#define UHYVE_PORT_IBV_GET_DEVICE_GUID          0x62C
#define UHYVE_PORT_IBV_OPEN_DEVICE              0x62D
#define UHYVE_PORT_IBV_CLOSE_DEVICE             0x62E
#define UHYVE_PORT_IBV_GET_ASYNC_EVENT          0x62F
#define UHYVE_PORT_IBV_ACK_ASYNC_EVENT          0x630
#define UHYVE_PORT_IBV_QUERY_DEVICE             0x631
#define UHYVE_PORT_IBV_QUERY_PORT               0x632
#define UHYVE_PORT_IBV_QUERY_GID                0x633
#define UHYVE_PORT_IBV_QUERY_PKEY               0x634
#define UHYVE_PORT_IBV_ALLOC_PD                 0x635
#define UHYVE_PORT_IBV_DEALLOC_PD               0x636
#define UHYVE_PORT_IBV_CREATE_FLOW              0x637
#define UHYVE_PORT_IBV_DESTROY_FLOW             0x638
#define UHYVE_PORT_IBV_OPEN_XRCD                0x639
#define UHYVE_PORT_IBV_CLOSE_XRCD               0x63A
#define UHYVE_PORT_IBV_REG_MR                   0x63B
#define UHYVE_PORT_IBV_REREG_MR                 0x63C
#define UHYVE_PORT_IBV_DEREG_MR                 0x63D
#define UHYVE_PORT_IBV_ALLOC_MW                 0x63E
#define UHYVE_PORT_IBV_DEALLOC_MW               0x63F
#define UHYVE_PORT_IBV_INC_RKEY                 0x640
#define UHYVE_PORT_IBV_BIND_MW                  0x641
#define UHYVE_PORT_IBV_CREATE_COMP_CHANNEL      0x642
#define UHYVE_PORT_IBV_DESTROY_COMP_CHANNEL     0x643
#define UHYVE_PORT_IBV_CREATE_CQ                0x644
#define UHYVE_PORT_IBV_CREATE_CQ_EX             0x645
#define UHYVE_PORT_IBV_RESIZE_CQ                0x646
#define UHYVE_PORT_IBV_DESTROY_CQ               0x647
#define UHYVE_PORT_IBV_GET_CQ_EVENT             0x648
#define UHYVE_PORT_IBV_ACK_CQ_EVENTS            0x649
#define UHYVE_PORT_IBV_POLL_CQ                  0x64A
#define UHYVE_PORT_IBV_REQ_NOTIFY_CQ            0x64B
#define UHYVE_PORT_IBV_CREATE_SRQ               0x64C
#define UHYVE_PORT_IBV_CREATE_SRQ_EX            0x64D
#define UHYVE_PORT_IBV_MODIFY_SRQ               0x64E
#define UHYVE_PORT_IBV_QUERY_SRQ                0x64F
#define UHYVE_PORT_IBV_GET_SRQ_NUM              0x650
#define UHYVE_PORT_IBV_DESTROY_SRQ              0x651
#define UHYVE_PORT_IBV_POST_SRQ_RECV            0x652
#define UHYVE_PORT_IBV_CREATE_QP                0x653
#define UHYVE_PORT_IBV_CREATE_QP_EX             0x654
#define UHYVE_PORT_IBV_QUERY_RT_VALUES_EX       0x655
#define UHYVE_PORT_IBV_QUERY_DEVICE_EX          0x656
#define UHYVE_PORT_IBV_OPEN_QP                  0x657
#define UHYVE_PORT_IBV_MODIFY_QP                0x658
#define UHYVE_PORT_IBV_QUERY_QP                 0x659
#define UHYVE_PORT_IBV_DESTROY_QP               0x65A
#define UHYVE_PORT_IBV_CREATE_WQ                0x65B
#define UHYVE_PORT_IBV_MODIFY_WQ                0x65C
#define UHYVE_PORT_IBV_DESTROY_WQ               0x65D
#define UHYVE_PORT_IBV_CREATE_RWQ_IND_TABLE     0x65E
#define UHYVE_PORT_IBV_DESTROY_RWQ_IND_TABLE    0x65F
#define UHYVE_PORT_IBV_POST_SEND                0x660
#define UHYVE_PORT_IBV_POST_RECV                0x661
#define UHYVE_PORT_IBV_CREATE_AH                0x662
#define UHYVE_PORT_IBV_INIT_AH_FROM_WC          0x663
#define UHYVE_PORT_IBV_CREATE_AH_FROM_WC        0x664
#define UHYVE_PORT_IBV_DESTROY_AH               0x665
#define UHYVE_PORT_IBV_ATTACH_MCAST             0x666
#define UHYVE_PORT_IBV_DETACH_MCAST             0x667
#define UHYVE_PORT_IBV_FORK_INIT                0x668
#define UHYVE_PORT_IBV_NODE_TYPE_STR            0x669
#define UHYVE_PORT_IBV_PORT_STATE_STR           0x66A
#define UHYVE_PORT_IBV_EVENT_TYPE_STR           0x66B
// #define UHYVE_PORT_IBV_RESOLVE_ETH_L2_FROM_GID  0x66C
#define UHYVE_PORT_IBV_IS_QPT_SUPPORTED         0x66D

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
