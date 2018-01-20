#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include <getopt.h>
#include <limits.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>
/* #include <sys/mman.h> */
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>

#include "perftest_resources_write_bw.h"
#include "perftest_parameters_write_bw.h"


static enum ibv_wr_opcode opcode_verbs_array[] = {IBV_WR_SEND, IBV_WR_RDMA_WRITE, IBV_WR_RDMA_READ};
static enum ibv_wr_opcode opcode_atomic_array[] = {IBV_WR_ATOMIC_CMP_AND_SWP, IBV_WR_ATOMIC_FETCH_AND_ADD};


#define CPU_UTILITY "/proc/stat"

struct perftest_parameters* duration_param;
struct check_alive_data check_alive_data;

struct ibv_qp* ctx_qp_create(struct pingpong_context *ctx,
		struct perftest_parameters *user_param)
{
	struct ibv_qp_init_attr attr;
	struct ibv_qp* qp = NULL;

	memset(&attr, 0, sizeof(struct ibv_qp_init_attr));
	attr.send_cq             = ctx->send_cq;
	attr.recv_cq             = (user_param->verb == SEND) ? ctx->recv_cq : ctx->send_cq;
	attr.cap.max_send_wr     = user_param->tx_depth;
	attr.cap.max_send_sge    = MAX_SEND_SGE;
	attr.cap.max_inline_data = user_param->inline_size;

	if (user_param->use_srq && (user_param->tst == LAT || user_param->machine == SERVER || user_param->duplex == ON)) {
		attr.srq = ctx->srq;
		attr.cap.max_recv_wr = 0;
		attr.cap.max_recv_sge = 0;
	} else {
		attr.srq = NULL;
		attr.cap.max_recv_wr = user_param->rx_depth;
		attr.cap.max_recv_sge = MAX_RECV_SGE;
	}

	switch (user_param->connection_type) {
		case RC : attr.qp_type = IBV_QPT_RC; break;
		case UC : attr.qp_type = IBV_QPT_UC; break;
		case UD : attr.qp_type = IBV_QPT_UD; break;
		#ifdef HAVE_RAW_ETH
		case RawEth : attr.qp_type = IBV_QPT_RAW_PACKET; break;
		#endif
		default: fprintf(stderr, "Unknown connection type \n");
			  return NULL;
	}

	qp = ibv_create_qp(ctx->pd, &attr);
	return qp;
}

#if defined HAVE_EX_ODP || defined HAVE_EXP_ODP
static int check_odp_support(struct pingpong_context *ctx)
{
	#ifdef HAVE_EX_ODP
	struct ibv_device_attr_ex dattr;
	int odp_support_send = IBV_ODP_SUPPORT_SEND;
	int odp_support_recv = IBV_ODP_SUPPORT_RECV;
	int ret = ibv_query_device_ex(ctx->context, NULL, &dattr);
	/* #elif defined HAVE_EXP_ODP */
	/* struct ibv_exp_device_attr dattr; */
	/* int ret = ibv_exp_query_device(ctx->context, &dattr); */
	/* int odp_support_send = IBV_EXP_ODP_SUPPORT_SEND; */
	/* int odp_support_recv = IBV_EXP_ODP_SUPPORT_RECV; */
	#endif
	if (ret) {
		fprintf(stderr, " Couldn't query device for on-demand paging capabilities.\n");
		return 0;
	} else if (!(dattr.odp_caps.per_transport_caps.rc_odp_caps & odp_support_send)) {
		fprintf(stderr, " Send is not supported for RC transport.\n");
		return 0;
	} else if (!(dattr.odp_caps.per_transport_caps.rc_odp_caps & odp_support_recv)) {
		fprintf(stderr, " Receive is not supported for RC transport.\n");
		return 0;
	}
	return 1;
}
#endif


// -----------------------------------------------------------------------------


int create_single_mr(struct pingpong_context *ctx, struct perftest_parameters *user_param, int qp_index)
{
	int i;
	int flags = IBV_ACCESS_LOCAL_WRITE;

	/* ODP */
	#if defined HAVE_EX_ODP || defined HAVE_EXP_ODP
	if (user_param->use_odp) {
		if (!check_odp_support(ctx) )
			return FAILURE;

		/* ODP does not support contig pages */
		ctx->is_contig_supported = FAILURE;
		#ifdef HAVE_EX_ODP
		flags |= IBV_ACCESS_ON_DEMAND;
		#elif defined HAVE_EXP_ODP
		exp_flags |= IBV_EXP_ACCESS_ON_DEMAND;
		#endif
	}
	#endif

	/* #ifdef HAVE_CUDA */
	/* if (user_param->use_cuda) { */
		/* ctx->is_contig_supported = FAILURE; */
		/* if(pp_init_gpu(ctx, ctx->buff_size)) { */
			/* fprintf(stderr, "Couldn't allocate work buf.\n"); */
			/* return FAILURE; */
		/* } */
	/* } */
	/* #endif */

	/* if (user_param->mmap_file != NULL) { */
		/* ctx->buf = memalign(user_param->cycle_buffer, ctx->buff_size); */
		/* if (pp_init_mmap(ctx, ctx->buff_size, user_param->mmap_file, */
					/* user_param->mmap_offset)) */
		/* { */
			/* fprintf(stderr, "Couldn't allocate work buf.\n"); */
			/* return FAILURE; */
		/* } */
	/* } else { */

	/* Allocating buffer for data, in case driver not support contig pages. */
	if (ctx->is_contig_supported == FAILURE) {
		/* if (user_param->use_hugepages) { */
			/* if (alloc_hugepage_region(ctx) != SUCCESS){ */
				/* fprintf(stderr, "Failed to allocate hugepage region.\n"); */
				/* return FAILURE; */
			/* } */
			/* memset(ctx->buf[qp_index], 0, ctx->buff_size); */
		/* } else if (ctx->is_contig_supported == FAILURE) { */
			/* ctx->buf[qp_index] = memalign(user_param->cycle_buffer, ctx->buff_size); */
		/* } */

		ctx->buf[qp_index] = memalign(user_param->cycle_buffer, ctx->buff_size);
		if (!ctx->buf[qp_index]) {
			fprintf(stderr, "Couldn't allocate work buf.\n");
			return FAILURE;
		}
		memset(ctx->buf[qp_index], 0, ctx->buff_size);

	} else {
		ctx->buf[qp_index] = NULL;
		flags |= (1 << 5);
	}
	/* } */

	if (user_param->verb == WRITE) {
		flags |= IBV_ACCESS_REMOTE_WRITE;
	} else if (user_param->verb == READ) {
		flags |= IBV_ACCESS_REMOTE_READ;
		if (user_param->transport_type == IBV_TRANSPORT_IWARP)
			flags |= IBV_ACCESS_REMOTE_WRITE;
	/* } else if (user_param->verb == ATOMIC) { */
		/* flags |= IBV_ACCESS_REMOTE_ATOMIC; */
	}

	/* Allocating Memory region and assigning our buffer to it. */
	ctx->mr[qp_index] = ibv_reg_mr(ctx->pd, ctx->buf[qp_index], ctx->buff_size, flags);

	if (!ctx->mr[qp_index]) {
		fprintf(stderr, "Couldn't allocate MR\n");
		return FAILURE;
	}

	if (ctx->is_contig_supported == SUCCESS)
		ctx->buf[qp_index] = ctx->mr[qp_index]->addr;


	/* Initialize buffer with random numbers except in WRITE_LAT test that it 0's */
	if (!user_param->use_cuda) {
		srand(time(NULL));
		if (user_param->verb == WRITE && user_param->tst == LAT) {
			memset(ctx->buf[qp_index], 0, ctx->buff_size);
		} else {
			for (i = 0; i < ctx->buff_size; i++) {
				((char*)ctx->buf[qp_index])[i] = (char)rand();
			}
		}
	}

	return SUCCESS;
}

int create_reg_cqs(struct pingpong_context *ctx,
		   struct perftest_parameters *user_param,
		   int tx_buffer_depth, int need_recv_cq)
{
	ctx->send_cq = ibv_create_cq(ctx->context, tx_buffer_depth *
					user_param->num_of_qps, NULL, ctx->channel, user_param->eq_num);
	if (!ctx->send_cq) {
		fprintf(stderr, "Couldn't create CQ\n");
		return FAILURE;
	}

	if (need_recv_cq) {
		ctx->recv_cq = ibv_create_cq(ctx->context, user_param->rx_depth *
						user_param->num_of_qps, NULL, ctx->channel, user_param->eq_num);
		if (!ctx->recv_cq) {
			fprintf(stderr, "Couldn't create a receiver CQ\n");
			return FAILURE;
		}
	}

	return SUCCESS;
}

