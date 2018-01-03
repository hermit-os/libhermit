#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <limits.h>
#include <netinet/in.h>
#include <math.h>

#include "perftest_parameters_write_bw.h"

#define MAC_LEN (17)
#define ETHERTYPE_LEN (6)
#define MAC_ARR_LEN (6)
#define HEX_BASE (16)

#define inet_pton(af,src,dst) \
	(((af) == AF_INET) ? ip4addr_aton((src),(ip4_addr_t*)(dst)) : 0)

static const char *connStr[] = {"RC", "UC", "UD", "RawEth", "XRC", "DC"};
static const char *testsStr[] = {"Send", "RDMA_Write", "RDMA_Read", "Atomic"};
static const char *portStates[] = {"Nop", "Down", "Init", "Armed", "", "Active Defer"};
static const char *qp_state[] = {"OFF", "ON"};
static const char *exchange_state[] = {"Ethernet", "rdma_cm"};
static const char *atomicTypesStr[] = {"CMP_AND_SWAP", "FETCH_AND_ADD"};


// -----------------------------------------------------------------------------


int parse_ip_from_str(char *ip, u_int32_t *addr)
{
	return inet_pton(AF_INET, ip, addr);
}

const char *link_layer_str(int8_t link_layer)
{
	switch (link_layer) {
		case IBV_LINK_LAYER_UNSPECIFIED:
		case IBV_LINK_LAYER_INFINIBAND:
			return "IB";
		case IBV_LINK_LAYER_ETHERNET:
			return "Ethernet";
		default:
			return "Unknown";
	}
}

void flow_rules_force_dependecies(struct perftest_parameters *user_param)
{
	int min_iter_req = 0;
	if (user_param->flows != DEF_FLOWS) {
		if (user_param->is_server_port == OFF) {
			fprintf(stderr, " Flows feature works with UDP/TCP packets only for now\n");
			exit(1);
		}
		if (user_param->test_type == ITERATIONS) {
			min_iter_req = user_param->flows * user_param->flows_burst;
			if (user_param->iters / min_iter_req < 1) {
				fprintf(stderr, " Current iteration number will not complete full cycle on all flows, it need to be multiple of the product between flows and flows_burst\n");
				fprintf(stderr, " Set N*%d Iterations \n", user_param->flows * user_param->flows_burst);
				exit(FAILURE);
			}
		}
		if (user_param->tst == FS_RATE) {
			fprintf(stderr, "FS rate test not requiring flows parameter\n");
			exit(FAILURE);
		}
		if (user_param->duplex) {
			fprintf(stderr, " Flows is currently designed to work with unidir tests only\n");
			exit(FAILURE);
		}
	} else {
		if (user_param->flows_burst > 1) {
			fprintf(stderr, " Flows burst is designed to work with more then single flow\n");
			exit(FAILURE);
		}
	}
	return;
}

void get_gbps_str_by_ibv_rate(char *rate_input_value, int *rate)
{
	int i;
	for (i = 0; i < RATE_VALUES_COUNT; i++) {
		if (strcmp(rate_input_value, RATE_VALUES[i].rate_gbps_str) == 0) {
			*rate = (int)RATE_VALUES[i].rate_gbps_enum;
			return;
		}
	}
	printf("\x1b[31mThe input value for hw rate limit is not supported\x1b[0m\n");
	/* print_supported_ibv_rate_values(); */
}


// -----------------------------------------------------------------------------


static int get_cache_line_size()
{
	// HermitCore's cache line size is 64 (== DEF_CACHE_LINE_SIZE)
	int size = DEF_CACHE_LINE_SIZE;

	/* int size = 0; */
	/* size = sysconf(_SC_LEVEL1_DCACHE_LINESIZE); */
	/* if (size == 0) { */
		/* #if defined(__sparc__) && defined(__arch64__) */
		/* char* file_name = */
			/* "/sys/devices/system/cpu/cpu0/l2_cache_line_size"; */
		/* #else */
		/* char* file_name = */
			/* "/sys/devices/system/cpu/cpu0/cache/index0/coherency_line_size"; */
		/* #endif */

		/* FILE *fp; */
		/* char line[10]; */
		/* fp = fopen(file_name, "r"); */
		/* if (fp == NULL) { */
			/* return DEF_CACHE_LINE_SIZE; */
		/* } */
		/* if(fgets(line, 10,fp) != NULL) { */
			/* size = atoi(line); */
			/* fclose(fp); */
		/* } */
	/* } */
	/* if (size <= 0) */
		/* size = DEF_CACHE_LINE_SIZE; */

	return size;
}

