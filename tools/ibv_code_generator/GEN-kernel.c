/*
 * ibv_wc_status_str
 */

typedef struct {
	// Parameters:
	enum ibv_wc_status status;
	// Return value:
	const char * ret;
} __attribute__((packed)) uhyve_ibv_wc_status_str_t;

const char * ibv_wc_status_str(enum ibv_wc_status status) {
	uhyve_ibv_wc_status_str_t uhyve_args;
	uhyve_args.status = status;

	uhyve_send(UHYVE_PORT_IBV_WC_STATUS_STR, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
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
 * ibv_cq_ex_to_cq
 */

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	struct ibv_cq * ret;
} __attribute__((packed)) uhyve_ibv_cq_ex_to_cq_t;

struct ibv_cq * ibv_cq_ex_to_cq(struct ibv_cq_ex * cq) {
	uhyve_ibv_cq_ex_to_cq_t uhyve_args;
	uhyve_args.cq = cq;

	uhyve_send(UHYVE_PORT_IBV_CQ_EX_TO_CQ, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_start_poll
 */

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	struct ibv_poll_cq_attr * attr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_start_poll_t;

int ibv_start_poll(struct ibv_cq_ex * cq, struct ibv_poll_cq_attr * attr) {
	uhyve_ibv_start_poll_t uhyve_args;
	uhyve_args.cq = cq;
	uhyve_args.attr = (struct ibv_poll_cq_attr *) guest_to_host((size_t) attr);

	uhyve_send(UHYVE_PORT_IBV_START_POLL, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_next_poll
 */

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_next_poll_t;

int ibv_next_poll(struct ibv_cq_ex * cq) {
	uhyve_ibv_next_poll_t uhyve_args;
	uhyve_args.cq = cq;

	uhyve_send(UHYVE_PORT_IBV_NEXT_POLL, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_end_poll
 */

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
} __attribute__((packed)) uhyve_ibv_end_poll_t;

void ibv_end_poll(struct ibv_cq_ex * cq) {
	uhyve_ibv_end_poll_t uhyve_args;
	uhyve_args.cq = cq;

	uhyve_send(UHYVE_PORT_IBV_END_POLL, (unsigned) virt_to_phys((size_t) &uhyve_args));

}


/*
 * ibv_wc_read_opcode
 */

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	enum ibv_wc_opcode ret;
} __attribute__((packed)) uhyve_ibv_wc_read_opcode_t;

enum ibv_wc_opcode ibv_wc_read_opcode(struct ibv_cq_ex * cq) {
	uhyve_ibv_wc_read_opcode_t uhyve_args;
	uhyve_args.cq = cq;

	uhyve_send(UHYVE_PORT_IBV_WC_READ_OPCODE, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_wc_read_vendor_err
 */

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	uint32_t ret;
} __attribute__((packed)) uhyve_ibv_wc_read_vendor_err_t;

uint32_t ibv_wc_read_vendor_err(struct ibv_cq_ex * cq) {
	uhyve_ibv_wc_read_vendor_err_t uhyve_args;
	uhyve_args.cq = cq;

	uhyve_send(UHYVE_PORT_IBV_WC_READ_VENDOR_ERR, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_wc_read_byte_len
 */

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	uint32_t ret;
} __attribute__((packed)) uhyve_ibv_wc_read_byte_len_t;

uint32_t ibv_wc_read_byte_len(struct ibv_cq_ex * cq) {
	uhyve_ibv_wc_read_byte_len_t uhyve_args;
	uhyve_args.cq = cq;

	uhyve_send(UHYVE_PORT_IBV_WC_READ_BYTE_LEN, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_wc_read_imm_data
 */

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	__be32 ret;
} __attribute__((packed)) uhyve_ibv_wc_read_imm_data_t;

__be32 ibv_wc_read_imm_data(struct ibv_cq_ex * cq) {
	uhyve_ibv_wc_read_imm_data_t uhyve_args;
	uhyve_args.cq = cq;

	uhyve_send(UHYVE_PORT_IBV_WC_READ_IMM_DATA, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_wc_read_invalidated_rkey
 */

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	uint32_t ret;
} __attribute__((packed)) uhyve_ibv_wc_read_invalidated_rkey_t;

uint32_t ibv_wc_read_invalidated_rkey(struct ibv_cq_ex * cq) {
	uhyve_ibv_wc_read_invalidated_rkey_t uhyve_args;
	uhyve_args.cq = cq;

	uhyve_send(UHYVE_PORT_IBV_WC_READ_INVALIDATED_RKEY, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_wc_read_qp_num
 */

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	uint32_t ret;
} __attribute__((packed)) uhyve_ibv_wc_read_qp_num_t;

uint32_t ibv_wc_read_qp_num(struct ibv_cq_ex * cq) {
	uhyve_ibv_wc_read_qp_num_t uhyve_args;
	uhyve_args.cq = cq;

	uhyve_send(UHYVE_PORT_IBV_WC_READ_QP_NUM, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_wc_read_src_qp
 */

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	uint32_t ret;
} __attribute__((packed)) uhyve_ibv_wc_read_src_qp_t;

uint32_t ibv_wc_read_src_qp(struct ibv_cq_ex * cq) {
	uhyve_ibv_wc_read_src_qp_t uhyve_args;
	uhyve_args.cq = cq;

	uhyve_send(UHYVE_PORT_IBV_WC_READ_SRC_QP, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_wc_read_wc_flags
 */

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_wc_read_wc_flags_t;

int ibv_wc_read_wc_flags(struct ibv_cq_ex * cq) {
	uhyve_ibv_wc_read_wc_flags_t uhyve_args;
	uhyve_args.cq = cq;

	uhyve_send(UHYVE_PORT_IBV_WC_READ_WC_FLAGS, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_wc_read_slid
 */

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	uint32_t ret;
} __attribute__((packed)) uhyve_ibv_wc_read_slid_t;

uint32_t ibv_wc_read_slid(struct ibv_cq_ex * cq) {
	uhyve_ibv_wc_read_slid_t uhyve_args;
	uhyve_args.cq = cq;

	uhyve_send(UHYVE_PORT_IBV_WC_READ_SLID, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_wc_read_sl
 */

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	uint8_t ret;
} __attribute__((packed)) uhyve_ibv_wc_read_sl_t;

uint8_t ibv_wc_read_sl(struct ibv_cq_ex * cq) {
	uhyve_ibv_wc_read_sl_t uhyve_args;
	uhyve_args.cq = cq;

	uhyve_send(UHYVE_PORT_IBV_WC_READ_SL, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_wc_read_dlid_path_bits
 */

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	uint8_t ret;
} __attribute__((packed)) uhyve_ibv_wc_read_dlid_path_bits_t;

uint8_t ibv_wc_read_dlid_path_bits(struct ibv_cq_ex * cq) {
	uhyve_ibv_wc_read_dlid_path_bits_t uhyve_args;
	uhyve_args.cq = cq;

	uhyve_send(UHYVE_PORT_IBV_WC_READ_DLID_PATH_BITS, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_wc_read_completion_ts
 */

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	uint64_t ret;
} __attribute__((packed)) uhyve_ibv_wc_read_completion_ts_t;

uint64_t ibv_wc_read_completion_ts(struct ibv_cq_ex * cq) {
	uhyve_ibv_wc_read_completion_ts_t uhyve_args;
	uhyve_args.cq = cq;

	uhyve_send(UHYVE_PORT_IBV_WC_READ_COMPLETION_TS, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_wc_read_cvlan
 */

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	uint16_t ret;
} __attribute__((packed)) uhyve_ibv_wc_read_cvlan_t;

uint16_t ibv_wc_read_cvlan(struct ibv_cq_ex * cq) {
	uhyve_ibv_wc_read_cvlan_t uhyve_args;
	uhyve_args.cq = cq;

	uhyve_send(UHYVE_PORT_IBV_WC_READ_CVLAN, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_wc_read_flow_tag
 */

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	uint32_t ret;
} __attribute__((packed)) uhyve_ibv_wc_read_flow_tag_t;

uint32_t ibv_wc_read_flow_tag(struct ibv_cq_ex * cq) {
	uhyve_ibv_wc_read_flow_tag_t uhyve_args;
	uhyve_args.cq = cq;

	uhyve_send(UHYVE_PORT_IBV_WC_READ_FLOW_TAG, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_post_wq_recv
 */

typedef struct {
	// Parameters:
	struct ibv_wq * wq;
	struct ibv_recv_wr * recv_wr;
	struct ibv_recv_wr ** bad_recv_wr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_post_wq_recv_t;

int ibv_post_wq_recv(struct ibv_wq * wq, struct ibv_recv_wr * recv_wr, struct ibv_recv_wr ** bad_recv_wr) {
	uhyve_ibv_post_wq_recv_t uhyve_args;
	uhyve_args.wq = wq;
	uhyve_args.recv_wr = (struct ibv_recv_wr *) guest_to_host((size_t) recv_wr);
	uhyve_args.bad_recv_wr = (struct ibv_recv_wr **) guest_to_host((size_t) bad_recv_wr); // TODO: Check ** param here.

	// TODO: Take care of pointer conversions in recv_wr.
	// TODO: Take care of pointer conversions in bad_recv_wr.

	uhyve_send(UHYVE_PORT_IBV_POST_WQ_RECV, (unsigned) virt_to_phys((size_t) &uhyve_args));

	// TODO: Take care of reverse pointer conversions in recv_wr.
	// TODO: Take care of reverse pointer conversions in bad_recv_wr.

	return uhyve_args.ret;
}


/*
 * ibv_get_device_list
 */

typedef struct {
	// Parameters:
	int * num_devices;
	// Return value:
	struct ibv_device ** ret;
} __attribute__((packed)) uhyve_ibv_get_device_list_t;

struct ibv_device ** ibv_get_device_list(int * num_devices) {
	uhyve_ibv_get_device_list_t uhyve_args;
	uhyve_args.num_devices = (int *) guest_to_host((size_t) num_devices);

	uhyve_send(UHYVE_PORT_IBV_GET_DEVICE_LIST, (unsigned) virt_to_phys((size_t) &uhyve_args));

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
	uhyve_args.list = list;

	uhyve_send(UHYVE_PORT_IBV_FREE_DEVICE_LIST, (unsigned) virt_to_phys((size_t) &uhyve_args));

}


/*
 * ibv_get_device_name
 */

typedef struct {
	// Parameters:
	struct ibv_device * device;
	// Return value:
	const char * ret;
} __attribute__((packed)) uhyve_ibv_get_device_name_t;

const char * ibv_get_device_name(struct ibv_device * device) {
	uhyve_ibv_get_device_name_t uhyve_args;
	uhyve_args.device = device;

	uhyve_send(UHYVE_PORT_IBV_GET_DEVICE_NAME, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
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
	uhyve_args.event = (struct ibv_async_event *) guest_to_host((size_t) event);

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
	uhyve_args.event = (struct ibv_async_event *) guest_to_host((size_t) event);

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
	uhyve_args.device_attr = (struct ibv_device_attr *) guest_to_host((size_t) device_attr);

	uhyve_send(UHYVE_PORT_IBV_QUERY_DEVICE, (unsigned) virt_to_phys((size_t) &uhyve_args));

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
	uhyve_args.context = context;
	uhyve_args.port_num = port_num;
	uhyve_args.port_attr = (struct ibv_port_attr *) guest_to_host((size_t) port_attr);

	uhyve_send(UHYVE_PORT_IBV_QUERY_PORT, (unsigned) virt_to_phys((size_t) &uhyve_args));

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
	uhyve_args.gid = (union ibv_gid *) guest_to_host((size_t) gid);

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
	uhyve_args.pkey = (__be16 *) guest_to_host((size_t) pkey);

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
	uhyve_args.flow = (struct ibv_flow_attr *) guest_to_host((size_t) flow);

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
	uhyve_args.xrcd_init_attr = (struct ibv_xrcd_init_attr *) guest_to_host((size_t) xrcd_init_attr);

	// TODO: Take care of pointer conversions in xrcd_init_attr.

	uhyve_send(UHYVE_PORT_IBV_OPEN_XRCD, (unsigned) virt_to_phys((size_t) &uhyve_args));

	// TODO: Take care of reverse pointer conversions in xrcd_init_attr.

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
	uhyve_args.addr = (void *) guest_to_host((size_t) addr);
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
	uhyve_args.addr = (void *) guest_to_host((size_t) addr);
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
	uhyve_args.mw_bind = (struct ibv_mw_bind *) guest_to_host((size_t) mw_bind);

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
	uhyve_args.context = context;
	uhyve_args.cqe = cqe;
	uhyve_args.cq_context = (void *) guest_to_host((size_t) cq_context);
	uhyve_args.channel = channel;
	uhyve_args.comp_vector = comp_vector;

	uhyve_send(UHYVE_PORT_IBV_CREATE_CQ, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_create_cq_ex
 */

typedef struct {
	// Parameters:
	struct ibv_context * context;
	struct ibv_cq_init_attr_ex * cq_attr;
	// Return value:
	struct ibv_cq_ex * ret;
} __attribute__((packed)) uhyve_ibv_create_cq_ex_t;

struct ibv_cq_ex * ibv_create_cq_ex(struct ibv_context * context, struct ibv_cq_init_attr_ex * cq_attr) {
	uhyve_ibv_create_cq_ex_t uhyve_args;
	uhyve_args.context = context;
	uhyve_args.cq_attr = (struct ibv_cq_init_attr_ex *) guest_to_host((size_t) cq_attr);

	uhyve_send(UHYVE_PORT_IBV_CREATE_CQ_EX, (unsigned) virt_to_phys((size_t) &uhyve_args));

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
	uhyve_args.channel = channel;
	uhyve_args.cq = cq;
	uhyve_args.cq_context = (void **) guest_to_host((size_t) cq_context); // TODO: Check ** param here.

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
	uhyve_args.cq = cq;
	uhyve_args.num_entries = num_entries;
	uhyve_args.wc = (struct ibv_wc *) guest_to_host((size_t) wc);

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
	uhyve_args.srq_init_attr = (struct ibv_srq_init_attr *) guest_to_host((size_t) srq_init_attr);

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
	uhyve_args.srq_init_attr_ex = (struct ibv_srq_init_attr_ex *) guest_to_host((size_t) srq_init_attr_ex);

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
	uhyve_args.srq_attr = (struct ibv_srq_attr *) guest_to_host((size_t) srq_attr);
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
	uhyve_args.srq_attr = (struct ibv_srq_attr *) guest_to_host((size_t) srq_attr);

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
	uhyve_args.srq_num = (uint32_t *) guest_to_host((size_t) srq_num);

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
	uhyve_args.recv_wr = (struct ibv_recv_wr *) guest_to_host((size_t) recv_wr);
	uhyve_args.bad_recv_wr = (struct ibv_recv_wr **) guest_to_host((size_t) bad_recv_wr); // TODO: Check ** param here.

	// TODO: Take care of pointer conversions in recv_wr.
	// TODO: Take care of pointer conversions in bad_recv_wr.

	uhyve_send(UHYVE_PORT_IBV_POST_SRQ_RECV, (unsigned) virt_to_phys((size_t) &uhyve_args));

	// TODO: Take care of reverse pointer conversions in recv_wr.
	// TODO: Take care of reverse pointer conversions in bad_recv_wr.

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
	uhyve_args.pd = pd;
	uhyve_args.qp_init_attr = (struct ibv_qp_init_attr *) guest_to_host((size_t) qp_init_attr);

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
	uhyve_args.qp_init_attr_ex = (struct ibv_qp_init_attr_ex *) guest_to_host((size_t) qp_init_attr_ex);

	uhyve_send(UHYVE_PORT_IBV_CREATE_QP_EX, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_query_rt_values_ex
 */

typedef struct {
	// Parameters:
	struct ibv_context * context;
	struct ibv_values_ex * values;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_query_rt_values_ex_t;

int ibv_query_rt_values_ex(struct ibv_context * context, struct ibv_values_ex * values) {
	uhyve_ibv_query_rt_values_ex_t uhyve_args;
	uhyve_args.context = context;
	uhyve_args.values = (struct ibv_values_ex *) guest_to_host((size_t) values);

	uhyve_send(UHYVE_PORT_IBV_QUERY_RT_VALUES_EX, (unsigned) virt_to_phys((size_t) &uhyve_args));

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
	uhyve_args.input = (const struct ibv_query_device_ex_input *) guest_to_host((size_t) input);
	uhyve_args.attr = (struct ibv_device_attr_ex *) guest_to_host((size_t) attr);

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
	uhyve_args.qp_open_attr = (struct ibv_qp_open_attr *) guest_to_host((size_t) qp_open_attr);

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
	uhyve_args.qp = qp;
	uhyve_args.attr = (struct ibv_qp_attr *) guest_to_host((size_t) attr);
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
	uhyve_args.qp = qp;
	uhyve_args.attr = (struct ibv_qp_attr *) guest_to_host((size_t) attr);
	uhyve_args.attr_mask = attr_mask;
	uhyve_args.init_attr = (struct ibv_qp_init_attr *) guest_to_host((size_t) init_attr);

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
 * ibv_create_wq
 */

typedef struct {
	// Parameters:
	struct ibv_context * context;
	struct ibv_wq_init_attr * wq_init_attr;
	// Return value:
	struct ibv_wq * ret;
} __attribute__((packed)) uhyve_ibv_create_wq_t;

struct ibv_wq * ibv_create_wq(struct ibv_context * context, struct ibv_wq_init_attr * wq_init_attr) {
	uhyve_ibv_create_wq_t uhyve_args;
	uhyve_args.context = context;
	uhyve_args.wq_init_attr = (struct ibv_wq_init_attr *) guest_to_host((size_t) wq_init_attr);

	uhyve_send(UHYVE_PORT_IBV_CREATE_WQ, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_modify_wq
 */

typedef struct {
	// Parameters:
	struct ibv_wq * wq;
	struct ibv_wq_attr * wq_attr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_modify_wq_t;

int ibv_modify_wq(struct ibv_wq * wq, struct ibv_wq_attr * wq_attr) {
	uhyve_ibv_modify_wq_t uhyve_args;
	uhyve_args.wq = wq;
	uhyve_args.wq_attr = (struct ibv_wq_attr *) guest_to_host((size_t) wq_attr);

	uhyve_send(UHYVE_PORT_IBV_MODIFY_WQ, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_destroy_wq
 */

typedef struct {
	// Parameters:
	struct ibv_wq * wq;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_destroy_wq_t;

int ibv_destroy_wq(struct ibv_wq * wq) {
	uhyve_ibv_destroy_wq_t uhyve_args;
	uhyve_args.wq = wq;

	uhyve_send(UHYVE_PORT_IBV_DESTROY_WQ, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_create_rwq_ind_table
 */

typedef struct {
	// Parameters:
	struct ibv_context * context;
	struct ibv_rwq_ind_table_init_attr * init_attr;
	// Return value:
	struct ibv_rwq_ind_table * ret;
} __attribute__((packed)) uhyve_ibv_create_rwq_ind_table_t;

struct ibv_rwq_ind_table * ibv_create_rwq_ind_table(struct ibv_context * context, struct ibv_rwq_ind_table_init_attr * init_attr) {
	uhyve_ibv_create_rwq_ind_table_t uhyve_args;
	uhyve_args.context = context;
	uhyve_args.init_attr = (struct ibv_rwq_ind_table_init_attr *) guest_to_host((size_t) init_attr);

	// TODO: Take care of pointer conversions in init_attr.

	uhyve_send(UHYVE_PORT_IBV_CREATE_RWQ_IND_TABLE, (unsigned) virt_to_phys((size_t) &uhyve_args));

	// TODO: Take care of reverse pointer conversions in init_attr.

	return uhyve_args.ret;
}


/*
 * ibv_destroy_rwq_ind_table
 */

typedef struct {
	// Parameters:
	struct ibv_rwq_ind_table * rwq_ind_table;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_destroy_rwq_ind_table_t;

int ibv_destroy_rwq_ind_table(struct ibv_rwq_ind_table * rwq_ind_table) {
	uhyve_ibv_destroy_rwq_ind_table_t uhyve_args;
	uhyve_args.rwq_ind_table = rwq_ind_table;

	uhyve_send(UHYVE_PORT_IBV_DESTROY_RWQ_IND_TABLE, (unsigned) virt_to_phys((size_t) &uhyve_args));

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
	uhyve_args.wr = (struct ibv_send_wr *) guest_to_host((size_t) wr);
	uhyve_args.bad_wr = (struct ibv_send_wr **) guest_to_host((size_t) bad_wr); // TODO: Check ** param here.

	// TODO: Take care of pointer conversions in wr.
	// TODO: Take care of pointer conversions in bad_wr.

	uhyve_send(UHYVE_PORT_IBV_POST_SEND, (unsigned) virt_to_phys((size_t) &uhyve_args));

	// TODO: Take care of reverse pointer conversions in wr.
	// TODO: Take care of reverse pointer conversions in bad_wr.

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
	uhyve_ibv_post_recv_t uhyve_args;
	uhyve_args.qp = qp;
	uhyve_args.wr = (struct ibv_recv_wr *) guest_to_host((size_t) wr);
	uhyve_args.bad_wr = (struct ibv_recv_wr **) guest_to_host((size_t) bad_wr); // TODO: Check ** param here.

	// TODO: Take care of pointer conversions in wr.
	// TODO: Take care of pointer conversions in bad_wr.

	uhyve_send(UHYVE_PORT_IBV_POST_RECV, (unsigned) virt_to_phys((size_t) &uhyve_args));

	// TODO: Take care of reverse pointer conversions in wr.
	// TODO: Take care of reverse pointer conversions in bad_wr.

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
	uhyve_args.pd = pd;
	uhyve_args.attr = (struct ibv_ah_attr *) guest_to_host((size_t) attr);

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
	uhyve_args.wc = (struct ibv_wc *) guest_to_host((size_t) wc);
	uhyve_args.grh = (struct ibv_grh *) guest_to_host((size_t) grh);
	uhyve_args.ah_attr = (struct ibv_ah_attr *) guest_to_host((size_t) ah_attr);

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
	uhyve_args.wc = (struct ibv_wc *) guest_to_host((size_t) wc);
	uhyve_args.grh = (struct ibv_grh *) guest_to_host((size_t) grh);
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
	uhyve_args.gid = (const union ibv_gid *) guest_to_host((size_t) gid);
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
	uhyve_args.gid = (const union ibv_gid *) guest_to_host((size_t) gid);
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

int ibv_fork_init() {
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
	const char * ret;
} __attribute__((packed)) uhyve_ibv_node_type_str_t;

const char * ibv_node_type_str(enum ibv_node_type node_type) {
	uhyve_ibv_node_type_str_t uhyve_args;
	uhyve_args.node_type = node_type;

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
	const char * ret;
} __attribute__((packed)) uhyve_ibv_port_state_str_t;

const char * ibv_port_state_str(enum ibv_port_state port_state) {
	uhyve_ibv_port_state_str_t uhyve_args;
	uhyve_args.port_state = port_state;

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
	const char * ret;
} __attribute__((packed)) uhyve_ibv_event_type_str_t;

const char * ibv_event_type_str(enum ibv_event_type event) {
	uhyve_ibv_event_type_str_t uhyve_args;
	uhyve_args.event = event;

	uhyve_send(UHYVE_PORT_IBV_EVENT_TYPE_STR, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


/*
 * ibv_resolve_eth_l2_from_gid
 */

typedef struct {
	// Parameters:
	struct ibv_context * context;
	struct ibv_ah_attr * attr;
	uint8_t eth_mac[6];
	uint16_t * vid;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_resolve_eth_l2_from_gid_t;

int ibv_resolve_eth_l2_from_gid(struct ibv_context * context, struct ibv_ah_attr * attr, uint8_t eth_mac[6], uint16_t * vid) {
	uhyve_ibv_resolve_eth_l2_from_gid_t uhyve_args;
	uhyve_args.context = context;
	uhyve_args.attr = (struct ibv_ah_attr *) guest_to_host((size_t) attr);
	uhyve_args.eth_mac[6] = eth_mac[6];
	uhyve_args.vid = (uint16_t *) guest_to_host((size_t) vid);

	uhyve_send(UHYVE_PORT_IBV_RESOLVE_ETH_L2_FROM_GID, (unsigned) virt_to_phys((size_t) &uhyve_args));

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


