			case UHYVE_PORT_IBV_OPEN_DEVICE:
				call_ibv_open_device(run, guest_mem);
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
