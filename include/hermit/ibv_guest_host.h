/*
 * Copyright (c) 2017, Annika Wierichs, RWTH Aachen University
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
 *
 * TODO: Documentation
 *
 */

#ifndef __IBV_GUEST_HOST_H__
#define __IBV_GUEST_HOST_H__

#include <hermit/verbs.h>

extern uint8_t * kernel_start_host;
typedef enum {GUEST, HOST} addr_type;

inline size_t guest_to_host(size_t address) {
	return address ? virt_to_phys(address) + (size_t) kernel_start_host : address;
}

inline size_t host_to_guest(size_t address) {
	return address ? phys_to_virt(address - (size_t) kernel_start_host) : address;
}


// struct ibv_device *        guest_to_host_ibv_device(struct ibv_device * device);
// struct ibv_context *       guest_to_host_ibv_context(struct ibv_context * context);
// struct ibv_context_ops *   guest_to_host_ibv_context_ops(struct ibv_context_ops * context_ops);
// struct ibv_port_attr *     guest_to_host_ibv_port_attr(struct ibv_port_attr * port_attr);
struct ibv_recv_wr *       guest_to_host_ibv_recv_wr(struct ibv_recv_wr * wr);
struct ibv_send_wr *       guest_to_host_ibv_send_wr(struct ibv_send_wr * wr);
struct ibv_sge *           guest_to_host_ibv_sge(struct ibv_sge * sg);
// struct ibv_abi_compat_v2 * guest_to_host_ibv_abi_compat_v2(struct ibv_abi_compat_v2 * abi_compat);
// pthread_mutex_t *					 guest_to_host_pthread_mutex_t(pthread_mutex_t * mutex);

// struct ibv_device *        host_to_guest_ibv_device(struct ibv_device * device, addr_type type);
// struct ibv_context *       host_to_guest_ibv_context(struct ibv_context * context, addr_type type);
// struct ibv_context_ops *   host_to_guest_ibv_context_ops(struct ibv_context_ops * context_ops, addr_type type);
// struct ibv_port_attr *     host_to_guest_ibv_port_attr(struct ibv_port_attr * port_attr, addr_type type);
// struct ibv_comp_channel *  host_to_guest_ibv_comp_channel(struct ibv_comp_channel * channel, addr_type type);
struct ibv_recv_wr *       host_to_guest_ibv_recv_wr(struct ibv_recv_wr * wr, addr_type type);
struct ibv_send_wr *       host_to_guest_ibv_send_wr(struct ibv_send_wr * wr, addr_type type);
struct ibv_sge *           host_to_guest_ibv_sge(struct ibv_sge * sg, addr_type type);
// struct ibv_abi_compat_v2 * host_to_guest_ibv_abi_compat_v2(struct ibv_abi_compat_v2 * abi_compat, addr_type type);
// pthread_mutex_t *	         host_to_guest_pthread_mutex_t(pthread_mutex_t * mutex, addr_type type);

#endif // __IBV_GUEST_HOST_H__