int create_reg_qp_main(struct pingpong_context *ctx,
		       struct perftest_parameters *user_param,
		       int i, int num_of_qps)
{
	if (user_param->use_xrc) {
		/* #ifdef HAVE_XRCD */
		/* ctx->qp[i] = ctx_xrc_qp_create(ctx, user_param, i); */
		/* #endif */
	} else {
		ctx->qp[i] = ctx_qp_create(ctx, user_param);
	}

	if (ctx->qp[i] == NULL) {
		fprintf(stderr, "Unable to create QP.\n");
		return FAILURE;
	}

	return SUCCESS;
}

int ctx_modify_qp_to_init(struct ibv_qp *qp, struct perftest_parameters *user_param, uint64_t init_flag)
{
	int num_of_qps = user_param->num_of_qps;
	int num_of_qps_per_port = user_param->num_of_qps / 2;

	struct ibv_qp_attr attr;
	int flags = IBV_QP_STATE | IBV_QP_PKEY_INDEX | IBV_QP_PORT;

	static int portindex=0; /* for dual-port support */
	int ret = 0;

	memset(&attr, 0, sizeof(struct ibv_qp_attr));
	attr.qp_state = IBV_QPS_INIT;
	attr.pkey_index = user_param->pkey_index;

	if ( user_param->use_xrc && (user_param->duplex || user_param->tst == LAT)) {
		num_of_qps /= 2;
		num_of_qps_per_port = num_of_qps / 2;
	}

	if (user_param->dualport==ON) {
		if (portindex % num_of_qps < num_of_qps_per_port) {
			attr.port_num = user_param->ib_port;
			user_param->port_by_qp[portindex] = 0;
		} else {
			attr.port_num = user_param->ib_port2;
			user_param->port_by_qp[portindex] = 1;
		}
		portindex++;

	} else {

		attr.port_num = user_param->ib_port;
	}

	if (user_param->connection_type == RawEth) {
		flags = IBV_QP_STATE | IBV_QP_PORT;
	} else if (user_param->connection_type == UD) {
		attr.qkey = DEFF_QKEY;
		flags |= IBV_QP_QKEY;

	} else {
		switch (user_param->verb) {
			case ATOMIC: attr.qp_access_flags = IBV_ACCESS_REMOTE_ATOMIC; break;
			case READ : attr.qp_access_flags = IBV_ACCESS_REMOTE_READ; break;
			case WRITE : attr.qp_access_flags = IBV_ACCESS_REMOTE_WRITE; break;
			case SEND : attr.qp_access_flags = IBV_ACCESS_REMOTE_WRITE | IBV_ACCESS_LOCAL_WRITE;
		}
		flags |= IBV_QP_ACCESS_FLAGS;
	}

	#ifdef HAVE_MASKED_ATOMICS
	if (user_param->masked_atomics) {
		exp_attr.qp_access_flags = IBV_ACCESS_REMOTE_ATOMIC | IBV_ACCESS_REMOTE_WRITE | IBV_ACCESS_REMOTE_READ;
		exp_flags = IBV_EXP_QP_STATE | IBV_EXP_QP_PKEY_INDEX | IBV_EXP_QP_PORT | IBV_EXP_QP_ACCESS_FLAGS;
	}
	#endif

	ret = ibv_modify_qp(qp, &attr, flags);

	if (ret) {
		fprintf(stderr, "Failed to modify QP to INIT, ret=%d\n", ret);
		return 1;
	}
	return 0;
}


// -----------------------------------------------------------------------------


int create_mr(struct pingpong_context *ctx, struct perftest_parameters *user_param)
{
	int i;

	/* create first MR */
	if (create_single_mr(ctx, user_param, 0)) {
		fprintf(stderr, "failed to create mr\n");
		return 1;
	}

	/* create the rest if needed, or copy the first one */
	for (i = 1; i < user_param->num_of_qps; i++) {
		if (user_param->mr_per_qp) {
			if (create_single_mr(ctx, user_param, i)) {
				fprintf(stderr, "failed to create mr\n");
				return 1;
			}
		} else {
			ALLOCATE(ctx->mr[i], struct ibv_mr, 1);
			memset(ctx->mr[i], 0, sizeof(struct ibv_mr));
			ctx->mr[i] = ctx->mr[0];
			ctx->buf[i] = ctx->buf[0] + (i*BUFF_SIZE(ctx->size, ctx->cycle_buffer));
		}
	}

	return 0;
}

int create_cqs(struct pingpong_context *ctx, struct perftest_parameters *user_param)
{
	int ret;
	int dct_only = 0, need_recv_cq = 0;
	int tx_buffer_depth = user_param->tx_depth;

	if (user_param->connection_type == DC) {
		dct_only = (user_param->machine == SERVER && !(user_param->duplex || user_param->tst == LAT));
	}

	if (dct_only)
		tx_buffer_depth = user_param->rx_depth;

	if ((user_param->connection_type == DC && !dct_only) || (user_param->verb == SEND))
		need_recv_cq = 1;

	ret = create_reg_cqs(ctx, user_param, tx_buffer_depth, need_recv_cq);

	return ret;
}

int create_qp_main(struct pingpong_context *ctx,
		struct perftest_parameters *user_param, int i, int num_of_qps)
{
	int ret;
	ret = create_reg_qp_main(ctx, user_param, i, num_of_qps);
	return ret;
}

int modify_qp_to_init(struct pingpong_context *ctx,
		struct perftest_parameters *user_param, int qp_index, int num_of_qps)
{
	uint64_t init_flag = 0;

	#ifdef HAVE_RSS_EXP
	if (qp_index == 0 && user_param->use_rss) {
		init_flag = IBV_EXP_QP_GROUP_RSS;
	}
	else
	#endif
		init_flag = 0;

	if(user_param->connection_type == DC) {
		if ( !((!(user_param->duplex || user_param->tst == LAT) && (user_param->machine == SERVER) )
					|| ((user_param->duplex || user_param->tst == LAT) && (qp_index >= num_of_qps)))) {
			#ifdef HAVE_DC
			if (ctx_modify_dc_qp_to_init(ctx->qp[qp_index], user_param)) {
				fprintf(stderr, " Unable to create DC QP.\n");
				return FAILURE;
			}
			#endif
		}
	} else {
		if (ctx_modify_qp_to_init(ctx->qp[qp_index], user_param, init_flag)) {
			fprintf(stderr, "Failed to modify QP to INIT\n");
			return FAILURE;
		}
	}

	return SUCCESS;
}

#ifdef HAVE_PACKET_PACING
int check_packet_pacing_support(struct pingpong_context *ctx)
{
	struct ibv_device_attr_ex attr;
	memset(&attr, 0, sizeof (struct ibv_device_attr_ex));

	if (ibv_query_device_ex(ctx->context, NULL, &attr)) {
		fprintf(stderr, "ibv_query_device_ex failed\n");
		return FAILURE;
	}

	/* qp_rate_limit_max > 0 if PP is supported */
	return attr.packet_pacing_caps.qp_rate_limit_max > 0 ? SUCCESS : FAILURE;
}
#endif