static void init_perftest_params(struct perftest_parameters *user_param)
{
	user_param->port = DEF_PORT;
	user_param->ib_port = DEF_IB_PORT;
	user_param->ib_port2 = DEF_IB_PORT2;
	user_param->link_type = LINK_UNSPEC;
	user_param->link_type2 = LINK_UNSPEC;
	user_param->size = (user_param->tst == BW ) ? DEF_SIZE_BW : DEF_SIZE_LAT;
	user_param->tx_depth = (user_param->tst == BW || user_param->tst == LAT_BY_BW ) ? DEF_TX_BW : DEF_TX_LAT;
	user_param->qp_timeout = DEF_QP_TIME;
	user_param->test_method = RUN_REGULAR;
	user_param->cpu_freq_f = OFF;
	user_param->connection_type = (user_param->connection_type == RawEth) ? RawEth : RC;
	user_param->use_event = OFF;
	user_param->eq_num = 0;
	user_param->use_eq_num = OFF;
	user_param->num_of_qps = DEF_NUM_QPS;
	user_param->gid_index = DEF_GID_INDEX;
	user_param->gid_index2 = DEF_GID_INDEX;
	user_param->use_gid_user = 0;
	user_param->inline_size = DEF_INLINE;
	user_param->use_mcg = OFF;
	user_param->use_rdma_cm = OFF;
	user_param->work_rdma_cm = OFF;
	user_param->rx_depth = user_param->verb == SEND ? DEF_RX_SEND : DEF_RX_RDMA;
	user_param->duplex = OFF;
	user_param->noPeak = OFF;
	user_param->cq_mod = DEF_CQ_MOD;
	user_param->iters = (user_param->tst == BW && user_param->verb == WRITE) ? DEF_ITERS_WB : DEF_ITERS;
	user_param->dualport = OFF;
	user_param->post_list = 1;
	user_param->use_srq = OFF;
	user_param->use_xrc = OFF;
	user_param->use_rss = OFF;
	user_param->srq_exists = OFF;
	user_param->duration = DEF_DURATION;
	user_param->margin = DEF_INIT_MARGIN;
	user_param->test_type = ITERATIONS;
	user_param->state = START_STATE;
	user_param->tos = DEF_TOS;
	user_param->mac_fwd = OFF;
	user_param->report_fmt = MBS;
	user_param->report_both = OFF;
	user_param->is_reversed = OFF;
	user_param->is_limit_bw = OFF;
	user_param->limit_bw = 0;
	user_param->is_limit_msgrate = OFF;
	user_param->limit_msgrate = 0;
	user_param->pkey_index = 0;
	user_param->raw_qos = 0;
	user_param->inline_recv_size = 0;
	user_param->tcp = 0;
	user_param->burst_size = 0;
	user_param->rate_limit = 0;
	user_param->valid_hw_rate_limit = 0;
	user_param->rate_units = GIGA_BIT_PS;
	user_param->rate_limit_type = DISABLE_RATE_LIMIT;
	user_param->is_rate_limit_type = 0;
	user_param->output = -1;
	user_param->use_cuda = 0;
	user_param->mmap_file = NULL;
	user_param->mmap_offset = 0;
	user_param->iters_per_port[0] = 0;
	user_param->iters_per_port[1] = 0;
	user_param->wait_destroy = 0;
	user_param->is_old_raw_eth_param = 0;
	user_param->is_new_raw_eth_param = 0;
	user_param->reply_every = 1;
	user_param->vlan_en = OFF;
	user_param->vlan_pcp = 1;
	/* user_param->print_eth_func = &print_ethernet_header; */

	if (user_param->tst == LAT) {
		user_param->r_flag->unsorted = OFF;
		user_param->r_flag->histogram = OFF;
		user_param->r_flag->cycles = OFF;
	}

	if (user_param->verb == ATOMIC) {
		user_param->atomicType = FETCH_AND_ADD;
		user_param->size = DEF_SIZE_ATOMIC;
	}

	user_param->cpu_util = 0;
	user_param->cpu_util_data.enable = 0;
	user_param->retry_count = DEF_RETRY_COUNT;
	user_param->dont_xchg_versions = 0;
	user_param->use_exp = 0;
	user_param->ipv6 = 0;
	user_param->report_per_port = 0;
	user_param->use_odp = 0;
	user_param->use_hugepages = 0;
	user_param->use_promiscuous = 0;
	user_param->use_sniffer = 0;
	user_param->check_alive_exited = 0;
	user_param->raw_mcast = 0;
	user_param->masked_atomics = 0;
	user_param->cache_line_size = get_cache_line_size();
	/* user_param->cycle_buffer = sysconf(_SC_PAGESIZE); */
	user_param->cycle_buffer = DEF_PAGE_SIZE;

	/* if (user_param->cycle_buffer <= 0) { */
		/* user_param->cycle_buffer = DEF_PAGE_SIZE; */
	/* } */
	user_param->verb_type = NORMAL_INTF;
	user_param->is_exp_cq = 0;
	user_param->is_exp_qp = 0;
	user_param->use_res_domain = 0;
	user_param->mr_per_qp = 0;
	user_param->dlid = 0;
	user_param->traffic_class = 0;
	user_param->disable_fcs = 0;
	user_param->flows = DEF_FLOWS;
	user_param->flows_burst = 1;
	user_param->perform_warm_up = 0;
	user_param->use_ooo = 0;
}

static int set_link_layer(struct ibv_context *context, struct perftest_parameters *params)
{
	struct ibv_port_attr port_attr;
	int8_t curr_link = params->link_type;

	if (ibv_query_port(context, params->ib_port, &port_attr)) {
		fprintf(stderr, " Unable to query port %d attributes\n", params->ib_port);
		return FAILURE;
	}

	if (curr_link == LINK_UNSPEC)
		params->link_type = port_attr.link_layer;

	if (port_attr.state != IBV_PORT_ACTIVE) {
		fprintf(stderr, " Port number %d state is %s\n"
				, params->ib_port
				, portStates[port_attr.state]);
		return FAILURE;
	}

	if (strcmp("Unknown", link_layer_str(params->link_type)) == 0) {
		fprintf(stderr, "Link layer on port %d is Unknown\n", params->ib_port);
		return FAILURE;
	}

	if (params->dualport == ON) {
		curr_link = params->link_type2;
		if (ibv_query_port(context, params->ib_port2, &port_attr)) {
			fprintf(stderr, " Unable to query port %d attributes\n", params->ib_port2);
			return FAILURE;
		}

		if (curr_link == LINK_UNSPEC)
			params->link_type2 = port_attr.link_layer;

		if (port_attr.state != IBV_PORT_ACTIVE) {
			fprintf(stderr, " Port number %d state is %s\n"
				, params->ib_port2
				, portStates[port_attr.state]);
			return FAILURE;
		}

		if (strcmp("Unknown", link_layer_str(params->link_type2)) == 0) {
			fprintf(stderr, "Link layer on port %d is Unknown\n", params->ib_port2);
			return FAILURE;
		}
	}

	return SUCCESS;
}

static void ctx_set_max_inline(struct ibv_context *context, struct perftest_parameters *user_param)
{
	enum ctx_device current_dev = ib_dev_name(context);

	if (current_dev == UNKNOWN || current_dev == DEVICE_ERROR) {

		if (user_param->inline_size != DEF_INLINE) {
			printf(RESULT_LINE);
			fprintf(stderr, "Device not recognized to implement inline feature. Disabling it\n");
		}
		user_param->inline_size = 0;
		return;
	}

	if (user_param->inline_size == DEF_INLINE) {

		if (user_param->tst ==LAT) {

			switch(user_param->verb) {

				case WRITE: user_param->inline_size = (user_param->connection_type == DC)? DEF_INLINE_DC : DEF_INLINE_WRITE; break;
				case SEND : user_param->inline_size = (user_param->connection_type == DC)? DEF_INLINE_DC : (user_param->connection_type == UD)? DEF_INLINE_SEND_UD :
					    ((user_param->connection_type == XRC) ? DEF_INLINE_SEND_XRC : DEF_INLINE_SEND_RC_UC) ; break;
				default : user_param->inline_size = 0;
			}

		} else {
			user_param->inline_size = 0;
		}
	}

	return;
}

static int ctx_set_out_reads(struct ibv_context *context, int num_user_reads)
{
	int max_reads = 0;
	struct ibv_device_attr attr;

	if (!ibv_query_device(context, &attr)) {
		max_reads = attr.max_qp_rd_atom;
	}

	if (num_user_reads > max_reads) {
		printf(RESULT_LINE);
		fprintf(stderr, " Number of outstanding reads is above max = %d\n", max_reads);
		fprintf(stderr, " Changing to that max value\n");
		num_user_reads = max_reads;
	}
	else if (num_user_reads <= 0) {
		num_user_reads = max_reads;
	}

	return num_user_reads;
}

