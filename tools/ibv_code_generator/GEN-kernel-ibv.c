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