static int ctx_modify_qp_to_rtr(struct ibv_qp *qp,
		struct ibv_qp_attr *attr,
		struct perftest_parameters *user_param,
		struct pingpong_dest *dest,
		struct pingpong_dest *my_dest,
		int qpindex)
{
	int num_of_qps = user_param->num_of_qps;
	int num_of_qps_per_port = user_param->num_of_qps / 2;

	int flags = IBV_QP_STATE;
	int ooo_flags = 0;

	attr->qp_state = IBV_QPS_RTR;
	attr->ah_attr.src_path_bits = 0;

	/* in xrc with bidirectional,
	 * there are send qps and recv qps. the actual number of send/recv qps
	 * is num_of_qps / 2.
	 */
	if ( user_param->use_xrc && (user_param->duplex || user_param->tst == LAT)) {
		num_of_qps /= 2;
		num_of_qps_per_port = num_of_qps / 2;
	}

	/* first half of qps are for ib_port and second half are for ib_port2
	 * in xrc with bidirectional, the first half of qps are xrc_send qps and
	 * the second half are xrc_recv qps. the first half of the send/recv qps
	 * are for ib_port1 and the second half are for ib_port2
	 */
	if (user_param->dualport == ON && (qpindex % num_of_qps >= num_of_qps_per_port))
		attr->ah_attr.port_num = user_param->ib_port2;
	else
		attr->ah_attr.port_num = user_param->ib_port;

	if (user_param->connection_type != RawEth) {

		attr->ah_attr.dlid = (user_param->dlid) ? user_param->dlid : dest->lid;
		attr->ah_attr.sl = user_param->sl;

		if (((attr->ah_attr.port_num == user_param->ib_port) && (user_param->gid_index == DEF_GID_INDEX))
				|| ((attr->ah_attr.port_num == user_param->ib_port2) && (user_param->gid_index2 == DEF_GID_INDEX) && user_param->dualport)) {

			attr->ah_attr.is_global = 0;
		} else {

			attr->ah_attr.is_global = 1;
			attr->ah_attr.grh.dgid = dest->gid;
			attr->ah_attr.grh.sgid_index = (attr->ah_attr.port_num == user_param->ib_port) ? user_param->gid_index : user_param->gid_index2;
			attr->ah_attr.grh.hop_limit = 0xFF;
			attr->ah_attr.grh.traffic_class = user_param->traffic_class;
		}
		if (user_param->connection_type != UD) {

			attr->path_mtu = user_param->curr_mtu;
			attr->dest_qp_num = dest->qpn;
			attr->rq_psn = dest->psn;

			flags |= (IBV_QP_AV | IBV_QP_PATH_MTU | IBV_QP_DEST_QPN | IBV_QP_RQ_PSN);

			if (user_param->connection_type == RC || user_param->connection_type == XRC) {

				attr->max_dest_rd_atomic = my_dest->out_reads;
				attr->min_rnr_timer = 12;
				flags |= (IBV_QP_MIN_RNR_TIMER | IBV_QP_MAX_DEST_RD_ATOMIC);
			}
		}
	}
	else if (user_param->raw_qos) {
		attr->ah_attr.sl = user_param->sl;
		flags |= IBV_QP_AV;
	}

	#ifdef HAVE_OOO_ATTR
		ooo_flags |= IBV_QP_OOO_RW_DATA_PLACEMENT;
	#elif HAVE_EXP_OOO_ATTR
		ooo_flags |= IBV_EXP_QP_OOO_RW_DATA_PLACEMENT;
	#endif

	if (user_param->use_ooo)
		flags |= ooo_flags;
	return ibv_modify_qp(qp, attr, flags);
}

void ctx_set_send_reg_wqes(struct pingpong_context *ctx,
		struct perftest_parameters *user_param,
		struct pingpong_dest *rem_dest)
{
	int i, j;
	int num_of_qps = user_param->num_of_qps;
	int xrc_offset = 0;

	if((user_param->use_xrc || user_param->connection_type == DC) && (user_param->duplex || user_param->tst == LAT)) {
		num_of_qps /= 2;
		xrc_offset = num_of_qps;
	}

	for (i = 0; i < num_of_qps ; i++) {
		memset(&ctx->wr[i*user_param->post_list], 0, sizeof(struct ibv_send_wr));
		ctx->sge_list[i*user_param->post_list].addr = (uintptr_t)ctx->buf[i];

		if (user_param->mac_fwd) {
			if (user_param->mr_per_qp) {
				ctx->sge_list[i*user_param->post_list].addr =
					(uintptr_t)ctx->buf[0] + (num_of_qps + i)*BUFF_SIZE(ctx->size, ctx->cycle_buffer);
			} else {
				ctx->sge_list[i*user_param->post_list].addr = (uintptr_t)ctx->buf[i];
			}
		}

		if (user_param->verb == WRITE || user_param->verb == READ)
			ctx->wr[i*user_param->post_list].wr.rdma.remote_addr = rem_dest[xrc_offset + i].vaddr;

		else if (user_param->verb == ATOMIC)
			ctx->wr[i*user_param->post_list].wr.atomic.remote_addr = rem_dest[xrc_offset + i].vaddr;

		if (user_param->tst == BW || user_param->tst == LAT_BY_BW) {

			ctx->scnt[i] = 0;
			ctx->ccnt[i] = 0;
			ctx->my_addr[i] = (uintptr_t)ctx->buf[i];
			if (user_param->verb != SEND)
				ctx->rem_addr[i] = rem_dest[xrc_offset + i].vaddr;
		}

		for (j = 0; j < user_param->post_list; j++) {

			ctx->sge_list[i*user_param->post_list + j].length =
				(user_param->connection_type == RawEth) ? (user_param->size - HW_CRC_ADDITION) : user_param->size;

			ctx->sge_list[i*user_param->post_list + j].lkey = ctx->mr[i]->lkey;

			if (j > 0) {

				ctx->sge_list[i*user_param->post_list +j].addr = ctx->sge_list[i*user_param->post_list + (j-1)].addr;

				if ((user_param->tst == BW || user_param->tst == LAT_BY_BW) && user_param->size <= (ctx->cycle_buffer / 2))
					increase_loc_addr(&ctx->sge_list[i*user_param->post_list +j], user_param->size,
							j-1, ctx->my_addr[i], 0, ctx->cache_line_size, ctx->cycle_buffer);
			}

			ctx->wr[i*user_param->post_list + j].sg_list = &ctx->sge_list[i*user_param->post_list + j];
			ctx->wr[i*user_param->post_list + j].num_sge = MAX_SEND_SGE;
			ctx->wr[i*user_param->post_list + j].wr_id = i;

			if (j == (user_param->post_list - 1)) {
				ctx->wr[i*user_param->post_list + j].send_flags = IBV_SEND_SIGNALED;
				ctx->wr[i*user_param->post_list + j].next = NULL;
			}

			else {
				ctx->wr[i*user_param->post_list + j].next = &ctx->wr[i*user_param->post_list+j+1];
				ctx->wr[i*user_param->post_list + j].send_flags = 0;
			}

			/* if (user_param->verb == ATOMIC) { */
				/* ctx->wr[i*user_param->post_list + j].opcode = opcode_atomic_array[user_param->atomicType]; */
			/* } */
			/* else { */
				/* ctx->wr[i*user_param->post_list + j].opcode = opcode_verbs_array[user_param->verb]; */
			/* } */

			ctx->wr[i*user_param->post_list + j].opcode = opcode_verbs_array[user_param->verb];

			if (user_param->verb == WRITE || user_param->verb == READ) {

				ctx->wr[i*user_param->post_list + j].wr.rdma.rkey = rem_dest[xrc_offset + i].rkey;

				if (j > 0) {

					ctx->wr[i*user_param->post_list + j].wr.rdma.remote_addr =
						ctx->wr[i*user_param->post_list + (j-1)].wr.rdma.remote_addr;

					if ((user_param->tst == BW || user_param->tst == LAT_BY_BW ) && user_param->size <= (ctx->cycle_buffer / 2))
						increase_rem_addr(&ctx->wr[i*user_param->post_list + j], user_param->size,
								j-1, ctx->rem_addr[i], WRITE, ctx->cache_line_size, ctx->cycle_buffer);
				}

			} else if (user_param->verb == ATOMIC) {

				ctx->wr[i*user_param->post_list + j].wr.atomic.rkey = rem_dest[xrc_offset + i].rkey;

				if (j > 0) {

					ctx->wr[i*user_param->post_list + j].wr.atomic.remote_addr =
						ctx->wr[i*user_param->post_list + j-1].wr.atomic.remote_addr;
					if (user_param->tst == BW || user_param->tst == LAT_BY_BW)
						increase_rem_addr(&ctx->wr[i*user_param->post_list + j], user_param->size,
								j-1, ctx->rem_addr[i], ATOMIC, ctx->cache_line_size, ctx->cycle_buffer);
				}

				if (user_param->atomicType == FETCH_AND_ADD)
					ctx->wr[i*user_param->post_list + j].wr.atomic.compare_add = ATOMIC_ADD_VALUE;

				else
					ctx->wr[i*user_param->post_list + j].wr.atomic.swap = ATOMIC_SWAP_VALUE;


			} else if (user_param->verb == SEND) {

				if (user_param->connection_type == UD) {

					ctx->wr[i*user_param->post_list + j].wr.ud.ah = ctx->ah[i];
					ctx->wr[i*user_param->post_list + j].wr.ud.remote_qkey = DEF_QKEY;
					ctx->wr[i*user_param->post_list + j].wr.ud.remote_qpn = rem_dest[xrc_offset + i].qpn;
				}
			}

			if ((user_param->verb == SEND || user_param->verb == WRITE) && user_param->size <= user_param->inline_size)
				ctx->wr[i*user_param->post_list + j].send_flags |= IBV_SEND_INLINE;

			#ifdef HAVE_XRCD
			if (user_param->use_xrc)
				ctx->wr[i*user_param->post_list + j].qp_type.xrc.remote_srqn = rem_dest[xrc_offset + i].srqn;
			#endif
		}
	}
}

static int ctx_modify_qp_to_rts(struct ibv_qp *qp,
		void *_attr,
		struct perftest_parameters *user_param,
		struct pingpong_dest *dest,
		struct pingpong_dest *my_dest)
{
	/* #ifdef HAVE_PACKET_PACING_EXP */
	/* uint64_t flags = IBV_QP_STATE; */
	/* #else */
	int flags = IBV_QP_STATE;
	/* #endif */
	struct ibv_qp_attr *attr = (struct ibv_qp_attr*)_attr;

