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


#include <asm/page.h>

#include <hermit/ibv_guest_host.h>
#include <hermit/logging.h>


/*
 * struct ibv_device
 */

struct ibv_device * guest_to_host_ibv_device(struct ibv_device * device) {
	// _ops obsolete.
	return (struct ibv_device *) guest_to_host((size_t) device);
}

struct ibv_device * host_to_guest_ibv_device(struct ibv_device * device, addr_type type) {
	struct ibv_device * vaddr = (type == GUEST) ? device
		: (struct ibv_device *) host_to_guest((size_t) device);

	return vaddr;
}


/*
 * struct ibv_context
 */

struct ibv_context * guest_to_host_ibv_context(struct ibv_context * context) {
	context->device     = guest_to_host_ibv_device(context->device);
	context->abi_compat = guest_to_host_ibv_abi_compat_v2(context->abi_compat);

	guest_to_host_ibv_context_ops(&context->ops);
	guest_to_host_pthread_mutex_t(&context->mutex); // TODO

	return (struct ibv_context *) guest_to_host((size_t) context);
}

struct ibv_context * host_to_guest_ibv_context(struct ibv_context * context, addr_type type) {
	struct ibv_context * vaddr = (type == GUEST) ? context
		: (struct ibv_context *) host_to_guest((size_t) context);

	vaddr->device     = host_to_guest_ibv_device(vaddr->device, HOST);
	vaddr->abi_compat = host_to_guest_ibv_abi_compat_v2(vaddr->abi_compat, HOST);

	host_to_guest_ibv_context_ops(&vaddr->ops, GUEST);
	host_to_guest_pthread_mutex_t(&vaddr->mutex, GUEST);

	return vaddr;
}


/*
 * struct ibv_port_attr
 */

struct ibv_port_attr * guest_to_host_ibv_port_attr(struct ibv_port_attr * port_attr) {
	return (struct ibv_port_attr *) guest_to_host((size_t) port_attr);
}

struct ibv_port_attr * host_to_guest_ibv_port_attr(struct ibv_port_attr * port_attr, addr_type type) {
	struct ibv_port_attr * vaddr = (type == GUEST) ? port_attr
		: (struct ibv_port_attr *) host_to_guest((size_t) port_attr);

	return vaddr;
}


/*
 * struct ibv_sge
 */

struct ibv_sge * guest_to_host_ibv_sge(struct ibv_sge * sg) {
	LOG_INFO("Entered guest_to_host_ibv_recv_wr()\n");
	LOG_INFO("\tsg->addr before conversion: %lu\n", sg->addr);
	sg->addr = (uint64_t) guest_to_host((size_t) sg->addr);
	LOG_INFO("\tsg->addr after conversion: %lu\n", sg->addr);

	return (struct ibv_sge *) guest_to_host((size_t) sg);
}

struct ibv_sge * host_to_guest_ibv_sge(struct ibv_sge * sg, addr_type type) {
	LOG_INFO("Entered host_to_guest_ibv_recv_wr()\n");
	struct ibv_sge * vaddr = (type == GUEST) ? sg
		: (struct ibv_sge *) host_to_guest((size_t) sg);

	vaddr->addr = (uint64_t) host_to_guest((size_t) vaddr->addr);

	return vaddr;
}


// struct ibv_recv_wr {
// 	uint64_t		wr_id;
// 	struct ibv_recv_wr     *next;
// 	struct ibv_sge	       *sg_list;
// 	int			num_sge;
// };

// struct ibv_sge { // scatter/gather element
// 	uint64_t		addr;  // might have to be converted
// 	uint32_t		length;
// 	uint32_t		lkey;
// };

/*
 * struct ibv_recv_wr
 */

struct ibv_recv_wr * guest_to_host_ibv_recv_wr(struct ibv_recv_wr * wr) {
	LOG_INFO("Entered guest_to_host_ibv_recv_wr()\n");
	if (wr->next) {
		LOG_INFO("\twr->next is not NULL\n");
		wr->next    = guest_to_host_ibv_recv_wr(wr->next); // linked list
	}
	wr->sg_list = guest_to_host_ibv_sge(wr->sg_list);

	return (struct ibv_recv_wr *) guest_to_host((size_t) wr);
}

struct ibv_recv_wr * host_to_guest_ibv_recv_wr(struct ibv_recv_wr * wr, addr_type type) {
	LOG_INFO("Entered host_to_guest_ibv_recv_wr()\n");
	struct ibv_recv_wr * vaddr = (type == GUEST) ? wr
		: (struct ibv_recv_wr *) host_to_guest((size_t) wr);

