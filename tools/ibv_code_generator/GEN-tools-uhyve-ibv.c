void call_ibv_cq_ex_to_cq(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_cq_ex_to_cq_t * args = (uhyve_ibv_cq_ex_to_cq_t *) (guest_mem + data);

	args.ret = ibv_cq_ex_to_cq(args->cq);
}

void call_ibv_start_poll(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_start_poll_t * args = (uhyve_ibv_start_poll_t *) (guest_mem + data);

	args.ret = ibv_start_poll(args->cq, args->attr);
}

void call_ibv_next_poll(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_next_poll_t * args = (uhyve_ibv_next_poll_t *) (guest_mem + data);

	args.ret = ibv_next_poll(args->cq);
}

void call_ibv_end_poll(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_end_poll_t * args = (uhyve_ibv_end_poll_t *) (guest_mem + data);

	ibv_end_poll(args->cq);
}

void call_ibv_wc_read_completion_ts(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_wc_read_completion_ts_t * args = (uhyve_ibv_wc_read_completion_ts_t *) (guest_mem + data);

	args.ret = ibv_wc_read_completion_ts(args->cq);
}

void call_ibv_create_cq_ex(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));
	uhyve_ibv_create_cq_ex_t * args = (uhyve_ibv_create_cq_ex_t *) (guest_mem + data);

	args.ret = ibv_create_cq_ex(args->context, args->cq_attr);
}

