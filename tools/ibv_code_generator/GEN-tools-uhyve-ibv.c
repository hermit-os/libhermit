
void call_ibv_open_device(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_open_device_t * args = (uhyve_ibv_open_device_t *) (guest_mem + data);

	struct ibv_context * host_ret = 	(guest_mem+(size_t)args->device);
	memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
	// TODO: Convert ptrs contained in return value.
	// TODO: Delete host_ret data structure.
}

void call_ibv_get_device_list(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_get_device_list_t * args = (uhyve_ibv_get_device_list_t *) (guest_mem + data);

	struct ibv_device ** host_ret = 	(guest_mem+(size_t)args->num_devices);
	// TODO: Take care of struct ibv_device ** return value.
}

void call_ibv_get_device_name(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_get_device_name_t * args = (uhyve_ibv_get_device_name_t *) (guest_mem + data);

	const char * host_ret = 	(guest_mem+(size_t)args->device);
	memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
	// TODO: Convert ptrs contained in return value.
	// TODO: Delete host_ret data structure.
}

void call_ibv_query_port(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_query_port_t * args = (uhyve_ibv_query_port_t *) (guest_mem + data);

	int host_ret = 	(guest_mem+(size_t)args->context, port_num, guest_mem+(size_t)args->port_attr);
	args->ret = host_ret;
}

void call_ibv_create_comp_channel(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_create_comp_channel_t * args = (uhyve_ibv_create_comp_channel_t *) (guest_mem + data);

	struct ibv_comp_channel * host_ret = 	(guest_mem+(size_t)args->context);
	memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
	// TODO: Convert ptrs contained in return value.
	// TODO: Delete host_ret data structure.
}

void call_ibv_alloc_pd(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_alloc_pd_t * args = (uhyve_ibv_alloc_pd_t *) (guest_mem + data);

	struct ibv_pd * host_ret = 	(guest_mem+(size_t)args->context);
	memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
	// TODO: Convert ptrs contained in return value.
	// TODO: Delete host_ret data structure.
}

void call_ibv_reg_mr(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_reg_mr_t * args = (uhyve_ibv_reg_mr_t *) (guest_mem + data);

	struct ibv_mr * host_ret = 	(guest_mem+(size_t)args->pd, guest_mem+(size_t)args->addr, length, access);
	memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
	// TODO: Convert ptrs contained in return value.
	// TODO: Delete host_ret data structure.
}

void call_ibv_create_cq(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_create_cq_t * args = (uhyve_ibv_create_cq_t *) (guest_mem + data);

	struct ibv_cq * host_ret = 	(guest_mem+(size_t)args->context, cqe, guest_mem+(size_t)args->cq_context, guest_mem+(size_t)args->channel, comp_vector);
	memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
	// TODO: Convert ptrs contained in return value.
	// TODO: Delete host_ret data structure.
}

void call_ibv_create_qp(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_create_qp_t * args = (uhyve_ibv_create_qp_t *) (guest_mem + data);

	struct ibv_qp * host_ret = 	(guest_mem+(size_t)args->pd, guest_mem+(size_t)args->qp_init_attr);
	memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
	// TODO: Convert ptrs contained in return value.
	// TODO: Delete host_ret data structure.
}

void call_ibv_query_qp(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_query_qp_t * args = (uhyve_ibv_query_qp_t *) (guest_mem + data);

	int host_ret = 	(guest_mem+(size_t)args->qp, guest_mem+(size_t)args->attr, attr_mask, guest_mem+(size_t)args->init_attr);
	args->ret = host_ret;
}

void call_ibv_modify_qp(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_modify_qp_t * args = (uhyve_ibv_modify_qp_t *) (guest_mem + data);

	int host_ret = 	(guest_mem+(size_t)args->qp, guest_mem+(size_t)args->attr, attr_mask);
	args->ret = host_ret;
}

void call_ibv_destroy_qp(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_destroy_qp_t * args = (uhyve_ibv_destroy_qp_t *) (guest_mem + data);

	int host_ret = 	(guest_mem+(size_t)args->qp);
	args->ret = host_ret;
}

void call_ibv_destroy_cq(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_destroy_cq_t * args = (uhyve_ibv_destroy_cq_t *) (guest_mem + data);

	int host_ret = 	(guest_mem+(size_t)args->cq);
	args->ret = host_ret;
}

void call_ibv_dereg_mr(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_dereg_mr_t * args = (uhyve_ibv_dereg_mr_t *) (guest_mem + data);

	int host_ret = 	(guest_mem+(size_t)args->mr);
	args->ret = host_ret;
}

void call_ibv_dealloc_pd(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_dealloc_pd_t * args = (uhyve_ibv_dealloc_pd_t *) (guest_mem + data);

	int host_ret = 	(guest_mem+(size_t)args->pd);
	args->ret = host_ret;
}

void call_ibv_destroy_comp_channel(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_destroy_comp_channel_t * args = (uhyve_ibv_destroy_comp_channel_t *) (guest_mem + data);

	int host_ret = 	(guest_mem+(size_t)args->channel);
	args->ret = host_ret;
}

void call_ibv_close_device(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_close_device_t * args = (uhyve_ibv_close_device_t *) (guest_mem + data);

	int host_ret = 	(guest_mem+(size_t)args->context);
	args->ret = host_ret;
}