	attr->qp_state = IBV_QPS_RTS;

	if (user_param->connection_type != RawEth) {

		flags |= IBV_QP_SQ_PSN;
		attr->sq_psn = my_dest->psn;

		if (user_param->connection_type == RC || user_param->connection_type == XRC) {

			attr->timeout = user_param->qp_timeout;
			attr->retry_cnt = 7;
			attr->rnr_retry = 7;
			attr->max_rd_atomic = dest->out_reads;
			flags |= (IBV_QP_TIMEOUT | IBV_QP_RETRY_CNT | IBV_QP_RNR_RETRY | IBV_QP_MAX_QP_RD_ATOMIC);
		}
	}

	/* #ifdef HAVE_PACKET_PACING_EXP */
	/* if (user_param->rate_limit_type == PP_RATE_LIMIT) { */
		/* ((struct ibv_exp_qp_attr*)_attr)->rate_limit = user_param->rate_limit; */
		/* flags |= IBV_EXP_QP_RATE_LIMIT; */
		/* return ibv_exp_modify_qp(qp, (struct ibv_exp_qp_attr*)_attr, flags); */
	/* } */
	/* #elif defined(HAVE_PACKET_PACING) */
	/* if (user_param->rate_limit_type == PP_RATE_LIMIT) { */
		/* attr->rate_limit = user_param->rate_limit; */
		/* flags |= IBV_QP_RATE_LIMIT; */
	/* } */
	/* #endif */

	#ifdef HAVE_PACKET_PACING
	if (user_param->rate_limit_type == PP_RATE_LIMIT) {
		attr->rate_limit = user_param->rate_limit;
		flags |= IBV_QP_RATE_LIMIT;
	}
	#endif

	return ibv_modify_qp(qp, attr, flags);
}

int verify_params_with_device_context(struct ibv_context *context,
				      struct perftest_parameters *user_param)
{
	if(user_param->use_event) {
		if(user_param->eq_num > context->num_comp_vectors) {
			fprintf(stderr, " Completion vector specified is invalid\n");
			fprintf(stderr, " Max completion vector = %d\n",
				context->num_comp_vectors - 1);
			return FAILURE;
		}
	}

	return SUCCESS;
}


// -----------------------------------------------------------------------------


struct ibv_device* ctx_find_dev(const char *ib_devname)
{
	int num_of_device;
	struct ibv_device **dev_list;
	struct ibv_device *ib_dev = NULL;

	dev_list = ibv_get_device_list(&num_of_device);

	if (num_of_device <= 0) {
		fprintf(stderr, " Did not detect devices \n");
		fprintf(stderr, " If device exists, check if driver is up\n");
		return NULL;
	}

	if (!ib_devname) {
		ib_dev = dev_list[0];
		if (!ib_dev) {
			fprintf(stderr, "No IB devices found\n");
			exit (1);
		}
	} else {
		for (; (ib_dev = *dev_list); ++dev_list)
			if (!strcmp(ibv_get_device_name(ib_dev), ib_devname))
				break;
		if (!ib_dev)
			fprintf(stderr, "IB device %s not found\n", ib_devname);
	}
	return ib_dev;
}

void alloc_ctx(struct pingpong_context *ctx, struct perftest_parameters *user_param)
{
	uint64_t tarr_size;
	int num_of_qps_factor;
	ctx->cycle_buffer    = user_param->cycle_buffer;
	ctx->cache_line_size = user_param->cache_line_size;

	ALLOCATE(user_param->port_by_qp, uint64_t, user_param->num_of_qps);

	tarr_size = (user_param->noPeak) ? 1 : user_param->iters*user_param->num_of_qps;
	ALLOCATE(user_param->tposted, cycles_t, tarr_size);
	memset(user_param->tposted, 0, sizeof(cycles_t)*tarr_size);
	if ((user_param->tst == LAT || user_param->tst == FS_RATE) && user_param->test_type == DURATION)
		ALLOCATE(user_param->tcompleted, cycles_t, 1);

	ALLOCATE(ctx->qp, struct ibv_qp*, user_param->num_of_qps);
	ALLOCATE(ctx->mr, struct ibv_mr*, user_param->num_of_qps);
	ALLOCATE(ctx->buf, void* , user_param->num_of_qps);

	/* #ifdef HAVE_ACCL_VERBS */
	/* ALLOCATE(ctx->qp_burst_family, struct ibv_exp_qp_burst_family*, user_param->num_of_qps); */
	/* #endif */

	/* #ifdef HAVE_DC */
	/* if (user_param->connection_type == DC) { */
		/* ALLOCATE(ctx->dct, struct ibv_dct*, user_param->num_of_qps); */
	/* } */
	/* #endif */

	if ((user_param->tst == BW || user_param->tst == LAT_BY_BW) && (user_param->machine == CLIENT || user_param->duplex)) {
		ALLOCATE(user_param->tcompleted, cycles_t, tarr_size);
		memset(user_param->tcompleted, 0, sizeof(cycles_t)*tarr_size);
		ALLOCATE(ctx->my_addr, uint64_t, user_param->num_of_qps);
		ALLOCATE(ctx->rem_addr, uint64_t, user_param->num_of_qps);
		ALLOCATE(ctx->scnt, uint64_t, user_param->num_of_qps);
		ALLOCATE(ctx->ccnt, uint64_t, user_param->num_of_qps);
		memset(ctx->scnt, 0, user_param->num_of_qps * sizeof (uint64_t));
		memset(ctx->ccnt, 0, user_param->num_of_qps * sizeof (uint64_t));

	} else if ((user_param->tst == BW || user_param->tst == LAT_BY_BW)
		   && user_param->verb == SEND && user_param->machine == SERVER) {

		ALLOCATE(ctx->my_addr, uint64_t, user_param->num_of_qps);
		ALLOCATE(user_param->tcompleted, cycles_t, 1);

	} else if (user_param->tst == FS_RATE && user_param->test_type == ITERATIONS) {
		ALLOCATE(user_param->tcompleted, cycles_t, tarr_size);
		memset(user_param->tcompleted, 0, sizeof(cycles_t) * tarr_size);
	}

	if (user_param->machine == CLIENT || user_param->tst == LAT || user_param->duplex) {
		ALLOCATE(ctx->sge_list, struct ibv_sge, user_param->num_of_qps * user_param->post_list);
		ALLOCATE(ctx->wr, struct ibv_send_wr, user_param->num_of_qps * user_param->post_list);

		if ((user_param->verb == SEND && user_param->connection_type == UD ) || user_param->connection_type == DC) {
			ALLOCATE(ctx->ah, struct ibv_ah*, user_param->num_of_qps);
		}
	}

	if (user_param->verb == SEND && (user_param->tst == LAT || user_param->machine == SERVER || user_param->duplex)) {
		ALLOCATE(ctx->recv_sge_list, struct ibv_sge, user_param->num_of_qps);
		ALLOCATE(ctx->rwr, struct ibv_recv_wr, user_param->num_of_qps);
		ALLOCATE(ctx->rx_buffer_addr, uint64_t, user_param->num_of_qps);
	}

	if (user_param->mac_fwd == ON )
		ctx->cycle_buffer = user_param->size * user_param->rx_depth;

	ctx->size = user_param->size;

	num_of_qps_factor = (user_param->mr_per_qp) ? 1 : user_param->num_of_qps;

	/* holds the size of maximum between msg size and cycle buffer,
	* aligned to cache line,
	* it is multiply by 2 for send and receive
	* with reference to number of flows and number of QPs */
	ctx->buff_size = INC(BUFF_SIZE(ctx->size, ctx->cycle_buffer),
				 ctx->cache_line_size) * 2 * num_of_qps_factor * user_param->flows;
	ctx->send_qp_buff_size = ctx->buff_size / num_of_qps_factor / 2;
	ctx->flow_buff_size = ctx->send_qp_buff_size / user_param->flows;
	user_param->buff_size = ctx->buff_size;
	if (user_param->connection_type == UD)
		ctx->buff_size += ctx->cache_line_size;
}

