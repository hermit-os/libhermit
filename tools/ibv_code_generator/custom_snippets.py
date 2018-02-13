BACKUP_AND_CONVERT = 2
REVERT = 1

# TODO anni: andere functionen hier noch zufügen

recv_wrs_backup_and_convert = \
"""
	struct ibv_recv_wr * curr_wr;
	int num_sges_max;
	int num_wrs;

	// Number of work requests in linked list and SGEs in each WR
	num_wrs = 0;
	num_sges_max = 0;
	for (curr_wr = recv_wr; curr_wr; curr_wr = curr_wr->next) {
		num_wrs++;
		if (num_sges_max < curr_wr->num_sge) {
			num_sges_max = curr_wr->num_sge;
		}
	}

	// Backup arrays for original guest memory pointers
	struct ibv_recv_wr * wr__next         [num_wrs];
	struct ibv_sge *     wr__sg_list      [num_wrs];
	uint64_t             wr__sg_list__addr[num_wrs][num_sges_max];

	curr_wr = recv_wr;
	for (int w = 0; w < num_wrs; w++) {
		// Next pointer
		wr__next[w] = curr_wr->next;
		curr_wr->next = (struct ibv_recv_wr *) guest_to_host((size_t) curr_wr->next);

		// SGE array
		for (int s = 0; s < curr_wr->num_sge; s++) {
			wr__sg_list__addr[w][s] = curr_wr->sg_list[s].addr;
			curr_wr->sg_list[s].addr = (uint64_t) guest_to_host((size_t) curr_wr->sg_list[s].addr);
		}

		wr__sg_list[w] = curr_wr->sg_list;
		curr_wr->sg_list = (struct ibv_sge *) guest_to_host((size_t) curr_wr->sg_list);

		curr_wr = wr__next[w];
	}
"""

recv_wrs_revert = \
"""
	if (*bad_recv_wr && *bad_recv_wr == uhyve_args.recv_wr) {
		*bad_recv_wr = recv_wr;
	}

	curr_wr = recv_wr;
	for (int w = 0; w < num_wrs; w++) {
		if (*bad_recv_wr && *bad_recv_wr == curr_wr->next) {
			*bad_recv_wr = wr__next[w];
		}

		curr_wr->next    = wr__next[w];
		curr_wr->sg_list = wr__sg_list[w];
		for (int s = 0; s < curr_wr->num_sge; s++) {
			curr_wr->sg_list[s].addr = wr__sg_list__addr[w][s];
		}

		curr_wr = curr_wr->next;
	}
"""


backup_and_convert_send_wrs = \
"""
	struct ibv_send_wr * curr_wr;
	int num_wrs;
	int num_sges_max;
	int is_bind_mw, is_tso;

	// Number of work requests in linked list and SGEs in each WR
	num_wrs = 0;
	num_sges_max = 0;
	for (curr_wr = wr; curr_wr; curr_wr = curr_wr->next) {
		num_wrs++;
		if (num_sges_max < curr_wr->num_sge) {
			num_sges_max = curr_wr->num_sge;
		}
	}

	// Backup arrays for original guest memory pointers
	struct ibv_send_wr * wr__next                    [num_wrs];
	struct ibv_sge *     wr__sg_list                 [num_wrs];
	uint64_t             wr__sg_list__addr           [num_wrs][num_sges_max];
	uint64_t             wr__bind_mw__bind_info__addr[num_wrs];
	void *               wr__tso__hdr                [num_wrs];

	curr_wr = wr;
	for (int w = 0; w < num_wrs; w++) {
		is_bind_mw = curr_wr->opcode == IBV_WR_BIND_MW;
		is_tso     = curr_wr->opcode == IBV_WR_TSO;

		// union: bind_mw and tso
		if (is_bind_mw) {
			wr__bind_mw__bind_info__addr[w] = curr_wr->bind_mw.bind_info.addr;
			curr_wr->bind_mw.bind_info.addr = (uint64_t) guest_to_host((size_t) curr_wr->bind_mw.bind_info.addr);
		} else if (is_tso) {
			wr__tso__hdr[w] = curr_wr->tso.hdr;
			curr_wr->tso.hdr = (void *) guest_to_host((size_t) curr_wr->tso.hdr);
		}

		// Next pointer and SGE array
		wr__next[w] = curr_wr->next;
		curr_wr->next = (struct ibv_send_wr *) guest_to_host((size_t) curr_wr->next);

		for (int s = 0; s < curr_wr->num_sge; s++) {
			wr__sg_list__addr[w][s] = curr_wr->sg_list[s].addr;
			curr_wr->sg_list[s].addr = (uint64_t) guest_to_host((size_t) curr_wr->sg_list[s].addr);
		}

		wr__sg_list[w] = curr_wr->sg_list;
		curr_wr->sg_list = (struct ibv_sge *) guest_to_host((size_t) curr_wr->sg_list);

		curr_wr = wr__next[w];
	}
"""

send_wrs_revert = \
"""
	if (*bad_wr && *bad_wr == uhyve_args.wr) {
		*bad_wr = wr;
	}

	curr_wr = wr;
	for (int w = 0; w < num_wrs; w++) {
		is_bind_mw = curr_wr->opcode == IBV_WR_BIND_MW;
		is_tso     = curr_wr->opcode == IBV_WR_TSO;

		// union: bind_mw and tso
		if (is_bind_mw) {
			 curr_wr->bind_mw.bind_info.addr = wr__bind_mw__bind_info__addr[w];
		} else if (is_tso) {
			 curr_wr->tso.hdr = wr__tso__hdr[w];
		}

		// Bad request
		if (*bad_wr && *bad_wr == curr_wr->next) {
			*bad_wr = wr__next[w];
		}

		// Next pointer and SGE array
		curr_wr->next = wr__next[w];
		curr_wr->sg_list = wr__sg_list[w];
		for (int s = 0; s < curr_wr->num_sge; s++) {
			curr_wr->sg_list[s].addr = wr__sg_list__addr[w][s];
		}

		curr_wr = curr_wr->next;
	}
"""


def generate(name, part):
  if name is "ibv_post_send":
    if part is BACKUP_AND_CONVERT:
      return send_wrs_backup_and_convert
    else:
      return send_wrs_revert

  if name is "ibv_post_recv" or name is "ibv_post_srq_recv" or name is "ibv_post_wq_recv":
    if part is BACKUP_AND_CONVERT:
      return recv_wrs_backup_and_convert
    else:
      return recv_wrs_revert