	if (wr->next) {
		LOG_INFO("\twr->next is not NULL\n");
		vaddr->next = host_to_guest_ibv_recv_wr(vaddr->next, HOST); // linked list
	}
	vaddr->sg_list = host_to_guest_ibv_sge(vaddr->sg_list, HOST);

	return vaddr;
}


/*
 * struct ibv_comp_channel
 */

struct ibv_comp_channel * guest_to_host_ibv_comp_channel(struct ibv_comp_channel * channel) {
	channel->context = guest_to_host_ibv_context(channel->context);

	return (struct ibv_comp_channel *) guest_to_host((size_t) channel);
}

struct ibv_comp_channel * host_to_guest_ibv_comp_channel(struct ibv_comp_channel * channel, addr_type type) {
	struct ibv_comp_channel * vaddr = (type == GUEST) ? channel
		: (struct ibv_comp_channel *) host_to_guest((size_t) channel);

	vaddr->context = host_to_guest_ibv_context(vaddr->context, HOST);

	return vaddr;
}


/*
 * struct ibv_abi_compat_v2
 */

struct ibv_abi_compat_v2 * guest_to_host_ibv_abi_compat_v2(struct ibv_abi_compat_v2 * abi_compat) {
	guest_to_host_ibv_comp_channel(&abi_compat->channel);
	guest_to_host_pthread_mutex_t(&abi_compat->in_use);

	return (struct ibv_abi_compat_v2 *) guest_to_host((size_t) abi_compat);
}

struct ibv_abi_compat_v2 *  host_to_guest_ibv_abi_compat_v2(struct ibv_abi_compat_v2 * abi_compat, addr_type type) {
	struct ibv_abi_compat_v2 * vaddr = (type == GUEST) ? abi_compat
		: (struct ibv_abi_compat_v2 *) host_to_guest((size_t) abi_compat);

	host_to_guest_ibv_comp_channel(&abi_compat->channel, GUEST);
	host_to_guest_pthread_mutex_t(&abi_compat->in_use, GUEST);

	return vaddr;
}


/*
 * pthread_mutex_t
 */

pthread_mutex_t * guest_to_host_pthread_mutex_t(pthread_mutex_t * mutex) {
	/* mutex->__m_owner = guest_to_host__pthread_descr(mutex->__m_owner); */

	return (pthread_mutex_t *) guest_to_host((size_t) mutex);
}

pthread_mutex_t * host_to_guest_pthread_mutex_t(pthread_mutex_t * mutex, addr_type type) {
	pthread_mutex_t * vaddr = (type == GUEST) ? mutex
		: (pthread_mutex_t *) host_to_guest((size_t) mutex);
	/* host_to_guest__pthread_descr(mutex->__m_owner); */

	return vaddr;
}


/*
 * struct ibv_context_ops
 */

