typedef struct {
	// Parameters:
	struct ibv_device * device;
	// Return value:
	struct ibv_context * ret;
} __attribute__((packed)) uhyve_ibv_open_device_t;

struct ibv_context * ibv_open_device(struct ibv_device * device) {
	uhyve_ibv_open_device_t uhyve_args;
	uhyve_args->device = (struct ibv_device *) virt_to_phys((size_t) device);

	uhyve_args->ret = kmalloc(sizeof(struct ibv_context));

	uhyve_send(UHYVE_PORT_IBV_OPEN_DEVICE, (unsigned) virt_to_phys((size_t) &uhyve_args));

	// TODO: Fix pointers in returned data structures.
	return uhyve_args.ret;
}


typedef struct {
	// Parameters:
	int * num_devices;
	// Return value:
	struct ibv_device ** ret;
} __attribute__((packed)) uhyve_ibv_get_device_list_t;

struct ibv_device ** ibv_get_device_list(int * num_devices) {
	uhyve_ibv_get_device_list_t uhyve_args;
	uhyve_args->num_devices = (int *) virt_to_phys((size_t) num_devices);

	// TODO: Take care of return value.

	uhyve_send(UHYVE_PORT_IBV_GET_DEVICE_LIST, (unsigned) virt_to_phys((size_t) &uhyve_args));

	// TODO: Fix pointers in returned data structures.
	return uhyve_args.ret;
}


typedef struct {
	// Parameters:
	struct ibv_device * device;
	// Return value:
	const char * ret;
} __attribute__((packed)) uhyve_ibv_get_device_name_t;

const char * ibv_get_device_name(struct ibv_device * device) {
	uhyve_ibv_get_device_name_t uhyve_args;
	uhyve_args->device = (struct ibv_device *) virt_to_phys((size_t) device);

	uhyve_args->ret = kmalloc(sizeof(const char));

	uhyve_send(UHYVE_PORT_IBV_GET_DEVICE_NAME, (unsigned) virt_to_phys((size_t) &uhyve_args));

	// TODO: Fix pointers in returned data structures.
	return uhyve_args.ret;
}


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
	uhyve_args->context = (struct ibv_context *) virt_to_phys((size_t) context);
	uhyve_args->port_num = port_num;
	uhyve_args->port_attr = (struct ibv_port_attr *) virt_to_phys((size_t) port_attr);

	uhyve_send(UHYVE_PORT_IBV_QUERY_PORT, (unsigned) virt_to_phys((size_t) &uhyve_args));

	// TODO: Fix pointers in returned data structures.
	return uhyve_args.ret;
}


typedef struct {
	// Parameters:
	struct ibv_context * context;
	// Return value:
	struct ibv_comp_channel * ret;
} __attribute__((packed)) uhyve_ibv_create_comp_channel_t;

struct ibv_comp_channel * ibv_create_comp_channel(struct ibv_context * context) {
	uhyve_ibv_create_comp_channel_t uhyve_args;
	uhyve_args->context = (struct ibv_context *) virt_to_phys((size_t) context);

	uhyve_args->ret = kmalloc(sizeof(struct ibv_comp_channel));

	uhyve_send(UHYVE_PORT_IBV_CREATE_COMP_CHANNEL, (unsigned) virt_to_phys((size_t) &uhyve_args));

	// TODO: Fix pointers in returned data structures.
	return uhyve_args.ret;
}


typedef struct {
	// Parameters:
	struct ibv_context * context;
	// Return value:
	struct ibv_pd * ret;
} __attribute__((packed)) uhyve_ibv_alloc_pd_t;

struct ibv_pd * ibv_alloc_pd(struct ibv_context * context) {
	uhyve_ibv_alloc_pd_t uhyve_args;
	uhyve_args->context = (struct ibv_context *) virt_to_phys((size_t) context);

	uhyve_args->ret = kmalloc(sizeof(struct ibv_pd));

	uhyve_send(UHYVE_PORT_IBV_ALLOC_PD, (unsigned) virt_to_phys((size_t) &uhyve_args));

	// TODO: Fix pointers in returned data structures.
	return uhyve_args.ret;
}


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
	uhyve_args->pd = (struct ibv_pd *) virt_to_phys((size_t) pd);
	uhyve_args->addr = (void *) virt_to_phys((size_t) addr);
	uhyve_args->length = length;
	uhyve_args->access = access;

	uhyve_args->ret = kmalloc(sizeof(struct ibv_mr));

	uhyve_send(UHYVE_PORT_IBV_REG_MR, (unsigned) virt_to_phys((size_t) &uhyve_args));

	// TODO: Fix pointers in returned data structures.
	return uhyve_args.ret;
}


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
	uhyve_args->context = (struct ibv_context *) virt_to_phys((size_t) context);
	uhyve_args->cqe = cqe;
	uhyve_args->cq_context = (void *) virt_to_phys((size_t) cq_context);
	uhyve_args->channel = (struct ibv_comp_channel *) virt_to_phys((size_t) channel);
	uhyve_args->comp_vector = comp_vector;

	uhyve_args->ret = kmalloc(sizeof(struct ibv_cq));

	uhyve_send(UHYVE_PORT_IBV_CREATE_CQ, (unsigned) virt_to_phys((size_t) &uhyve_args));

	// TODO: Fix pointers in returned data structures.
	return uhyve_args.ret;
}


