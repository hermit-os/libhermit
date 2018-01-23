/*
 * ibv_wc_status_str
 */

void call_ibv_wc_status_str(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_wc_status_str\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_wc_status_str_t * args = (uhyve_ibv_wc_status_str_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_wc_status_str(args->status);
	use_ib_mem_pool = false;
}


/*
 * ibv_rate_to_mult
 */

void call_ibv_rate_to_mult(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_rate_to_mult\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_rate_to_mult_t * args = (uhyve_ibv_rate_to_mult_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_rate_to_mult(args->rate);
	use_ib_mem_pool = false;
}


/*
 * mult_to_ibv_rate
 */

void call_mult_to_ibv_rate(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_mult_to_ibv_rate\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_mult_to_ibv_rate_t * args = (uhyve_mult_to_ibv_rate_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = mult_to_ibv_rate(args->mult);
	use_ib_mem_pool = false;
}


/*
 * ibv_rate_to_mbps
 */

void call_ibv_rate_to_mbps(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_rate_to_mbps\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_rate_to_mbps_t * args = (uhyve_ibv_rate_to_mbps_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_rate_to_mbps(args->rate);
	use_ib_mem_pool = false;
}


/*
 * mbps_to_ibv_rate
 */

void call_mbps_to_ibv_rate(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_mbps_to_ibv_rate\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_mbps_to_ibv_rate_t * args = (uhyve_mbps_to_ibv_rate_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = mbps_to_ibv_rate(args->mbps);
	use_ib_mem_pool = false;
}


/*
 * ibv_cq_ex_to_cq
 */

void call_ibv_cq_ex_to_cq(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_cq_ex_to_cq\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_cq_ex_to_cq_t * args = (uhyve_ibv_cq_ex_to_cq_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_cq_ex_to_cq(args->cq);
	use_ib_mem_pool = false;
}


/*
 * ibv_start_poll
 */

void call_ibv_start_poll(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_start_poll\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_start_poll_t * args = (uhyve_ibv_start_poll_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_start_poll(args->cq, args->attr);
	use_ib_mem_pool = false;
}


/*
 * ibv_next_poll
 */

void call_ibv_next_poll(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_next_poll\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_next_poll_t * args = (uhyve_ibv_next_poll_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_next_poll(args->cq);
	use_ib_mem_pool = false;
}


/*
 * ibv_end_poll
 */

void call_ibv_end_poll(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_end_poll\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_end_poll_t * args = (uhyve_ibv_end_poll_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	ibv_end_poll(args->cq);
	use_ib_mem_pool = false;
}


/*
 * ibv_wc_read_opcode
 */

void call_ibv_wc_read_opcode(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_wc_read_opcode\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_wc_read_opcode_t * args = (uhyve_ibv_wc_read_opcode_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_wc_read_opcode(args->cq);
	use_ib_mem_pool = false;
}


/*
 * ibv_wc_read_vendor_err
 */

void call_ibv_wc_read_vendor_err(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_wc_read_vendor_err\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_wc_read_vendor_err_t * args = (uhyve_ibv_wc_read_vendor_err_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_wc_read_vendor_err(args->cq);
	use_ib_mem_pool = false;
}


/*
 * ibv_wc_read_byte_len
 */

void call_ibv_wc_read_byte_len(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_wc_read_byte_len\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_wc_read_byte_len_t * args = (uhyve_ibv_wc_read_byte_len_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_wc_read_byte_len(args->cq);
	use_ib_mem_pool = false;
}


/*
 * ibv_wc_read_imm_data
 */

void call_ibv_wc_read_imm_data(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_wc_read_imm_data\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_wc_read_imm_data_t * args = (uhyve_ibv_wc_read_imm_data_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_wc_read_imm_data(args->cq);
	use_ib_mem_pool = false;
}


/*
 * ibv_wc_read_invalidated_rkey
 */

void call_ibv_wc_read_invalidated_rkey(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_wc_read_invalidated_rkey\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_wc_read_invalidated_rkey_t * args = (uhyve_ibv_wc_read_invalidated_rkey_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_wc_read_invalidated_rkey(args->cq);
	use_ib_mem_pool = false;
}


/*
 * ibv_wc_read_qp_num
 */

void call_ibv_wc_read_qp_num(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_wc_read_qp_num\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_wc_read_qp_num_t * args = (uhyve_ibv_wc_read_qp_num_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_wc_read_qp_num(args->cq);
	use_ib_mem_pool = false;
}


/*
 * ibv_wc_read_src_qp
 */

void call_ibv_wc_read_src_qp(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_wc_read_src_qp\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_wc_read_src_qp_t * args = (uhyve_ibv_wc_read_src_qp_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_wc_read_src_qp(args->cq);
	use_ib_mem_pool = false;
}


/*
 * ibv_wc_read_wc_flags
 */

void call_ibv_wc_read_wc_flags(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_wc_read_wc_flags\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_wc_read_wc_flags_t * args = (uhyve_ibv_wc_read_wc_flags_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_wc_read_wc_flags(args->cq);
	use_ib_mem_pool = false;
}


/*
 * ibv_wc_read_slid
 */

void call_ibv_wc_read_slid(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_wc_read_slid\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_wc_read_slid_t * args = (uhyve_ibv_wc_read_slid_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_wc_read_slid(args->cq);
	use_ib_mem_pool = false;
}


/*
 * ibv_wc_read_sl
 */

void call_ibv_wc_read_sl(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_wc_read_sl\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_wc_read_sl_t * args = (uhyve_ibv_wc_read_sl_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_wc_read_sl(args->cq);
	use_ib_mem_pool = false;
}


/*
 * ibv_wc_read_dlid_path_bits
 */

void call_ibv_wc_read_dlid_path_bits(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_wc_read_dlid_path_bits\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_wc_read_dlid_path_bits_t * args = (uhyve_ibv_wc_read_dlid_path_bits_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_wc_read_dlid_path_bits(args->cq);
	use_ib_mem_pool = false;
}


/*
 * ibv_wc_read_completion_ts
 */

void call_ibv_wc_read_completion_ts(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_wc_read_completion_ts\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_wc_read_completion_ts_t * args = (uhyve_ibv_wc_read_completion_ts_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_wc_read_completion_ts(args->cq);
	use_ib_mem_pool = false;
}


/*
 * ibv_wc_read_cvlan
 */

void call_ibv_wc_read_cvlan(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_wc_read_cvlan\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_wc_read_cvlan_t * args = (uhyve_ibv_wc_read_cvlan_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_wc_read_cvlan(args->cq);
	use_ib_mem_pool = false;
}


/*
 * ibv_wc_read_flow_tag
 */

void call_ibv_wc_read_flow_tag(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_wc_read_flow_tag\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_wc_read_flow_tag_t * args = (uhyve_ibv_wc_read_flow_tag_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_wc_read_flow_tag(args->cq);
	use_ib_mem_pool = false;
}


/*
 * ibv_post_wq_recv
 */

void call_ibv_post_wq_recv(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_post_wq_recv\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_post_wq_recv_t * args = (uhyve_ibv_post_wq_recv_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_post_wq_recv(args->wq, args->recv_wr, args->bad_recv_wr);
	use_ib_mem_pool = false;
}


/*
 * ibv_get_device_list
 */

void call_ibv_get_device_list(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_get_device_list\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_get_device_list_t * args = (uhyve_ibv_get_device_list_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_get_device_list(args->num_devices);
	use_ib_mem_pool = false;
}


/*
 * ibv_free_device_list
 */

void call_ibv_free_device_list(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_free_device_list\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_free_device_list_t * args = (uhyve_ibv_free_device_list_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	ibv_free_device_list(args->list);
	use_ib_mem_pool = false;
}


/*
 * ibv_get_device_name
 */

void call_ibv_get_device_name(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_get_device_name\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_get_device_name_t * args = (uhyve_ibv_get_device_name_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_get_device_name(args->device);
	use_ib_mem_pool = false;
}


/*
 * ibv_get_device_guid
 */

void call_ibv_get_device_guid(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_get_device_guid\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_get_device_guid_t * args = (uhyve_ibv_get_device_guid_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_get_device_guid(args->device);
	use_ib_mem_pool = false;
}


/*
 * ibv_open_device
 */

void call_ibv_open_device(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_open_device\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_open_device_t * args = (uhyve_ibv_open_device_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_open_device(args->device);
	use_ib_mem_pool = false;
}


/*
 * ibv_close_device
 */

void call_ibv_close_device(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_close_device\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_close_device_t * args = (uhyve_ibv_close_device_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_close_device(args->context);
	use_ib_mem_pool = false;
}


/*
 * ibv_get_async_event
 */

void call_ibv_get_async_event(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_get_async_event\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_get_async_event_t * args = (uhyve_ibv_get_async_event_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_get_async_event(args->context, args->event);
	use_ib_mem_pool = false;
}


/*
 * ibv_ack_async_event
 */

void call_ibv_ack_async_event(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_ack_async_event\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_ack_async_event_t * args = (uhyve_ibv_ack_async_event_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	ibv_ack_async_event(args->event);
	use_ib_mem_pool = false;
}


/*
 * ibv_query_device
 */

void call_ibv_query_device(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_query_device\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_query_device_t * args = (uhyve_ibv_query_device_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_query_device(args->context, args->device_attr);
	use_ib_mem_pool = false;
}


/*
 * ibv_query_port
 */

void call_ibv_query_port(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_query_port\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_query_port_t * args = (uhyve_ibv_query_port_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_query_port(args->context, args->port_num, args->port_attr);
	use_ib_mem_pool = false;
}


/*
 * ibv_query_gid
 */

void call_ibv_query_gid(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_query_gid\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_query_gid_t * args = (uhyve_ibv_query_gid_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_query_gid(args->context, args->port_num, args->index, args->gid);
	use_ib_mem_pool = false;
}


/*
 * ibv_query_pkey
 */

void call_ibv_query_pkey(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_query_pkey\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_query_pkey_t * args = (uhyve_ibv_query_pkey_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_query_pkey(args->context, args->port_num, args->index, args->pkey);
	use_ib_mem_pool = false;
}


/*
 * ibv_alloc_pd
 */

void call_ibv_alloc_pd(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_alloc_pd\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_alloc_pd_t * args = (uhyve_ibv_alloc_pd_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_alloc_pd(args->context);
	use_ib_mem_pool = false;
}


/*
 * ibv_dealloc_pd
 */

void call_ibv_dealloc_pd(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_dealloc_pd\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_dealloc_pd_t * args = (uhyve_ibv_dealloc_pd_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_dealloc_pd(args->pd);
	use_ib_mem_pool = false;
}


/*
 * ibv_create_flow
 */

void call_ibv_create_flow(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_create_flow\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_create_flow_t * args = (uhyve_ibv_create_flow_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_create_flow(args->qp, args->flow);
	use_ib_mem_pool = false;
}


/*
 * ibv_destroy_flow
 */

void call_ibv_destroy_flow(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_destroy_flow\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_destroy_flow_t * args = (uhyve_ibv_destroy_flow_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_destroy_flow(args->flow_id);
	use_ib_mem_pool = false;
}


/*
 * ibv_open_xrcd
 */

void call_ibv_open_xrcd(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_open_xrcd\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_open_xrcd_t * args = (uhyve_ibv_open_xrcd_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_open_xrcd(args->context, args->xrcd_init_attr);
	use_ib_mem_pool = false;
}


/*
 * ibv_close_xrcd
 */

void call_ibv_close_xrcd(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_close_xrcd\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_close_xrcd_t * args = (uhyve_ibv_close_xrcd_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_close_xrcd(args->xrcd);
	use_ib_mem_pool = false;
}


/*
 * ibv_reg_mr
 */

void call_ibv_reg_mr(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_reg_mr\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_reg_mr_t * args = (uhyve_ibv_reg_mr_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_reg_mr(args->pd, args->addr, args->length, args->access);
	use_ib_mem_pool = false;
}


/*
 * ibv_rereg_mr
 */

void call_ibv_rereg_mr(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_rereg_mr\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_rereg_mr_t * args = (uhyve_ibv_rereg_mr_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_rereg_mr(args->mr, args->flags, args->pd, args->addr, args->length, args->access);
	use_ib_mem_pool = false;
}


/*
 * ibv_dereg_mr
 */

void call_ibv_dereg_mr(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_dereg_mr\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_dereg_mr_t * args = (uhyve_ibv_dereg_mr_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_dereg_mr(args->mr);
	use_ib_mem_pool = false;
}


/*
 * ibv_alloc_mw
 */

void call_ibv_alloc_mw(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_alloc_mw\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_alloc_mw_t * args = (uhyve_ibv_alloc_mw_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_alloc_mw(args->pd, args->type);
	use_ib_mem_pool = false;
}


/*
 * ibv_dealloc_mw
 */

void call_ibv_dealloc_mw(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_dealloc_mw\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_dealloc_mw_t * args = (uhyve_ibv_dealloc_mw_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_dealloc_mw(args->mw);
	use_ib_mem_pool = false;
}


/*
 * ibv_inc_rkey
 */

void call_ibv_inc_rkey(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_inc_rkey\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_inc_rkey_t * args = (uhyve_ibv_inc_rkey_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_inc_rkey(args->rkey);
	use_ib_mem_pool = false;
}


/*
 * ibv_bind_mw
 */

void call_ibv_bind_mw(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_bind_mw\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_bind_mw_t * args = (uhyve_ibv_bind_mw_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_bind_mw(args->qp, args->mw, args->mw_bind);
	use_ib_mem_pool = false;
}


/*
 * ibv_create_comp_channel
 */

void call_ibv_create_comp_channel(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_create_comp_channel\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_create_comp_channel_t * args = (uhyve_ibv_create_comp_channel_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_create_comp_channel(args->context);
	use_ib_mem_pool = false;
}


/*
 * ibv_destroy_comp_channel
 */

void call_ibv_destroy_comp_channel(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_destroy_comp_channel\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_destroy_comp_channel_t * args = (uhyve_ibv_destroy_comp_channel_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_destroy_comp_channel(args->channel);
	use_ib_mem_pool = false;
}


/*
 * ibv_create_cq
 */

void call_ibv_create_cq(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_create_cq\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_create_cq_t * args = (uhyve_ibv_create_cq_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_create_cq(args->context, args->cqe, args->cq_context, args->channel, args->comp_vector);
	use_ib_mem_pool = false;
}


/*
 * ibv_create_cq_ex
 */

void call_ibv_create_cq_ex(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_create_cq_ex\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_create_cq_ex_t * args = (uhyve_ibv_create_cq_ex_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_create_cq_ex(args->context, args->cq_attr);
	use_ib_mem_pool = false;
}


/*
 * ibv_resize_cq
 */

void call_ibv_resize_cq(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_resize_cq\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_resize_cq_t * args = (uhyve_ibv_resize_cq_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_resize_cq(args->cq, args->cqe);
	use_ib_mem_pool = false;
}


/*
 * ibv_destroy_cq
 */

void call_ibv_destroy_cq(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_destroy_cq\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_destroy_cq_t * args = (uhyve_ibv_destroy_cq_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_destroy_cq(args->cq);
	use_ib_mem_pool = false;
}


/*
 * ibv_get_cq_event
 */

void call_ibv_get_cq_event(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_get_cq_event\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_get_cq_event_t * args = (uhyve_ibv_get_cq_event_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_get_cq_event(args->channel, args->cq, args->cq_context);
	use_ib_mem_pool = false;
}


/*
 * ibv_ack_cq_events
 */

void call_ibv_ack_cq_events(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_ack_cq_events\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_ack_cq_events_t * args = (uhyve_ibv_ack_cq_events_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	ibv_ack_cq_events(args->cq, args->nevents);
	use_ib_mem_pool = false;
}


/*
 * ibv_poll_cq
 */

void call_ibv_poll_cq(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_poll_cq\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_poll_cq_t * args = (uhyve_ibv_poll_cq_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_poll_cq(args->cq, args->num_entries, args->wc);
	use_ib_mem_pool = false;
}


/*
 * ibv_req_notify_cq
 */

void call_ibv_req_notify_cq(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_req_notify_cq\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_req_notify_cq_t * args = (uhyve_ibv_req_notify_cq_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_req_notify_cq(args->cq, args->solicited_only);
	use_ib_mem_pool = false;
}


/*
 * ibv_create_srq
 */

void call_ibv_create_srq(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_create_srq\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_create_srq_t * args = (uhyve_ibv_create_srq_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_create_srq(args->pd, args->srq_init_attr);
	use_ib_mem_pool = false;
}


/*
 * ibv_create_srq_ex
 */

void call_ibv_create_srq_ex(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_create_srq_ex\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_create_srq_ex_t * args = (uhyve_ibv_create_srq_ex_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_create_srq_ex(args->context, args->srq_init_attr_ex);
	use_ib_mem_pool = false;
}


/*
 * ibv_modify_srq
 */

void call_ibv_modify_srq(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_modify_srq\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_modify_srq_t * args = (uhyve_ibv_modify_srq_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_modify_srq(args->srq, args->srq_attr, args->srq_attr_mask);
	use_ib_mem_pool = false;
}


/*
 * ibv_query_srq
 */

void call_ibv_query_srq(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_query_srq\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_query_srq_t * args = (uhyve_ibv_query_srq_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_query_srq(args->srq, args->srq_attr);
	use_ib_mem_pool = false;
}


/*
 * ibv_get_srq_num
 */

void call_ibv_get_srq_num(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_get_srq_num\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_get_srq_num_t * args = (uhyve_ibv_get_srq_num_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_get_srq_num(args->srq, args->srq_num);
	use_ib_mem_pool = false;
}


/*
 * ibv_destroy_srq
 */

void call_ibv_destroy_srq(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_destroy_srq\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_destroy_srq_t * args = (uhyve_ibv_destroy_srq_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_destroy_srq(args->srq);
	use_ib_mem_pool = false;
}


/*
 * ibv_post_srq_recv
 */

void call_ibv_post_srq_recv(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_post_srq_recv\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_post_srq_recv_t * args = (uhyve_ibv_post_srq_recv_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_post_srq_recv(args->srq, args->recv_wr, args->bad_recv_wr);
	use_ib_mem_pool = false;
}


/*
 * ibv_create_qp
 */

void call_ibv_create_qp(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_create_qp\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_create_qp_t * args = (uhyve_ibv_create_qp_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_create_qp(args->pd, args->qp_init_attr);
	use_ib_mem_pool = false;
}


/*
 * ibv_create_qp_ex
 */

void call_ibv_create_qp_ex(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_create_qp_ex\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_create_qp_ex_t * args = (uhyve_ibv_create_qp_ex_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_create_qp_ex(args->context, args->qp_init_attr_ex);
	use_ib_mem_pool = false;
}


/*
 * ibv_query_rt_values_ex
 */

void call_ibv_query_rt_values_ex(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_query_rt_values_ex\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_query_rt_values_ex_t * args = (uhyve_ibv_query_rt_values_ex_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_query_rt_values_ex(args->context, args->values);
	use_ib_mem_pool = false;
}


/*
 * ibv_query_device_ex
 */

void call_ibv_query_device_ex(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_query_device_ex\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_query_device_ex_t * args = (uhyve_ibv_query_device_ex_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_query_device_ex(args->context, args->input, args->attr);
	use_ib_mem_pool = false;
}


/*
 * ibv_open_qp
 */

void call_ibv_open_qp(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_open_qp\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_open_qp_t * args = (uhyve_ibv_open_qp_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_open_qp(args->context, args->qp_open_attr);
	use_ib_mem_pool = false;
}


/*
 * ibv_modify_qp
 */

void call_ibv_modify_qp(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_modify_qp\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_modify_qp_t * args = (uhyve_ibv_modify_qp_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_modify_qp(args->qp, args->attr, args->attr_mask);
	use_ib_mem_pool = false;
}


/*
 * ibv_query_qp
 */

void call_ibv_query_qp(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_query_qp\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_query_qp_t * args = (uhyve_ibv_query_qp_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_query_qp(args->qp, args->attr, args->attr_mask, args->init_attr);
	use_ib_mem_pool = false;
}


/*
 * ibv_destroy_qp
 */

void call_ibv_destroy_qp(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_destroy_qp\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_destroy_qp_t * args = (uhyve_ibv_destroy_qp_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_destroy_qp(args->qp);
	use_ib_mem_pool = false;
}


/*
 * ibv_create_wq
 */

void call_ibv_create_wq(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_create_wq\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_create_wq_t * args = (uhyve_ibv_create_wq_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_create_wq(args->context, args->wq_init_attr);
	use_ib_mem_pool = false;
}


/*
 * ibv_modify_wq
 */

void call_ibv_modify_wq(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_modify_wq\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_modify_wq_t * args = (uhyve_ibv_modify_wq_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_modify_wq(args->wq, args->wq_attr);
	use_ib_mem_pool = false;
}


/*
 * ibv_destroy_wq
 */

void call_ibv_destroy_wq(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_destroy_wq\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_destroy_wq_t * args = (uhyve_ibv_destroy_wq_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_destroy_wq(args->wq);
	use_ib_mem_pool = false;
}


/*
 * ibv_create_rwq_ind_table
 */

void call_ibv_create_rwq_ind_table(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_create_rwq_ind_table\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_create_rwq_ind_table_t * args = (uhyve_ibv_create_rwq_ind_table_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_create_rwq_ind_table(args->context, args->init_attr);
	use_ib_mem_pool = false;
}


/*
 * ibv_destroy_rwq_ind_table
 */

void call_ibv_destroy_rwq_ind_table(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_destroy_rwq_ind_table\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_destroy_rwq_ind_table_t * args = (uhyve_ibv_destroy_rwq_ind_table_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_destroy_rwq_ind_table(args->rwq_ind_table);
	use_ib_mem_pool = false;
}


/*
 * ibv_post_send
 */

void call_ibv_post_send(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_post_send\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_post_send_t * args = (uhyve_ibv_post_send_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_post_send(args->qp, args->wr, args->bad_wr);
	use_ib_mem_pool = false;
}


/*
 * ibv_post_recv
 */

void call_ibv_post_recv(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_post_recv\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_post_recv_t * args = (uhyve_ibv_post_recv_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_post_recv(args->qp, args->wr, args->bad_wr);
	use_ib_mem_pool = false;
}


/*
 * ibv_create_ah
 */

void call_ibv_create_ah(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_create_ah\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_create_ah_t * args = (uhyve_ibv_create_ah_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_create_ah(args->pd, args->attr);
	use_ib_mem_pool = false;
}


/*
 * ibv_init_ah_from_wc
 */

void call_ibv_init_ah_from_wc(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_init_ah_from_wc\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_init_ah_from_wc_t * args = (uhyve_ibv_init_ah_from_wc_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_init_ah_from_wc(args->context, args->port_num, args->wc, args->grh, args->ah_attr);
	use_ib_mem_pool = false;
}


/*
 * ibv_create_ah_from_wc
 */

void call_ibv_create_ah_from_wc(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_create_ah_from_wc\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_create_ah_from_wc_t * args = (uhyve_ibv_create_ah_from_wc_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_create_ah_from_wc(args->pd, args->wc, args->grh, args->port_num);
	use_ib_mem_pool = false;
}


/*
 * ibv_destroy_ah
 */

void call_ibv_destroy_ah(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_destroy_ah\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_destroy_ah_t * args = (uhyve_ibv_destroy_ah_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_destroy_ah(args->ah);
	use_ib_mem_pool = false;
}


/*
 * ibv_attach_mcast
 */

void call_ibv_attach_mcast(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_attach_mcast\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_attach_mcast_t * args = (uhyve_ibv_attach_mcast_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_attach_mcast(args->qp, args->gid, args->lid);
	use_ib_mem_pool = false;
}


/*
 * ibv_detach_mcast
 */

void call_ibv_detach_mcast(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_detach_mcast\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_detach_mcast_t * args = (uhyve_ibv_detach_mcast_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_detach_mcast(args->qp, args->gid, args->lid);
	use_ib_mem_pool = false;
}


/*
 * ibv_fork_init
 */

void call_ibv_fork_init(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_fork_init\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_fork_init_t * args = (uhyve_ibv_fork_init_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_fork_init();
	use_ib_mem_pool = false;
}


/*
 * ibv_node_type_str
 */

void call_ibv_node_type_str(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_node_type_str\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_node_type_str_t * args = (uhyve_ibv_node_type_str_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_node_type_str(args->node_type);
	use_ib_mem_pool = false;
}


/*
 * ibv_port_state_str
 */

void call_ibv_port_state_str(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_port_state_str\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_port_state_str_t * args = (uhyve_ibv_port_state_str_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_port_state_str(args->port_state);
	use_ib_mem_pool = false;
}


/*
 * ibv_event_type_str
 */

void call_ibv_event_type_str(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_event_type_str\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_event_type_str_t * args = (uhyve_ibv_event_type_str_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_event_type_str(args->event);
	use_ib_mem_pool = false;
}


/*
 * ibv_resolve_eth_l2_from_gid
 */

void call_ibv_resolve_eth_l2_from_gid(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_resolve_eth_l2_from_gid\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_resolve_eth_l2_from_gid_t * args = (uhyve_ibv_resolve_eth_l2_from_gid_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_resolve_eth_l2_from_gid(args->context, args->attr, args->eth_mac, args->vid);
	use_ib_mem_pool = false;
}


/*
 * ibv_is_qpt_supported
 */

void call_ibv_is_qpt_supported(struct kvm_run * run, uint8_t * guest_mem) {
	printf("LOG: UHYVE - call_ibv_is_qpt_supported\n");
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_is_qpt_supported_t * args = (uhyve_ibv_is_qpt_supported_t *) (guest_mem + data);

	use_ib_mem_pool = true;
	args->ret = ibv_is_qpt_supported(args->caps, args->qpt);
	use_ib_mem_pool = false;
}


