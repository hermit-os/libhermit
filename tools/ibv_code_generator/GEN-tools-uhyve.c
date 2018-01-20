			case UHYVE_PORT_SET_IB_POOL_ADDR: {
					unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
					uint64_t * temp = (uint64_t*)(guest_mem + data);
					ib_pool_addr = (uint8_t*) *temp;
					ib_pool_top = ib_pool_addr;
					break;
			}

			case UHYVE_PORT_IBV_WC_STATUS_STR:
				call_ibv_wc_status_str(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_RATE_TO_MULT:
				call_ibv_rate_to_mult(run, guest_mem);
				break;
			case UHYVE_PORT_MULT_TO_IBV_RATE:
				call_mult_to_ibv_rate(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_RATE_TO_MBPS:
				call_ibv_rate_to_mbps(run, guest_mem);
				break;
			case UHYVE_PORT_MBPS_TO_IBV_RATE:
				call_mbps_to_ibv_rate(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_CQ_EX_TO_CQ:
				call_ibv_cq_ex_to_cq(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_START_POLL:
				call_ibv_start_poll(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_NEXT_POLL:
				call_ibv_next_poll(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_END_POLL:
				call_ibv_end_poll(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_WC_READ_OPCODE:
				call_ibv_wc_read_opcode(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_WC_READ_VENDOR_ERR:
				call_ibv_wc_read_vendor_err(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_WC_READ_BYTE_LEN:
				call_ibv_wc_read_byte_len(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_WC_READ_IMM_DATA:
				call_ibv_wc_read_imm_data(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_WC_READ_INVALIDATED_RKEY:
				call_ibv_wc_read_invalidated_rkey(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_WC_READ_QP_NUM:
				call_ibv_wc_read_qp_num(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_WC_READ_SRC_QP:
				call_ibv_wc_read_src_qp(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_WC_READ_WC_FLAGS:
				call_ibv_wc_read_wc_flags(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_WC_READ_SLID:
				call_ibv_wc_read_slid(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_WC_READ_SL:
				call_ibv_wc_read_sl(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_WC_READ_DLID_PATH_BITS:
				call_ibv_wc_read_dlid_path_bits(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_WC_READ_COMPLETION_TS:
				call_ibv_wc_read_completion_ts(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_WC_READ_CVLAN:
				call_ibv_wc_read_cvlan(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_WC_READ_FLOW_TAG:
				call_ibv_wc_read_flow_tag(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_POST_WQ_RECV:
				call_ibv_post_wq_recv(run, guest_mem);
				break;
			case UHYVE_PORT_VERBS_GET_CTX:
				call_verbs_get_ctx(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_GET_DEVICE_LIST:
				call_ibv_get_device_list(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_FREE_DEVICE_LIST:
				call_ibv_free_device_list(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_GET_DEVICE_NAME:
				call_ibv_get_device_name(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_GET_DEVICE_GUID:
				call_ibv_get_device_guid(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_OPEN_DEVICE:
				call_ibv_open_device(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_CLOSE_DEVICE:
				call_ibv_close_device(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_GET_ASYNC_EVENT:
				call_ibv_get_async_event(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_ACK_ASYNC_EVENT:
				call_ibv_ack_async_event(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_QUERY_DEVICE:
				call_ibv_query_device(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_QUERY_PORT:
				call_ibv_query_port(run, guest_mem);
				break;
			case UHYVE_PORT____IBV_QUERY_PORT:
				call____ibv_query_port(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_QUERY_GID:
				call_ibv_query_gid(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_QUERY_PKEY:
				call_ibv_query_pkey(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_ALLOC_PD:
				call_ibv_alloc_pd(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_DEALLOC_PD:
				call_ibv_dealloc_pd(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_CREATE_FLOW:
				call_ibv_create_flow(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_DESTROY_FLOW:
				call_ibv_destroy_flow(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_OPEN_XRCD:
				call_ibv_open_xrcd(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_CLOSE_XRCD:
				call_ibv_close_xrcd(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_REG_MR:
				call_ibv_reg_mr(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_REREG_MR:
				call_ibv_rereg_mr(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_DEREG_MR:
				call_ibv_dereg_mr(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_ALLOC_MW:
				call_ibv_alloc_mw(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_DEALLOC_MW:
				call_ibv_dealloc_mw(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_INC_RKEY:
				call_ibv_inc_rkey(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_BIND_MW:
				call_ibv_bind_mw(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_CREATE_COMP_CHANNEL:
				call_ibv_create_comp_channel(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_DESTROY_COMP_CHANNEL:
				call_ibv_destroy_comp_channel(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_CREATE_CQ:
				call_ibv_create_cq(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_CREATE_CQ_EX:
				call_ibv_create_cq_ex(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_RESIZE_CQ:
				call_ibv_resize_cq(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_DESTROY_CQ:
				call_ibv_destroy_cq(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_GET_CQ_EVENT:
				call_ibv_get_cq_event(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_ACK_CQ_EVENTS:
				call_ibv_ack_cq_events(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_POLL_CQ:
				call_ibv_poll_cq(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_REQ_NOTIFY_CQ:
				call_ibv_req_notify_cq(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_CREATE_SRQ:
				call_ibv_create_srq(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_CREATE_SRQ_EX:
				call_ibv_create_srq_ex(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_MODIFY_SRQ:
				call_ibv_modify_srq(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_QUERY_SRQ:
				call_ibv_query_srq(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_GET_SRQ_NUM:
				call_ibv_get_srq_num(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_DESTROY_SRQ:
				call_ibv_destroy_srq(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_POST_SRQ_RECV:
				call_ibv_post_srq_recv(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_CREATE_QP:
				call_ibv_create_qp(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_CREATE_QP_EX:
				call_ibv_create_qp_ex(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_QUERY_RT_VALUES_EX:
				call_ibv_query_rt_values_ex(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_QUERY_DEVICE_EX:
				call_ibv_query_device_ex(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_OPEN_QP:
				call_ibv_open_qp(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_MODIFY_QP:
				call_ibv_modify_qp(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_QUERY_QP:
				call_ibv_query_qp(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_DESTROY_QP:
				call_ibv_destroy_qp(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_CREATE_WQ:
				call_ibv_create_wq(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_MODIFY_WQ:
				call_ibv_modify_wq(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_DESTROY_WQ:
				call_ibv_destroy_wq(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_CREATE_RWQ_IND_TABLE:
				call_ibv_create_rwq_ind_table(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_DESTROY_RWQ_IND_TABLE:
				call_ibv_destroy_rwq_ind_table(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_POST_SEND:
				call_ibv_post_send(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_POST_RECV:
				call_ibv_post_recv(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_CREATE_AH:
				call_ibv_create_ah(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_INIT_AH_FROM_WC:
				call_ibv_init_ah_from_wc(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_CREATE_AH_FROM_WC:
				call_ibv_create_ah_from_wc(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_DESTROY_AH:
				call_ibv_destroy_ah(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_ATTACH_MCAST:
				call_ibv_attach_mcast(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_DETACH_MCAST:
				call_ibv_detach_mcast(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_FORK_INIT:
				call_ibv_fork_init(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_NODE_TYPE_STR:
				call_ibv_node_type_str(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_PORT_STATE_STR:
				call_ibv_port_state_str(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_EVENT_TYPE_STR:
				call_ibv_event_type_str(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_RESOLVE_ETH_L2_FROM_GID:
				call_ibv_resolve_eth_l2_from_gid(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_IS_QPT_SUPPORTED:
				call_ibv_is_qpt_supported(run, guest_mem);
				break;
