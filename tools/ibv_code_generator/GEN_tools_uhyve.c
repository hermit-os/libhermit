
			case UHYVE_PORT_IBV_WC_STATUS_STR: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_wc_status_str_t * args = (uhyve_ibv_wc_status_str_t *) (guest_mem + data);

				const char * host_ret = ibv_wc_status_str(status);
				memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
				break;
			}

			case UHYVE_PORT_IBV_RATE_TO_MULT: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_rate_to_mult_t * args = (uhyve_ibv_rate_to_mult_t *) (guest_mem + data);

				int host_ret = ibv_rate_to_mult(rate);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_MULT_TO_IBV_RATE: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_mult_to_ibv_rate_t * args = (uhyve_mult_to_ibv_rate_t *) (guest_mem + data);

				enum ibv_rate host_ret = mult_to_ibv_rate(mult);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_RATE_TO_MBPS: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_rate_to_mbps_t * args = (uhyve_ibv_rate_to_mbps_t *) (guest_mem + data);

				int host_ret = ibv_rate_to_mbps(rate);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_MBPS_TO_IBV_RATE: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_mbps_to_ibv_rate_t * args = (uhyve_mbps_to_ibv_rate_t *) (guest_mem + data);

				enum ibv_rate host_ret = mbps_to_ibv_rate(mbps);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_CQ_EX_TO_CQ: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_cq_ex_to_cq_t * args = (uhyve_ibv_cq_ex_to_cq_t *) (guest_mem + data);

				struct ibv_cq * host_ret = ibv_cq_ex_to_cq(guest_mem+(size_t)args->cq);
				memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
				break;
			}

			case UHYVE_PORT_IBV_START_POLL: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_start_poll_t * args = (uhyve_ibv_start_poll_t *) (guest_mem + data);

				int host_ret = ibv_start_poll(guest_mem+(size_t)args->cq, guest_mem+(size_t)args->attr);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_NEXT_POLL: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_next_poll_t * args = (uhyve_ibv_next_poll_t *) (guest_mem + data);

				int host_ret = ibv_next_poll(guest_mem+(size_t)args->cq);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_END_POLL: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_end_poll_t * args = (uhyve_ibv_end_poll_t *) (guest_mem + data);

				void host_ret = ibv_end_poll(guest_mem+(size_t)args->cq);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_WC_READ_OPCODE: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_wc_read_opcode_t * args = (uhyve_ibv_wc_read_opcode_t *) (guest_mem + data);

				enum ibv_wc_opcode host_ret = ibv_wc_read_opcode(guest_mem+(size_t)args->cq);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_WC_READ_VENDOR_ERR: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_wc_read_vendor_err_t * args = (uhyve_ibv_wc_read_vendor_err_t *) (guest_mem + data);

				uint32_t host_ret = ibv_wc_read_vendor_err(guest_mem+(size_t)args->cq);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_WC_READ_BYTE_LEN: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_wc_read_byte_len_t * args = (uhyve_ibv_wc_read_byte_len_t *) (guest_mem + data);

				uint32_t host_ret = ibv_wc_read_byte_len(guest_mem+(size_t)args->cq);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_WC_READ_IMM_DATA: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_wc_read_imm_data_t * args = (uhyve_ibv_wc_read_imm_data_t *) (guest_mem + data);

				__be32 host_ret = ibv_wc_read_imm_data(guest_mem+(size_t)args->cq);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_WC_READ_INVALIDATED_RKEY: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_wc_read_invalidated_rkey_t * args = (uhyve_ibv_wc_read_invalidated_rkey_t *) (guest_mem + data);

				uint32_t host_ret = ibv_wc_read_invalidated_rkey(guest_mem+(size_t)args->cq);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_WC_READ_QP_NUM: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_wc_read_qp_num_t * args = (uhyve_ibv_wc_read_qp_num_t *) (guest_mem + data);

				uint32_t host_ret = ibv_wc_read_qp_num(guest_mem+(size_t)args->cq);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_WC_READ_SRC_QP: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_wc_read_src_qp_t * args = (uhyve_ibv_wc_read_src_qp_t *) (guest_mem + data);

				uint32_t host_ret = ibv_wc_read_src_qp(guest_mem+(size_t)args->cq);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_WC_READ_WC_FLAGS: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_wc_read_wc_flags_t * args = (uhyve_ibv_wc_read_wc_flags_t *) (guest_mem + data);

				int host_ret = ibv_wc_read_wc_flags(guest_mem+(size_t)args->cq);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_WC_READ_SLID: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_wc_read_slid_t * args = (uhyve_ibv_wc_read_slid_t *) (guest_mem + data);

				uint32_t host_ret = ibv_wc_read_slid(guest_mem+(size_t)args->cq);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_WC_READ_SL: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_wc_read_sl_t * args = (uhyve_ibv_wc_read_sl_t *) (guest_mem + data);

				uint8_t host_ret = ibv_wc_read_sl(guest_mem+(size_t)args->cq);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_WC_READ_DLID_PATH_BITS: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_wc_read_dlid_path_bits_t * args = (uhyve_ibv_wc_read_dlid_path_bits_t *) (guest_mem + data);

				uint8_t host_ret = ibv_wc_read_dlid_path_bits(guest_mem+(size_t)args->cq);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_WC_READ_COMPLETION_TS: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_wc_read_completion_ts_t * args = (uhyve_ibv_wc_read_completion_ts_t *) (guest_mem + data);

				uint64_t host_ret = ibv_wc_read_completion_ts(guest_mem+(size_t)args->cq);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_WC_READ_CVLAN: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_wc_read_cvlan_t * args = (uhyve_ibv_wc_read_cvlan_t *) (guest_mem + data);

				uint16_t host_ret = ibv_wc_read_cvlan(guest_mem+(size_t)args->cq);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_WC_READ_FLOW_TAG: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_wc_read_flow_tag_t * args = (uhyve_ibv_wc_read_flow_tag_t *) (guest_mem + data);

				uint32_t host_ret = ibv_wc_read_flow_tag(guest_mem+(size_t)args->cq);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_POST_WQ_RECV: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_post_wq_recv_t * args = (uhyve_ibv_post_wq_recv_t *) (guest_mem + data);

				int host_ret = ibv_post_wq_recv(guest_mem+(size_t)args->wq, guest_mem+(size_t)args->recv_wr, /* TODO: param bad_recv_wr*/);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_VERBS_GET_CTX: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_verbs_get_ctx_t * args = (uhyve_verbs_get_ctx_t *) (guest_mem + data);

				struct verbs_context * host_ret = verbs_get_ctx(guest_mem+(size_t)args->ctx);
				memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
				break;
			}

			case UHYVE_PORT_IBV_GET_DEVICE_LIST: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_get_device_list_t * args = (uhyve_ibv_get_device_list_t *) (guest_mem + data);

				struct ibv_device ** host_ret = ibv_get_device_list(guest_mem+(size_t)args->num_devices);
				// TODO: Take care of struct ibv_device ** return value.
				break;
			}

			case UHYVE_PORT_IBV_FREE_DEVICE_LIST: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_free_device_list_t * args = (uhyve_ibv_free_device_list_t *) (guest_mem + data);

				void host_ret = ibv_free_device_list(/* TODO: param list*/);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_GET_DEVICE_NAME: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_get_device_name_t * args = (uhyve_ibv_get_device_name_t *) (guest_mem + data);

				const char * host_ret = ibv_get_device_name(guest_mem+(size_t)args->device);
				memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
				break;
			}

			case UHYVE_PORT_IBV_GET_DEVICE_GUID: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_get_device_guid_t * args = (uhyve_ibv_get_device_guid_t *) (guest_mem + data);

				__be64 host_ret = ibv_get_device_guid(guest_mem+(size_t)args->device);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_OPEN_DEVICE: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_open_device_t * args = (uhyve_ibv_open_device_t *) (guest_mem + data);

				struct ibv_context * host_ret = ibv_open_device(guest_mem+(size_t)args->device);
				memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
				break;
			}

			case UHYVE_PORT_IBV_CLOSE_DEVICE: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_close_device_t * args = (uhyve_ibv_close_device_t *) (guest_mem + data);

				int host_ret = ibv_close_device(guest_mem+(size_t)args->context);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_GET_ASYNC_EVENT: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_get_async_event_t * args = (uhyve_ibv_get_async_event_t *) (guest_mem + data);

				int host_ret = ibv_get_async_event(guest_mem+(size_t)args->context, guest_mem+(size_t)args->event);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_ACK_ASYNC_EVENT: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_ack_async_event_t * args = (uhyve_ibv_ack_async_event_t *) (guest_mem + data);

				void host_ret = ibv_ack_async_event(guest_mem+(size_t)args->event);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_QUERY_DEVICE: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_query_device_t * args = (uhyve_ibv_query_device_t *) (guest_mem + data);

				int host_ret = ibv_query_device(guest_mem+(size_t)args->context, guest_mem+(size_t)args->device_attr);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_QUERY_PORT: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_query_port_t * args = (uhyve_ibv_query_port_t *) (guest_mem + data);

				int host_ret = ibv_query_port(guest_mem+(size_t)args->context, port_num, guest_mem+(size_t)args->port_attr);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT____IBV_QUERY_PORT: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve____ibv_query_port_t * args = (uhyve____ibv_query_port_t *) (guest_mem + data);

				int host_ret = ___ibv_query_port(guest_mem+(size_t)args->context, port_num, guest_mem+(size_t)args->port_attr);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_QUERY_GID: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_query_gid_t * args = (uhyve_ibv_query_gid_t *) (guest_mem + data);

				int host_ret = ibv_query_gid(guest_mem+(size_t)args->context, port_num, index, guest_mem+(size_t)args->gid);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_QUERY_PKEY: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_query_pkey_t * args = (uhyve_ibv_query_pkey_t *) (guest_mem + data);

				int host_ret = ibv_query_pkey(guest_mem+(size_t)args->context, port_num, index, guest_mem+(size_t)args->pkey);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_ALLOC_PD: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_alloc_pd_t * args = (uhyve_ibv_alloc_pd_t *) (guest_mem + data);

				struct ibv_pd * host_ret = ibv_alloc_pd(guest_mem+(size_t)args->context);
				memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
				break;
			}

			case UHYVE_PORT_IBV_DEALLOC_PD: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_dealloc_pd_t * args = (uhyve_ibv_dealloc_pd_t *) (guest_mem + data);

				int host_ret = ibv_dealloc_pd(guest_mem+(size_t)args->pd);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_CREATE_FLOW: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_create_flow_t * args = (uhyve_ibv_create_flow_t *) (guest_mem + data);

				struct ibv_flow * host_ret = ibv_create_flow(guest_mem+(size_t)args->qp, guest_mem+(size_t)args->flow);
				memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
				break;
			}

			case UHYVE_PORT_IBV_DESTROY_FLOW: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_destroy_flow_t * args = (uhyve_ibv_destroy_flow_t *) (guest_mem + data);

				int host_ret = ibv_destroy_flow(guest_mem+(size_t)args->flow_id);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_OPEN_XRCD: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_open_xrcd_t * args = (uhyve_ibv_open_xrcd_t *) (guest_mem + data);

				struct ibv_xrcd * host_ret = ibv_open_xrcd(guest_mem+(size_t)args->context, guest_mem+(size_t)args->xrcd_init_attr);
				memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
				break;
			}

			case UHYVE_PORT_IBV_CLOSE_XRCD: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_close_xrcd_t * args = (uhyve_ibv_close_xrcd_t *) (guest_mem + data);

				int host_ret = ibv_close_xrcd(guest_mem+(size_t)args->xrcd);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_REG_MR: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_reg_mr_t * args = (uhyve_ibv_reg_mr_t *) (guest_mem + data);

				struct ibv_mr * host_ret = ibv_reg_mr(guest_mem+(size_t)args->pd, guest_mem+(size_t)args->addr, length, access);
				memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
				break;
			}

			case UHYVE_PORT_IBV_REREG_MR: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_rereg_mr_t * args = (uhyve_ibv_rereg_mr_t *) (guest_mem + data);

				int host_ret = ibv_rereg_mr(guest_mem+(size_t)args->mr, flags, guest_mem+(size_t)args->pd, guest_mem+(size_t)args->addr, length, access);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_DEREG_MR: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_dereg_mr_t * args = (uhyve_ibv_dereg_mr_t *) (guest_mem + data);

				int host_ret = ibv_dereg_mr(guest_mem+(size_t)args->mr);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_ALLOC_MW: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_alloc_mw_t * args = (uhyve_ibv_alloc_mw_t *) (guest_mem + data);

				struct ibv_mw * host_ret = ibv_alloc_mw(guest_mem+(size_t)args->pd, type);
				memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
				break;
			}

			case UHYVE_PORT_IBV_DEALLOC_MW: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_dealloc_mw_t * args = (uhyve_ibv_dealloc_mw_t *) (guest_mem + data);

				int host_ret = ibv_dealloc_mw(guest_mem+(size_t)args->mw);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_INC_RKEY: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_inc_rkey_t * args = (uhyve_ibv_inc_rkey_t *) (guest_mem + data);

				uint32_t host_ret = ibv_inc_rkey(rkey);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_BIND_MW: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_bind_mw_t * args = (uhyve_ibv_bind_mw_t *) (guest_mem + data);

				int host_ret = ibv_bind_mw(guest_mem+(size_t)args->qp, guest_mem+(size_t)args->mw, guest_mem+(size_t)args->mw_bind);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_CREATE_COMP_CHANNEL: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_create_comp_channel_t * args = (uhyve_ibv_create_comp_channel_t *) (guest_mem + data);

				struct ibv_comp_channel * host_ret = ibv_create_comp_channel(guest_mem+(size_t)args->context);
				memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
				break;
			}

			case UHYVE_PORT_IBV_DESTROY_COMP_CHANNEL: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_destroy_comp_channel_t * args = (uhyve_ibv_destroy_comp_channel_t *) (guest_mem + data);

				int host_ret = ibv_destroy_comp_channel(guest_mem+(size_t)args->channel);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_CREATE_CQ: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_create_cq_t * args = (uhyve_ibv_create_cq_t *) (guest_mem + data);

				struct ibv_cq * host_ret = ibv_create_cq(guest_mem+(size_t)args->context, cqe, guest_mem+(size_t)args->cq_context, guest_mem+(size_t)args->channel, comp_vector);
				memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
				break;
			}

			case UHYVE_PORT_IBV_CREATE_CQ_EX: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_create_cq_ex_t * args = (uhyve_ibv_create_cq_ex_t *) (guest_mem + data);

				struct ibv_cq_ex * host_ret = ibv_create_cq_ex(guest_mem+(size_t)args->context, guest_mem+(size_t)args->cq_attr);
				memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
				break;
			}

			case UHYVE_PORT_IBV_RESIZE_CQ: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_resize_cq_t * args = (uhyve_ibv_resize_cq_t *) (guest_mem + data);

				int host_ret = ibv_resize_cq(guest_mem+(size_t)args->cq, cqe);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_DESTROY_CQ: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_destroy_cq_t * args = (uhyve_ibv_destroy_cq_t *) (guest_mem + data);

				int host_ret = ibv_destroy_cq(guest_mem+(size_t)args->cq);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_GET_CQ_EVENT: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_get_cq_event_t * args = (uhyve_ibv_get_cq_event_t *) (guest_mem + data);

				int host_ret = ibv_get_cq_event(guest_mem+(size_t)args->channel, /* TODO: param cq*/, /* TODO: param cq_context*/);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_ACK_CQ_EVENTS: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_ack_cq_events_t * args = (uhyve_ibv_ack_cq_events_t *) (guest_mem + data);

				void host_ret = ibv_ack_cq_events(guest_mem+(size_t)args->cq, nevents);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_POLL_CQ: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_poll_cq_t * args = (uhyve_ibv_poll_cq_t *) (guest_mem + data);

				int host_ret = ibv_poll_cq(guest_mem+(size_t)args->cq, num_entries, guest_mem+(size_t)args->wc);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_REQ_NOTIFY_CQ: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_req_notify_cq_t * args = (uhyve_ibv_req_notify_cq_t *) (guest_mem + data);

				int host_ret = ibv_req_notify_cq(guest_mem+(size_t)args->cq, solicited_only);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_CREATE_SRQ: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_create_srq_t * args = (uhyve_ibv_create_srq_t *) (guest_mem + data);

				struct ibv_srq * host_ret = ibv_create_srq(guest_mem+(size_t)args->pd, guest_mem+(size_t)args->srq_init_attr);
				memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
				break;
			}

			case UHYVE_PORT_IBV_CREATE_SRQ_EX: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_create_srq_ex_t * args = (uhyve_ibv_create_srq_ex_t *) (guest_mem + data);

				struct ibv_srq * host_ret = ibv_create_srq_ex(guest_mem+(size_t)args->context, guest_mem+(size_t)args->srq_init_attr_ex);
				memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
				break;
			}

			case UHYVE_PORT_IBV_MODIFY_SRQ: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_modify_srq_t * args = (uhyve_ibv_modify_srq_t *) (guest_mem + data);

				int host_ret = ibv_modify_srq(guest_mem+(size_t)args->srq, guest_mem+(size_t)args->srq_attr, srq_attr_mask);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_QUERY_SRQ: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_query_srq_t * args = (uhyve_ibv_query_srq_t *) (guest_mem + data);

				int host_ret = ibv_query_srq(guest_mem+(size_t)args->srq, guest_mem+(size_t)args->srq_attr);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_GET_SRQ_NUM: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_get_srq_num_t * args = (uhyve_ibv_get_srq_num_t *) (guest_mem + data);

				int host_ret = ibv_get_srq_num(guest_mem+(size_t)args->srq, guest_mem+(size_t)args->srq_num);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_DESTROY_SRQ: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_destroy_srq_t * args = (uhyve_ibv_destroy_srq_t *) (guest_mem + data);

				int host_ret = ibv_destroy_srq(guest_mem+(size_t)args->srq);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_POST_SRQ_RECV: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_post_srq_recv_t * args = (uhyve_ibv_post_srq_recv_t *) (guest_mem + data);

				int host_ret = ibv_post_srq_recv(guest_mem+(size_t)args->srq, guest_mem+(size_t)args->recv_wr, /* TODO: param bad_recv_wr*/);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_CREATE_QP: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_create_qp_t * args = (uhyve_ibv_create_qp_t *) (guest_mem + data);

				struct ibv_qp * host_ret = ibv_create_qp(guest_mem+(size_t)args->pd, guest_mem+(size_t)args->qp_init_attr);
				memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
				break;
			}

			case UHYVE_PORT_IBV_CREATE_QP_EX: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_create_qp_ex_t * args = (uhyve_ibv_create_qp_ex_t *) (guest_mem + data);

				struct ibv_qp * host_ret = ibv_create_qp_ex(guest_mem+(size_t)args->context, guest_mem+(size_t)args->qp_init_attr_ex);
				memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
				break;
			}

			case UHYVE_PORT_IBV_QUERY_RT_VALUES_EX: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_query_rt_values_ex_t * args = (uhyve_ibv_query_rt_values_ex_t *) (guest_mem + data);

				int host_ret = ibv_query_rt_values_ex(guest_mem+(size_t)args->context, guest_mem+(size_t)args->values);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_QUERY_DEVICE_EX: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_query_device_ex_t * args = (uhyve_ibv_query_device_ex_t *) (guest_mem + data);

				int host_ret = ibv_query_device_ex(guest_mem+(size_t)args->context, guest_mem+(size_t)args->input, guest_mem+(size_t)args->attr);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_OPEN_QP: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_open_qp_t * args = (uhyve_ibv_open_qp_t *) (guest_mem + data);

				struct ibv_qp * host_ret = ibv_open_qp(guest_mem+(size_t)args->context, guest_mem+(size_t)args->qp_open_attr);
				memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
				break;
			}

			case UHYVE_PORT_IBV_MODIFY_QP: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_modify_qp_t * args = (uhyve_ibv_modify_qp_t *) (guest_mem + data);

				int host_ret = ibv_modify_qp(guest_mem+(size_t)args->qp, guest_mem+(size_t)args->attr, attr_mask);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_QUERY_QP: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_query_qp_t * args = (uhyve_ibv_query_qp_t *) (guest_mem + data);

				int host_ret = ibv_query_qp(guest_mem+(size_t)args->qp, guest_mem+(size_t)args->attr, attr_mask, guest_mem+(size_t)args->init_attr);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_DESTROY_QP: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_destroy_qp_t * args = (uhyve_ibv_destroy_qp_t *) (guest_mem + data);

				int host_ret = ibv_destroy_qp(guest_mem+(size_t)args->qp);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_CREATE_WQ: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_create_wq_t * args = (uhyve_ibv_create_wq_t *) (guest_mem + data);

				struct ibv_wq * host_ret = ibv_create_wq(guest_mem+(size_t)args->context, guest_mem+(size_t)args->wq_init_attr);
				memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
				break;
			}

			case UHYVE_PORT_IBV_MODIFY_WQ: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_modify_wq_t * args = (uhyve_ibv_modify_wq_t *) (guest_mem + data);

				int host_ret = ibv_modify_wq(guest_mem+(size_t)args->wq, guest_mem+(size_t)args->wq_attr);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_DESTROY_WQ: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_destroy_wq_t * args = (uhyve_ibv_destroy_wq_t *) (guest_mem + data);

				int host_ret = ibv_destroy_wq(guest_mem+(size_t)args->wq);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_CREATE_RWQ_IND_TABLE: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_create_rwq_ind_table_t * args = (uhyve_ibv_create_rwq_ind_table_t *) (guest_mem + data);

				struct ibv_rwq_ind_table * host_ret = ibv_create_rwq_ind_table(guest_mem+(size_t)args->context, guest_mem+(size_t)args->init_attr);
				memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
				break;
			}

			case UHYVE_PORT_IBV_DESTROY_RWQ_IND_TABLE: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_destroy_rwq_ind_table_t * args = (uhyve_ibv_destroy_rwq_ind_table_t *) (guest_mem + data);

				int host_ret = ibv_destroy_rwq_ind_table(guest_mem+(size_t)args->rwq_ind_table);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_POST_SEND: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_post_send_t * args = (uhyve_ibv_post_send_t *) (guest_mem + data);

				int host_ret = ibv_post_send(guest_mem+(size_t)args->qp, guest_mem+(size_t)args->wr, /* TODO: param bad_wr*/);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_POST_RECV: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_post_recv_t * args = (uhyve_ibv_post_recv_t *) (guest_mem + data);

				int host_ret = ibv_post_recv(guest_mem+(size_t)args->qp, guest_mem+(size_t)args->wr, /* TODO: param bad_wr*/);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_CREATE_AH: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_create_ah_t * args = (uhyve_ibv_create_ah_t *) (guest_mem + data);

				struct ibv_ah * host_ret = ibv_create_ah(guest_mem+(size_t)args->pd, guest_mem+(size_t)args->attr);
				memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
				break;
			}

			case UHYVE_PORT_IBV_INIT_AH_FROM_WC: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_init_ah_from_wc_t * args = (uhyve_ibv_init_ah_from_wc_t *) (guest_mem + data);

				int host_ret = ibv_init_ah_from_wc(guest_mem+(size_t)args->context, port_num, guest_mem+(size_t)args->wc, guest_mem+(size_t)args->grh, guest_mem+(size_t)args->ah_attr);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_CREATE_AH_FROM_WC: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_create_ah_from_wc_t * args = (uhyve_ibv_create_ah_from_wc_t *) (guest_mem + data);

				struct ibv_ah * host_ret = ibv_create_ah_from_wc(guest_mem+(size_t)args->pd, guest_mem+(size_t)args->wc, guest_mem+(size_t)args->grh, port_num);
				memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
				break;
			}

			case UHYVE_PORT_IBV_DESTROY_AH: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_destroy_ah_t * args = (uhyve_ibv_destroy_ah_t *) (guest_mem + data);

				int host_ret = ibv_destroy_ah(guest_mem+(size_t)args->ah);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_ATTACH_MCAST: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_attach_mcast_t * args = (uhyve_ibv_attach_mcast_t *) (guest_mem + data);

				int host_ret = ibv_attach_mcast(guest_mem+(size_t)args->qp, guest_mem+(size_t)args->gid, lid);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_DETACH_MCAST: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_detach_mcast_t * args = (uhyve_ibv_detach_mcast_t *) (guest_mem + data);

				int host_ret = ibv_detach_mcast(guest_mem+(size_t)args->qp, guest_mem+(size_t)args->gid, lid);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_FORK_INIT: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_fork_init_t * args = (uhyve_ibv_fork_init_t *) (guest_mem + data);

				int host_ret = ibv_fork_init();
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_NODE_TYPE_STR: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_node_type_str_t * args = (uhyve_ibv_node_type_str_t *) (guest_mem + data);

				const char * host_ret = ibv_node_type_str(node_type);
				memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
				break;
			}

			case UHYVE_PORT_IBV_PORT_STATE_STR: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_port_state_str_t * args = (uhyve_ibv_port_state_str_t *) (guest_mem + data);

				const char * host_ret = ibv_port_state_str(port_state);
				memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
				break;
			}

			case UHYVE_PORT_IBV_EVENT_TYPE_STR: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_event_type_str_t * args = (uhyve_ibv_event_type_str_t *) (guest_mem + data);

				const char * host_ret = ibv_event_type_str(event);
				memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
				break;
			}

			case UHYVE_PORT_IBV_RESOLVE_ETH_L2_FROM_GID: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_resolve_eth_l2_from_gid_t * args = (uhyve_ibv_resolve_eth_l2_from_gid_t *) (guest_mem + data);

				int host_ret = ibv_resolve_eth_l2_from_gid(guest_mem+(size_t)args->context, guest_mem+(size_t)args->attr, eth_mac, guest_mem+(size_t)args->vid);
				args->ret = host_ret;
				break;
			}

			case UHYVE_PORT_IBV_IS_QPT_SUPPORTED: {
				unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
				uhyve_ibv_is_qpt_supported_t * args = (uhyve_ibv_is_qpt_supported_t *) (guest_mem + data);

				int host_ret = ibv_is_qpt_supported(caps, qpt);
				args->ret = host_ret;
				break;
			}
