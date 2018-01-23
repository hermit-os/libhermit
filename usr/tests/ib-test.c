/*
 * Copyright (c) 2017, Annika Wierichs, RWTH Aachen University
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the name of the University nor the names of its contributors
 *      may be used to endorse or promote products derived from this
 *      software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#include <hermit/ibv.h>	// Geht per cmake copy workaround

/* #define N	255 */

/* static void test_handler(int s) */
/* { */
	/* printf("Receive signal with number %d\n", s); */
/* } */

int main(int argc, char** argv)
{
// CONTAINING HOST PTRS:

struct ibv_wq_init_attr {
	void *wq_context; // host
	enum ibv_wq_type wq_type;
	uint32_t max_wr;
	uint32_t max_sge;
	struct ibv_pd *pd; // host
	struct ibv_cq *cq; // host
	uint32_t comp_mask; /* Use ibv_wq_init_attr_mask */
	uint32_t create_flags; /* use ibv_wq_flags */
};

struct ibv_qp_init_attr {
	void *qp_context; // host
	struct ibv_cq *send_cq; // host
	struct ibv_cq *recv_cq; // host
	struct ibv_srq *srq; // host
	struct ibv_qp_cap cap;
	enum ibv_qp_type qp_type;
	int sq_sig_all;
};

struct ibv_qp_init_attr_ex {
	void *qp_context; // host
	struct ibv_cq *send_cq; // host
	struct ibv_cq *recv_cq; // host
	struct ibv_srq *srq; // host
	struct ibv_qp_cap cap;
	enum ibv_qp_type qp_type;
	int sq_sig_all;

	uint32_t comp_mask;
	struct ibv_pd *pd; // host
	struct ibv_xrcd *xrcd; // host
	uint32_t create_flags;
	uint16_t max_tso_header;
	struct ibv_rwq_ind_table *rwq_ind_tbl; // host
	struct ibv_rx_hash_conf rx_hash_conf;
	uint32_t source_qpn;
};

struct ibv_srq_init_attr_ex {
	void *srq_context; // host
	struct ibv_srq_attr attr;

	uint32_t comp_mask;
	enum ibv_srq_type srq_type;
	struct ibv_pd *pd; // host
	struct ibv_xrcd *xrcd; // host
	struct ibv_cq *cq; // host
};

struct ibv_srq_init_attr {
	void *srq_context; // host
	struct ibv_srq_attr attr;
};

struct ibv_qp_open_attr {
	uint32_t comp_mask;
	uint32_t qp_num;
	struct ibv_xrcd *xrcd; // host
	void *qp_context; // host
	enum ibv_qp_type qp_type;
};

struct ibv_cq_init_attr_ex {
	/* Minimum number of entries required for CQ */
	uint32_t cqe;
	void *cq_context; // host
	struct ibv_comp_channel *channel; // host
	/* Completion vector used to signal completion events.
	 * Must be < context->num_comp_vectors.
	 */
	uint32_t comp_vector;
	uint64_t wc_flags;
	uint32_t comp_mask;
	uint32_t flags;
};

struct ibv_async_event {
	union {
		struct ibv_cq *cq;
		struct ibv_qp *qp;
		struct ibv_srq *srq;
		struct ibv_wq *wq;
		int port_num;
	} element;
	enum ibv_event_type event_type;
};

	int i, random;


	int num_devices;
	printf("\t\tib-test.c: before get dev list.\n");
	struct ibv_device ** dev_list = ibv_get_device_list(&num_devices);
	printf("\t\tib-test.c: after get device list -- ib-test.c: num devices: %d \n", num_devices);
	printf("\t\tib-test.c: dev_list ptr: %p\n", dev_list);
	/* printf("after get device list -- ib-test.c: ptr 1: %p\n",  dev_list[0]); */
	/* printf("after get device list -- ib-test.c: ptr 2: %p\n",  dev_list[1]); */
	/* printf("\t\tafter get device list -- ib-test.c: name 1: %s\n", dev_list[0]->name); */
	/* printf("\t\tafter get device list -- ib-test.c: name 2: %s\n", dev_list[1]->name); */

	printf("\t\tib-test.c: before get device name loop.\n");
	for (int i=0; i < num_devices; i++) {
		const char* dev_name = ibv_get_device_name(dev_list[i]);
		printf("\t\tib-test.c: after get device name -- Device name %d: %s\n", i, dev_name);
	}

	printf("\t\tib-test.c: before open_device\n");
	struct ibv_context * context = ibv_open_device(dev_list[0]);
	printf("\t\tib-test.c: after open device\n");

	return 0;
}