int ctx_init(struct pingpong_context *ctx, struct perftest_parameters *user_param)
{
	int i;
	int num_of_qps = user_param->num_of_qps / 2;

	ctx->is_contig_supported = FAILURE;

	/* #ifdef HAVE_ACCL_VERBS */
	/* enum ibv_exp_query_intf_status intf_status; */
	/* struct ibv_exp_query_intf_params intf_params; */
	/* #endif */

	/* #if defined HAVE_OOO_ATTR || defined HAVE_EXP_OOO_ATTR */
	/* if (user_param->use_ooo) { */
		/* if (verify_ooo_settings(ctx, user_param) != SUCCESS) { */
			/* fprintf(stderr, "Incompatible OOO settings\n"); */
			/* return FAILURE; */
		/* } */
	/* } */
	/* #endif */

	if (user_param->use_hugepages)
		ctx->is_contig_supported = FAILURE;

	/* Allocating an event channel if requested. */
	if (user_param->use_event) {
		ctx->channel = ibv_create_comp_channel(ctx->context);
		if (!ctx->channel) {
			fprintf(stderr, "Couldn't create completion channel\n");
			return FAILURE;
		}
	}

	/* Allocating the Protection domain. */
	ctx->pd = ibv_alloc_pd(ctx->context);
	if (!ctx->pd) {
		fprintf(stderr, "Couldn't allocate PD\n");
		return FAILURE;
	}

	/* #ifdef HAVE_ACCL_VERBS */
	/* if (user_param->use_res_domain) { */
		/* ctx->res_domain = create_res_domain(ctx, user_param); */
		/* if (!ctx->res_domain) { */
			/* fprintf(stderr, "Couldn't create resource domain\n"); */
			/* return FAILURE; */
		/* } */
	/* } */
	/* #endif */

	if (create_mr(ctx, user_param)) {
		fprintf(stderr, "Failed to create MR\n");
		return FAILURE;
	}

	if (create_cqs(ctx, user_param)) {
		fprintf(stderr, "Failed to create CQs\n");
		return FAILURE;
	}

	/* #ifdef HAVE_XRCD */
	/* if (user_param->use_xrc) { */
		/* if (ctx_xrcd_create(ctx, user_param)) { */
			/* fprintf(stderr, "Couldn't create XRC resources\n"); */
			/* return FAILURE; */
		/* } */

		/* if (ctx_xrc_srq_create(ctx, user_param)) { */
			/* fprintf(stderr, "Couldn't create SRQ XRC resources\n"); */
			/* return FAILURE; */
		/* } */
	/* } */
	/* #endif */

	if (user_param->use_srq && !user_param->use_xrc && (user_param->tst == LAT ||
				user_param->machine == SERVER || user_param->duplex == ON)) {

		struct ibv_srq_init_attr attr = {
			.attr = {
				/* when using sreq, rx_depth sets the max_wr */
				.max_wr = user_param->rx_depth,
				.max_sge = 1
			}
		};

		ctx->srq = ibv_create_srq(ctx->pd, &attr);
		if (!ctx->srq) {
			fprintf(stderr, "Couldn't create SRQ\n");
			return FAILURE;
		}
	}

	/* #ifdef HAVE_RSS_EXP */
	/* if (user_param->use_rss) { */
		/* struct ibv_exp_device_attr attr; */

		/* attr.comp_mask = IBV_EXP_DEVICE_ATTR_EXP_CAP_FLAGS | */
			/* IBV_EXP_DEVICE_ATTR_RSS_TBL_SZ; */
		/* if (ibv_exp_query_device(ctx->context, &attr)) { */
			/* fprintf(stderr, "Experimental ibv_exp_query_device.\n"); */
			/* exit(1); */
		/* } */

		/* if (!((attr.exp_device_cap_flags & IBV_EXP_DEVICE_QPG) && */
					/* (attr.exp_device_cap_flags & IBV_EXP_DEVICE_UD_RSS) && */
					/* (attr.comp_mask & IBV_EXP_DEVICE_ATTR_RSS_TBL_SZ) && */
					/* (attr.max_rss_tbl_sz > 0))) { */
			/* fprintf(stderr, "RSS not supported .\n"); */
			/* exit(1); */
		/* } */

		/* [> num of qps includes the parent <] */
		/* if (user_param->num_of_qps > attr.max_rss_tbl_sz + 1) { */
			/* fprintf(stderr, "RSS limit is %d .\n", */
					/* attr.max_rss_tbl_sz); */
			/* exit(1); */
		/* } */
	/* } */
	/* #endif */

	for (i=0; i < user_param->num_of_qps; i++) {
		if (create_qp_main(ctx, user_param, i, num_of_qps)) {
			fprintf(stderr, "Failed to create QP.\n");
			return FAILURE;
		}

		modify_qp_to_init(ctx, user_param, i, num_of_qps);
		/* #ifdef HAVE_ACCL_VERBS */
		/* if (user_param->verb_type == ACCL_INTF) { */
			/* memset(&intf_params, 0, sizeof(intf_params)); */
			/* intf_params.intf_scope = IBV_EXP_INTF_GLOBAL; */
			/* intf_params.intf = IBV_EXP_INTF_QP_BURST; */
			/* intf_params.obj = ctx->qp[i]; */
			/* ctx->qp_burst_family[i] = ibv_exp_query_intf(ctx->context, &intf_params, &intf_status); */
			/* if (!ctx->qp_burst_family[i]) { */
				/* fprintf(stderr, "Couldn't get QP burst family.\n"); */
				/* return FAILURE; */
			/* } */
		/* } */
		/* #endif */
	}

	return SUCCESS;
}

int ctx_connect(struct pingpong_context *ctx,
		struct pingpong_dest *dest,
		struct perftest_parameters *user_param,
		struct pingpong_dest *my_dest)
{
	int i;

	/* #ifdef HAVE_DC */
	/* struct ibv_qp_attr_ex attr_ex; */
	/* #elif HAVE_PACKET_PACING_EXP */
	/* struct ibv_exp_qp_attr attr_ex; */
	/* #endif */

	struct ibv_qp_attr attr;
	int xrc_offset = 0;

	if((user_param->use_xrc || user_param->connection_type == DC) &&
     (user_param->duplex  || user_param->tst == LAT)) {
		xrc_offset = user_param->num_of_qps / 2;
	}

	for (i=0; i < user_param->num_of_qps; i++) {
		if (user_param->connection_type == DC) {
			if ( ((!(user_param->duplex || user_param->tst == LAT) && (user_param->machine == SERVER) )
						|| ((user_param->duplex || user_param->tst == LAT) && (i >= user_param->num_of_qps/2)))) {
				continue;
			}
		}
		/* #if defined (HAVE_DC) || defined (HAVE_PACKET_PACING_EXP) */
		/* memset(&attr_ex, 0, sizeof attr_ex); */
		/* #endif */
		memset(&attr, 0, sizeof attr);

		if (user_param->rate_limit_type == HW_RATE_LIMIT)
			attr.ah_attr.static_rate = user_param->valid_hw_rate_limit;

		#if defined (HAVE_PACKET_PACING_EXP) || defined (HAVE_PACKET_PACING)
		if (user_param->rate_limit_type == PP_RATE_LIMIT && (check_packet_pacing_support(ctx) == FAILURE)) {
			fprintf(stderr, "Packet Pacing isn't supported.\n");
			return FAILURE;
		}
		#endif

		if ((i >= xrc_offset) && (user_param->use_xrc || user_param->connection_type == DC) &&
        (user_param->duplex || user_param->tst == LAT))
			xrc_offset = -1*xrc_offset;

		/* if(user_param->connection_type == DC) { */
			/* #ifdef HAVE_DC */
			/* if(ctx_modify_dc_qp_to_rtr(ctx->qp[i], &attr_ex, user_param, &dest[xrc_offset + i], &my_dest[i], i)) { */
				/* fprintf(stderr, "Failed to modify QP %d to RTR\n", ctx->qp[i]->qp_num); */
				/* return FAILURE; */
			/* } */
			/* #endif */
		/* } else { */

		if(ctx_modify_qp_to_rtr(ctx->qp[i], &attr, user_param, &dest[xrc_offset + i], &my_dest[i], i)) {
			fprintf(stderr, "Failed to modify QP %d to RTR\n", ctx->qp[i]->qp_num);
			return FAILURE;
		}

		/* } */

		if (user_param->tst == LAT || user_param->machine == CLIENT || user_param->duplex) {
			if(ctx_modify_qp_to_rts(ctx->qp[i], &attr, user_param, &dest[xrc_offset + i], &my_dest[i])) {
				fprintf(stderr, "Failed to modify QP to RTS\n");
				return FAILURE;
			}

			/* if(user_param->connection_type == DC) { */
				/* #ifdef HAVE_DC */
				/* if(ctx_modify_dc_qp_to_rts(ctx->qp[i], &attr_ex, user_param, &dest[xrc_offset + i], &my_dest[i])) { */
					/* fprintf(stderr, "Failed to modify QP to RTS\n"); */
					/* return FAILURE; */
				/* } */
				/* #endif */
			/* } else { */
				/* #ifdef HAVE_PACKET_PACING_EXP */
				/* if (user_param->rate_limit_type == PP_RATE_LIMIT) { */
					/* if(ctx_modify_qp_to_rts(ctx->qp[i], &attr_ex, user_param, &dest[xrc_offset + i], &my_dest[i])) { */
						/* fprintf(stderr, "Failed to modify QP %x to RTS\n", ctx->qp[i]->qp_num); */
						/* return FAILURE; */
					/* } */
				/* } else { */
				/* #endif */
					/* if(ctx_modify_qp_to_rts(ctx->qp[i], &attr, user_param, &dest[xrc_offset + i], &my_dest[i])) { */
						/* fprintf(stderr, "Failed to modify QP to RTS\n"); */
						/* return FAILURE; */
					/* } */
				/* #ifdef HAVE_PACKET_PACING_EXP */
				/* } */
				/* #endif */
		}

		if ((user_param->connection_type == UD || user_param->connection_type == DC) &&
				(user_param->tst == LAT || user_param->machine == CLIENT || user_param->duplex)) {
			/* #ifdef HAVE_DC */
			/* if(user_param->connection_type == DC) */
				/* ctx->ah[i] = ibv_create_ah(ctx->pd, &(attr_ex.ah_attr)); */
			/* else */
			/* #endif */
				ctx->ah[i] = ibv_create_ah(ctx->pd, &(attr.ah_attr));

			if (!ctx->ah[i]) {
				fprintf(stderr, "Failed to create AH for UD\n");
				return FAILURE;
			}
		}

		if (user_param->rate_limit_type == HW_RATE_LIMIT) {
			struct ibv_qp_attr qp_attr;
			struct ibv_qp_init_attr init_attr;
			int err, qp_static_rate = 0;

			memset(&qp_attr,   0, sizeof(struct ibv_qp_attr));
			memset(&init_attr, 0, sizeof(struct ibv_qp_init_attr));

			err = ibv_query_qp(ctx->qp[i], &qp_attr, IBV_QP_AV, &init_attr);
			if (err)
				fprintf(stderr, "ibv_query_qp failed to get ah_attr\n");
			else
				qp_static_rate = (int)(qp_attr.ah_attr.static_rate);

			//- Fall back to SW Limit only if flag undefined
			if(err || (qp_static_rate != user_param->valid_hw_rate_limit)) {
				if(!user_param->is_rate_limit_type) {
					user_param->rate_limit_type = SW_RATE_LIMIT;
					fprintf(stderr, "\x1b[31mThe QP failed to accept HW rate limit, providing SW rate limit \x1b[0m\n");
				} else {
					fprintf(stderr, "\x1b[31mThe QP failed to accept HW rate limit \x1b[0m\n");
					return FAILURE;
				}

			}
		}

		if((user_param->use_xrc || user_param->connection_type == DC) && (user_param->duplex || user_param->tst == LAT))
			xrc_offset = user_param->num_of_qps / 2;

	}
	return SUCCESS;
}

