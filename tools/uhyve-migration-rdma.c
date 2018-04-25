/*
 * Copyright (c) 2018, Simon Pickartz, RWTH Aachen University
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

#define _GNU_SOURCE

#include <stdlib.h>
#include <arpa/inet.h>
#include <infiniband/verbs.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include "uhyve-migration.h"
#include "uhyve.h"


#ifdef __RDMA_MIGRATION__

#define IB_USED_PORT 		(1)
#define IB_CQ_ENTRIES 		(1)
#define IB_MAX_INLINE_DATA 	(0)
#define IB_MAX_DEST_RD_ATOMIC 	(1)
#define IB_MIN_RNR_TIMER 	(1)
#define IB_MAX_RECV_WR 		(1)
#define IB_MAX_SEND_SGE 	(1)
#define IB_MAX_RECV_SGE 	(1)

typedef enum ib_wr_ids {
	IB_WR_NO_ID = 0,
	IB_WR_WRITE_PAGE_ID,
	IB_WR_WRITE_LAST_PAGE_ID,
	IB_WR_RECV_LAST_PAGE_ID
} ib_wr_ids_t;

typedef struct qp_info {
	uint32_t qpn;
	uint16_t lid;
	uint16_t psn;
	uint32_t key;
	uint64_t addr;
} qp_info_t;

typedef struct com_hndl {
	struct ibv_context 	*ctx; 		/* device context */
	struct ibv_device_attr  dev_attr; 	/* device attributes */
	struct ibv_pd 		*pd;  		/* protection domain */
	struct ibv_mr 		*mr;  		/* memory region */
	struct ibv_cq 		*cq;  		/* completion queue */
	struct ibv_qp 		*qp;  		/* queue pair */
	struct ibv_comp_channel	*comp_chan;  	/* completion event channel */
	qp_info_t 	loc_qp_info;
	qp_info_t 	rem_qp_info;
	uint8_t 		*buf; 		/* the communication buffer */
	uint32_t 		size; 		/* size of the buffer */
} com_hndl_t;


static com_hndl_t com_hndl;
static struct ibv_send_wr *send_list = NULL;
static struct ibv_send_wr *send_list_last = NULL;
static size_t send_list_length = 0;


/**
 * \brief Initializes the IB communication structures
 *
 * \param com_hndl the structure containing all communication relevant infos
 * \param buf the buffer that should be registrered with the QP
 *
 * This function sets up the IB communication channel. It registers the 'buf'
 * with a new protection domain. On its termination there is a QP in the INIT
 * state ready to be connected with the remote side.
 */