static int ctx_chk_pkey_index(struct ibv_context *context, int pkey_idx)
{
	int idx = 0;
	struct ibv_device_attr attr;

	if (!ibv_query_device(context, &attr)) {
		if (pkey_idx > attr.max_pkeys - 1) {
			printf(RESULT_LINE);
			fprintf(stderr, " Specified PKey Index, %i, greater than allowed max, %i\n", pkey_idx, attr.max_pkeys - 1);
			fprintf(stderr, " Changing to 0\n");
			idx = 0;
		} else
			idx = pkey_idx;
	} else {
		fprintf(stderr, " Unable to validata PKey Index, changing to 0\n");
		idx = 0;
	}

	return idx;

}

void set_raw_eth_parameters(struct perftest_parameters *user_param)
{
	int i;

	if (user_param->is_new_raw_eth_param == 1 && user_param->is_old_raw_eth_param == 1) {
		printf(RESULT_LINE);
		fprintf(stderr," Invalid Command line.\nMix of source with local|remote and dest with local|remote is not supported.\n");
		fprintf(stderr,"For L2 tests you must enter local and remote mac by this format --local_mac XX:XX:XX:XX:XX:XX --remote_mac XX:XX:XX:XX:XX:XX\n");
		fprintf(stderr,"For L3 tests You must add also local and remote ip by this format --local_ip X.X.X.X --remote_ip X.X.X.X\n");
		fprintf(stderr,"For L4 you need to add also local and remote port by this format --local_port XXXX --remote_port XXXX\n");
		exit(1);
	}

	if (user_param->is_new_raw_eth_param) {
		for (i = 0; i < MAC_ARR_LEN; i++) {
			user_param->source_mac[i] = user_param->local_mac[i];
			user_param->dest_mac[i] = user_param->remote_mac[i];
		}

		if (user_param->machine == SERVER) {
			user_param->server_ip   = user_param->local_ip;
			user_param->client_ip   = user_param->remote_ip;
			user_param->server_port = user_param->local_port;
			user_param->client_port = user_param->remote_port;
		} else if (user_param->machine == CLIENT) {
			user_param->server_ip   = user_param->remote_ip;
			user_param->client_ip   = user_param->local_ip;
			user_param->server_port = user_param->remote_port;
			user_param->client_port = user_param->local_port;
		}
	}
}