int destroy_ctx(struct pingpong_context *ctx,
		struct perftest_parameters *user_param)
{
	int i, first, dereg_counter;
	int test_result = 0;
	int num_of_qps = user_param->num_of_qps;

	if (user_param->wait_destroy) {
		printf(" Waiting %u seconds before releasing resources...\n",
		       user_param->wait_destroy);

		/* sleep(user_param->wait_destroy); */

		// sleep replacement:
		struct timeval tv;
		tv.tv_sec  = user_param->wait_destroy;
		tv.tv_usec = 0;
		select(0, NULL, NULL, NULL, &tv);
	}

	dereg_counter = (user_param->mr_per_qp) ? user_param->num_of_qps : 1;

	/* in dc with bidirectional, there are send qps and recv qps. the actual 
	 * number of send/recv qps is num_of_qps / 2. */
	if (user_param->duplex || user_param->tst == LAT) {
		num_of_qps /= 2;
	}

	/* RSS parent should be last */
	if (user_param->use_rss)
		first = 1;
	else
		first = 0;

	for (i = first; i < user_param->num_of_qps; i++) {
		if (( (user_param->connection_type == DC && !((!(user_param->duplex || user_param->tst == LAT) && (user_param->machine == SERVER) )
							|| ((user_param->duplex || user_param->tst == LAT) && (i >= num_of_qps)))) ||
					user_param->connection_type == UD) && (user_param->tst == LAT || user_param->machine == CLIENT || user_param->duplex)) {
			if (ibv_destroy_ah(ctx->ah[i])) {
				fprintf(stderr, "Failed to destroy AH\n");
				test_result = 1;
			}
		}
		/* #ifdef HAVE_DC */
		/* if (user_param->connection_type == DC && ((!(user_param->duplex || user_param->tst == LAT) */
						/* && (user_param->machine == SERVER)) || ((user_param->duplex || user_param->tst == LAT) && (i >= num_of_qps)))) { */
			/* if (ibv_exp_destroy_dct(ctx->dct[i])) { */
				/* fprintf(stderr, "Failed to destroy dct\n"); */
				/* test_result = 1; */
			/* } */
			/* if ( i == user_param->num_of_qps -1 ) */
				/* return test_result; */
		/* } else */
		/* #endif */

		if (ibv_destroy_qp(ctx->qp[i])) {
			fprintf(stderr, "Couldn't destroy QP - %s\n", strerror(errno));
			test_result = 1;
		}
	}

	if (user_param->use_rss) {
		if (user_param->connection_type == UD && (user_param->tst == LAT || user_param->machine == CLIENT || user_param->duplex)) {
			if (ibv_destroy_ah(ctx->ah[0])) {
				fprintf(stderr, "Failed to destroy AH\n");
				test_result = 1;
			}
		}

		if (ibv_destroy_qp(ctx->qp[0])) {
			fprintf(stderr, "Couldn't destroy QP - %s\n", strerror(errno));
			test_result = 1;
		}
	}
	if (user_param->srq_exists) {
		if (ibv_destroy_srq(ctx->srq)) {
			fprintf(stderr, "Couldn't destroy SRQ\n");
			test_result = 1;
		}
	}

	/* #ifdef HAVE_XRCD */
	/* if (user_param->use_xrc) { */

		/* if (ibv_close_xrcd(ctx->xrc_domain)) { */
			/* fprintf(stderr, "Couldn't destroy XRC domain\n"); */
			/* test_result = 1; */
		/* } */

		/* if (ctx->fd >= 0 && close(ctx->fd)) { */
			/* fprintf(stderr, "Couldn't close the file for the XRC Domain\n"); */
			/* test_result = 1; */
		/* } */

	/* } */
	/* #endif */

	if (ibv_destroy_cq(ctx->send_cq)) {
		fprintf(stderr, "Failed to destroy CQ - %s\n", strerror(errno));
		test_result = 1;
	}

	if (user_param->verb == SEND && (user_param->tst == LAT || user_param->machine == SERVER || user_param->duplex || (ctx->channel)) ) {
		if (!(user_param->connection_type == DC && user_param->machine == SERVER)) {
			if (ibv_destroy_cq(ctx->recv_cq)) {
				fprintf(stderr, "Failed to destroy CQ - %s\n", strerror(errno));
				test_result = 1;
			}
		}
	}

	for (i = 0; i < dereg_counter; i++) {
		if (ibv_dereg_mr(ctx->mr[i])) {
			fprintf(stderr, "Failed to deregister MR #%d\n", i+1);
			test_result = 1;
		}
	}

	if (ibv_dealloc_pd(ctx->pd)) {
		fprintf(stderr, "Failed to deallocate PD - %s\n", strerror(errno));
		test_result = 1;
	}

	if (ctx->channel) {
		if (ibv_destroy_comp_channel(ctx->channel)) {
			fprintf(stderr, "Failed to close event channel\n");
			test_result = 1;
		}
	}

	if (ibv_close_device(ctx->context)) {
		fprintf(stderr, "Failed to close device context\n");
		test_result = 1;
	}

	/* #ifdef HAVE_CUDA */
	/* if (user_param->use_cuda) { */
		/* pp_free_gpu(ctx); */
	/* } */
	/* else */
	/* #endif */

	/* if (user_param->mmap_file != NULL) { */
		/* pp_free_mmap(ctx); */
	/* } else if (ctx->is_contig_supported == FAILURE) { */

	if (ctx->is_contig_supported == FAILURE) {
		for (i = 0; i < dereg_counter; i++) {
			/* if (user_param->use_hugepages) { */
				/* shmdt(ctx->buf[i]); */
			/* } else { */
				/* free(ctx->buf[i]); */
			/* } */

			free(ctx->buf[i]);
		}
	}
	free(ctx->qp);

	if ((user_param->tst == BW || user_param->tst == LAT_BY_BW ) && 
      (user_param->machine == CLIENT || user_param->duplex)) {
		free(user_param->tposted);
		free(user_param->tcompleted);
		free(ctx->my_addr);
		free(ctx->rem_addr);
		free(ctx->scnt);
		free(ctx->ccnt);
	}

