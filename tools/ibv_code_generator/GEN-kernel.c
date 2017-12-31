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
	uhyve_args.attr = attr;

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
	uhyve_args.cq_attr = cq_attr;

	uhyve_send(UHYVE_PORT_IBV_CREATE_CQ_EX, (unsigned) virt_to_phys((size_t) &uhyve_args));

	return uhyve_args.ret;
}