struct ibv_context_ops * guest_to_host_ibv_context_ops(struct ibv_context_ops * context_ops) {
	// TODO: Does this work?
	context_ops->query_device  = (int (*)(struct ibv_context *, struct ibv_device_attr *))                        guest_to_host((size_t) context_ops->query_device);
	context_ops->query_port    = (int (*)(struct ibv_context *, uint8_t, struct ibv_port_attr *))                 guest_to_host((size_t) context_ops->query_port);
	context_ops->alloc_pd      = (struct ibv_pd * (*)(struct ibv_context *))                                      guest_to_host((size_t) context_ops->alloc_pd);
	context_ops->dealloc_pd    = (int (*)(struct ibv_pd *))                                                       guest_to_host((size_t) context_ops->dealloc_pd);
	context_ops->reg_mr        = (struct ibv_mr * (*)(struct ibv_pd *, void *, size_t, int))                      guest_to_host((size_t) context_ops->reg_mr);
	context_ops->rereg_mr      = (int (*)(struct ibv_mr *, int, struct ibv_pd *, void *, size_t, int))            guest_to_host((size_t) context_ops->rereg_mr);
	context_ops->dereg_mr      = (int (*)(struct ibv_mr *))                                                       guest_to_host((size_t) context_ops->dereg_mr);
	context_ops->alloc_mw      = (struct ibv_mw * (*)(struct ibv_pd *, enum ibv_mw_type))                         guest_to_host((size_t) context_ops->alloc_mw);
	context_ops->bind_mw       = (int (*)(struct ibv_qp *, struct ibv_mw *, struct ibv_mw_bind *))                guest_to_host((size_t) context_ops->bind_mw);
	context_ops->dealloc_mw    = (int (*)(struct ibv_mw *))                                                       guest_to_host((size_t) context_ops->dealloc_mw);
	context_ops->create_cq     = (struct ibv_cq * (*)(struct ibv_context *, int, struct ibv_comp_channel *, int)) guest_to_host((size_t) context_ops->create_cq);
	context_ops->poll_cq       = (int (*)(struct ibv_cq *, int, struct ibv_wc *))                                 guest_to_host((size_t) context_ops->poll_cq);
	context_ops->req_notify_cq = (int (*)(struct ibv_cq *, int))                                                  guest_to_host((size_t) context_ops->req_notify_cq);
	context_ops->cq_event      = (void (*)(struct ibv_cq *))                                                      guest_to_host((size_t) context_ops->cq_event);
	context_ops->resize_cq     = (int (*)(struct ibv_cq *, int))                                                  guest_to_host((size_t) context_ops->resize_cq);
	context_ops->destroy_cq    = (int (*)(struct ibv_cq *))                                                       guest_to_host((size_t) context_ops->destroy_cq);
	context_ops->create_srq    = (struct ibv_srq * (*)(struct ibv_pd *, struct ibv_srq_init_attr *))              guest_to_host((size_t) context_ops->create_srq);
	context_ops->modify_srq    = (int (*)(struct ibv_srq *, struct ibv_srq_attr *, int))                          guest_to_host((size_t) context_ops->modify_srq);
	context_ops->query_srq     = (int (*)(struct ibv_srq *, struct ibv_srq_attr *))                               guest_to_host((size_t) context_ops->query_srq);
	context_ops->destroy_srq   = (int (*)(struct ibv_srq *))                                                      guest_to_host((size_t) context_ops->destroy_srq);
	context_ops->post_srq_recv = (int (*)(struct ibv_srq *, struct ibv_recv_wr *, struct ibv_recv_wr **))         guest_to_host((size_t) context_ops->post_srq_recv);
	context_ops->create_qp     = (struct ibv_qp * (*)(struct ibv_pd *, struct ibv_qp_init_attr *))                guest_to_host((size_t) context_ops->create_qp);
	context_ops->query_qp      = (int (*)(struct ibv_qp *, struct ibv_qp_attr *, int, struct ibv_qp_init_attr *)) guest_to_host((size_t) context_ops->query_qp);
	context_ops->modify_qp     = (int (*)(struct ibv_qp *, struct ibv_qp_attr *, int))                            guest_to_host((size_t) context_ops->modify_qp);
	context_ops->destroy_qp    = (int (*)(struct ibv_qp *))                                                       guest_to_host((size_t) context_ops->destroy_qp);
	context_ops->post_send     = (int (*)(struct ibv_qp *, struct ibv_send_wr *, struct ibv_send_wr **))          guest_to_host((size_t) context_ops->post_send);
	context_ops->post_recv     = (int (*)(struct ibv_qp *, struct ibv_recv_wr *, struct ibv_recv_wr **))          guest_to_host((size_t) context_ops->post_recv);
	context_ops->create_ah     = (struct ibv_ah * (*)(struct ibv_pd *, struct ibv_ah_attr *))                     guest_to_host((size_t) context_ops->create_ah);
	context_ops->destroy_ah    = (int (*)(struct ibv_ah *))                                                       guest_to_host((size_t) context_ops->destroy_ah);
	context_ops->attach_mcast  = (int (*)(struct ibv_qp *, const union ibv_gid *, uint16_t))                      guest_to_host((size_t) context_ops->attach_mcast);
	context_ops->detach_mcast  = (int (*)(struct ibv_qp *, const union ibv_gid *, uint16_t))                      guest_to_host((size_t) context_ops->detach_mcast);
	context_ops->async_event   = (void (*)(struct ibv_async_event *))                                             guest_to_host((size_t) context_ops->async_event);

	return (struct ibv_context_ops *) guest_to_host((size_t) context_ops);
}