static void force_dependecies(struct perftest_parameters *user_param)
{
	/*Additional configuration and assignments.*/
	if (user_param->test_type == ITERATIONS) {
		if (user_param->tx_depth > user_param->iters) {
			user_param->tx_depth = user_param->iters;
		}

		if (user_param->verb == SEND && user_param->rx_depth > user_param->iters) {
			user_param->rx_depth = user_param->iters;
		}

		if (user_param->connection_type == UD || user_param->connection_type == UC) {
			if (user_param->rx_depth == DEF_RX_SEND) {
				user_param->rx_depth = (user_param->iters < UC_MAX_RX) ? user_param->iters : UC_MAX_RX;
			}
		}
	}

	if (user_param->tst == LAT_BY_BW && user_param->rate_limit_type == DISABLE_RATE_LIMIT) {
		if (user_param->output == FULL_VERBOSITY)
			printf("rate_limit type is forced to SW.\n");
		user_param->rate_limit_type = SW_RATE_LIMIT;
	}

	if (user_param->cq_mod > user_param->tx_depth) {
		user_param->cq_mod = user_param->tx_depth;
	}

	if (user_param->verb == READ || user_param->verb == ATOMIC)
		user_param->inline_size = 0;

	if (user_param->test_method == RUN_ALL)
		user_param->size = MAX_SIZE;

	if (user_param->verb == ATOMIC && user_param->size != DEF_SIZE_ATOMIC) {
		user_param->size = DEF_SIZE_ATOMIC;
	}

	if (user_param->use_srq && user_param->verb != SEND) {
		printf(RESULT_LINE);
		printf(" Using SRQ only avavilible in SEND tests.\n");
		exit (1);
	}

	if (user_param->dualport == ON) {

		user_param->num_of_qps *= 2;
		if (user_param->tst != BW) {
			printf(" Dual-port mode only supports BW tests.\n");
			exit (1);
		}

		if (user_param->use_mcg){
			printf(" Dual-port mode not supported in multicast feature\n");
			exit (1);
		}
		if (user_param->link_type != LINK_UNSPEC)
			user_param->link_type2 = user_param->link_type;
	}

	if (user_param->post_list > 1) {
		user_param->cq_mod = user_param->post_list;
		printf(RESULT_LINE);
		printf("Post List requested - CQ moderation will be the size of the post list\n");
	}

	if (user_param->test_type==DURATION) {

		/* When working with Duration, iters=0 helps us to satisfy loop cond. in run_iter_bw.
		We also use it for "global" counter of packets.
		*/
		user_param->iters = 0;
		user_param->noPeak = ON;

		if (user_param->use_event) {
			printf(RESULT_LINE);
			fprintf(stderr,"Duration mode doesn't work with events.\n");
			exit(1);
		}

		if (user_param->test_method == RUN_ALL) {
			printf(RESULT_LINE);
			fprintf(stderr, "Duration mode currently doesn't support running on all sizes.\n");
			exit(1);
		}
		if (user_param->cpu_util) {
			user_param->cpu_util_data.enable = 1;
		}
	}

	if ( (user_param->test_type != DURATION) && user_param->cpu_util ) {
		printf(RESULT_LINE);
		fprintf(stderr, " CPU Utilization works only with Duration mode.\n");
	}

	if (user_param->connection_type == RawEth) {

		if (user_param->test_method == RUN_ALL) {
			fprintf(stderr, "Raw Ethernet tests do not support -a / --all flag.\n");
			exit(1);
		}

		if (user_param->use_gid_user) {
			fprintf(stderr," GID index isn't supported for Raw Ethernet tests\n");
			exit(1);
		}

		if (user_param->mmap_file != NULL || user_param->mmap_offset) {
			fprintf(stderr," mmaped files aren't supported for Raw Ethernet tests\n");
			exit(1);
		}

		if(user_param->machine == UNCHOSEN) {
			printf(RESULT_LINE);
			fprintf(stderr," Invalid Command line.\n you must choose test side --client or --server\n");
			exit(1);
		}

		/* Verify the packet */
		if(user_param->is_source_mac == OFF) {
			printf(RESULT_LINE);
			fprintf(stderr," Invalid Command line.\n you must enter source mac by this format -B XX:XX:XX:XX:XX:XX\n");
			exit(1);
		}

		if(user_param->is_dest_mac == OFF && (user_param->tst == LAT || (user_param->machine == CLIENT && !user_param->raw_mcast))) {
			printf(RESULT_LINE);
			fprintf(stderr," Invalid Command line.\n you must enter dest mac by this format -E XX:XX:XX:XX:XX:XX\n");
			exit(1);
		}

		if((user_param->is_server_port == ON && user_param->is_client_port == OFF) || (user_param->is_server_port == OFF && user_param->is_client_port == ON)) {
			printf(RESULT_LINE);
			fprintf(stderr," Invalid Command line.\n if you would like to send UDP header,\n you must enter server&client port --server_port X --client_port X\n");
			exit(1);
		}

		if ((user_param->is_server_port == ON) && (user_param->is_server_ip == OFF || user_param->is_client_ip == OFF)) {
			printf(RESULT_LINE);
			fprintf(stderr," Invalid Command line.\nPlease provide source_ip and/or dest_ip when using UDP\n");
			exit(1);
		}
		/* UDP packet is ok by now. check tcp flag */
		if (user_param->tcp == ON && user_param->is_server_port == OFF) {
			printf(RESULT_LINE);
			fprintf(stderr,"Invalid Command line.\nPlease provide UDP information (IP & UDP Port src/dest) in order to use TCP\n");
			exit(1);
		}

		/* Mac forwarding dependencies */
		if (user_param->duplex == OFF && user_param->mac_fwd == ON) {
			printf("mac_fwd should run in duplex mode only. changing to duplex mode.\n");
			user_param->duplex = ON;
		}
		if (user_param->mac_fwd == ON && user_param->cq_mod >= user_param->rx_depth) {
			fprintf(stderr," CQ moderation can't be grater than rx depth.\n");
			user_param->cq_mod = user_param->rx_depth < user_param->tx_depth ? user_param->rx_depth : user_param->tx_depth;
			fprintf(stderr," Changing CQ moderation to min( rx depth , tx depth) = %d.\n",user_param->cq_mod);
		}

		if (user_param->raw_mcast && user_param->duplex) {
			fprintf(stderr, " Multicast feature works on unidirectional traffic only\n");
			exit(1);
		}

		flow_rules_force_dependecies(user_param);
	}

	if (user_param->use_mcg && user_param->gid_index == -1) {
		user_param->gid_index = 0;
	}


	if (user_param->verb == ATOMIC && user_param->connection_type == DC) {
		printf(RESULT_LINE);
		fprintf(stderr, " ATOMIC tests don't support DC transport\n");
		exit(1);
	}

	if (user_param->tos != DEF_TOS && user_param->connection_type != RawEth) {
		fprintf(stdout," TOS only valid for rdma_cm based QP and RawEth QP \n");
		exit(1);
	}

	if (user_param->use_mcg) {

		if (user_param->connection_type != UD)
			user_param->connection_type = UD;

		if (user_param->duplex) {
			fprintf(stdout,"Bidirectional mode not supported in multicast\n");
			exit (1);
		}

		if (user_param->num_of_qps > 1) {
			fprintf(stdout,"Only 1 QP supported in multicast\n");
			exit(1);
		}
	}

	if(user_param->verb == ATOMIC && user_param->use_odp) {
		printf(RESULT_LINE);
		fprintf(stderr," ODP does not support ATOMICS for now\n");
		exit(1);
	}

	if (user_param->verb == SEND && user_param->tst == BW && user_param->machine == SERVER && !user_param->duplex )
		user_param->noPeak = ON;

	/* Run infinitely dependencies */
	if (user_param->test_method == RUN_INFINITELY) {
		user_param->noPeak = ON;
		user_param->test_type = DURATION;
		if (user_param->use_event) {
			printf(RESULT_LINE);
			fprintf(stderr," run_infinitely does not support events feature yet.\n");
			exit(1);
		}

		if (user_param->tst == LAT) {
			printf(RESULT_LINE);
			fprintf(stderr," run_infinitely exists only in BW tests for now.\n");
			exit(1);

		}

		if (user_param->duplex && user_param->verb == SEND) {
			printf(RESULT_LINE);
			fprintf(stderr," run_infinitely mode is not supported in SEND Bidirectional BW test\n");
			exit(1);
		}
		if (user_param->rate_limit_type != DISABLE_RATE_LIMIT) {
			printf(RESULT_LINE);
			fprintf(stderr," run_infinitely does not support rate limit feature yet\n");
			exit(1);
		}
	}

	if (user_param->connection_type == DC && !user_param->use_srq)
		user_param->use_srq = 1;

	/* XRC Part */
	if (user_param->connection_type == XRC) {
		user_param->use_xrc = ON;
		user_param->use_srq = ON;
	}

	#ifndef HAVE_RSS_EXP
	if (user_param->use_rss) {
		printf(RESULT_LINE);
		fprintf(stderr," RSS feature is not available in libibverbs\n");
		exit(1);
	}
	#endif

	if ((user_param->use_srq && (user_param->tst == LAT || user_param->machine == SERVER || user_param->duplex == ON)) || user_param->use_xrc)
		user_param->srq_exists = 1;

	if (user_param->burst_size > 0) {
		if (user_param->rate_limit_type == DISABLE_RATE_LIMIT && user_param->tst != LAT_BY_BW ) {
			printf(RESULT_LINE);
			fprintf(stderr," Can't enable burst mode when rate limiter is off\n");
			exit(1);
		}
	}

	if (user_param->burst_size <= 0) {
		if (user_param->rate_limit_type == SW_RATE_LIMIT)
			fprintf(stderr," Setting burst size to tx depth = %d\n", user_param->tx_depth);
		user_param->burst_size = user_param->tx_depth;
	}

	if (user_param->rate_limit_type == SW_RATE_LIMIT) {
		if (user_param->tst != BW || user_param->verb == ATOMIC || (user_param->verb == SEND && user_param->duplex)) {
			printf(RESULT_LINE);
			fprintf(stderr,"SW Rate limiter cann't be executed on non-BW, ATOMIC or bidirectional SEND tests\n");
			exit(1);
		}
	} else if (user_param->rate_limit_type == HW_RATE_LIMIT) {
		double rate_limit_gbps = 0;
		switch (user_param->rate_units) {
			case MEGA_BYTE_PS:
				rate_limit_gbps =((double)(((user_param->rate_limit)*8*1024*1024) / 1000000000));
				break;
			case GIGA_BIT_PS:
				rate_limit_gbps = user_param->rate_limit;
				break;
			case PACKET_PS:
				printf(RESULT_LINE);
				fprintf(stderr, " Failed: pps rate limit units is not supported when setting HW rate limit\n");
				exit(1);
			default:
				printf(RESULT_LINE);
				fprintf(stderr, " Failed: Unknown rate limit units\n");
				exit(1);
		}
		if (rate_limit_gbps > 0) {
			int rate_to_set = -1;
			get_gbps_str_by_ibv_rate(user_param->rate_limit_str, &rate_to_set);
			if (rate_to_set == -1) {
				printf(RESULT_LINE);
				fprintf(stderr, " Failed: Unknown rate limit value\n");
				exit(1);
			}
			user_param->valid_hw_rate_limit = rate_to_set;
		}
	} else if (user_param->rate_limit_type == PP_RATE_LIMIT) {
		if (user_param->rate_limit < 0) {
			fprintf(stderr," Must specify a rate limit when using Packet Pacing.\n Please add --rate_limit=<limit>.\n");
			exit(1);
		}
		if (user_param->connection_type != RawEth) {
			fprintf(stderr,"Packet Pacing is only supported for Raw Ethernet.\n");
			exit(1);
		}

		if (user_param->rate_units != MEGA_BYTE_PS) {
			fprintf(stderr,"Packet Pacing only supports MEGA_BYTE_PS.\n");
			exit(1);
		}

		user_param->rate_limit = user_param->rate_limit * 8 * 1024;
	}

	if (user_param->tst == LAT_BY_BW) {
		if ( user_param->test_type == DURATION) {
			fprintf(stderr, "Latency under load test is currently support iteration mode only.\n");
			exit(1);
		}
		if (user_param->num_of_qps > 1) {
			fprintf(stderr, "Multi QP is not supported in LAT under load test\n");
			exit(1);
		}
		if (user_param->duplex) {
			fprintf(stderr, "Bi-Dir is not supported in LAT under load test\n");
			exit(1);
		}
		if(user_param->output != FULL_VERBOSITY && user_param->output != OUTPUT_LAT) {
			printf(RESULT_LINE);
			fprintf(stderr," Output verbosity level for BW can be latency\n");
			exit(1);
		}
	}

	if (user_param->output != FULL_VERBOSITY) {
		if (user_param->tst == BW && !(user_param->output == OUTPUT_BW || user_param->output == OUTPUT_MR)) {
			printf(RESULT_LINE);
			fprintf(stderr," Output verbosity level for BW can be: bandwidth, message_rate\n");
			exit(1);
		}

		if (user_param->tst == LAT && !(user_param->output == OUTPUT_LAT)) {
			printf(RESULT_LINE);
			fprintf(stderr," Output verbosity level for LAT can be: latency\n");
			exit(1);
		}
	}

	if ( (user_param->latency_gap > 0) && user_param->tst != LAT ) {
		printf(RESULT_LINE);
		fprintf(stderr," Latency gap feature is only for latency tests\n");
		exit(1);
	}

	if ( user_param->test_type == DURATION && user_param->margin == DEF_INIT_MARGIN) {
		user_param->margin = user_param->duration / 4;
	}

	/* #if defined(HAVE_VERBS_EXP) && defined(HAVE_DC) */
	/* if (user_param->connection_type == DC) { */
		/* user_param->use_exp = 1; */
	/* } */
	/* #endif */

	/* #ifdef HAVE_CUDA */
	/* if (user_param->use_cuda) { */
		/* if (user_param->tst != BW) { */
			/* printf(RESULT_LINE); */
			/* fprintf(stderr," Perftest supports CUDA only in BW tests\n"); */
			/* exit(1); */
		/* } */
	/* } */

	/* if (user_param->use_cuda && user_param->mmap_file != NULL) { */
		/* printf(RESULT_LINE); */
		/* fprintf(stderr,"You cannot use CUDA and an mmap'd file at the same time\n"); */
		/* exit(1); */
	/* } */
	/* #endif */

	if ( (user_param->connection_type == UD) && (user_param->inline_size > MAX_INLINE_UD) ) {
		printf(RESULT_LINE);
		fprintf(stderr, "Setting inline size to %d (Max inline size in UD)\n",MAX_INLINE_UD);
		user_param->inline_size = MAX_INLINE_UD;
	}

	if (user_param->report_per_port && (user_param->test_type != DURATION || !user_param->dualport)) {
		printf(RESULT_LINE);
		fprintf(stderr, "report per port feature work only with Duration and Dualport\n");
		exit(1);
	}

	/* WA for a bug when rx_depth is odd in SEND */
	if (user_param->verb == SEND && (user_param->rx_depth % 2 == 1) && user_param->test_method == RUN_REGULAR)
		user_param->rx_depth += 1;

	if (user_param->test_type == ITERATIONS && user_param->iters > 20000 && user_param->noPeak == OFF && user_param->tst == BW)
		user_param->noPeak = ON;

	if (!(user_param->duration > 2*user_param->margin)) {
		printf(RESULT_LINE);
		fprintf(stderr, "please check that DURATION > 2*MARGIN\n");
		exit(1);
	}

	if((user_param->use_event == OFF) && user_param->use_eq_num == ON) {
		fprintf(stderr, " Events must be enabled to select a completion vector\n");
		exit(1);
	}

	/* #ifdef HAVE_ACCL_VERBS */
	/* if (user_param->verb_type != NORMAL_INTF || user_param->use_res_domain) { */
		/* user_param->is_exp_cq = 1; */
		/* user_param->use_exp = 1; */
	/* } */

	/* if (user_param->verb_type == ACCL_INTF) { */
		/* if (user_param->connection_type != RC && */
			/* user_param->connection_type != UC && user_param->connection_type != RawEth) { */
			/* fprintf(stderr, "Accelerated verbs support RC/UC/RAW_ETH connections only.\n"); */
			/* exit(1); */
		/* } */

		/* if (user_param->verb != SEND) { */
			/* fprintf(stderr, "Accelerated verbs support SEND opcode only.\n"); */
			/* exit(1); */
		/* } */

		/* if (user_param->num_of_qps > 1) { */
			/* fprintf(stderr, "Accelerated verbs in perftest support only 1 qp for now.\n"); */
			/* exit(1); */
		/* } */

		/* if (user_param->tst != BW) { */
			/* fprintf(stderr, "Accelerated verbs in perftest supports only BW tests for now.\n"); */
			/* exit(1); */
		/* } */

		/* if (user_param->duplex) { */
			/* fprintf(stderr, "Accelerated verbs in perftest supports only unidir tests for now\n"); */
			/* exit(1); */
		/* } */

		/* if (user_param->test_method == RUN_INFINITELY) { */
			/* fprintf(stderr, "Accelerated verbs in perftest does not support Run Infinitely mode for now\n"); */
			/* exit(1); */
		/* } */
	/* } */
	/* if (user_param->perform_warm_up && */
			/* !(user_param->tst == BW && */
			/* (user_param->verb == ATOMIC || user_param->verb == WRITE || user_param->verb == READ))) { */
		/* fprintf(stderr, "Perform warm up is available in ATOMIC, READ and WRITE BW tests only"); */
		/* exit(1); */
	/* } */
	/* #endif */

	return;
}

