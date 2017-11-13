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

#include <hermit/ibv_struct_address_conversion.h>


/*
 * struct ibv_device
 */

static struct {
	char * name;
	char * dev_name;
	char * dev_path;
	char * ibdev_path;
} ibv_device_virt_ptrs;

struct ibv_device * virt_to_phys_ibv_device(struct ibv_device * device) {
	ibv_device_virt_ptrs.name       = device->name;;
	ibv_device_virt_ptrs.dev_name   = device->dev_name;
	ibv_device_virt_ptrs.dev_path   = device->dev_path;
	ibv_device_virt_ptrs.ibdev_path = device->ibdev_path;

	device->name       = (char *) virt_to_phys((size_t) device->name);
	device->dev_name   = (char *) virt_to_phys((size_t) device->dev_name);
	device->dev_path   = (char *) virt_to_phys((size_t) device->dev_path);
	device->ibdev_path = (char *) virt_to_phys((size_t) device->ibdev_path);
	// _ops obsolete.

	return (struct ibv_device *) virt_to_phys((size_t) device);
}

void phys_to_virt_ibv_device(struct ibv_device * device) {
	device->name       = ibv_device_virt_ptrs.name;
	device->dev_name   = ibv_device_virt_ptrs.dev_name;
	device->dev_path   = ibv_device_virt_ptrs.dev_path;
	device->ibdev_path = ibv_device_virt_ptrs.ibdev_path;
	// _ops obsolete.
}


/*
 * struct ibv_context
 */

static struct {
	struct ibv_device * device;
	void * abi_compat;
} ibv_context_virt_ptrs;

struct ibv_context * virt_to_phys_ibv_context(struct ibv_context * context) {
	ibv_context_virt_ptrs.device = context->device,
	ibv_context_virt_ptrs.abi_compat = context->abi_compat,

	context->device = virt_to_phys_ibv_device(context->device);
	context->abi_compat = virt_to_phys_ibv_abi_compat_v2(context->abi_compat);
	virt_to_phys_ibv_context_ops(&context->ops);
	/*virt_to_phys_pthread_mutex_t(&context->mutex); // TODO*/

	return (struct ibv_context *) virt_to_phys((size_t) context);
}

void phys_to_virt_ibv_context(struct ibv_context * context) {
	context->device = ibv_context_virt_ptrs.device;
	context->abi_compat = ibv_context_virt_ptrs.abi_compat;

	phys_to_virt_ibv_device(context->device);
	phys_to_virt_ibv_abi_compat_v2(context->abi_compat);
	phys_to_virt_ibv_context_ops(&context->ops);
}


/*
 * struct ibv_context_ops
 */