struct ibv_context_ops * host_to_guest_ibv_context_ops(
		struct ibv_context_ops * context_ops, addr_type type) {
	struct ibv_context_ops * vaddr = (type == GUEST) ? context_ops
		: (struct ibv_context_ops *) host_to_guest((size_t) context_ops);

	vaddr->query_device  = (int (*)(struct ibv_context *, struct ibv_device_attr *))                        host_to_guest((size_t) vaddr->query_device);
	vaddr->query_port    = (int (*)(struct ibv_context *, uint8_t, struct ibv_port_attr *))                 host_to_guest((size_t) vaddr->query_port);
	vaddr->alloc_pd      = (struct ibv_pd * (*)(struct ibv_context *))                                      host_to_guest((size_t) vaddr->alloc_pd);
	vaddr->dealloc_pd    = (int (*)(struct ibv_pd *))                                                       host_to_guest((size_t) vaddr->dealloc_pd);
	vaddr->reg_mr        = (struct ibv_mr * (*)(struct ibv_pd *, void *, size_t, int))                      host_to_guest((size_t) vaddr->reg_mr);
	vaddr->rereg_mr      = (int (*)(struct ibv_mr *, int, struct ibv_pd *, void *, size_t, int))            host_to_guest((size_t) vaddr->rereg_mr);
	vaddr->dereg_mr      = (int (*)(struct ibv_mr *))                                                       host_to_guest((size_t) vaddr->dereg_mr);
	vaddr->alloc_mw      = (struct ibv_mw * (*)(struct ibv_pd *, enum ibv_mw_type))                         host_to_guest((size_t) vaddr->alloc_mw);
	vaddr->bind_mw       = (int (*)(struct ibv_qp *, struct ibv_mw *, struct ibv_mw_bind *))                host_to_guest((size_t) vaddr->bind_mw);
	vaddr->dealloc_mw    = (int (*)(struct ibv_mw *))                                                       host_to_guest((size_t) vaddr->dealloc_mw);
	vaddr->create_cq     = (struct ibv_cq * (*)(struct ibv_context *, int, struct ibv_comp_channel *, int)) host_to_guest((size_t) vaddr->create_cq);
	vaddr->poll_cq       = (int (*)(struct ibv_cq *, int, struct ibv_wc *))                                 host_to_guest((size_t) vaddr->poll_cq);
	vaddr->req_notify_cq = (int (*)(struct ibv_cq *, int))                                                  host_to_guest((size_t) vaddr->req_notify_cq);
	vaddr->cq_event      = (void (*)(struct ibv_cq *))                                                      host_to_guest((size_t) vaddr->cq_event);
	vaddr->resize_cq     = (int (*)(struct ibv_cq *, int))                                                  host_to_guest((size_t) vaddr->resize_cq);
	vaddr->destroy_cq    = (int (*)(struct ibv_cq *))                                                       host_to_guest((size_t) vaddr->destroy_cq);
	vaddr->create_srq    = (struct ibv_srq * (*)(struct ibv_pd *, struct ibv_srq_init_attr *))              host_to_guest((size_t) vaddr->create_srq);
	vaddr->modify_srq    = (int (*)(struct ibv_srq *, struct ibv_srq_attr *, int))                          host_to_guest((size_t) vaddr->modify_srq);
	vaddr->query_srq     = (int (*)(struct ibv_srq *, struct ibv_srq_attr *))                               host_to_guest((size_t) vaddr->query_srq);
	vaddr->destroy_srq   = (int (*)(struct ibv_srq *))                                                      host_to_guest((size_t) vaddr->destroy_srq);
	vaddr->post_srq_recv = (int (*)(struct ibv_srq *, struct ibv_recv_wr *, struct ibv_recv_wr **))         host_to_guest((size_t) vaddr->post_srq_recv);
	vaddr->create_qp     = (struct ibv_qp * (*)(struct ibv_pd *, struct ibv_qp_init_attr *))                host_to_guest((size_t) vaddr->create_qp);
	vaddr->query_qp      = (int (*)(struct ibv_qp *, struct ibv_qp_attr *, int, struct ibv_qp_init_attr *)) host_to_guest((size_t) vaddr->query_qp);
	vaddr->modify_qp     = (int (*)(struct ibv_qp *, struct ibv_qp_attr *, int))                            host_to_guest((size_t) vaddr->modify_qp);
	vaddr->destroy_qp    = (int (*)(struct ibv_qp *))                                                       host_to_guest((size_t) vaddr->destroy_qp);
	vaddr->post_send     = (int (*)(struct ibv_qp *, struct ibv_send_wr *, struct ibv_send_wr **))          host_to_guest((size_t) vaddr->post_send);
	vaddr->post_recv     = (int (*)(struct ibv_qp *, struct ibv_recv_wr *, struct ibv_recv_wr **))          host_to_guest((size_t) vaddr->post_recv);
	vaddr->create_ah     = (struct ibv_ah * (*)(struct ibv_pd *, struct ibv_ah_attr *))                     host_to_guest((size_t) vaddr->create_ah);
	vaddr->destroy_ah    = (int (*)(struct ibv_ah *))                                                       host_to_guest((size_t) vaddr->destroy_ah);
	vaddr->attach_mcast  = (int (*)(struct ibv_qp *, const union ibv_gid *, uint16_t))                      host_to_guest((size_t) vaddr->attach_mcast);
	vaddr->detach_mcast  = (int (*)(struct ibv_qp *, const union ibv_gid *, uint16_t))                      host_to_guest((size_t) vaddr->detach_mcast);
	vaddr->async_event   = (void (*)(struct ibv_async_event *))                                             host_to_guest((size_t) vaddr->async_event);

	return vaddr;
}