static float calc_cpu_util(struct perftest_parameters *user_param)
{
	long long ustat_diff, idle_diff;
	ustat_diff = user_param->cpu_util_data.ustat[1] - user_param->cpu_util_data.ustat[0];
	idle_diff = user_param->cpu_util_data.idle[1] - user_param->cpu_util_data.idle[0];

	if ((ustat_diff + idle_diff) != 0)
		return ((float)ustat_diff / (ustat_diff + idle_diff)) * 100;
	else
		return 0;
}

const char *transport_str(enum ibv_transport_type type)
{
	switch (type) {
		case IBV_TRANSPORT_IB:
			return "IB";
			break;
		case IBV_TRANSPORT_IWARP:
			return "IW";
			break;
		default:
			return "Unknown";
	}
}


// -----------------------------------------------------------------------------


int parser(struct perftest_parameters *user_param, char *argv[], int argc)
{
	int c, size_len;
	int size_factor = 1;
	static int run_inf_flag = 0;
	static int report_fmt_flag = 0;
	static int srq_flag = 0;
	static int report_both_flag = 0;
	static int is_reversed_flag = 0;
	static int pkey_flag = 0;
	static int inline_recv_flag = 0;
	static int tcp_flag = 0;
	static int burst_size_flag = 0;
	static int rate_limit_flag = 0;
	static int rate_units_flag = 0;
	static int rate_limit_type_flag = 0;
	static int verbosity_output_flag = 0;
	static int cpu_util_flag = 0;
	static int latency_gap_flag = 0;
	static int flow_label_flag = 0;
	static int retry_count_flag = 0;
	static int dont_xchg_versions_flag = 0;
	static int use_exp_flag = 0;
	static int use_cuda_flag = 0;
	static int mmap_file_flag = 0;
	static int mmap_offset_flag = 0;
	static int ipv6_flag = 0;
	static int raw_ipv6_flag = 0;
	static int report_per_port_flag = 0;
	static int odp_flag = 0;
	static int hugepages_flag = 0;
	static int use_promiscuous_flag = 0;
	static int use_sniffer_flag = 0;
	static int raw_mcast_flag = 0;
	static int verb_type_flag = 0;
	static int use_res_domain_flag = 0;
	static int mr_per_qp_flag = 0;
	static int dlid_flag = 0;
	static int tclass_flag = 0;
	static int wait_destroy_flag = 0;
	static int disable_fcs_flag = 0;
	static int flows_flag = 0;
	static int flows_burst_flag = 0;
	static int force_link_flag = 0;
	static int local_ip_flag = 0;
	static int remote_ip_flag = 0;
	static int local_port_flag = 0;
	static int remote_port_flag = 0;
	static int local_mac_flag = 0;
	static int remote_mac_flag = 0;
	static int reply_every_flag = 0;
	static int perform_warm_up_flag = 0;
	static int use_ooo_flag = 0;
	static int vlan_en = 0;
	static int vlan_pcp_flag = 0;

	char *server_ip = NULL;
	char *client_ip = NULL;
	char *local_ip = NULL;
	char *remote_ip = NULL;

	// Initialize parameters
	init_perftest_params(user_param);

	if(user_param->connection_type == RawEth)
		user_param->machine = UNCHOSEN;

	if (tcp_flag) {
		user_param->tcp = 1;
	}
	if (run_inf_flag) {
		user_param->test_method = RUN_INFINITELY;
	}
	if (srq_flag) {
		user_param->use_srq = 1;
	}
	if (report_fmt_flag) {
		user_param->report_fmt = GBS;
	}
	if (dont_xchg_versions_flag) {
		user_param->dont_xchg_versions = 1;
	}
	if (use_exp_flag) {
		user_param->use_exp = 1;
	}
	if (use_res_domain_flag) {
		user_param->use_res_domain = 1;
	}
	if (use_cuda_flag) {
		user_param->use_cuda = 1;
	}
	if (report_both_flag) {
		user_param->report_both = 1;
	}
	if (is_reversed_flag) {
		user_param->is_reversed = 1;
	}
	if (cpu_util_flag) {
		user_param->cpu_util = 1;
	}
	if (report_per_port_flag) {
		user_param->report_per_port = 1;
	}
	if (ipv6_flag) {
		user_param->ipv6 = 1;
	}

	if (raw_ipv6_flag) {
		if (user_param->is_new_raw_eth_param) {
			if (user_param->is_server_ip) {
				if(1 != parse_ip6_from_str(local_ip,
							  (struct in6_addr *)&(user_param->local_ip6))) {
					fprintf(stderr, " Invalid local IP address\n");
					return FAILURE;
				}
			}
			if (user_param->is_client_ip) {
				if(1 != parse_ip6_from_str(remote_ip,
							  (struct in6_addr *)&(user_param->remote_ip6))) {
					fprintf(stderr, " Invalid remote IP address\n");
					return FAILURE;
				}
			}
		} else {
			if (user_param->is_server_ip) {
				if(1 != parse_ip6_from_str(server_ip,
							  (struct in6_addr *)&(user_param->server_ip6))) {
					fprintf(stderr, " Invalid server IP address\n");
					return FAILURE;
				}
			}
			if (user_param->is_client_ip) {
				if(1 != parse_ip6_from_str(client_ip,
							  (struct in6_addr *)&(user_param->client_ip6))) {
					fprintf(stderr, " Invalid client IP address\n");
					return FAILURE;
				}
			}
		}
		user_param->raw_ipv6 = 1;
	} else {
		if (user_param->is_new_raw_eth_param) {
			if (user_param->is_server_ip) {
				if(1 != parse_ip_from_str(local_ip,
							  &(user_param->local_ip))) {
					fprintf(stderr, " Invalid local IP address\n");
					return FAILURE;
				}
			}
			if (user_param->is_client_ip) {
				if(1 != parse_ip_from_str(remote_ip,
							  &(user_param->remote_ip))) {
					fprintf(stderr, " Invalid remote IP address\n");
					return FAILURE;
				}
			}
		} else {
			if (user_param->is_server_ip) {
				if(1 != parse_ip_from_str(server_ip,
							  &(user_param->server_ip))) {
					fprintf(stderr, " Invalid server IP address\n");
					return FAILURE;
				}
			}
			if (user_param->is_client_ip) {
				if(1 != parse_ip_from_str(client_ip,
							  &(user_param->client_ip))) {
					fprintf(stderr, " Invalid client IP address\n");
					return FAILURE;
				}
			}
		}
	}

	if(odp_flag) {
		user_param->use_odp = 1;
	}
	if(hugepages_flag) {
		user_param->use_hugepages = 1;
	}
	if (use_promiscuous_flag) {
		user_param->use_promiscuous = 1;
	}
	if (use_sniffer_flag) {
		user_param->use_sniffer = 1;
	}
	if (raw_mcast_flag) {
		user_param->raw_mcast = 1;
	}
	if (mr_per_qp_flag) {
		user_param->mr_per_qp = 1;
	}
	if (disable_fcs_flag) {
		user_param->disable_fcs = 1;
	}
	if (perform_warm_up_flag) {
		user_param->perform_warm_up = 1;
	}
	if (use_ooo_flag)
		user_param->use_ooo = 1;

	if(vlan_en) {
		user_param->vlan_en = ON;
		/* user_param->print_eth_func = &print_ethernet_vlan_header; */
		vlan_en = 0;
	}

	user_param->servername = SERVER_NAME;

	if(user_param->connection_type != RawEth)
		user_param->machine = user_param->servername ? CLIENT : SERVER;

	/* fan-in addition */
	if (user_param->is_reversed) {
		if (user_param->machine == SERVER)
			user_param->machine = CLIENT;
		else
			user_param->machine = SERVER;
	}

	set_raw_eth_parameters(user_param);
	force_dependecies(user_param);
	return 0;
}