static struct {
	int	             (*query_device)(struct ibv_context *, struct ibv_device_attr *);
	int              (*query_port)(struct ibv_context *, uint8_t, struct ibv_port_attr *);
	struct ibv_pd *  (*alloc_pd)(struct ibv_context *);
	int              (*dealloc_pd)(struct ibv_pd *);
	struct ibv_mr *  (*reg_mr)(struct ibv_pd *, void *, size_t, int);
	int	             (*rereg_mr)(struct ibv_mr *, int, struct ibv_pd *, void *, size_t, int);
	int	             (*dereg_mr)(struct ibv_mr *);
	struct ibv_mw *  (*alloc_mw)(struct ibv_pd *, enum ibv_mw_type);
	int	             (*bind_mw)(struct ibv_qp *, struct ibv_mw *, struct ibv_mw_bind *);
	int	             (*dealloc_mw)(struct ibv_mw *);
	struct ibv_cq *  (*create_cq)(struct ibv_context *, int, struct ibv_comp_channel *, int);
	int              (*poll_cq)(struct ibv_cq *, int, struct ibv_wc *);
	int              (*req_notify_cq)(struct ibv_cq *, int);
	void             (*cq_event)(struct ibv_cq *);
	int	             (*resize_cq)(struct ibv_cq *, int);
	int	             (*destroy_cq)(struct ibv_cq *);
	struct ibv_srq * (*create_srq)(struct ibv_pd *, struct ibv_srq_init_attr *);
	int              (*modify_srq)(struct ibv_srq *, struct ibv_srq_attr *, int);
	int              (*query_srq)(struct ibv_srq *, struct ibv_srq_attr *);
	int              (*destroy_srq)(struct ibv_srq *);
	int              (*post_srq_recv)(struct ibv_srq *, struct ibv_recv_wr *, struct ibv_recv_wr **);
	struct ibv_qp *  (*create_qp)(struct ibv_pd *, struct ibv_qp_init_attr *);
	int	             (*query_qp)(struct ibv_qp *, struct ibv_qp_attr *, int, struct ibv_qp_init_attr *);
	int	             (*modify_qp)(struct ibv_qp *, struct ibv_qp_attr *, int);
	int	             (*destroy_qp)(struct ibv_qp *);
	int	             (*post_send)(struct ibv_qp *, struct ibv_send_wr *, struct ibv_send_wr **);
	int	             (*post_recv)(struct ibv_qp *, struct ibv_recv_wr *, struct ibv_recv_wr **);
	struct ibv_ah *  (*create_ah)(struct ibv_pd *, struct ibv_ah_attr *);
	int	             (*destroy_ah)(struct ibv_ah *);
	int	             (*attach_mcast)(struct ibv_qp *, const union ibv_gid *, uint16_t);
	int	             (*detach_mcast)(struct ibv_qp *, const union ibv_gid *, uint16_t);
	void             (*async_event)(struct ibv_async_event *);
} ibv_context_ops_virt_ptrs;

struct ibv_context_ops * virt_to_phys_ibv_context_ops(struct ibv_context_ops * context_ops) {
	ibv_context_virt_ptrs.query_device  = context_ops->query_device;
	ibv_context_virt_ptrs.query_port    = context_ops->query_port;
	ibv_context_virt_ptrs.alloc_pd      = context_ops->alloc_pd;
	ibv_context_virt_ptrs.dealloc_pd    = context_ops->dealloc_pd;
	ibv_context_virt_ptrs.reg_mr        = context_ops->reg_mr;
	ibv_context_virt_ptrs.rereg_mr      = context_ops->rereg_mr;
	ibv_context_virt_ptrs.dereg_mr      = context_ops->dereg_mr;
	ibv_context_virt_ptrs.alloc_mw      = context_ops->alloc_mw;
	ibv_context_virt_ptrs.bind_mw       = context_ops->bind_mw;
	ibv_context_virt_ptrs.dealloc_mw    = context_ops->dealloc_mw;
	ibv_context_virt_ptrs.create_cq     = context_ops->create_cq;
	ibv_context_virt_ptrs.poll_cq       = context_ops->poll_cq;
	ibv_context_virt_ptrs.req_notify_cq = context_ops->req_notify_cq;
	ibv_context_virt_ptrs.cq_event      = context_ops->cq_event;
	ibv_context_virt_ptrs.resize_cq     = context_ops->resize_cq;
	ibv_context_virt_ptrs.destroy_cq    = context_ops->destroy_cq;
	ibv_context_virt_ptrs.create_srq    = context_ops->create_srq;
	ibv_context_virt_ptrs.modify_srq    = context_ops->modify_srq;
	ibv_context_virt_ptrs.query_srq     = context_ops->query_srq;
	ibv_context_virt_ptrs.destroy_srq   = context_ops->destroy_srq;
	ibv_context_virt_ptrs.post_srq_recv = context_ops->post_srq_recv;
	ibv_context_virt_ptrs.create_qp     = context_ops->create_qp;
	ibv_context_virt_ptrs.query_qp      = context_ops->query_qp;
	ibv_context_virt_ptrs.modify_qp     = context_ops->modify_qp;
	ibv_context_virt_ptrs.destroy_qp    = context_ops->destroy_qp;
	ibv_context_virt_ptrs.post_send     = context_ops->post_send;
	ibv_context_virt_ptrs.post_recv     = context_ops->post_recv;
	ibv_context_virt_ptrs.create_ah     = context_ops->create_ah;
	ibv_context_virt_ptrs.destroy_ah    = context_ops->destroy_ah;
	ibv_context_virt_ptrs.attach_mcast  = context_ops->attach_mcast;
	ibv_context_virt_ptrs.detach_mcast  = context_ops->detach_mcast;
	ibv_context_virt_ptrs.async_event   = context_ops->async_event;