	else if ((user_param->tst == BW || user_param->tst == LAT_BY_BW ) && 
           user_param->verb == SEND && user_param->machine == SERVER) {
		free(user_param->tposted);
		free(user_param->tcompleted);
		free(ctx->my_addr);
	}

	if (user_param->machine == CLIENT || user_param->tst == LAT || user_param->duplex) {
		free(ctx->sge_list);
		free(ctx->wr);
	}

	if (user_param->verb == SEND && (user_param->tst == LAT || user_param->machine == SERVER || user_param->duplex)) {
		free(ctx->rx_buffer_addr);
		free(ctx->recv_sge_list);
		free(ctx->rwr);
	}

	return test_result;
}

void ctx_set_send_wqes(struct pingpong_context *ctx,
		struct perftest_parameters *user_param,
		struct pingpong_dest *rem_dest)
{
	ctx_set_send_reg_wqes(ctx, user_param, rem_dest);

}

int perform_warm_up(struct pingpong_context *ctx, struct perftest_parameters *user_param)
{
	int ne, index, warmindex, warmupsession;
	int err = 0;

	struct ibv_send_wr *bad_wr = NULL;
	struct ibv_wc      wc;
	struct ibv_wc      *wc_for_cleaning = NULL;

	int num_of_qps = user_param->num_of_qps;
	int return_value = 0;

	if(user_param->duplex && (user_param->use_xrc || user_param->connection_type == DC))
		num_of_qps /= 2;

	warmupsession = (user_param->post_list == 1) ? user_param->tx_depth : user_param->post_list;
	ALLOCATE(wc_for_cleaning, struct ibv_wc, user_param->tx_depth);

	/* Clean up the pipe */
	ne = ibv_poll_cq(ctx->send_cq, user_param->tx_depth, wc_for_cleaning);

	for (index=0 ; index < num_of_qps ; index++) {
		for (warmindex = 0 ;warmindex < warmupsession ;warmindex += user_param->post_list) {
			err = ibv_post_send(ctx->qp[index], &ctx->wr[index*user_param->post_list], &bad_wr);
			if (err) {
				fprintf(stderr, "Couldn't post send during warm up: qp %d scnt=%d \n", index, warmindex);
				return_value = FAILURE;
				goto cleaning;
			}
		}

		do {
			ne = ibv_poll_cq(ctx->send_cq, 1, &wc);
			if (ne > 0) {
				if (wc.status != IBV_WC_SUCCESS) {
					return_value = FAILURE;
					goto cleaning;
				}
				warmindex -= user_param->post_list;
			} else if (ne < 0) {
				return_value = FAILURE;
				goto cleaning;
			}
		} while (warmindex);
	}

cleaning:
	free(wc_for_cleaning);

	return return_value;
}

int run_iter_bw(struct pingpong_context *ctx, struct perftest_parameters *user_param)
{
	uint64_t totscnt = 0;
	uint64_t totccnt = 0;
	int i = 0;
	int index, ne;
	uint64_t tot_iters;
	int err = 0;

	struct ibv_send_wr *bad_wr = NULL;
	struct ibv_wc *wc = NULL;
	int num_of_qps = user_param->num_of_qps;

	/* Rate Limiter*/
	int rate_limit_pps = 0;
	double gap_time = 0; /* in usec */
	cycles_t gap_cycles = 0; /* in cycles */
	cycles_t gap_deadline = 0;
	unsigned int number_of_bursts = 0;
	int burst_iter = 0;
	int is_sending_burst = 0;
	int cpu_mhz = 0;
	int return_value = 0;
	int wc_id;
	int send_flows_index = 0;
	uintptr_t primary_send_addr = ctx->sge_list[0].addr;
	int address_offset = 0;
	int flows_burst_iter = 0;

	ALLOCATE(wc , struct ibv_wc , CTX_POLL_BATCH);

	if (user_param->duplex && (user_param->use_xrc || user_param->connection_type == DC))
		num_of_qps /= 2;

	/* Will be 0, in case of Duration (look at force_dependencies or in the exp above). */
	tot_iters = (uint64_t) user_param->iters*num_of_qps;

	if (user_param->test_type == ITERATIONS && user_param->noPeak == ON)
		user_param->tposted[0] = get_cycles();

	/* If using rate limiter, calculate gap time between bursts */
	if (user_param->rate_limit_type == SW_RATE_LIMIT ) {
		/* Calculate rate limit in pps */
		switch (user_param->rate_units) {

			case MEGA_BYTE_PS:
				rate_limit_pps = ((double)(user_param->rate_limit) / user_param->size) * 1048576;
				break;
			case GIGA_BIT_PS:
				rate_limit_pps = ((double)(user_param->rate_limit) / (user_param->size * 8)) * 1000000000;
				break;
			case PACKET_PS:
				rate_limit_pps = user_param->rate_limit;
				break;

			default:
				fprintf(stderr, " Failed: Unknown rate limit units\n");
				return_value = FAILURE;
				goto cleaning;
		}

		cpu_mhz = get_cpu_mhz(user_param->cpu_freq_f);
		if (cpu_mhz <= 0) {
			fprintf(stderr, "Failed: couldn't acquire cpu frequency for rate limiter.\n");
		}
		number_of_bursts = rate_limit_pps / user_param->burst_size;
		gap_time = 1000000 * (1.0 / number_of_bursts);
		gap_cycles = cpu_mhz * gap_time;
	}

	/* main loop for posting */
	while (totscnt < tot_iters || totccnt < tot_iters ||
		(user_param->test_type == DURATION && user_param->state != END_STATE) ) {

		/* main loop to run over all the qps and post each time n messages */
		for (index =0; index < num_of_qps ; index++) {
			if (user_param->rate_limit_type == SW_RATE_LIMIT && is_sending_burst == 0) {
				if (gap_deadline > get_cycles()) {
					/* Go right to cq polling until gap time is over. */
					continue;
				}

				gap_deadline = get_cycles() + gap_cycles;
				is_sending_burst = 1;
				burst_iter = 0;
			}

			while ( (ctx->scnt[index] < user_param->iters || user_param->test_type == DURATION) &&
              ((ctx->scnt[index] - ctx->ccnt[index]) < (user_param->tx_depth)) &&
					   !((user_param->rate_limit_type == SW_RATE_LIMIT ) && is_sending_burst == 0)) {

				if (ctx->send_rcredit) {
					uint32_t swindow = ctx->scnt[index] + user_param->post_list - ctx->credit_buf[index];
					if (swindow >= user_param->rx_depth)
						break;
				}

				if (user_param->post_list == 1 && (ctx->scnt[index] % user_param->cq_mod == 0 && user_param->cq_mod > 1) &&
            !(ctx->scnt[index] == (user_param->iters - 1) && user_param->test_type == ITERATIONS)) {
					ctx->wr[index].send_flags &= ~IBV_SEND_SIGNALED;

				}

				if (user_param->noPeak == OFF)
					user_param->tposted[totscnt] = get_cycles();

				/* if (user_param->test_type == DURATION && user_param->state == END_STATE) */
					/* break; */

				err = ibv_post_send(ctx->qp[index], &ctx->wr[index*user_param->post_list], &bad_wr);
				if (err) {
					fprintf(stderr, "Couldn't post send: qp %d scnt=%lu \n", index, ctx->scnt[index]);
					return_value = FAILURE;
					goto cleaning;
				}

				/* if we have more than single flow and the burst iter is the last one */
				if (user_param->flows != DEF_FLOWS) {
					if (++flows_burst_iter == user_param->flows_burst) {
						flows_burst_iter = 0;
						/* inc the send_flows_index and update the address */
						if (++send_flows_index == user_param->flows)
							send_flows_index = 0;
						address_offset = send_flows_index * ctx->flow_buff_size;
						ctx->sge_list[0].addr = primary_send_addr + address_offset;
					}
				}

				/* in multiple flow scenarios we will go to next cycle buffer address in the main buffer*/
				if (user_param->post_list == 1 && user_param->size <= (ctx->cycle_buffer / 2)) {
					increase_loc_addr(ctx->wr[index].sg_list, user_param->size,
							ctx->scnt[index], ctx->my_addr[index] + address_offset , 0,
							ctx->cache_line_size, ctx->cycle_buffer);

					if (user_param->verb != SEND) {
							increase_rem_addr(&ctx->wr[index], user_param->size,
									ctx->scnt[index], ctx->rem_addr[index], user_param->verb,
									ctx->cache_line_size, ctx->cycle_buffer);
					}
				}

				ctx->scnt[index] += user_param->post_list;
				totscnt += user_param->post_list;

				/* ask for completion on this wr */
				if (user_param->post_list == 1 &&
						(ctx->scnt[index]%user_param->cq_mod == user_param->cq_mod - 1 ||
						 (user_param->test_type == ITERATIONS && ctx->scnt[index] == user_param->iters - 1))) {
					ctx->wr[index].send_flags |= IBV_SEND_SIGNALED;
				}

				/* Check if a full burst was sent. */
				if (user_param->rate_limit_type == SW_RATE_LIMIT) {
					burst_iter += user_param->post_list;
					if (burst_iter >= user_param->burst_size) {
						is_sending_burst = 0;
					}
				}
			}
		}

		if (totccnt < tot_iters || (user_param->test_type == DURATION && totccnt < totscnt)) {
			if (user_param->use_event) {
				if (ctx_notify_events(ctx->channel)) {
					fprintf(stderr, "Couldn't request CQ notification\n");
					return_value = FAILURE;
					goto cleaning;
				}
			}

			/* #ifdef HAVE_ACCL_VERBS */
			/* if (user_param->verb_type == ACCL_INTF) */
			/* ne = ctx->send_cq_family->poll_cnt(ctx->send_cq, CTX_POLL_BATCH); */
			/* else */
			/* #endif */
			ne = ibv_poll_cq(ctx->send_cq, CTX_POLL_BATCH, wc);

			if (ne > 0) {
				for (i = 0; i < ne; i++) {
					wc_id = (user_param->verb_type == ACCL_INTF) ?
						0 : (int)wc[i].wr_id;

					if (user_param->verb_type != ACCL_INTF) {
						if (wc[i].status != IBV_WC_SUCCESS) {
							NOTIFY_COMP_ERROR_SEND(wc[i], totscnt, totccnt);
							return_value = FAILURE;
							goto cleaning;
						}
					}

					ctx->ccnt[wc_id] += user_param->cq_mod;
					totccnt += user_param->cq_mod;

					if (user_param->noPeak == OFF) {
						if (totccnt >= tot_iters - 1)
							user_param->tcompleted[user_param->iters*num_of_qps - 1] = get_cycles();
						else
							user_param->tcompleted[totccnt-1] = get_cycles();
					}

					if (user_param->test_type==DURATION && user_param->state == SAMPLE_STATE) {
						if (user_param->report_per_port) {
							user_param->iters_per_port[user_param->port_by_qp[wc_id]] += user_param->cq_mod;
						}
						user_param->iters += user_param->cq_mod;
					}
				}

			} else if (ne < 0) {
				fprintf(stderr, "poll CQ failed %d\n", ne);
				return_value = FAILURE;
				goto cleaning;
			}
		}
	}

	if (user_param->noPeak == ON && user_param->test_type == ITERATIONS)
		user_param->tcompleted[0] = get_cycles();

cleaning:

	free(wc);
	return return_value;
}