int check_link(struct ibv_context *context, struct perftest_parameters *user_param)
{
	user_param->transport_type = context->device->transport_type;

	if (set_link_layer(context, user_param) == FAILURE){
		fprintf(stderr, " Couldn't set the link layer\n");
		return FAILURE;
	}

	if (user_param->link_type == IBV_LINK_LAYER_ETHERNET && user_param->gid_index == -1) {
		user_param->gid_index = 0;
	}

	if (user_param->connection_type == RawEth) {

		if (user_param->link_type != IBV_LINK_LAYER_ETHERNET) {
			fprintf(stderr, " Raw Etherent test can only run on Ethernet link! exiting ...\n");
			return FAILURE;
		}
	}

	/* in case of dual-port mode */
	if (user_param->dualport==ON) {
		if (user_param->link_type2 == IBV_LINK_LAYER_ETHERNET && user_param->gid_index2 == -1) {
			user_param->gid_index2 = 1;
		}
	}

	/* Compute Max inline size with pre found statistics values */
	ctx_set_max_inline(context, user_param);

	if (user_param->verb == READ || user_param->verb == ATOMIC)
		user_param->out_reads = ctx_set_out_reads(context, user_param->out_reads);
	else
		user_param->out_reads = 1;


	if (!user_param->ib_devname)
		GET_STRING(user_param->ib_devname, ibv_get_device_name(context->device))

	if (user_param->pkey_index > 0)
		user_param->pkey_index = ctx_chk_pkey_index(context, user_param->pkey_index);

	return SUCCESS;
}