	context_ops->query_device  = virt_to_phys((size_t) context_ops->query_device);
	context_ops->query_port    = virt_to_phys((size_t) context_ops->query_port);
	context_ops->alloc_pd      = virt_to_phys((size_t) context_ops->alloc_pd);
	context_ops->dealloc_pd    = virt_to_phys((size_t) context_ops->dealloc_pd);
	context_ops->reg_mr        = virt_to_phys((size_t) context_ops->reg_mr);
	context_ops->rereg_mr      = virt_to_phys((size_t) context_ops->rereg_mr);
	context_ops->dereg_mr      = virt_to_phys((size_t) context_ops->dereg_mr);
	context_ops->alloc_mw      = virt_to_phys((size_t) context_ops->alloc_mw);
	context_ops->bind_mw       = virt_to_phys((size_t) context_ops->bind_mw);
	context_ops->dealloc_mw    = virt_to_phys((size_t) context_ops->dealloc_mw);
	context_ops->create_cq     = virt_to_phys((size_t) context_ops->create_cq);
	context_ops->poll_cq       = virt_to_phys((size_t) context_ops->poll_cq);
	context_ops->req_notify_cq = virt_to_phys((size_t) context_ops->req_notify_cq);
	context_ops->cq_event      = virt_to_phys((size_t) context_ops->cq_event);
	context_ops->resize_cq     = virt_to_phys((size_t) context_ops->resize_cq);
	context_ops->destroy_cq    = virt_to_phys((size_t) context_ops->destroy_cq);
	context_ops->create_srq    = virt_to_phys((size_t) context_ops->create_srq);
	context_ops->modify_srq    = virt_to_phys((size_t) context_ops->modify_srq);
	context_ops->query_srq     = virt_to_phys((size_t) context_ops->query_srq);
	context_ops->destroy_srq   = virt_to_phys((size_t) context_ops->destroy_srq);
	context_ops->post_srq_recv = virt_to_phys((size_t) context_ops->post_srq_recv);
	context_ops->create_qp     = virt_to_phys((size_t) context_ops->create_qp);
	context_ops->query_qp      = virt_to_phys((size_t) context_ops->query_qp);
	context_ops->modify_qp     = virt_to_phys((size_t) context_ops->modify_qp);
	context_ops->destroy_qp    = virt_to_phys((size_t) context_ops->destroy_qp);
	context_ops->post_send     = virt_to_phys((size_t) context_ops->post_send);
	context_ops->post_recv     = virt_to_phys((size_t) context_ops->post_recv);
	context_ops->create_ah     = virt_to_phys((size_t) context_ops->create_ah);
	context_ops->destroy_ah    = virt_to_phys((size_t) context_ops->destroy_ah);
	context_ops->attach_mcast  = virt_to_phys((size_t) context_ops->attach_mcast);
	context_ops->detach_mcast  = virt_to_phys((size_t) context_ops->detach_mcast);
	context_ops->async_event   = virt_to_phys((size_t) context_ops->async_event);

	return (struct ibv_context_ops *) virt_to_phys((size_t) context_ops);
}

