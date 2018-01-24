/* Copyright (c) 2017, RWTH Aachen University
 * Author(s): Annika Wierichs <annika.wierichs@rwth-aachen.de>
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose with or without fee is hereby granted, provided
 * that the above copyright notice and this permission notice appear
 * in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef UHYVE_IBV_H
#define UHYVE_IBV_H

#include <infiniband/verbs.h>
#include <linux/kvm.h>
#include <stdbool.h>

extern bool use_ib_mem_pool;

typedef enum {
	UHYVE_PORT_SET_IB_POOL_ADDR             = 0x60F,
	UHYVE_PORT_IBV_WC_STATUS_STR            = 0x610,
	UHYVE_PORT_IBV_RATE_TO_MULT             = 0x611,
	UHYVE_PORT_MULT_TO_IBV_RATE             = 0x612,
	UHYVE_PORT_IBV_RATE_TO_MBPS             = 0x613,
	UHYVE_PORT_MBPS_TO_IBV_RATE             = 0x614,
	UHYVE_PORT_IBV_CQ_EX_TO_CQ              = 0x615,
	UHYVE_PORT_IBV_START_POLL               = 0x616,
	UHYVE_PORT_IBV_NEXT_POLL                = 0x617,
	UHYVE_PORT_IBV_END_POLL                 = 0x618,
	UHYVE_PORT_IBV_WC_READ_OPCODE           = 0x619,
	UHYVE_PORT_IBV_WC_READ_VENDOR_ERR       = 0x61A,
	UHYVE_PORT_IBV_WC_READ_BYTE_LEN         = 0x61B,
	UHYVE_PORT_IBV_WC_READ_IMM_DATA         = 0x61C,
	UHYVE_PORT_IBV_WC_READ_INVALIDATED_RKEY = 0x61D,
	UHYVE_PORT_IBV_WC_READ_QP_NUM           = 0x61E,
	UHYVE_PORT_IBV_WC_READ_SRC_QP           = 0x61F,
	UHYVE_PORT_IBV_WC_READ_WC_FLAGS         = 0x620,
	UHYVE_PORT_IBV_WC_READ_SLID             = 0x621,
	UHYVE_PORT_IBV_WC_READ_SL               = 0x622,
	UHYVE_PORT_IBV_WC_READ_DLID_PATH_BITS   = 0x623,
	UHYVE_PORT_IBV_WC_READ_COMPLETION_TS    = 0x624,
	UHYVE_PORT_IBV_WC_READ_CVLAN            = 0x625,
	UHYVE_PORT_IBV_WC_READ_FLOW_TAG         = 0x626,
	UHYVE_PORT_IBV_POST_WQ_RECV             = 0x627,
	UHYVE_PORT_IBV_GET_DEVICE_LIST          = 0x628,
	UHYVE_PORT_IBV_FREE_DEVICE_LIST         = 0x629,
	UHYVE_PORT_IBV_GET_DEVICE_NAME          = 0x62A,
	UHYVE_PORT_IBV_GET_DEVICE_GUID          = 0x62B,
	UHYVE_PORT_IBV_OPEN_DEVICE              = 0x62C,
	UHYVE_PORT_IBV_CLOSE_DEVICE             = 0x62D,
	UHYVE_PORT_IBV_GET_ASYNC_EVENT          = 0x62E,
	UHYVE_PORT_IBV_ACK_ASYNC_EVENT          = 0x62F,
	UHYVE_PORT_IBV_QUERY_DEVICE             = 0x630,
	UHYVE_PORT_IBV_QUERY_PORT               = 0x631,
	UHYVE_PORT_IBV_QUERY_GID                = 0x632,
	UHYVE_PORT_IBV_QUERY_PKEY               = 0x633,
	UHYVE_PORT_IBV_ALLOC_PD                 = 0x634,
	UHYVE_PORT_IBV_DEALLOC_PD               = 0x635,
	UHYVE_PORT_IBV_CREATE_FLOW              = 0x636,
	UHYVE_PORT_IBV_DESTROY_FLOW             = 0x637,
	UHYVE_PORT_IBV_OPEN_XRCD                = 0x638,
	UHYVE_PORT_IBV_CLOSE_XRCD               = 0x639,
	UHYVE_PORT_IBV_REG_MR                   = 0x63A,
	UHYVE_PORT_IBV_REREG_MR                 = 0x63B,
	UHYVE_PORT_IBV_DEREG_MR                 = 0x63C,
	UHYVE_PORT_IBV_ALLOC_MW                 = 0x63D,
	UHYVE_PORT_IBV_DEALLOC_MW               = 0x63E,
	UHYVE_PORT_IBV_INC_RKEY                 = 0x63F,
	UHYVE_PORT_IBV_BIND_MW                  = 0x640,
	UHYVE_PORT_IBV_CREATE_COMP_CHANNEL      = 0x641,
	UHYVE_PORT_IBV_DESTROY_COMP_CHANNEL     = 0x642,
	UHYVE_PORT_IBV_CREATE_CQ                = 0x643,
	UHYVE_PORT_IBV_CREATE_CQ_EX             = 0x644,
	UHYVE_PORT_IBV_RESIZE_CQ                = 0x645,
	UHYVE_PORT_IBV_DESTROY_CQ               = 0x646,
	UHYVE_PORT_IBV_GET_CQ_EVENT             = 0x647,
	UHYVE_PORT_IBV_ACK_CQ_EVENTS            = 0x648,
	UHYVE_PORT_IBV_POLL_CQ                  = 0x649,
	UHYVE_PORT_IBV_REQ_NOTIFY_CQ            = 0x64A,
	UHYVE_PORT_IBV_CREATE_SRQ               = 0x64B,
	UHYVE_PORT_IBV_CREATE_SRQ_EX            = 0x64C,
	UHYVE_PORT_IBV_MODIFY_SRQ               = 0x64D,
	UHYVE_PORT_IBV_QUERY_SRQ                = 0x64E,
	UHYVE_PORT_IBV_GET_SRQ_NUM              = 0x64F,
	UHYVE_PORT_IBV_DESTROY_SRQ              = 0x650,
	UHYVE_PORT_IBV_POST_SRQ_RECV            = 0x651,
	UHYVE_PORT_IBV_CREATE_QP                = 0x652,
	UHYVE_PORT_IBV_CREATE_QP_EX             = 0x653,
	UHYVE_PORT_IBV_QUERY_RT_VALUES_EX       = 0x654,
	UHYVE_PORT_IBV_QUERY_DEVICE_EX          = 0x655,
	UHYVE_PORT_IBV_OPEN_QP                  = 0x656,
	UHYVE_PORT_IBV_MODIFY_QP                = 0x657,
	UHYVE_PORT_IBV_QUERY_QP                 = 0x658,
	UHYVE_PORT_IBV_DESTROY_QP               = 0x659,
	UHYVE_PORT_IBV_CREATE_WQ                = 0x65A,
	UHYVE_PORT_IBV_MODIFY_WQ                = 0x65B,
	UHYVE_PORT_IBV_DESTROY_WQ               = 0x65C,
	UHYVE_PORT_IBV_CREATE_RWQ_IND_TABLE     = 0x65D,
	UHYVE_PORT_IBV_DESTROY_RWQ_IND_TABLE    = 0x65E,
	UHYVE_PORT_IBV_POST_SEND                = 0x65F,
	UHYVE_PORT_IBV_POST_RECV                = 0x660,
	UHYVE_PORT_IBV_CREATE_AH                = 0x661,
	UHYVE_PORT_IBV_INIT_AH_FROM_WC          = 0x662,
	UHYVE_PORT_IBV_CREATE_AH_FROM_WC        = 0x663,
	UHYVE_PORT_IBV_DESTROY_AH               = 0x664,
	UHYVE_PORT_IBV_ATTACH_MCAST             = 0x665,
	UHYVE_PORT_IBV_DETACH_MCAST             = 0x666,
	UHYVE_PORT_IBV_FORK_INIT                = 0x667,
	UHYVE_PORT_IBV_NODE_TYPE_STR            = 0x668,
	UHYVE_PORT_IBV_PORT_STATE_STR           = 0x669,
	UHYVE_PORT_IBV_EVENT_TYPE_STR           = 0x66A,
	// UHYVE_PORT_IBV_RESOLVE_ETH_L2_FROM_GID  = 0x66B,
	UHYVE_PORT_IBV_IS_QPT_SUPPORTED         = 0x66C,

	UHYVE_PORT_KERNEL_IBV_LOG               = 0x66F,
} uhyve_ibv_t;


typedef struct {
	// Parameters:
	enum ibv_wc_status status;
	// Return value:
	const char * ret;
} __attribute__((packed)) uhyve_ibv_wc_status_str_t;

typedef struct {
	// Parameters:
	enum ibv_rate rate;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_rate_to_mult_t;

typedef struct {
	// Parameters:
	int mult;
	// Return value:
	enum ibv_rate ret;
} __attribute__((packed)) uhyve_mult_to_ibv_rate_t;

typedef struct {
	// Parameters:
	enum ibv_rate rate;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_rate_to_mbps_t;

typedef struct {
	// Parameters:
	int mbps;
	// Return value:
	enum ibv_rate ret;
} __attribute__((packed)) uhyve_mbps_to_ibv_rate_t;

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	struct ibv_cq * ret;
} __attribute__((packed)) uhyve_ibv_cq_ex_to_cq_t;

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	struct ibv_poll_cq_attr * attr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_start_poll_t;

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_next_poll_t;

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
} __attribute__((packed)) uhyve_ibv_end_poll_t;

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	enum ibv_wc_opcode ret;
} __attribute__((packed)) uhyve_ibv_wc_read_opcode_t;

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	uint32_t ret;
} __attribute__((packed)) uhyve_ibv_wc_read_vendor_err_t;

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	uint32_t ret;
} __attribute__((packed)) uhyve_ibv_wc_read_byte_len_t;

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	__be32 ret;
} __attribute__((packed)) uhyve_ibv_wc_read_imm_data_t;

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	uint32_t ret;
} __attribute__((packed)) uhyve_ibv_wc_read_invalidated_rkey_t;

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	uint32_t ret;
} __attribute__((packed)) uhyve_ibv_wc_read_qp_num_t;

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	uint32_t ret;
} __attribute__((packed)) uhyve_ibv_wc_read_src_qp_t;

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_wc_read_wc_flags_t;

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	uint32_t ret;
} __attribute__((packed)) uhyve_ibv_wc_read_slid_t;

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	uint8_t ret;
} __attribute__((packed)) uhyve_ibv_wc_read_sl_t;

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	uint8_t ret;
} __attribute__((packed)) uhyve_ibv_wc_read_dlid_path_bits_t;

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	uint64_t ret;
} __attribute__((packed)) uhyve_ibv_wc_read_completion_ts_t;

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	uint16_t ret;
} __attribute__((packed)) uhyve_ibv_wc_read_cvlan_t;

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	uint32_t ret;
} __attribute__((packed)) uhyve_ibv_wc_read_flow_tag_t;

typedef struct {
	// Parameters:
	struct ibv_wq * wq;
	struct ibv_recv_wr * recv_wr;
	struct ibv_recv_wr ** bad_recv_wr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_post_wq_recv_t;

typedef struct {
	// Parameters:
	int * num_devices;
	// Return value:
	struct ibv_device ** ret;
} __attribute__((packed)) uhyve_ibv_get_device_list_t;

typedef struct {
	// Parameters:
	struct ibv_device ** list;
} __attribute__((packed)) uhyve_ibv_free_device_list_t;

typedef struct {
	// Parameters:
	struct ibv_device * device;
	// Return value:
	const char * ret;
} __attribute__((packed)) uhyve_ibv_get_device_name_t;

typedef struct {
	// Parameters:
	struct ibv_device * device;
	// Return value:
	__be64 ret;
} __attribute__((packed)) uhyve_ibv_get_device_guid_t;

typedef struct {
	// Parameters:
	struct ibv_device * device;
	// Return value:
	struct ibv_context * ret;
} __attribute__((packed)) uhyve_ibv_open_device_t;

typedef struct {
	// Parameters:
	struct ibv_context * context;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_close_device_t;

typedef struct {
	// Parameters:
	struct ibv_context * context;
	struct ibv_async_event * event;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_get_async_event_t;

typedef struct {
	// Parameters:
	struct ibv_async_event * event;
} __attribute__((packed)) uhyve_ibv_ack_async_event_t;

typedef struct {
	// Parameters:
	struct ibv_context * context;
	struct ibv_device_attr * device_attr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_query_device_t;

typedef struct {
	// Parameters:
	struct ibv_context * context;
	uint8_t port_num;
	struct ibv_port_attr * port_attr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_query_port_t;

typedef struct {
	// Parameters:
	struct ibv_context * context;
	uint8_t port_num;
	int index;
	union ibv_gid * gid;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_query_gid_t;

typedef struct {
	// Parameters:
	struct ibv_context * context;
	uint8_t port_num;
	int index;
	__be16 * pkey;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_query_pkey_t;

typedef struct {
	// Parameters:
	struct ibv_context * context;
	// Return value:
	struct ibv_pd * ret;
} __attribute__((packed)) uhyve_ibv_alloc_pd_t;

typedef struct {
	// Parameters:
	struct ibv_pd * pd;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_dealloc_pd_t;

typedef struct {
	// Parameters:
	struct ibv_qp * qp;
	struct ibv_flow_attr * flow;
	// Return value:
	struct ibv_flow * ret;
} __attribute__((packed)) uhyve_ibv_create_flow_t;

typedef struct {
	// Parameters:
	struct ibv_flow * flow_id;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_destroy_flow_t;

typedef struct {
	// Parameters:
	struct ibv_context * context;
	struct ibv_xrcd_init_attr * xrcd_init_attr;
	// Return value:
	struct ibv_xrcd * ret;
} __attribute__((packed)) uhyve_ibv_open_xrcd_t;

typedef struct {
	// Parameters:
	struct ibv_xrcd * xrcd;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_close_xrcd_t;

typedef struct {
	// Parameters:
	struct ibv_pd * pd;
	void * addr;
	int length;
	int access;
	// Return value:
	struct ibv_mr * ret;
} __attribute__((packed)) uhyve_ibv_reg_mr_t;

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

typedef struct {
	// Parameters:
	struct ibv_mr * mr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_dereg_mr_t;

typedef struct {
	// Parameters:
	struct ibv_pd * pd;
	enum ibv_mw_type type;
	// Return value:
	struct ibv_mw * ret;
} __attribute__((packed)) uhyve_ibv_alloc_mw_t;

typedef struct {
	// Parameters:
	struct ibv_mw * mw;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_dealloc_mw_t;

typedef struct {
	// Parameters:
	uint32_t rkey;
	// Return value:
	uint32_t ret;
} __attribute__((packed)) uhyve_ibv_inc_rkey_t;

typedef struct {
	// Parameters:
	struct ibv_qp * qp;
	struct ibv_mw * mw;
	struct ibv_mw_bind * mw_bind;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_bind_mw_t;

typedef struct {
	// Parameters:
	struct ibv_context * context;
	// Return value:
	struct ibv_comp_channel * ret;
} __attribute__((packed)) uhyve_ibv_create_comp_channel_t;

typedef struct {
	// Parameters:
	struct ibv_comp_channel * channel;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_destroy_comp_channel_t;

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

typedef struct {
	// Parameters:
	struct ibv_context * context;
	struct ibv_cq_init_attr_ex * cq_attr;
	// Return value:
	struct ibv_cq_ex * ret;
} __attribute__((packed)) uhyve_ibv_create_cq_ex_t;

typedef struct {
	// Parameters:
	struct ibv_cq * cq;
	int cqe;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_resize_cq_t;

typedef struct {
	// Parameters:
	struct ibv_cq * cq;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_destroy_cq_t;

typedef struct {
	// Parameters:
	struct ibv_comp_channel * channel;
	struct ibv_cq ** cq;
	void ** cq_context;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_get_cq_event_t;

typedef struct {
	// Parameters:
	struct ibv_cq * cq;
	unsigned int nevents;
} __attribute__((packed)) uhyve_ibv_ack_cq_events_t;

typedef struct {
	// Parameters:
	struct ibv_cq * cq;
	int num_entries;
	struct ibv_wc * wc;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_poll_cq_t;

typedef struct {
	// Parameters:
	struct ibv_cq * cq;
	int solicited_only;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_req_notify_cq_t;

typedef struct {
	// Parameters:
	struct ibv_pd * pd;
	struct ibv_srq_init_attr * srq_init_attr;
	// Return value:
	struct ibv_srq * ret;
} __attribute__((packed)) uhyve_ibv_create_srq_t;

typedef struct {
	// Parameters:
	struct ibv_context * context;
	struct ibv_srq_init_attr_ex * srq_init_attr_ex;
	// Return value:
	struct ibv_srq * ret;
} __attribute__((packed)) uhyve_ibv_create_srq_ex_t;

typedef struct {
	// Parameters:
	struct ibv_srq * srq;
	struct ibv_srq_attr * srq_attr;
	int srq_attr_mask;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_modify_srq_t;

typedef struct {
	// Parameters:
	struct ibv_srq * srq;
	struct ibv_srq_attr * srq_attr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_query_srq_t;

typedef struct {
	// Parameters:
	struct ibv_srq * srq;
	uint32_t * srq_num;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_get_srq_num_t;

typedef struct {
	// Parameters:
	struct ibv_srq * srq;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_destroy_srq_t;

typedef struct {
	// Parameters:
	struct ibv_srq * srq;
	struct ibv_recv_wr * recv_wr;
	struct ibv_recv_wr ** bad_recv_wr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_post_srq_recv_t;

typedef struct {
	// Parameters:
	struct ibv_pd * pd;
	struct ibv_qp_init_attr * qp_init_attr;
	// Return value:
	struct ibv_qp * ret;
} __attribute__((packed)) uhyve_ibv_create_qp_t;

typedef struct {
	// Parameters:
	struct ibv_context * context;
	struct ibv_qp_init_attr_ex * qp_init_attr_ex;
	// Return value:
	struct ibv_qp * ret;
} __attribute__((packed)) uhyve_ibv_create_qp_ex_t;

typedef struct {
	// Parameters:
	struct ibv_context * context;
	struct ibv_values_ex * values;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_query_rt_values_ex_t;

typedef struct {
	// Parameters:
	struct ibv_context * context;
	const struct ibv_query_device_ex_input * input;
	struct ibv_device_attr_ex * attr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_query_device_ex_t;

typedef struct {
	// Parameters:
	struct ibv_context * context;
	struct ibv_qp_open_attr * qp_open_attr;
	// Return value:
	struct ibv_qp * ret;
} __attribute__((packed)) uhyve_ibv_open_qp_t;

typedef struct {
	// Parameters:
	struct ibv_qp * qp;
	struct ibv_qp_attr * attr;
	int attr_mask;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_modify_qp_t;

typedef struct {
	// Parameters:
	struct ibv_qp * qp;
	struct ibv_qp_attr * attr;
	int attr_mask;
	struct ibv_qp_init_attr * init_attr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_query_qp_t;

typedef struct {
	// Parameters:
	struct ibv_qp * qp;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_destroy_qp_t;

typedef struct {
	// Parameters:
	struct ibv_context * context;
	struct ibv_wq_init_attr * wq_init_attr;
	// Return value:
	struct ibv_wq * ret;
} __attribute__((packed)) uhyve_ibv_create_wq_t;

typedef struct {
	// Parameters:
	struct ibv_wq * wq;
	struct ibv_wq_attr * wq_attr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_modify_wq_t;

typedef struct {
	// Parameters:
	struct ibv_wq * wq;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_destroy_wq_t;

typedef struct {
	// Parameters:
	struct ibv_context * context;
	struct ibv_rwq_ind_table_init_attr * init_attr;
	// Return value:
	struct ibv_rwq_ind_table * ret;
} __attribute__((packed)) uhyve_ibv_create_rwq_ind_table_t;

typedef struct {
	// Parameters:
	struct ibv_rwq_ind_table * rwq_ind_table;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_destroy_rwq_ind_table_t;

typedef struct {
	// Parameters:
	struct ibv_qp * qp;
	struct ibv_send_wr * wr;
	struct ibv_send_wr ** bad_wr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_post_send_t;

typedef struct {
	// Parameters:
	struct ibv_qp * qp;
	struct ibv_recv_wr * wr;
	struct ibv_recv_wr ** bad_wr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_post_recv_t;

typedef struct {
	// Parameters:
	struct ibv_pd * pd;
	struct ibv_ah_attr * attr;
	// Return value:
	struct ibv_ah * ret;
} __attribute__((packed)) uhyve_ibv_create_ah_t;

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

typedef struct {
	// Parameters:
	struct ibv_pd * pd;
	struct ibv_wc * wc;
	struct ibv_grh * grh;
	uint8_t port_num;
	// Return value:
	struct ibv_ah * ret;
} __attribute__((packed)) uhyve_ibv_create_ah_from_wc_t;

typedef struct {
	// Parameters:
	struct ibv_ah * ah;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_destroy_ah_t;

typedef struct {
	// Parameters:
	struct ibv_qp * qp;
	const union ibv_gid * gid;
	uint16_t lid;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_attach_mcast_t;

typedef struct {
	// Parameters:
	struct ibv_qp * qp;
	const union ibv_gid * gid;
	uint16_t lid;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_detach_mcast_t;

typedef struct {
	// Parameters:
	 ;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_fork_init_t;

typedef struct {
	// Parameters:
	enum ibv_node_type node_type;
	// Return value:
	const char * ret;
} __attribute__((packed)) uhyve_ibv_node_type_str_t;

typedef struct {
	// Parameters:
	enum ibv_port_state port_state;
	// Return value:
	const char * ret;
} __attribute__((packed)) uhyve_ibv_port_state_str_t;

typedef struct {
	// Parameters:
	enum ibv_event_type event;
	// Return value:
	const char * ret;
} __attribute__((packed)) uhyve_ibv_event_type_str_t;

// typedef struct {
	// // Parameters:
	// struct ibv_context * context;
	// struct ibv_ah_attr * attr;
	// uint8_t eth_mac[ETHERNET_LL_SIZE];
	// uint16_t * vid;
	// // Return value:
	// int ret;
// } __attribute__((packed)) uhyve_ibv_resolve_eth_l2_from_gid_t;

typedef struct {
	// Parameters:
	uint32_t caps;
	enum ibv_qp_type qpt;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_is_qpt_supported_t;



void call_ibv_wc_status_str(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_rate_to_mult(struct kvm_run * run, uint8_t * guest_mem);
void call_mult_to_ibv_rate(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_rate_to_mbps(struct kvm_run * run, uint8_t * guest_mem);
void call_mbps_to_ibv_rate(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_cq_ex_to_cq(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_start_poll(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_next_poll(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_end_poll(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_wc_read_opcode(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_wc_read_vendor_err(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_wc_read_byte_len(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_wc_read_imm_data(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_wc_read_invalidated_rkey(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_wc_read_qp_num(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_wc_read_src_qp(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_wc_read_wc_flags(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_wc_read_slid(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_wc_read_sl(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_wc_read_dlid_path_bits(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_wc_read_completion_ts(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_wc_read_cvlan(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_wc_read_flow_tag(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_post_wq_recv(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_get_device_list(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_free_device_list(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_get_device_name(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_get_device_guid(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_open_device(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_close_device(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_get_async_event(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_ack_async_event(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_query_device(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_query_port(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_query_gid(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_query_pkey(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_alloc_pd(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_dealloc_pd(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_create_flow(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_destroy_flow(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_open_xrcd(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_close_xrcd(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_reg_mr(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_rereg_mr(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_dereg_mr(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_alloc_mw(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_dealloc_mw(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_inc_rkey(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_bind_mw(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_create_comp_channel(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_destroy_comp_channel(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_create_cq(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_create_cq_ex(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_resize_cq(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_destroy_cq(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_get_cq_event(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_ack_cq_events(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_poll_cq(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_req_notify_cq(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_create_srq(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_create_srq_ex(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_modify_srq(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_query_srq(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_get_srq_num(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_destroy_srq(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_post_srq_recv(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_create_qp(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_create_qp_ex(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_query_rt_values_ex(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_query_device_ex(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_open_qp(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_modify_qp(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_query_qp(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_destroy_qp(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_create_wq(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_modify_wq(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_destroy_wq(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_create_rwq_ind_table(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_destroy_rwq_ind_table(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_post_send(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_post_recv(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_create_ah(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_init_ah_from_wc(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_create_ah_from_wc(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_destroy_ah(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_attach_mcast(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_detach_mcast(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_fork_init(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_node_type_str(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_port_state_str(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_event_type_str(struct kvm_run * run, uint8_t * guest_mem);
// void call_ibv_resolve_eth_l2_from_gid(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_is_qpt_supported(struct kvm_run * run, uint8_t * guest_mem);

#endif // UHYVE_IBV_H