void ctx_print_test_info(struct perftest_parameters *user_param)
{
	int temp = 0;

	if (user_param->output != FULL_VERBOSITY)
		return;

	printf(RESULT_LINE);
	printf(" ");
	printf("%s ", testsStr[user_param->verb]);

	if (user_param->verb == ATOMIC) {
		printf("%s ", atomicTypesStr[user_param->atomicType]);
	}

	if (user_param->tst == BW) {

		if (user_param->duplex) {
			printf("Bidirectional ");
		}

		if (user_param->post_list > 1) {
			printf("Post List ");
		}

		printf("BW ");

	} else if (user_param->tst == LAT) {
		printf("Latency ");
	}

	if (user_param->mac_fwd) {
		printf("forwarding ");
	}

	if (user_param->use_mcg)
		printf("Multicast ");

	printf("Test\n");

	if (user_param->use_event) {
		printf(" Test with events. Using %s_comp%d\n", user_param->ib_devname, user_param->eq_num);
	}

	if (user_param->use_mcg)
		printf(" MultiCast runs on UD!\n");

	printf(" Dual-port : %s\t\tDevice : %s\n", user_param->dualport ? "ON" : "OFF", user_param->ib_devname);
	printf(" Number of qps : %d\t\tTransport type : %s\n", user_param->num_of_qps, transport_str(user_param->transport_type));
	printf(" Connection type : %s\t\tUsing SRQ : %s\n", connStr[user_param->connection_type], user_param->use_srq ? "ON" : "OFF");

	if (user_param->machine == CLIENT || user_param->duplex) {
		printf(" TX depth : %d\n", user_param->tx_depth);
	}

	if (user_param->post_list > 1)
		printf(" Post List : %d\n", user_param->post_list);

	if (user_param->verb == SEND && (user_param->machine == SERVER || user_param->duplex)) {
		printf(" RX depth : %d\n", user_param->rx_depth);
	}

	if (user_param->tst == BW) {
		printf(" CQ Moderation : %d\n", user_param->cq_mod);
	}

	printf(" Mtu : %lu[B]\n", user_param->connection_type == RawEth ? user_param->curr_mtu : MTU_SIZE(user_param->curr_mtu));
	printf(" Link type : %s\n" , link_layer_str(user_param->link_type));

	/* we use the receive buffer only for mac forwarding. */
	if (user_param->mac_fwd == ON)
		printf(" Buffer size : %d[B]\n" , user_param->buff_size/2);

	if (user_param->gid_index != DEF_GID_INDEX)
		printf(" GID index : %d\n", user_param->gid_index);
	if ((user_param->dualport == ON) && (user_param->gid_index2 != DEF_GID_INDEX))
		printf(" GID index2 : %d\n", user_param->gid_index2);

	if (user_param->verb != READ && user_param->verb != ATOMIC)
		printf(" Max inline data : %d[B]\n", user_param->inline_size);

	else
		printf(" Outstand reads : %d\n", user_param->out_reads);

	printf(" rdma_cm QPs : %s\n", qp_state[user_param->work_rdma_cm]);
	printf(" Data ex. method : %s", exchange_state[temp]);
	putchar('\n');

	printf(RESULT_LINE);
}

