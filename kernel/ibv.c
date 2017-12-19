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
#include <asm/uhyve.h>
#include <hermit/stddef.h>
#include <hermit/stdio.h>
#include <hermit/stdlib.h>
#include <hermit/logging.h>

#include <hermit/ibv.h>
#include <hermit/ibv_guest_host.h>

#define MAX_CHAR_ARR_LENGTH    1024
#define MAX_NUM_OF_IBV_DEVICES 16 // TODO: is this enough?
#define ETHERNET_LL_SIZE       6


/*
 * ibv_get_device_list
 */

typedef struct {
	// Parameters:
	int * num_devices;
	// Return value:
	struct ibv_device ** ret;
} __attribute__((packed)) uhyve_ibv_get_device_list_t;

struct ibv_device ** ibv_get_device_list(int * num_devices) { // !
	uhyve_ibv_get_device_list_t uhyve_args;
	uhyve_args.num_devices = (int *) guest_to_host((size_t) num_devices);

	struct ibv_device ** list;
	list = kmalloc(MAX_NUM_OF_IBV_DEVICES * sizeof(struct ibv_device *));	// NUM + 1 ???
	uhyve_args.ret = (struct ibv_device **) guest_to_host((size_t) list);

	uhyve_send(UHYVE_PORT_IBV_GET_DEVICE_LIST, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return list;
}


/*
 * ibv_get_device_name
 */

typedef struct {
	// Parameters:
	struct ibv_device * device;
	// Return value:
	char * ret;
} __attribute__((packed)) uhyve_ibv_get_device_name_t;

const char * ibv_get_device_name(struct ibv_device * device) {
	uhyve_ibv_get_device_name_t uhyve_args;
	uhyve_args.device = device;

	uhyve_args.ret = kmalloc(MAX_CHAR_ARR_LENGTH);
	uhyve_send(UHYVE_PORT_IBV_GET_DEVICE_NAME, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_query_port
 */

typedef struct {
	// Parameters:
	struct ibv_context * context;
	uint8_t port_num;
	struct ibv_port_attr * port_attr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_query_port_t;

int ibv_query_port(struct ibv_context * context, uint8_t port_num, struct ibv_port_attr * port_attr) {
	uhyve_ibv_query_port_t uhyve_args;
	uhyve_args.context   = context;
	uhyve_args.port_num  = port_num;
	uhyve_args.port_attr = (struct ibv_port_attr *) guest_to_host((size_t) port_attr); // own fnc?

	uhyve_send(UHYVE_PORT_IBV_QUERY_PORT, (unsigned) virt_to_phys((size_t) &uhyve_args));

	/* host_to_guest_ibv_port_attr(port_attr, GUEST); // ! not necessary atm */

	return uhyve_args.ret;
}


/*
 * IBV KERNEL LOG
 */

/* void kernel_ibv_log() { */
	/* char log_message[128]; */
	/* ksprintf(log_message, "%p", kernel_start_host); */
	/* uhyve_send(UHYVE_PORT_KERNEL_IBV_LOG, (unsigned) virt_to_phys((size_t) log_message)); */
/* } */



// ----------------------------------------------------------------------------





/*
 * ibv_wc_status_str
 */

typedef struct {
	// Parameters:
	enum ibv_wc_status status;
	// Return value:
	char * ret;
} __attribute__((packed)) uhyve_ibv_wc_status_str_t;

const char * ibv_wc_status_str(enum ibv_wc_status status) {
	uhyve_ibv_wc_status_str_t uhyve_args;
	uhyve_args.status = status;

	static const char ret[MAX_CHAR_ARR_LENGTH];
	uhyve_args.ret = ret;

	uhyve_send(UHYVE_PORT_IBV_WC_STATUS_STR, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return ret;
}


/*
 * ibv_rate_to_mult
 */

typedef struct {
	// Parameters:
	enum ibv_rate rate;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_rate_to_mult_t;

int ibv_rate_to_mult(enum ibv_rate rate) {
	uhyve_ibv_rate_to_mult_t uhyve_args;
	uhyve_args.rate = rate;

	uhyve_send(UHYVE_PORT_IBV_RATE_TO_MULT, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * mult_to_ibv_rate
 */

typedef struct {
	// Parameters:
	int mult;
	// Return value:
	enum ibv_rate ret;
} __attribute__((packed)) uhyve_mult_to_ibv_rate_t;

enum ibv_rate mult_to_ibv_rate(int mult) {
	uhyve_mult_to_ibv_rate_t uhyve_args;
	uhyve_args.mult = mult;

	uhyve_send(UHYVE_PORT_MULT_TO_IBV_RATE, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_rate_to_mbps
 */

typedef struct {
	// Parameters:
	enum ibv_rate rate;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_rate_to_mbps_t;

int ibv_rate_to_mbps(enum ibv_rate rate) {
	uhyve_ibv_rate_to_mbps_t uhyve_args;
	uhyve_args.rate = rate;

	uhyve_send(UHYVE_PORT_IBV_RATE_TO_MBPS, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * mbps_to_ibv_rate
 */

typedef struct {
	// Parameters:
	int mbps;
	// Return value:
	enum ibv_rate ret;
} __attribute__((packed)) uhyve_mbps_to_ibv_rate_t;

enum ibv_rate mbps_to_ibv_rate(int mbps) {
	uhyve_mbps_to_ibv_rate_t uhyve_args;
	uhyve_args.mbps = mbps;

	uhyve_send(UHYVE_PORT_MBPS_TO_IBV_RATE, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * verbs_get_ctx
 */

typedef struct {
	// Parameters:
	struct ibv_context * ctx;
	// Return value:
	struct verbs_context * ret;
} __attribute__((packed)) uhyve_verbs_get_ctx_t;

struct verbs_context * verbs_get_ctx(struct ibv_context * ctx) {
	uhyve_verbs_get_ctx_t uhyve_args;
	uhyve_args.ctx = ctx;

	uhyve_send(UHYVE_PORT_VERBS_GET_CTX, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_free_device_list
 */

typedef struct {
	// Parameters:
	struct ibv_device ** list;
} __attribute__((packed)) uhyve_ibv_free_device_list_t;

void ibv_free_device_list(struct ibv_device ** list) {
	uhyve_ibv_free_device_list_t uhyve_args;
	uhyve_args.list = (struct ibv_device **) guest_to_host((size_t) list);

	kfree(list);

	uhyve_send(UHYVE_PORT_IBV_FREE_DEVICE_LIST, (unsigned) virt_to_phys((size_t) &uhyve_args));
}


/*
 * ibv_get_device_guid
 */

typedef struct {
	// Parameters:
	struct ibv_device * device;
	// Return value:
	__be64 ret;
} __attribute__((packed)) uhyve_ibv_get_device_guid_t;

__be64 ibv_get_device_guid(struct ibv_device * device) {
	uhyve_ibv_get_device_guid_t uhyve_args;
	uhyve_args.device = device;

	uhyve_send(UHYVE_PORT_IBV_GET_DEVICE_GUID, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_open_device
 */

typedef struct {
	// Parameters:
	struct ibv_device * device;
	// Return value:
	struct ibv_context * ret;
} __attribute__((packed)) uhyve_ibv_open_device_t;

struct ibv_context * ibv_open_device(struct ibv_device * device) {
	uhyve_ibv_open_device_t uhyve_args;
	uhyve_args.device = device;

	uhyve_send(UHYVE_PORT_IBV_OPEN_DEVICE, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_close_device
 */

typedef struct {
	// Parameters:
	struct ibv_context * context;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_close_device_t;

int ibv_close_device(struct ibv_context * context) {
	uhyve_ibv_close_device_t uhyve_args;
	uhyve_args.context = context;

	uhyve_send(UHYVE_PORT_IBV_CLOSE_DEVICE, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_get_async_event
 */

typedef struct {
	// Parameters:
	struct ibv_context * context;
	struct ibv_async_event * event;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_get_async_event_t;

int ibv_get_async_event(struct ibv_context * context, struct ibv_async_event * event) {
	uhyve_ibv_get_async_event_t uhyve_args;
	uhyve_args.context = context;
	uhyve_args.event = event;

	uhyve_send(UHYVE_PORT_IBV_GET_ASYNC_EVENT, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_ack_async_event
 */

typedef struct {
	// Parameters:
	struct ibv_async_event * event;
} __attribute__((packed)) uhyve_ibv_ack_async_event_t;

void ibv_ack_async_event(struct ibv_async_event * event) {
	uhyve_ibv_ack_async_event_t uhyve_args;
	uhyve_args.event = event;

	uhyve_send(UHYVE_PORT_IBV_ACK_ASYNC_EVENT, (unsigned) virt_to_phys((size_t) &uhyve_args));
}


/*
 * ibv_query_device
 */

typedef struct {
	// Parameters:
	struct ibv_context * context;
	struct ibv_device_attr * device_attr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_query_device_t;

int ibv_query_device(struct ibv_context * context, struct ibv_device_attr * device_attr) {
	uhyve_ibv_query_device_t uhyve_args;
	uhyve_args.context = context;
	uhyve_args.device_attr = (struct ibv_device_attr *) guest_to_host((size_t) device_attr); // !

	uhyve_send(UHYVE_PORT_IBV_QUERY_DEVICE, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_query_gid
 */

typedef struct {
	// Parameters:
	struct ibv_context * context;
	uint8_t port_num;
	int index;
	union ibv_gid * gid;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_query_gid_t;

int ibv_query_gid(struct ibv_context * context, uint8_t port_num, int index, union ibv_gid * gid) {
	uhyve_ibv_query_gid_t uhyve_args;
	uhyve_args.context = context;
	uhyve_args.port_num = port_num;
	uhyve_args.index = index;
	uhyve_args.gid = (union ibv_gid *) guest_to_host((size_t) gid); // !

	uhyve_send(UHYVE_PORT_IBV_QUERY_GID, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_query_pkey
 */

typedef struct {
	// Parameters:
	struct ibv_context * context;
	uint8_t port_num;
	int index;
	__be16 * pkey;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_query_pkey_t;

int ibv_query_pkey(struct ibv_context * context, uint8_t port_num, int index, __be16 * pkey) {
	uhyve_ibv_query_pkey_t uhyve_args;
	uhyve_args.context = context;
	uhyve_args.port_num = port_num;
	uhyve_args.index = index;
	uhyve_args.pkey = (__be16 *) guest_to_host((size_t) pkey); // !

	uhyve_send(UHYVE_PORT_IBV_QUERY_PKEY, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_alloc_pd
 */

typedef struct {
	// Parameters:
	struct ibv_context * context;
	// Return value:
	struct ibv_pd * ret;
} __attribute__((packed)) uhyve_ibv_alloc_pd_t;

struct ibv_pd * ibv_alloc_pd(struct ibv_context * context) {
	uhyve_ibv_alloc_pd_t uhyve_args;
	uhyve_args.context = context;

	uhyve_send(UHYVE_PORT_IBV_ALLOC_PD, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_dealloc_pd
 */

typedef struct {
	// Parameters:
	struct ibv_pd * pd;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_dealloc_pd_t;

int ibv_dealloc_pd(struct ibv_pd * pd) {
	uhyve_ibv_dealloc_pd_t uhyve_args;
	uhyve_args.pd = pd;

	uhyve_send(UHYVE_PORT_IBV_DEALLOC_PD, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_create_flow
 */

typedef struct {
	// Parameters:
	struct ibv_qp * qp;
	struct ibv_flow_attr * flow;
	// Return value:
	struct ibv_flow * ret;
} __attribute__((packed)) uhyve_ibv_create_flow_t;

struct ibv_flow * ibv_create_flow(struct ibv_qp * qp, struct ibv_flow_attr * flow) {
	uhyve_ibv_create_flow_t uhyve_args;
	uhyve_args.qp = qp;
	uhyve_args.flow = flow;

	uhyve_send(UHYVE_PORT_IBV_CREATE_FLOW, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_destroy_flow
 */

typedef struct {
	// Parameters:
	struct ibv_flow * flow_id;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_destroy_flow_t;

int ibv_destroy_flow(struct ibv_flow * flow_id) {
	uhyve_ibv_destroy_flow_t uhyve_args;
	uhyve_args.flow_id = flow_id;

	uhyve_send(UHYVE_PORT_IBV_DESTROY_FLOW, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_open_xrcd
 */

typedef struct {
	// Parameters:
	struct ibv_context * context;
	struct ibv_xrcd_init_attr * xrcd_init_attr;
	// Return value:
	struct ibv_xrcd * ret;
} __attribute__((packed)) uhyve_ibv_open_xrcd_t;

struct ibv_xrcd * ibv_open_xrcd(struct ibv_context * context, struct ibv_xrcd_init_attr * xrcd_init_attr) {
	uhyve_ibv_open_xrcd_t uhyve_args;
	uhyve_args.context = context;
	uhyve_args.xrcd_init_attr = xrcd_init_attr;

	uhyve_send(UHYVE_PORT_IBV_OPEN_XRCD, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_close_xrcd
 */

typedef struct {
	// Parameters:
	struct ibv_xrcd * xrcd;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_close_xrcd_t;

int ibv_close_xrcd(struct ibv_xrcd * xrcd) {
	uhyve_ibv_close_xrcd_t uhyve_args;
	uhyve_args.xrcd = xrcd;

	uhyve_send(UHYVE_PORT_IBV_CLOSE_XRCD, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_reg_mr
 */

typedef struct {
	// Parameters:
	struct ibv_pd * pd;
	void * addr;
	int length;
	int access;
	// Return value:
	struct ibv_mr * ret;
} __attribute__((packed)) uhyve_ibv_reg_mr_t;

struct ibv_mr * ibv_reg_mr(struct ibv_pd * pd, void * addr, int length, int access) {
	uhyve_ibv_reg_mr_t uhyve_args;
	uhyve_args.pd = pd;
	uhyve_args.addr = (void *) guest_to_host((size_t) addr); // !
	uhyve_args.length = length;
	uhyve_args.access = access;

	uhyve_send(UHYVE_PORT_IBV_REG_MR, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_rereg_mr
 */

typedef struct {
	// Parameters:
	struct ibv_mr * mr;
	int flags;
	struct ibv_pd * pd;
	void * addr;
	int length;
	int access;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_rereg_mr_t;

int ibv_rereg_mr(struct ibv_mr * mr, int flags, struct ibv_pd * pd, void * addr, int length, int access) {
	uhyve_ibv_rereg_mr_t uhyve_args;
	uhyve_args.mr = mr;
	uhyve_args.flags = flags;
	uhyve_args.pd = pd;
	uhyve_args.addr = (void *) guest_to_host((size_t) addr); // !
	uhyve_args.length = length;
	uhyve_args.access = access;

	uhyve_send(UHYVE_PORT_IBV_REREG_MR, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_dereg_mr
 */

typedef struct {
	// Parameters:
	struct ibv_mr * mr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_dereg_mr_t;

int ibv_dereg_mr(struct ibv_mr * mr) {
	uhyve_ibv_dereg_mr_t uhyve_args;
	uhyve_args.mr = mr;

	uhyve_send(UHYVE_PORT_IBV_DEREG_MR, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_alloc_mw
 */

typedef struct {
	// Parameters:
	struct ibv_pd * pd;
	enum ibv_mw_type type;
	// Return value:
	struct ibv_mw * ret;
} __attribute__((packed)) uhyve_ibv_alloc_mw_t;

struct ibv_mw * ibv_alloc_mw(struct ibv_pd * pd, enum ibv_mw_type type) {
	uhyve_ibv_alloc_mw_t uhyve_args;
	uhyve_args.pd = pd;
	uhyve_args.type = type;

	uhyve_send(UHYVE_PORT_IBV_ALLOC_MW, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_dealloc_mw
 */

typedef struct {
	// Parameters:
	struct ibv_mw * mw;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_dealloc_mw_t;

int ibv_dealloc_mw(struct ibv_mw * mw) {
	uhyve_ibv_dealloc_mw_t uhyve_args;
	uhyve_args.mw = mw;

	uhyve_send(UHYVE_PORT_IBV_DEALLOC_MW, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_inc_rkey
 */

typedef struct {
	// Parameters:
	uint32_t rkey;
	// Return value:
	uint32_t ret;
} __attribute__((packed)) uhyve_ibv_inc_rkey_t;

uint32_t ibv_inc_rkey(uint32_t rkey) {
	uhyve_ibv_inc_rkey_t uhyve_args;
	uhyve_args.rkey = rkey;

	uhyve_send(UHYVE_PORT_IBV_INC_RKEY, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_bind_mw
 */

typedef struct {
	// Parameters:
	struct ibv_qp * qp;
	struct ibv_mw * mw;
	struct ibv_mw_bind * mw_bind;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_bind_mw_t;

int ibv_bind_mw(struct ibv_qp * qp, struct ibv_mw * mw, struct ibv_mw_bind * mw_bind) {
	uhyve_ibv_bind_mw_t uhyve_args;
	uhyve_args.qp = qp;
	uhyve_args.mw = mw;
	uhyve_args.mw_bind = mw_bind;

	uhyve_send(UHYVE_PORT_IBV_BIND_MW, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_create_comp_channel
 */

typedef struct {
	// Parameters:
	struct ibv_context * context;
	// Return value:
	struct ibv_comp_channel * ret;
} __attribute__((packed)) uhyve_ibv_create_comp_channel_t;

struct ibv_comp_channel * ibv_create_comp_channel(struct ibv_context * context) {
	uhyve_ibv_create_comp_channel_t uhyve_args;
	uhyve_args.context = context;

	uhyve_send(UHYVE_PORT_IBV_CREATE_COMP_CHANNEL, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_destroy_comp_channel
 */

typedef struct {
	// Parameters:
	struct ibv_comp_channel * channel;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_destroy_comp_channel_t;

int ibv_destroy_comp_channel(struct ibv_comp_channel * channel) {
	uhyve_ibv_destroy_comp_channel_t uhyve_args;
	uhyve_args.channel = channel;

	uhyve_send(UHYVE_PORT_IBV_DESTROY_COMP_CHANNEL, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_create_cq
 */

typedef struct {
	// Parameters:
	struct ibv_context * context;
	int cqe;
	void * cq_context;
	struct ibv_comp_channel * channel;
	int comp_vector;
	// Return value:
	struct ibv_cq * ret;
} __attribute__((packed)) uhyve_ibv_create_cq_t;

struct ibv_cq * ibv_create_cq(struct ibv_context * context, int cqe, void * cq_context, struct ibv_comp_channel * channel, int comp_vector) {
	uhyve_ibv_create_cq_t uhyve_args;

	uhyve_args.context     = context;
	uhyve_args.cqe         = cqe;
	uhyve_args.cq_context  = cq_context;
	uhyve_args.channel     = channel;
	uhyve_args.comp_vector = comp_vector;

	uhyve_send(UHYVE_PORT_IBV_CREATE_CQ, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_resize_cq
 */

typedef struct {
	// Parameters:
	struct ibv_cq * cq;
	int cqe;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_resize_cq_t;

int ibv_resize_cq(struct ibv_cq * cq, int cqe) {
	uhyve_ibv_resize_cq_t uhyve_args;
	uhyve_args.cq = cq;
	uhyve_args.cqe = cqe;

	uhyve_send(UHYVE_PORT_IBV_RESIZE_CQ, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_destroy_cq
 */

typedef struct {
	// Parameters:
	struct ibv_cq * cq;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_destroy_cq_t;

int ibv_destroy_cq(struct ibv_cq * cq) {
	uhyve_ibv_destroy_cq_t uhyve_args;
	uhyve_args.cq = cq;

	uhyve_send(UHYVE_PORT_IBV_DESTROY_CQ, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_get_cq_event
 */

typedef struct {
	// Parameters:
	struct ibv_comp_channel * channel;
	struct ibv_cq ** cq;
	void ** cq_context;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_get_cq_event_t;

int ibv_get_cq_event(struct ibv_comp_channel * channel, struct ibv_cq ** cq, void ** cq_context) {
	uhyve_ibv_get_cq_event_t uhyve_args;
	uhyve_args.channel    = channel;
	uhyve_args.cq         = (struct ibv_cq **) guest_to_host((size_t) cq); // !
	uhyve_args.cq_context = (void **) guest_to_host((size_t) cq_context); // !

	uhyve_send(UHYVE_PORT_IBV_GET_CQ_EVENT, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_ack_cq_events
 */

typedef struct {
	// Parameters:
	struct ibv_cq * cq;
	unsigned int nevents;
} __attribute__((packed)) uhyve_ibv_ack_cq_events_t;

void ibv_ack_cq_events(struct ibv_cq * cq, unsigned int nevents) {
	uhyve_ibv_ack_cq_events_t uhyve_args;
	uhyve_args.cq = cq;
	uhyve_args.nevents = nevents;

	uhyve_send(UHYVE_PORT_IBV_ACK_CQ_EVENTS, (unsigned) virt_to_phys((size_t) &uhyve_args));
}


/*
 * ibv_poll_cq
 */

typedef struct {
	// Parameters:
	struct ibv_cq * cq;
	int num_entries;
	struct ibv_wc * wc;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_poll_cq_t;

int ibv_poll_cq(struct ibv_cq * cq, int num_entries, struct ibv_wc * wc) {
	uhyve_ibv_poll_cq_t uhyve_args;

	uhyve_args.cq          = cq;
	uhyve_args.num_entries = num_entries;
	uhyve_args.wc          = (struct ibv_wc *) guest_to_host((size_t) wc); // !

	uhyve_send(UHYVE_PORT_IBV_POLL_CQ, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_req_notify_cq
 */

typedef struct {
	// Parameters:
	struct ibv_cq * cq;
	int solicited_only;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_req_notify_cq_t;

int ibv_req_notify_cq(struct ibv_cq * cq, int solicited_only) {
	uhyve_ibv_req_notify_cq_t uhyve_args;
	uhyve_args.cq = cq;
	uhyve_args.solicited_only = solicited_only;

	uhyve_send(UHYVE_PORT_IBV_REQ_NOTIFY_CQ, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_create_srq
 */

typedef struct {
	// Parameters:
	struct ibv_pd * pd;
	struct ibv_srq_init_attr * srq_init_attr;
	// Return value:
	struct ibv_srq * ret;
} __attribute__((packed)) uhyve_ibv_create_srq_t;

struct ibv_srq * ibv_create_srq(struct ibv_pd * pd, struct ibv_srq_init_attr * srq_init_attr) {
	uhyve_ibv_create_srq_t uhyve_args;
	uhyve_args.pd = pd;
	uhyve_args.srq_init_attr = srq_init_attr;

	uhyve_send(UHYVE_PORT_IBV_CREATE_SRQ, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_create_srq_ex
 */

typedef struct {
	// Parameters:
	struct ibv_context * context;
	struct ibv_srq_init_attr_ex * srq_init_attr_ex;
	// Return value:
	struct ibv_srq * ret;
} __attribute__((packed)) uhyve_ibv_create_srq_ex_t;

struct ibv_srq * ibv_create_srq_ex(struct ibv_context * context, struct ibv_srq_init_attr_ex * srq_init_attr_ex) {
	uhyve_ibv_create_srq_ex_t uhyve_args;
	uhyve_args.context = context;
	uhyve_args.srq_init_attr_ex = srq_init_attr_ex;

	uhyve_send(UHYVE_PORT_IBV_CREATE_SRQ_EX, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_modify_srq
 */

typedef struct {
	// Parameters:
	struct ibv_srq * srq;
	struct ibv_srq_attr * srq_attr;
	int srq_attr_mask;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_modify_srq_t;

int ibv_modify_srq(struct ibv_srq * srq, struct ibv_srq_attr * srq_attr, int srq_attr_mask) {
	uhyve_ibv_modify_srq_t uhyve_args;
	uhyve_args.srq = srq;
	uhyve_args.srq_attr = srq_attr;
	uhyve_args.srq_attr_mask = srq_attr_mask;

	uhyve_send(UHYVE_PORT_IBV_MODIFY_SRQ, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_query_srq
 */

typedef struct {
	// Parameters:
	struct ibv_srq * srq;
	struct ibv_srq_attr * srq_attr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_query_srq_t;

int ibv_query_srq(struct ibv_srq * srq, struct ibv_srq_attr * srq_attr) {
	uhyve_ibv_query_srq_t uhyve_args;
	uhyve_args.srq = srq;
	uhyve_args.srq_attr = srq_attr;

	uhyve_send(UHYVE_PORT_IBV_QUERY_SRQ, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_get_srq_num
 */

typedef struct {
	// Parameters:
	struct ibv_srq * srq;
	uint32_t * srq_num;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_get_srq_num_t;

int ibv_get_srq_num(struct ibv_srq * srq, uint32_t * srq_num) {
	uhyve_ibv_get_srq_num_t uhyve_args;
	uhyve_args.srq = srq;
	uhyve_args.srq_num = srq_num;

	uhyve_send(UHYVE_PORT_IBV_GET_SRQ_NUM, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_destroy_srq
 */

typedef struct {
	// Parameters:
	struct ibv_srq * srq;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_destroy_srq_t;

int ibv_destroy_srq(struct ibv_srq * srq) {
	uhyve_ibv_destroy_srq_t uhyve_args;
	uhyve_args.srq = srq;

	uhyve_send(UHYVE_PORT_IBV_DESTROY_SRQ, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_post_srq_recv
 */

typedef struct {
	// Parameters:
	struct ibv_srq * srq;
	struct ibv_recv_wr * recv_wr;
	struct ibv_recv_wr ** bad_recv_wr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_post_srq_recv_t;

int ibv_post_srq_recv(struct ibv_srq * srq, struct ibv_recv_wr * recv_wr, struct ibv_recv_wr ** bad_recv_wr) {
	uhyve_ibv_post_srq_recv_t uhyve_args;
	uhyve_args.srq = srq;
	uhyve_args.recv_wr = recv_wr;
	// TODO: Take care of ** parameter.

	uhyve_send(UHYVE_PORT_IBV_POST_SRQ_RECV, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_create_qp
 */

typedef struct {
	// Parameters:
	struct ibv_pd * pd;
	struct ibv_qp_init_attr * qp_init_attr;
	// Return value:
	struct ibv_qp * ret;
} __attribute__((packed)) uhyve_ibv_create_qp_t;

struct ibv_qp * ibv_create_qp(struct ibv_pd * pd, struct ibv_qp_init_attr * qp_init_attr) {
	uhyve_ibv_create_qp_t uhyve_args;
	uhyve_args.pd           = pd;
	uhyve_args.qp_init_attr = (struct ibv_qp_init_attr *) guest_to_host((size_t) qp_init_attr); // !

	uhyve_send(UHYVE_PORT_IBV_CREATE_QP, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_create_qp_ex
 */

typedef struct {
	// Parameters:
	struct ibv_context * context;
	struct ibv_qp_init_attr_ex * qp_init_attr_ex;
	// Return value:
	struct ibv_qp * ret;
} __attribute__((packed)) uhyve_ibv_create_qp_ex_t;

struct ibv_qp * ibv_create_qp_ex(struct ibv_context * context, struct ibv_qp_init_attr_ex * qp_init_attr_ex) {
	uhyve_ibv_create_qp_ex_t uhyve_args;
	uhyve_args.context = context;
	uhyve_args.qp_init_attr_ex = qp_init_attr_ex;

	uhyve_send(UHYVE_PORT_IBV_CREATE_QP_EX, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_query_device_ex
 */

typedef struct {
	// Parameters:
	struct ibv_context * context;
	const struct ibv_query_device_ex_input * input;
	struct ibv_device_attr_ex * attr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_query_device_ex_t;

int ibv_query_device_ex(struct ibv_context * context, const struct ibv_query_device_ex_input * input, struct ibv_device_attr_ex * attr) {
	uhyve_ibv_query_device_ex_t uhyve_args;
	uhyve_args.context = context;
	uhyve_args.input = input;
	uhyve_args.attr = attr;

	uhyve_send(UHYVE_PORT_IBV_QUERY_DEVICE_EX, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_open_qp
 */

typedef struct {
	// Parameters:
	struct ibv_context * context;
	struct ibv_qp_open_attr * qp_open_attr;
	// Return value:
	struct ibv_qp * ret;
} __attribute__((packed)) uhyve_ibv_open_qp_t;

struct ibv_qp * ibv_open_qp(struct ibv_context * context, struct ibv_qp_open_attr * qp_open_attr) {
	uhyve_ibv_open_qp_t uhyve_args;
	uhyve_args.context = context;
	uhyve_args.qp_open_attr = qp_open_attr;

	uhyve_send(UHYVE_PORT_IBV_OPEN_QP, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_modify_qp
 */

typedef struct {
	// Parameters:
	struct ibv_qp * qp;
	struct ibv_qp_attr * attr;
	int attr_mask;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_modify_qp_t;

int ibv_modify_qp(struct ibv_qp * qp, struct ibv_qp_attr * attr, int attr_mask) {
	uhyve_ibv_modify_qp_t uhyve_args;
	uhyve_args.qp        = qp;
	uhyve_args.attr      = (struct ibv_qp_attr *) guest_to_host((size_t) attr); // !
	uhyve_args.attr_mask = attr_mask;

	uhyve_send(UHYVE_PORT_IBV_MODIFY_QP, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_query_qp
 */

typedef struct {
	// Parameters:
	struct ibv_qp * qp;
	struct ibv_qp_attr * attr;
	int attr_mask;
	struct ibv_qp_init_attr * init_attr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_query_qp_t;

int ibv_query_qp(struct ibv_qp * qp, struct ibv_qp_attr * attr, int attr_mask, struct ibv_qp_init_attr * init_attr) {
	uhyve_ibv_query_qp_t uhyve_args;

	uhyve_args.qp        = qp;
	uhyve_args.attr      = (struct ibv_qp_attr *) guest_to_host((size_t) attr); // !
	uhyve_args.attr_mask = attr_mask;
	uhyve_args.init_attr = (struct ibv_qp_init_attr *) guest_to_host((size_t) init_attr); // !

	uhyve_send(UHYVE_PORT_IBV_QUERY_QP, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_destroy_qp
 */

typedef struct {
	// Parameters:
	struct ibv_qp * qp;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_destroy_qp_t;

int ibv_destroy_qp(struct ibv_qp * qp) {
	uhyve_ibv_destroy_qp_t uhyve_args;
	uhyve_args.qp = qp;

	uhyve_send(UHYVE_PORT_IBV_DESTROY_QP, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_post_send
 */

typedef struct {
	// Parameters:
	struct ibv_qp * qp;
	struct ibv_send_wr * wr;
	struct ibv_send_wr ** bad_wr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_post_send_t;

int ibv_post_send(struct ibv_qp * qp, struct ibv_send_wr * wr, struct ibv_send_wr ** bad_wr) {
	uhyve_ibv_post_send_t uhyve_args;
	uhyve_args.qp = qp;
	uhyve_args.wr = guest_to_host_ibv_send_wr(wr); // !
	uhyve_args.bad_wr = (struct ibv_send_wr **) guest_to_host((size_t) bad_wr); // will be written to

	uhyve_send(UHYVE_PORT_IBV_POST_SEND, (unsigned) virt_to_phys((size_t) &uhyve_args));

	// TODO: Do we want to convert bad_wr's content back to guest memory?

	return uhyve_args.ret;
}


/*
 * ibv_post_recv
 */

typedef struct {
	// Parameters:
	struct ibv_qp * qp;
	struct ibv_recv_wr * wr;
	struct ibv_recv_wr ** bad_wr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_post_recv_t;

int ibv_post_recv(struct ibv_qp * qp, struct ibv_recv_wr * wr, struct ibv_recv_wr ** bad_wr) {
	/* LOG_INFO("KERNEL: ibv_post_recv()\n"); */
	uhyve_ibv_post_recv_t uhyve_args;

	uhyve_args.qp     = qp;
	uhyve_args.wr     = guest_to_host_ibv_recv_wr(wr);
	uhyve_args.bad_wr = (struct ibv_recv_wr **) guest_to_host((size_t) bad_wr); // will be written to

	uhyve_send(UHYVE_PORT_IBV_POST_RECV, (unsigned) virt_to_phys((size_t) &uhyve_args));

	/* host_to_guest_ibv_recv_wr(wr, GUEST); */ // TODO: add this back in
	/* LOG_INFO("KERNEL: ibv_post_recv()\n"); */

	// TODO: Do we want to convert bad_wr's content back to guest memory?

	return uhyve_args.ret;
}


/*
 * ibv_create_ah
 */

typedef struct {
	// Parameters:
	struct ibv_pd * pd;
	struct ibv_ah_attr * attr;
	// Return value:
	struct ibv_ah * ret;
} __attribute__((packed)) uhyve_ibv_create_ah_t;

struct ibv_ah * ibv_create_ah(struct ibv_pd * pd, struct ibv_ah_attr * attr) {
	uhyve_ibv_create_ah_t uhyve_args;
	uhyve_args.pd   = pd;
	uhyve_args.attr = (struct ibv_ah_attr *) guest_to_host((size_t) attr); // !

	uhyve_send(UHYVE_PORT_IBV_CREATE_AH, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_init_ah_from_wc
 */

typedef struct {
	// Parameters:
	struct ibv_context * context;
	uint8_t port_num;
	struct ibv_wc * wc;
	struct ibv_grh * grh;
	struct ibv_ah_attr * ah_attr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_init_ah_from_wc_t;

int ibv_init_ah_from_wc(struct ibv_context * context, uint8_t port_num, struct ibv_wc * wc, struct ibv_grh * grh, struct ibv_ah_attr * ah_attr) {
	uhyve_ibv_init_ah_from_wc_t uhyve_args;
	uhyve_args.context = context;
	uhyve_args.port_num = port_num;
	uhyve_args.wc = wc;
	uhyve_args.grh = grh;
	uhyve_args.ah_attr = ah_attr;

	uhyve_send(UHYVE_PORT_IBV_INIT_AH_FROM_WC, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_create_ah_from_wc
 */

typedef struct {
	// Parameters:
	struct ibv_pd * pd;
	struct ibv_wc * wc;
	struct ibv_grh * grh;
	uint8_t port_num;
	// Return value:
	struct ibv_ah * ret;
} __attribute__((packed)) uhyve_ibv_create_ah_from_wc_t;

struct ibv_ah * ibv_create_ah_from_wc(struct ibv_pd * pd, struct ibv_wc * wc, struct ibv_grh * grh, uint8_t port_num) {
	uhyve_ibv_create_ah_from_wc_t uhyve_args;
	uhyve_args.pd = pd;
	uhyve_args.wc = wc;
	uhyve_args.grh = grh;
	uhyve_args.port_num = port_num;

	uhyve_send(UHYVE_PORT_IBV_CREATE_AH_FROM_WC, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_destroy_ah
 */

typedef struct {
	// Parameters:
	struct ibv_ah * ah;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_destroy_ah_t;

int ibv_destroy_ah(struct ibv_ah * ah) {
	uhyve_ibv_destroy_ah_t uhyve_args;
	uhyve_args.ah = ah;

	uhyve_send(UHYVE_PORT_IBV_DESTROY_AH, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_attach_mcast
 */

typedef struct {
	// Parameters:
	struct ibv_qp * qp;
	const union ibv_gid * gid;
	uint16_t lid;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_attach_mcast_t;

int ibv_attach_mcast(struct ibv_qp * qp, const union ibv_gid * gid, uint16_t lid) {
	uhyve_ibv_attach_mcast_t uhyve_args;
	uhyve_args.qp = qp;
	uhyve_args.gid = gid;
	uhyve_args.lid = lid;

	uhyve_send(UHYVE_PORT_IBV_ATTACH_MCAST, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_detach_mcast
 */

typedef struct {
	// Parameters:
	struct ibv_qp * qp;
	const union ibv_gid * gid;
	uint16_t lid;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_detach_mcast_t;

int ibv_detach_mcast(struct ibv_qp * qp, const union ibv_gid * gid, uint16_t lid) {
	uhyve_ibv_detach_mcast_t uhyve_args;
	uhyve_args.qp = qp;
	uhyve_args.gid = gid;
	uhyve_args.lid = lid;

	uhyve_send(UHYVE_PORT_IBV_DETACH_MCAST, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_fork_init
 */

typedef struct {
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_fork_init_t;

int ibv_fork_init( ) {
	uhyve_ibv_fork_init_t uhyve_args;

	uhyve_send(UHYVE_PORT_IBV_FORK_INIT, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_node_type_str
 */

typedef struct {
	// Parameters:
	enum ibv_node_type node_type;
	// Return value:
	char * ret;
} __attribute__((packed)) uhyve_ibv_node_type_str_t;

const char * ibv_node_type_str(enum ibv_node_type node_type) {
	uhyve_ibv_node_type_str_t uhyve_args;
	uhyve_args.node_type = node_type;

	uhyve_args.ret = kmalloc(MAX_CHAR_ARR_LENGTH); // !
	uhyve_send(UHYVE_PORT_IBV_NODE_TYPE_STR, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_port_state_str
 */

typedef struct {
	// Parameters:
	enum ibv_port_state port_state;
	// Return value:
	char * ret;
} __attribute__((packed)) uhyve_ibv_port_state_str_t;

const char * ibv_port_state_str(enum ibv_port_state port_state) {
	uhyve_ibv_port_state_str_t uhyve_args;
	uhyve_args.port_state = port_state;

	uhyve_args.ret = kmalloc(MAX_CHAR_ARR_LENGTH); // !
	uhyve_send(UHYVE_PORT_IBV_PORT_STATE_STR, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_event_type_str
 */

typedef struct {
	// Parameters:
	enum ibv_event_type event;
	// Return value:
	char * ret;
} __attribute__((packed)) uhyve_ibv_event_type_str_t;

const char * ibv_event_type_str(enum ibv_event_type event) {
	uhyve_ibv_event_type_str_t uhyve_args;
	uhyve_args.event = event;

	uhyve_args.ret = kmalloc(MAX_CHAR_ARR_LENGTH); // !
	uhyve_send(UHYVE_PORT_IBV_EVENT_TYPE_STR, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_is_qpt_supported
 */

typedef struct {
	// Parameters:
	uint32_t caps;
	enum ibv_qp_type qpt;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_is_qpt_supported_t;

int ibv_is_qpt_supported(uint32_t caps, enum ibv_qp_type qpt) {
	uhyve_ibv_is_qpt_supported_t uhyve_args;
	uhyve_args.caps = caps;
	uhyve_args.qpt = qpt;

	uhyve_send(UHYVE_PORT_IBV_IS_QPT_SUPPORTED, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_get_mr_lkey
 */

typedef struct {
	// Parameters:
	struct ibv_mr * mr;
	// Return value:
	uint32_t ret;
} __attribute__((packed)) uhyve_ibv_get_mr_lkey_t;

uint32_t ibv_get_mr_lkey(struct ibv_mr * mr) {
	uhyve_ibv_get_mr_lkey_t uhyve_args;
	uhyve_args.mr = mr;

	uhyve_send(UHYVE_PORT_IBV_GET_MR_LKEY, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_get_qp_num
 */

typedef struct {
	// Parameters:
	struct ibv_qp * qp;
	// Return value:
	uint32_t ret;
} __attribute__((packed)) uhyve_ibv_get_qp_num_t;

uint32_t ibv_get_qp_num(struct ibv_qp * qp) {
	uhyve_ibv_get_qp_num_t uhyve_args;
	uhyve_args.qp = qp;

	uhyve_send(UHYVE_PORT_IBV_GET_QP_NUM, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}