typedef struct {
	// Parameters:
	struct ibv_pd * pd;
	struct ibv_qp_init_attr * qp_init_attr;
	// Return value:
	struct ibv_qp * ret;
} __attribute__((packed)) uhyve_ibv_create_qp_t;

struct ibv_qp * ibv_create_qp(struct ibv_pd * pd, struct ibv_qp_init_attr * qp_init_attr) {
	uhyve_ibv_create_qp_t uhyve_args;
	uhyve_args->pd = (struct ibv_pd *) virt_to_phys((size_t) pd);
	uhyve_args->qp_init_attr = (struct ibv_qp_init_attr *) virt_to_phys((size_t) qp_init_attr);

	uhyve_args->ret = kmalloc(sizeof(struct ibv_qp));

	uhyve_send(UHYVE_PORT_IBV_CREATE_QP, (unsigned) virt_to_phys((size_t) &uhyve_args));

	// TODO: Fix pointers in returned data structures.
	return uhyve_args.ret;
}


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
	uhyve_args->qp = (struct ibv_qp *) virt_to_phys((size_t) qp);
	uhyve_args->attr = (struct ibv_qp_attr *) virt_to_phys((size_t) attr);
	uhyve_args->attr_mask = attr_mask;
	uhyve_args->init_attr = (struct ibv_qp_init_attr *) virt_to_phys((size_t) init_attr);

	uhyve_send(UHYVE_PORT_IBV_QUERY_QP, (unsigned) virt_to_phys((size_t) &uhyve_args));

	// TODO: Fix pointers in returned data structures.
	return uhyve_args.ret;
}


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
	uhyve_args->qp = (struct ibv_qp *) virt_to_phys((size_t) qp);
	uhyve_args->attr = (struct ibv_qp_attr *) virt_to_phys((size_t) attr);
	uhyve_args->attr_mask = attr_mask;

	uhyve_send(UHYVE_PORT_IBV_MODIFY_QP, (unsigned) virt_to_phys((size_t) &uhyve_args));

	// TODO: Fix pointers in returned data structures.
	return uhyve_args.ret;
}


typedef struct {
	// Parameters:
	struct ibv_qp * qp;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_destroy_qp_t;

int ibv_destroy_qp(struct ibv_qp * qp) {
	uhyve_ibv_destroy_qp_t uhyve_args;
	uhyve_args->qp = (struct ibv_qp *) virt_to_phys((size_t) qp);

	uhyve_send(UHYVE_PORT_IBV_DESTROY_QP, (unsigned) virt_to_phys((size_t) &uhyve_args));

	// TODO: Fix pointers in returned data structures.
	return uhyve_args.ret;
}


typedef struct {
	// Parameters:
	struct ibv_cq * cq;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_destroy_cq_t;

int ibv_destroy_cq(struct ibv_cq * cq) {
	uhyve_ibv_destroy_cq_t uhyve_args;
	uhyve_args->cq = (struct ibv_cq *) virt_to_phys((size_t) cq);

	uhyve_send(UHYVE_PORT_IBV_DESTROY_CQ, (unsigned) virt_to_phys((size_t) &uhyve_args));

	// TODO: Fix pointers in returned data structures.
	return uhyve_args.ret;
}


typedef struct {
	// Parameters:
	struct ibv_mr * mr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_dereg_mr_t;

int ibv_dereg_mr(struct ibv_mr * mr) {
	uhyve_ibv_dereg_mr_t uhyve_args;
	uhyve_args->mr = (struct ibv_mr *) virt_to_phys((size_t) mr);

	uhyve_send(UHYVE_PORT_IBV_DEREG_MR, (unsigned) virt_to_phys((size_t) &uhyve_args));

	// TODO: Fix pointers in returned data structures.
	return uhyve_args.ret;
}


typedef struct {
	// Parameters:
	struct ibv_pd * pd;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_dealloc_pd_t;

int ibv_dealloc_pd(struct ibv_pd * pd) {
	uhyve_ibv_dealloc_pd_t uhyve_args;
	uhyve_args->pd = (struct ibv_pd *) virt_to_phys((size_t) pd);

	uhyve_send(UHYVE_PORT_IBV_DEALLOC_PD, (unsigned) virt_to_phys((size_t) &uhyve_args));

	// TODO: Fix pointers in returned data structures.
	return uhyve_args.ret;
}


typedef struct {
	// Parameters:
	struct ibv_comp_channel * channel;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_destroy_comp_channel_t;

int ibv_destroy_comp_channel(struct ibv_comp_channel * channel) {
	uhyve_ibv_destroy_comp_channel_t uhyve_args;
	uhyve_args->channel = (struct ibv_comp_channel *) virt_to_phys((size_t) channel);

	uhyve_send(UHYVE_PORT_IBV_DESTROY_COMP_CHANNEL, (unsigned) virt_to_phys((size_t) &uhyve_args));

	// TODO: Fix pointers in returned data structures.
	return uhyve_args.ret;
}


typedef struct {
	// Parameters:
	struct ibv_context * context;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_close_device_t;

int ibv_close_device(struct ibv_context * context) {
	uhyve_ibv_close_device_t uhyve_args;
	uhyve_args->context = (struct ibv_context *) virt_to_phys((size_t) context);

	uhyve_send(UHYVE_PORT_IBV_CLOSE_DEVICE, (unsigned) virt_to_phys((size_t) &uhyve_args));

	// TODO: Fix pointers in returned data structures.
	return uhyve_args.ret;
}


