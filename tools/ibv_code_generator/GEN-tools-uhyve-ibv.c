void call_ibv_open_device(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_open_device_t * args = (uhyve_ibv_open_device_t *) (guest_mem + data);

	struct ibv_context * host_ret = ibv_open_device(guest_mem+(size_t)args->device);
	memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
	// TODO: Convert ptrs contained in return value.
	// TODO: Delete host_ret data structure.
}

void call_ibv_get_device_name(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_get_device_name_t * args = (uhyve_ibv_get_device_name_t *) (guest_mem + data);

	const char * host_ret = ibv_get_device_name(guest_mem+(size_t)args->device);
	memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
	// TODO: Convert ptrs contained in return value.
	// TODO: Delete host_ret data structure.
}

void call_ibv_query_port(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_query_port_t * args = (uhyve_ibv_query_port_t *) (guest_mem + data);

	int host_ret = ibv_query_port(guest_mem+(size_t)args->context, port_num, guest_mem+(size_t)args->port_attr);
	args->ret = host_ret;
}

void call_ibv_create_comp_channel(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_create_comp_channel_t * args = (uhyve_ibv_create_comp_channel_t *) (guest_mem + data);

	struct ibv_comp_channel * host_ret = ibv_create_comp_channel(guest_mem+(size_t)args->context);
	memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
	// TODO: Convert ptrs contained in return value.
	// TODO: Delete host_ret data structure.
}