int run_iter_lat(struct pingpong_context *ctx,struct perftest_parameters *user_param)
{
	uint64_t scnt = 0;
	int ne;
	int err = 0;
	struct ibv_send_wr *bad_wr = NULL;
	struct ibv_wc wc;

	int cpu_mhz = get_cpu_mhz(user_param->cpu_freq_f);
	int total_gap_cycles = user_param->latency_gap * cpu_mhz;
	cycles_t end_cycle, start_gap=0;

	ctx->wr[0].sg_list->length = user_param->size;
	ctx->wr[0].send_flags = IBV_SEND_SIGNALED;

	/* Duration support in latency tests. */
	/* if (user_param->test_type == DURATION) { */
		/* duration_param=user_param; */
		/* duration_param->state = START_STATE; */
		/* signal(SIGALRM, catch_alarm); */
		/* user_param->iters = 0; */
		/* if (user_param->margin > 0) */
			/* alarm(user_param->margin); */
		/* else */
			/* catch_alarm(0); */
	/* } */

	while (scnt < user_param->iters || (user_param->test_type == DURATION && user_param->state != END_STATE)) {
		if (user_param->latency_gap) {
			start_gap = get_cycles();
			end_cycle = start_gap + total_gap_cycles;
			while (get_cycles() < end_cycle) {
				continue;
			}
		}
		if (user_param->test_type == ITERATIONS)
			user_param->tposted[scnt++] = get_cycles();

		err = ibv_post_send(ctx->qp[0],&ctx->wr[0],&bad_wr);
		if (err) {
			fprintf(stderr,"Couldn't post send: scnt=%lu\n",scnt);
			return 1;
		}

		if (user_param->test_type == DURATION && user_param->state == END_STATE)
			break;

		if (user_param->use_event) {
			if (ctx_notify_events(ctx->channel)) {
				fprintf(stderr, "Couldn't request CQ notification\n");
				return 1;
			}
		}

		do {
			ne = ibv_poll_cq(ctx->send_cq, 1, &wc);
			if(ne > 0) {
				if (wc.status != IBV_WC_SUCCESS) {
					NOTIFY_COMP_ERROR_SEND(wc,scnt,scnt);
					return 1;
				}
				if (user_param->test_type==DURATION && user_param->state == SAMPLE_STATE)
					user_param->iters++;

			} else if (ne < 0) {
				fprintf(stderr, "poll CQ failed %d\n", ne);
				return FAILURE;
			}

		} while (!user_param->use_event && ne == 0);
	}

	return 0;
}

int run_iter_lat_write(struct pingpong_context *ctx,struct perftest_parameters *user_param)
{
	uint64_t scnt = 0;
	uint64_t ccnt = 0;
	uint64_t rcnt = 0;
	int ne;
	int err = 0;
	int poll_buf_offset = 0;
	volatile char *poll_buf = NULL;
	volatile char *post_buf = NULL;
	struct ibv_send_wr *bad_wr = NULL;
	struct ibv_wc wc;

	int cpu_mhz = get_cpu_mhz(user_param->cpu_freq_f);
	int total_gap_cycles = user_param->latency_gap * cpu_mhz;
	cycles_t end_cycle, start_gap=0;

	ctx->wr[0].sg_list->length = user_param->size;
	ctx->wr[0].send_flags = IBV_SEND_SIGNALED;
	if (user_param->size <= user_param->inline_size)
		ctx->wr[0].send_flags |= IBV_SEND_INLINE;

	if((user_param->use_xrc || user_param->connection_type == DC))
		poll_buf_offset = 1;

	post_buf = (char*)ctx->buf[0] + user_param->size - 1;
	poll_buf = (char*)ctx->buf[0] + (user_param->num_of_qps + poll_buf_offset)*BUFF_SIZE(ctx->size, ctx->cycle_buffer) + user_param->size - 1;

	/* Duration support in latency tests. */
	/* if (user_param->test_type == DURATION) { */
		/* duration_param=user_param; */
		/* duration_param->state = START_STATE; */
		/* signal(SIGALRM, catch_alarm); */
		/* user_param->iters = 0; */
		/* if (user_param->margin > 0) */
			/* alarm(user_param->margin); */
		/* else */
			/* catch_alarm(0); */
	/* } */

	/* Done with setup. Start the test. */
	while (scnt < user_param->iters || ccnt < user_param->iters || rcnt < user_param->iters
			|| ((user_param->test_type == DURATION && user_param->state != END_STATE))) {

		if ((rcnt < user_param->iters || user_param->test_type == DURATION) && 
        !(scnt < 1 && user_param->machine == SERVER)) {
			rcnt++;
			while (*poll_buf != (char)rcnt && user_param->state != END_STATE);
		}

		if (scnt < user_param->iters || user_param->test_type == DURATION) {
			if (user_param->latency_gap) {
				start_gap = get_cycles();
				end_cycle = start_gap + total_gap_cycles;
				while (get_cycles() < end_cycle) {
					continue;
				}
			}

			if (user_param->test_type == ITERATIONS)
				user_param->tposted[scnt] = get_cycles();

			*post_buf = (char)++scnt;
			err = ibv_post_send(ctx->qp[0],&ctx->wr[0],&bad_wr);
			if (err) {
				fprintf(stderr,"Couldn't post send: scnt=%lu\n",scnt);
				return 1;
			}
		}

		if (user_param->test_type == DURATION && user_param->state == END_STATE)
			break;

		if (ccnt < user_param->iters || user_param->test_type == DURATION) {
			do {
				ne = ibv_poll_cq(ctx->send_cq, 1, &wc);
			} while (ne == 0);

			if(ne > 0) {
				if (wc.status != IBV_WC_SUCCESS) {
					NOTIFY_COMP_ERROR_SEND(wc,scnt,ccnt);
					return 1;
				}
				ccnt++;
				if (user_param->test_type==DURATION && user_param->state == SAMPLE_STATE) {
					user_param->iters++;
				}

			} else if (ne < 0) {
				fprintf(stderr, "poll CQ failed %d\n", ne);
				return FAILURE;
			}
		}
	}

	return 0;
}






