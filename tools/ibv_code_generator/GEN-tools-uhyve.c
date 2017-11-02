
			case UHYVE_PORT_IBV_OPEN_DEVICE:
				call_ibv_open_device(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_GET_DEVICE_LIST:
				call_ibv_get_device_list(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_GET_DEVICE_NAME:
				call_ibv_get_device_name(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_QUERY_PORT:
				call_ibv_query_port(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_CREATE_COMP_CHANNEL:
				call_ibv_create_comp_channel(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_ALLOC_PD:
				call_ibv_alloc_pd(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_REG_MR:
				call_ibv_reg_mr(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_CREATE_CQ:
				call_ibv_create_cq(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_CREATE_QP:
				call_ibv_create_qp(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_QUERY_QP:
				call_ibv_query_qp(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_MODIFY_QP:
				call_ibv_modify_qp(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_DESTROY_QP:
				call_ibv_destroy_qp(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_DESTROY_CQ:
				call_ibv_destroy_cq(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_DEREG_MR:
				call_ibv_dereg_mr(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_DEALLOC_PD:
				call_ibv_dealloc_pd(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_DESTROY_COMP_CHANNEL:
				call_ibv_destroy_comp_channel(run, guest_mem);
				break;
			case UHYVE_PORT_IBV_CLOSE_DEVICE:
				call_ibv_close_device(run, guest_mem);
				break;