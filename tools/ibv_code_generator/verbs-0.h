struct ibv_srq_init_attr_ex {
	uint32_t		comp_mask;
	struct ibv_srq_attr	attr;
	void		       *srq_context;
	struct ibv_pd	       *pd;
	enum ibv_srq_type	srq_type;
};