void phys_to_virt_ibv_context_ops(struct ibv_context_ops * context_ops) {
	context_ops->query_device  = ibv_context_ops_virt_ptrs.query_device;
	context_ops->query_port    = ibv_context_ops_virt_ptrs.query_port;
	context_ops->alloc_pd      = ibv_context_ops_virt_ptrs.alloc_pd;
	context_ops->dealloc_pd    = ibv_context_ops_virt_ptrs.dealloc_pd;
	context_ops->reg_mr        = ibv_context_ops_virt_ptrs.reg_mr;
	context_ops->rereg_mr      = ibv_context_ops_virt_ptrs.rereg_mr;
	context_ops->dereg_mr      = ibv_context_ops_virt_ptrs.dereg_mr;
	context_ops->alloc_mw      = ibv_context_ops_virt_ptrs.alloc_mw;
	context_ops->bind_mw       = ibv_context_ops_virt_ptrs.bind_mw;
	context_ops->dealloc_mw    = ibv_context_ops_virt_ptrs.dealloc_mw;
	context_ops->create_cq     = ibv_context_ops_virt_ptrs.create_cq;
	context_ops->poll_cq       = ibv_context_ops_virt_ptrs.poll_cq;
	context_ops->req_notify_cq = ibv_context_ops_virt_ptrs.req_notify_cq;
	context_ops->cq_event      = ibv_context_ops_virt_ptrs.cq_event;
	context_ops->resize_cq     = ibv_context_ops_virt_ptrs.resize_cq;
	context_ops->destroy_cq    = ibv_context_ops_virt_ptrs.destroy_cq;
	context_ops->create_srq    = ibv_context_ops_virt_ptrs.create_srq;
	context_ops->modify_srq    = ibv_context_ops_virt_ptrs.modify_srq;
	context_ops->query_srq     = ibv_context_ops_virt_ptrs.query_srq;
	context_ops->destroy_srq   = ibv_context_ops_virt_ptrs.destroy_srq;
	context_ops->post_srq_recv = ibv_context_ops_virt_ptrs.post_srq_recv;
	context_ops->create_qp     = ibv_context_ops_virt_ptrs.create_qp;
	context_ops->query_qp      = ibv_context_ops_virt_ptrs.query_qp;
	context_ops->modify_qp     = ibv_context_ops_virt_ptrs.modify_qp;
	context_ops->destroy_qp    = ibv_context_ops_virt_ptrs.destroy_qp;
	context_ops->post_send     = ibv_context_ops_virt_ptrs.post_send;
	context_ops->post_recv     = ibv_context_ops_virt_ptrs.post_recv;
	context_ops->create_ah     = ibv_context_ops_virt_ptrs.create_ah;
	context_ops->destroy_ah    = ibv_context_ops_virt_ptrs.destroy_ah;
	context_ops->attach_mcast  = ibv_context_ops_virt_ptrs.attach_mcast;
	context_ops->detach_mcast  = ibv_context_ops_virt_ptrs.detach_mcast;
	context_ops->async_event   = ibv_context_ops_virt_ptrs.async_event;

}


/*
 * struct ibv_port_attr
 */

struct ibv_port_attr * virt_to_phys_ibv_port_attr(struct ibv_port_attr * port_attr) {
	return (struct ibv_port_attr *) virt_to_phys((size_t) port_attr);
}

void phys_to_virt_ibv_port_attr(struct ibv_port_attr * port_attr) {}


/*
 * struct ibv_abi_compat_v2
 */

struct ibv_abi_compat_v2 * virt_to_phys_ibv_abi_compat_v2(struct ibv_abi_compat_v2 * abi_compat) {
	virt_to_phys_ibv_comp_channel(&abi_compat->channel);
	virt_to_phys_pthread_mutex_t(&abi_compat->in_use);

	return (struct ibv_abi_compat_v2 *) virt_to_phys((size_t) abi_compat);
}

void phys_to_virt_ibv_abi_compat_v2(struct ibv_abi_compat_v2 * abi_compat) {
	phys_to_virt_ibv_comp_channel(&abi_compat->channel);
	phys_to_virt_pthread_mutex_t(&abi_compat->in_use);
}


/*
 * struct ibv_comp_channel 
 */

static struct {
	struct ibv_context * context;
} ibv_comp_channel_virt_ptrs;

struct ibv_comp_channel * virt_to_phys_ibv_comp_channel(struct ibv_comp_channel * channel) {
	ibv_comp_channel_virt_ptrs.context = channel->context,

	channel->context = virt_to_phys_ibv_device(channel->context);

	return (struct ibv_comp_channel *) virt_to_phys((size_t) channel);
}

void phys_to_virt_ibv_comp_channel(struct ibv_comp_channel * channel) {
	channel->context = ibv_comp_channel_virt_ptrs.context;

	phys_to_virt_ibv_device(channel->context);
}