void print_report_bw(struct perftest_parameters *user_param, struct bw_report_data *my_bw_rep)
{
	double cycles_to_units, sum_of_test_cycles;
	int location_arr;
	int opt_completed = 0;
	int opt_posted = 0;
	int i, j;
	int run_inf_bi_factor;
	int num_of_qps = user_param->num_of_qps;
	long format_factor;
	long num_of_calculated_iters = user_param->iters;

	int free_my_bw_rep = 0;
	if (user_param->test_method == RUN_INFINITELY)
		user_param->tcompleted[opt_posted] = get_cycles();

	cycles_t t, opt_delta, peak_up, peak_down, tsize;

	opt_delta = user_param->tcompleted[opt_posted] - user_param->tposted[opt_completed];

	if((user_param->connection_type == DC || user_param->use_xrc) && user_param->duplex)
		num_of_qps /= 2;

	if (user_param->noPeak == OFF) {
		/* Find the peak bandwidth unless asked not to in command line */
		for (i = 0; i < num_of_calculated_iters * num_of_qps; ++i) {
			for (j = i; j < num_of_calculated_iters * num_of_qps; ++j) {
				t = (user_param->tcompleted[j] - user_param->tposted[i]) / (j - i + 1);
				if (t < opt_delta) {
					opt_delta = t;
					opt_posted = i;
					opt_completed = j;
				}
			}
		}
	}

	cycles_to_units = get_cpu_mhz(user_param->cpu_freq_f) * 1000000;
	if ((cycles_to_units == 0 && !user_param->cpu_freq_f)) {
		fprintf(stderr, "Can't produce a report\n");
		exit(1);
	}

	run_inf_bi_factor = (user_param->duplex && user_param->test_method == RUN_INFINITELY) ? (user_param->verb == SEND ? 1 : 2) : 1 ;
	tsize = run_inf_bi_factor * user_param->size;
	num_of_calculated_iters *= (user_param->test_type == DURATION) ? 1 : num_of_qps;
	location_arr = (user_param->noPeak) ? 0 : num_of_calculated_iters - 1;
	/* support in GBS format */
	format_factor = (user_param->report_fmt == MBS) ? 0x100000 : 125000000;

	sum_of_test_cycles = ((double)(user_param->tcompleted[location_arr] - user_param->tposted[0]));

	double bw_avg = ((double)tsize*num_of_calculated_iters * cycles_to_units) / (sum_of_test_cycles * format_factor);
	double msgRate_avg = ((double)num_of_calculated_iters * cycles_to_units * run_inf_bi_factor) / (sum_of_test_cycles * 1000000);

	double bw_avg_p1 = ((double)tsize*user_param->iters_per_port[0] * cycles_to_units) / (sum_of_test_cycles * format_factor);
	double msgRate_avg_p1 = ((double)user_param->iters_per_port[0] * cycles_to_units * run_inf_bi_factor) / (sum_of_test_cycles * 1000000);

	double bw_avg_p2 = ((double)tsize*user_param->iters_per_port[1] * cycles_to_units) / (sum_of_test_cycles * format_factor);
	double msgRate_avg_p2 = ((double)user_param->iters_per_port[1] * cycles_to_units * run_inf_bi_factor) / (sum_of_test_cycles * 1000000);

	peak_up = !(user_param->noPeak)*(cycles_t)tsize*(cycles_t)cycles_to_units;
	peak_down = (cycles_t)opt_delta * format_factor;

	if (my_bw_rep == NULL) {
		free_my_bw_rep = 1;
		ALLOCATE(my_bw_rep , struct bw_report_data , 1);
		memset(my_bw_rep, 0, sizeof(struct bw_report_data));
	}

	my_bw_rep->size = (unsigned long)user_param->size;
	my_bw_rep->iters = num_of_calculated_iters;
	my_bw_rep->bw_peak = (double)peak_up/peak_down;
	my_bw_rep->bw_avg = bw_avg;
	my_bw_rep->msgRate_avg = msgRate_avg;
	my_bw_rep->bw_avg_p1 = bw_avg_p1;
	my_bw_rep->msgRate_avg_p1 = msgRate_avg_p1;
	my_bw_rep->bw_avg_p2 = bw_avg_p2;
	my_bw_rep->msgRate_avg_p2 = msgRate_avg_p2;
	my_bw_rep->sl = user_param->sl;

	if (!user_param->duplex || (user_param->verb == SEND && user_param->test_type == DURATION)
			|| user_param->test_method == RUN_INFINITELY || user_param->connection_type == RawEth)
		print_full_bw_report(user_param, my_bw_rep, NULL);

	if (free_my_bw_rep == 1) {
		free(my_bw_rep);
	}
}

void print_full_bw_report (struct perftest_parameters *user_param, struct bw_report_data *my_bw_rep, struct bw_report_data *rem_bw_rep)
{
	double bw_peak        = my_bw_rep->bw_peak;
	double bw_avg         = my_bw_rep->bw_avg;
	double bw_avg_p1      = my_bw_rep->bw_avg_p1;
	double bw_avg_p2      = my_bw_rep->bw_avg_p2;
	double msgRate_avg    = my_bw_rep->msgRate_avg;
	double msgRate_avg_p1 = my_bw_rep->msgRate_avg_p1;
	double msgRate_avg_p2 = my_bw_rep->msgRate_avg_p2;
	int inc_accuracy = ((bw_avg < 0.1) && (user_param->report_fmt == GBS));

	if (rem_bw_rep != NULL) {
		bw_peak        += rem_bw_rep->bw_peak;
		bw_avg         += rem_bw_rep->bw_avg;
		bw_avg_p1      += rem_bw_rep->bw_avg_p1;
		bw_avg_p2      += rem_bw_rep->bw_avg_p2;
		msgRate_avg    += rem_bw_rep->msgRate_avg;
		msgRate_avg_p1 += rem_bw_rep->msgRate_avg_p1;
		msgRate_avg_p2 += rem_bw_rep->msgRate_avg_p2;
	}

	if ( (user_param->duplex && rem_bw_rep != NULL) || (!user_param->duplex && rem_bw_rep == NULL)) {
		/* Verify Limits */
		if ( ((user_param->is_limit_bw == ON )&& (user_param->limit_bw > bw_avg)) )
			user_param->is_bw_limit_passed |= 0;
		else
			user_param->is_bw_limit_passed |= 1;

		if ( (user_param->is_limit_msgrate) && (user_param->limit_msgrate > msgRate_avg) )
			user_param->is_msgrate_limit_passed |= 0;
		else
			user_param->is_msgrate_limit_passed |= 1;
	}

	if (user_param->output == OUTPUT_BW)
		printf("%lf\n", bw_avg);
	else if (user_param->output == OUTPUT_MR)
		printf("%lf\n", msgRate_avg);
	else if (user_param->raw_qos)
		printf( REPORT_FMT_QOS, my_bw_rep->size, my_bw_rep->sl, my_bw_rep->iters, bw_peak, bw_avg, msgRate_avg);
	else if (user_param->report_per_port)
		printf(REPORT_FMT_PER_PORT, my_bw_rep->size, my_bw_rep->iters, bw_peak, bw_avg, msgRate_avg, bw_avg_p1, msgRate_avg_p1, bw_avg_p2, msgRate_avg_p2);
	else
		printf( inc_accuracy ? REPORT_FMT_EXT : REPORT_FMT, my_bw_rep->size, my_bw_rep->iters, bw_peak, bw_avg, msgRate_avg);
	if (user_param->output == FULL_VERBOSITY) {
		fflush(stdout);
		fprintf(stdout, user_param->cpu_util_data.enable ? REPORT_EXT_CPU_UTIL : REPORT_EXT , calc_cpu_util(user_param));
	}
}
