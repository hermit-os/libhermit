typedef enum {
	UHYVE_PORT_IBV_CQ_EX_TO_CQ = 0x510,
	UHYVE_PORT_IBV_START_POLL = 0x511,
	UHYVE_PORT_IBV_NEXT_POLL = 0x512,
	UHYVE_PORT_IBV_END_POLL = 0x513,
	UHYVE_PORT_IBV_WC_READ_COMPLETION_TS = 0x514,
	UHYVE_PORT_IBV_CREATE_CQ_EX = 0x515,
} uhyve_ibv_t;

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	struct ibv_cq * ret;
} __attribute__((packed)) uhyve_ibv_cq_ex_to_cq_t;

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	struct ibv_poll_cq_attr * attr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_start_poll_t;

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_next_poll_t;

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
} __attribute__((packed)) uhyve_ibv_end_poll_t;

typedef struct {
	// Parameters:
	struct ibv_cq_ex * cq;
	// Return value:
	uint64_t ret;
} __attribute__((packed)) uhyve_ibv_wc_read_completion_ts_t;

typedef struct {
	// Parameters:
	struct ibv_context * context;
	struct ibv_cq_init_attr_ex * cq_attr;
	// Return value:
	struct ibv_cq_ex * ret;
} __attribute__((packed)) uhyve_ibv_create_cq_ex_t;



void call_ibv_cq_ex_to_cq(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_start_poll(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_next_poll(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_end_poll(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_wc_read_completion_ts(struct kvm_run * run, uint8_t * guest_mem);
void call_ibv_create_cq_ex(struct kvm_run * run, uint8_t * guest_mem);
