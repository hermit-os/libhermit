typedef struct {
	// Parameters:
	struct ibv_device * device;
	// Return value:
	struct ibv_context * ret;
} __attribute__((packed)) uhyve_ibv_open_device_t;

typedef struct {
	// Parameters:
	int * num_devices;
	// Return value:
	struct ibv_device ** ret;
} __attribute__((packed)) uhyve_ibv_get_device_list_t;

typedef struct {
	// Parameters:
	struct ibv_device * device;
	// Return value:
	const char * ret;
} __attribute__((packed)) uhyve_ibv_get_device_name_t;

typedef struct {
	// Parameters:
	struct ibv_context * context;
	uint8_t port_num;
	struct ibv_port_attr * port_attr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_query_port_t;

typedef struct {
	// Parameters:
	struct ibv_context * context;
	// Return value:
	struct ibv_comp_channel * ret;
} __attribute__((packed)) uhyve_ibv_create_comp_channel_t;

typedef struct {
	// Parameters:
	struct ibv_context * context;
	// Return value:
	struct ibv_pd * ret;
} __attribute__((packed)) uhyve_ibv_alloc_pd_t;

typedef struct {
	// Parameters:
	struct ibv_pd * pd;
	void * addr;
	int length;
	int access;
	// Return value:
	struct ibv_mr * ret;
} __attribute__((packed)) uhyve_ibv_reg_mr_t;

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

typedef struct {
	// Parameters:
	struct ibv_pd * pd;
	struct ibv_qp_init_attr * qp_init_attr;
	// Return value:
	struct ibv_qp * ret;
} __attribute__((packed)) uhyve_ibv_create_qp_t;

typedef struct {
	// Parameters:
	struct ibv_qp * qp;
	struct ibv_qp_attr * attr;
	int attr_mask;
	struct ibv_qp_init_attr * init_attr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_query_qp_t;

typedef struct {
	// Parameters:
	struct ibv_qp * qp;
	struct ibv_qp_attr * attr;
	int attr_mask;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_modify_qp_t;

typedef struct {
	// Parameters:
	struct ibv_qp * qp;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_destroy_qp_t;

typedef struct {
	// Parameters:
	struct ibv_cq * cq;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_destroy_cq_t;

typedef struct {
	// Parameters:
	struct ibv_mr * mr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_dereg_mr_t;

typedef struct {
	// Parameters:
	struct ibv_pd * pd;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_dealloc_pd_t;

typedef struct {
	// Parameters:
	struct ibv_comp_channel * channel;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_destroy_comp_channel_t;

typedef struct {
	// Parameters:
	struct ibv_context * context;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_close_device_t;