static void
init_com_hndl(void)
{
	/* the guest physical memory is the communication buffer */
	com_hndl.size = guest_size;
	com_hndl.buf = guest_mem;

	struct ibv_device **device_list;
	struct ibv_device *ib_pp_device;
	int num_devices;

	/* determine first available device */
	if ((device_list = ibv_get_device_list(&num_devices)) == NULL) {
		fprintf(stderr,
		    	"ERROR: Could not determine available IB devices "
			"- %d (%s). Abort!\n",
			errno,
			strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (num_devices != 0) {
		ib_pp_device = device_list[0];
	} else {
		fprintf(stderr,
		        "ERROR: Could not find any IB device. Abort!\n");
		exit(EXIT_FAILURE);
	}

	/* open the device context and create protection domain */
	if ((com_hndl.ctx = ibv_open_device(ib_pp_device)) == NULL) {
		fprintf(stderr,
		    	"ERROR: Could not open the device context "
			"- %d (%s). Abort!\n",
			errno,
			strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* query device capability (e.g., to determine 'max_qp_wr') */
	if (ibv_query_device(com_hndl.ctx, &com_hndl.dev_attr) < 0) {
		fprintf(stderr,
		    	"ERROR: Could not query device attributes "
			"- %d (%s). Abort!\n",
			errno,
			strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* allocate protection domain */
	if ((com_hndl.pd = ibv_alloc_pd(com_hndl.ctx)) == NULL) {
		fprintf(stderr,
		    	"ERROR: Could not allocate protection domain "
			"- %d (%s). Abort!\n",
			errno,
			strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* determine LID */
	struct ibv_port_attr port_attr;
	if (ibv_query_port(com_hndl.ctx, IB_USED_PORT, &port_attr) < 0){
		fprintf(stderr,
		    	"ERROR: Could not query port %u "
			"- %d (%s). Abort!\n",
			IB_USED_PORT,
			errno,
			strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* register guest memory with the protection domain */
	if ((com_hndl.mr = ibv_reg_mr(com_hndl.pd,
					com_hndl.buf,
					com_hndl.size,
					IBV_ACCESS_LOCAL_WRITE |
					IBV_ACCESS_REMOTE_WRITE)) == NULL) {
		fprintf(stderr,
		    	"ERROR: Could not register the memory region "
			"- %d (%s). Abort!\n",
			errno,
			strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* create completion event channel */
	if ((com_hndl.comp_chan =
		ibv_create_comp_channel(com_hndl.ctx)) == NULL) {
		fprintf(stderr,
		    	"ERROR: Could not create the completion channel "
			"- %d (%s). Abort!\n",
			errno,
			strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* create the completion queue */
	if ((com_hndl.cq = ibv_create_cq(com_hndl.ctx,
		    			       IB_CQ_ENTRIES,
		    			       NULL,
					       com_hndl.comp_chan,
					       0)) == NULL) {
		fprintf(stderr,
		    	"ERROR: Could not create the completion queue "
			"- %d (%s). Abort!\n",
			errno,
			strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* create send and recv queue pair  and initialize it */
	struct ibv_qp_init_attr init_attr = {
		.send_cq = com_hndl.cq,
		.recv_cq = com_hndl.cq,
		.cap 	 = {
			.max_send_wr  		= com_hndl.dev_attr.max_qp_wr,
			.max_recv_wr  		= IB_MAX_RECV_WR,
			.max_send_sge 		= IB_MAX_SEND_SGE,
			.max_recv_sge 		= IB_MAX_RECV_SGE,
			.max_inline_data 	= IB_MAX_INLINE_DATA
		},
		.qp_type = IBV_QPT_RC,
		.sq_sig_all = 0 /* we do not want a CQE for each WR */
	};
	if ((com_hndl.qp = ibv_create_qp(com_hndl.pd, &init_attr)) == NULL) {
		fprintf(stderr,
		    	"ERROR: Could not create the queue pair "
			"- %d (%s). Abort!\n",
			errno,
			strerror(errno));
		exit(EXIT_FAILURE);
	}

	struct ibv_qp_attr attr = {
		.qp_state   		= IBV_QPS_INIT,
		.pkey_index 		= 0,
		.port_num 		= IB_USED_PORT,
		.qp_access_flags 	= (IBV_ACCESS_REMOTE_WRITE)
	};
	if (ibv_modify_qp(com_hndl.qp,
			  &attr,
			  IBV_QP_STATE |
			  IBV_QP_PKEY_INDEX |
			  IBV_QP_PORT |
			  IBV_QP_ACCESS_FLAGS) < 0) {
		fprintf(stderr,
		    	"ERROR: Could not set QP into init state "
			"- %d (%s). Abort!\n",
			errno,
			strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* fill in local qp_info */
	com_hndl.loc_qp_info.qpn 	= com_hndl.qp->qp_num;
	com_hndl.loc_qp_info.psn 	= lrand48() & 0xffffff;
	com_hndl.loc_qp_info.key 	= com_hndl.mr->rkey;
	com_hndl.loc_qp_info.addr 	= (uint64_t)com_hndl.buf;
	com_hndl.loc_qp_info.lid 	= port_attr.lid;

}

/**
 * \brief Frees IB related resources
 *
 * \param com_hndl the structure containing all communication relevant infos
  */
static void
destroy_com_hndl(void)
{
	if (ibv_destroy_qp(com_hndl.qp) < 0) {
		fprintf(stderr,
		    	"ERROR: Could not destroy the queue pair "
			"- %d (%s). Abort!\n",
			errno,
			strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (ibv_destroy_cq(com_hndl.cq) < 0) {
		fprintf(stderr,
		    	"ERROR: Could not deallocate the protection domain "
			"- %d (%s). Abort!\n",
			errno,
			strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (ibv_destroy_comp_channel(com_hndl.comp_chan) < 0) {
		fprintf(stderr,
		    	"ERROR: Could not deallocate the protection domain "
			"- %d (%s). Abort!\n",
			errno,
			strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (ibv_dereg_mr(com_hndl.mr) < 0) {
		fprintf(stderr,
		    	"ERROR: Could not deallocate the protection domain "
			"- %d (%s). Abort!\n",
			errno,
			strerror(errno));
		exit(EXIT_FAILURE);
	}



	if (ibv_dealloc_pd(com_hndl.pd) < 0) {
		fprintf(stderr,
		    	"ERROR: Could not deallocate the protection domain "
			"- %d (%s). Abort!\n",
			errno,
			strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (ibv_close_device(com_hndl.ctx) < 0) {
		fprintf(stderr,
		    	"ERROR: Could not close the device context "
			"- %d (%s). Abort!\n",
			errno,
			strerror(errno));
		exit(EXIT_FAILURE);
	}

}

/**
 * \brief Connects the QP created within init_com_hndl
 *
 * \param com_hndl the structure containing all communication relevant infos
 *
 * This function performs the actual connection setup between the two QPs.
 */
static void
con_com_buf(void) {
	/* transistion to ready-to-receive state */
	struct ibv_qp_attr qp_attr = {
		.qp_state 		= IBV_QPS_RTR,
		.path_mtu 		= IBV_MTU_2048,
		.dest_qp_num 		= com_hndl.rem_qp_info.qpn,
		.rq_psn			= com_hndl.rem_qp_info.psn,
		.max_dest_rd_atomic	= IB_MAX_DEST_RD_ATOMIC,
		.min_rnr_timer		= IB_MIN_RNR_TIMER,
		.ah_attr 		= {
			.is_global 	= 0,
			.sl 		= 0,
			.src_path_bits 	= 0,
			.dlid 		= com_hndl.rem_qp_info.lid,
			.port_num 	= IB_USED_PORT,
		}
	};
	if (ibv_modify_qp(com_hndl.qp,
			  &qp_attr,
			  IBV_QP_STATE |
			  IBV_QP_PATH_MTU |
			  IBV_QP_DEST_QPN |
			  IBV_QP_RQ_PSN |
			  IBV_QP_MAX_DEST_RD_ATOMIC |
			  IBV_QP_MIN_RNR_TIMER |
			  IBV_QP_AV)) {
		fprintf(stderr,
		    	"ERROR: Could not put QP into RTR state"
			"- %d (%s). Abort!\n",
			errno,
			strerror(errno));
		exit(errno);
	}

	/* transistion to ready-to-send state */
	qp_attr.qp_state    	= IBV_QPS_RTS;
	qp_attr.timeout	    	= 14;
	qp_attr.retry_cnt   	= 7;
	qp_attr.rnr_retry   	= 7; /* infinite retrys on RNR NACK */
	qp_attr.sq_psn	    	= com_hndl.loc_qp_info.psn;
	qp_attr.max_rd_atomic 	= 1;
	if (ibv_modify_qp(com_hndl.qp, &qp_attr,
			  IBV_QP_STATE              |
			  IBV_QP_TIMEOUT            |
			  IBV_QP_RETRY_CNT          |
			  IBV_QP_RNR_RETRY          |
			  IBV_QP_SQ_PSN             |
			  IBV_QP_MAX_QP_RD_ATOMIC)) {
		fprintf(stderr,
		    	"ERROR: Could not put QP into RTS state"
			"- %d (%s). Abort!\n",
			errno,
			strerror(errno));
		exit(errno);
	}
}

/**
 * \brief Set the destination node for a migration
 *
 * \param ip_str a string containing the IPv4 addr of the destination
 * \param port the migration port
 */
static void
exchange_qp_info(bool server)
{
	int res = 0;
	if (server) {
		res = recv_data(&com_hndl.rem_qp_info, sizeof(qp_info_t));
		res = send_data(&com_hndl.loc_qp_info, sizeof(qp_info_t));
	} else {
		res = send_data(&com_hndl.loc_qp_info, sizeof(qp_info_t));
		res = recv_data(&com_hndl.rem_qp_info, sizeof(qp_info_t));
	}

	fprintf(stderr, "QP info sent! (QPN: %lu; LID: %lu; PSN: %lu; KEY: %lu; ADDR: 0x%x)\n",
			com_hndl.loc_qp_info.qpn,
			com_hndl.loc_qp_info.lid,
			com_hndl.loc_qp_info.psn,
			com_hndl.loc_qp_info.key,
			com_hndl.loc_qp_info.addr);
	fprintf(stderr, "QP info received! (QPN: %lu; LID: %lu; PSN: %lu; KEY: %lu; ADDR: 0x%x)\n",
			com_hndl.rem_qp_info.qpn,
			com_hndl.rem_qp_info.lid,
			com_hndl.rem_qp_info.psn,
			com_hndl.rem_qp_info.key,
			com_hndl.rem_qp_info.addr);
}

/**
 * \brief Prepares the an 'ibv_send_wr'
 *
 * This function prepares an 'ibv_send_wr' structure that is prepared for the
 * transmission of a single memory page using the IBV_WR_RDMA_WRITE verb.
 */
static inline struct ibv_send_wr *
prepare_send_list_elem(void)
{
	/* create work request */
	struct ibv_send_wr *send_wr =  (struct ibv_send_wr*)calloc(1, sizeof(struct ibv_send_wr));
	struct ibv_sge *sge =  (struct ibv_sge*)calloc(1, sizeof(struct ibv_sge));

	/* basic work request configuration */
	send_wr->next  	 	= NULL;
	send_wr->sg_list 	= sge;
	send_wr->num_sge 	= 1;
	send_wr->wr_id  	= IB_WR_WRITE_PAGE_ID;
	send_wr->opcode 	= IBV_WR_RDMA_WRITE;

	return send_wr;

}

/**
 * \brief Creates an 'ibv_send_wr' and appends it to the send_list
 *
 * \param addr the page table entry of the memory page
 * \param addr_size the size of the page table entry
 * \param page the buffer to be send in this WR
 * \param page_size the size of the buffer
 *
 * This function creates an 'ibv_send_wr' structure and appends this to the
 * global send_list. It sets the source/destination information and sets the
 * IBV_SEND_SIGNALED flag as appropriate.
 */
static void
create_send_list_entry (void *addr, size_t addr_size, void *page, size_t page_size)
{
	/* create work request */
	struct ibv_send_wr *send_wr =  prepare_send_list_elem();

	/* configure source buffer */
	send_wr->sg_list->addr 		= (uintptr_t)page;
	send_wr->sg_list->length 	= page_size;
	send_wr->sg_list->lkey 		= com_hndl.mr->lkey;

	/* configure destination buffer */
	if (addr) {
		send_wr->wr.rdma.remote_addr 	= com_hndl.rem_qp_info.addr + determine_dest_offset(*(size_t*)addr);
	} else {
		send_wr->wr.rdma.remote_addr 	= com_hndl.rem_qp_info.addr;
	}
	send_wr->wr.rdma.rkey 		= com_hndl.rem_qp_info.key;

	/* apped work request to send list */
	if (send_list == NULL) {
		send_list = send_list_last = send_wr;
	} else {
		send_list_last->next = send_wr;
		send_list_last = send_list_last->next;
	}
	/* we have to request a CQE if max_send_wr is reached to avoid overflows */
	if ((++send_list_length%com_hndl.dev_attr.max_qp_wr) == 0) {
		send_list_last->send_flags 	= IBV_SEND_SIGNALED;
	}
}

/**
 * \brief Sends the guest memory to the destination
 *
 * \param mode MIG_MODE_COMPLETE_DUMP sends the complete memory and
 *             MIG_MODE_INCREMENTAL_DUMP only the mapped guest pages
 */
void send_guest_mem(mig_mode_t mode, bool final_dump)
{
	int res = 0;
	static bool ib_initialized = false;

	/* prepare IB channel */
	if (!ib_initialized) {
		init_com_hndl();
		exchange_qp_info(false);
		con_com_buf();

		ib_initialized = true;
	}

	/* determine migration mode */
	switch (mode) {
	case MIG_MODE_COMPLETE_DUMP:
		/* one send_wr for the whole guest memory */
		create_send_list_entry(NULL, 0, (void*)com_hndl.buf, guest_size);
		break;
	case MIG_MODE_INCREMENTAL_DUMP:
		/* iterate guest page tables */
		determine_dirty_pages(create_send_list_entry);
		break;
	default:
		fprintf(stderr, "ERROR: Unknown migration mode. Abort!\n");
		exit(EXIT_FAILURE);
	}

	/* create a dumy WR request if there is nothing to send */
	if (send_list_length == 0)
		create_send_list_entry(NULL, 0, NULL, 0);

	/* we have to wait for the last WR before informing dest */
	if ((mode == MIG_MODE_COMPLETE_DUMP) || final_dump) {
		send_list_last->wr_id 		= IB_WR_WRITE_LAST_PAGE_ID;
		send_list_last->opcode 		= IBV_WR_RDMA_WRITE_WITH_IMM;
		send_list_last->send_flags 	= IBV_SEND_SIGNALED | IBV_SEND_SOLICITED;
		send_list_last->imm_data 	= htonl(0x1);
	} else {
		send_list_last->wr_id 		= IB_WR_WRITE_LAST_PAGE_ID;
		send_list_last->send_flags 	= IBV_SEND_SIGNALED;
	}

	printf("DEBUG: Send list length %d\n", send_list_length);

	/* we have to call ibv_post_send() as long as 'send_list' contains elements  */
 	struct ibv_wc wc;
	struct ibv_send_wr *remaining_send_wr = NULL;
	do {
		/* send data */
		remaining_send_wr = NULL;
		if (ibv_post_send(com_hndl.qp, send_list, &remaining_send_wr) && (errno != ENOMEM)) {
			fprintf(stderr,
			    	"ERROR: Could not post send"
				"- %d (%s). Abort!\n",
				errno,
				strerror(errno));
			exit(EXIT_FAILURE);
		}

		/* wait for send WRs if CQ is full */
		do {
			if ((res = ibv_poll_cq(com_hndl.cq, 1, &wc)) < 0) {
				fprintf(stderr,
				    	"ERROR: Could not poll on CQ"
					"- %d (%s). Abort!\n",
					errno,
					strerror(errno));
				exit(EXIT_FAILURE);
			}
		} while (res < 1);
		if (wc.status != IBV_WC_SUCCESS) {
			fprintf(stderr,
			    "ERROR: WR failed status %s (%d) for wr_id %d\n",
			    ibv_wc_status_str(wc.status),
			    wc.status,
			    (int)wc.wr_id);
		}
		send_list = remaining_send_wr;
	} while (remaining_send_wr);


	/* ensure that we receive the CQE for the last page */
	if (wc.wr_id != IB_WR_WRITE_LAST_PAGE_ID) {
		fprintf(stderr,
		    "ERROR: WR failed status %s (%d) for wr_id %d\n",
		    ibv_wc_status_str(wc.status),
		    wc.status,
		    (int)wc.wr_id);
	}

	/* cleanup send_list */
	struct ibv_send_wr *cur_send_wr = send_list;
	struct ibv_send_wr *tmp_send_wr = NULL;
	while (cur_send_wr != NULL) {
		free(cur_send_wr->sg_list);
		tmp_send_wr = cur_send_wr;
		cur_send_wr = cur_send_wr->next;
		free(tmp_send_wr);
	}
	send_list_length = 0;

	/* do not close the channel in a pre-dump */
	if (!final_dump)
		return;

	/* free IB-related resources */
	destroy_com_hndl();
	ib_initialized = false;

	fprintf(stderr, "Guest memory sent!\n");
}



/**
 * \brief Receives the guest memory from the source
 *
 * The receive participates in the IB connection setup and waits for the
 * 'solicited' event sent with the last WR issued by the sender.
 */
void recv_guest_mem(void)
{
	int res = 0;

	/* prepare IB channel */
	init_com_hndl();
	exchange_qp_info(true);
	con_com_buf();

	/* request notification on the event channel */
	if (ibv_req_notify_cq(com_hndl.cq, 1) < 0) {
		fprintf(stderr,
		    	"ERROR: Could request notify for completion queue "
			"- %d (%s). Abort!\n",
			errno,
			strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* post recv matching IBV_RDMA_WRITE_WITH_IMM */
	struct ibv_cq *ev_cq;
	void *ev_ctx;
	struct ibv_sge sg;
	struct ibv_recv_wr recv_wr;
	struct ibv_recv_wr *bad_wr;
	uint32_t recv_buf = 0;

	memset(&sg, 0, sizeof(sg));
	sg.addr	  = (uintptr_t)&recv_buf;
	sg.length = sizeof(recv_buf);
	sg.lkey	  = com_hndl.mr->lkey;

	memset(&recv_wr, 0, sizeof(recv_wr));
	recv_wr.wr_id      = 0;
	recv_wr.sg_list    = &sg;
	recv_wr.num_sge    = 1;

	if (ibv_post_recv(com_hndl.qp, &recv_wr, &bad_wr) < 0) {
	    	fprintf(stderr,
		    	"ERROR: Could post recv - %d (%s). Abort!\n",
			errno,
			strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* wait for requested event */
	if (ibv_get_cq_event(com_hndl.comp_chan, &ev_cq, &ev_ctx) < 0) {
	    	fprintf(stderr,
		    	"ERROR: Could get event from completion channel "
			"- %d (%s). Abort!\n",
			errno,
			strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* acknowledge the event */
	ibv_ack_cq_events(com_hndl.cq, 1);

	/* free IB-related resources */
	destroy_com_hndl();

	fprintf(stderr, "Guest memory received!\n");
}
#endif /* __RDMA_MIGRATION__ */
