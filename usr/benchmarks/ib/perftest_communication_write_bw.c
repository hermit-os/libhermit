#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <getopt.h>
#include <malloc.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "perftest_communication_write_bw.h"


static const char *sideArray[] = {"local", "remote"};
static const char *gidArray[] = {"GID" , "MGID"};


// -----------------------------------------------------------------------------


static inline int ipv6_addr_v4mapped(const struct in6_addr *a)
{
	return ((a->un.u32_addr[0] | a->un.u32_addr[1]) | // !
			(a->un.u32_addr[2] ^ htonl(0x0000ffff))) == 0UL ||
			/* IPv4 encoded multicast addresses */
			(a->un.u32_addr[0] == htonl(0xff0e0000) &&
			((a->un.u32_addr[1] |
			(a->un.u32_addr[2] ^ htonl(0x0000ffff))) == 0UL));
}


// -----------------------------------------------------------------------------


enum ctx_device ib_dev_name(struct ibv_context *context)
{
	enum ctx_device dev_fname = UNKNOWN;
	struct ibv_device_attr attr;

	if (ibv_query_device(context,&attr)) {
		dev_fname = DEVICE_ERROR;
	}

	else if (attr.vendor_id == 5157) {

		switch (attr.vendor_part_id >> 12) {
			case 10 :
			case 4 : dev_fname = CHELSIO_T4; break;
			case 11 :
			case 5 : dev_fname = CHELSIO_T5; break;
			case 6 : dev_fname = CHELSIO_T6; break;
			default : dev_fname = UNKNOWN; break;
		}

		/* Assuming it's Mellanox HCA or unknown.
		If you want Inline support in other vendor devices, please send patch to gilr@dev.mellanox.co.il
		*/
	} else {

		switch (attr.vendor_part_id) {
			case 4099 : dev_fname = CONNECTX3; break;
			case 4100 : dev_fname = CONNECTX3; break;
			case 4103 : dev_fname = CONNECTX3_PRO; break;
			case 4104 : dev_fname = CONNECTX3_PRO; break;
			case 4113 : dev_fname = CONNECTIB; break;
			case 4115 : dev_fname = CONNECTX4; break;
			case 4116 : dev_fname = CONNECTX4; break;
			case 4117 : dev_fname = CONNECTX4LX; break;
			case 4118 : dev_fname = CONNECTX4LX; break;
			case 4119 : dev_fname = CONNECTX5; break;
			case 4120 : dev_fname = CONNECTX5; break;
			case 4121 : dev_fname = CONNECTX5EX; break;
			case 4122 : dev_fname = CONNECTX5EX; break;
			case 4123 : dev_fname = CONNECTX6; break;
			case 4124 : dev_fname = CONNECTX6; break;
			case 41682 : dev_fname = BLUEFIELD; break;
			case 41683 : dev_fname = BLUEFIELD; break;
			case 26418 : dev_fname = CONNECTX2; break;
			case 26428 : dev_fname = CONNECTX2; break;
			case 26438 : dev_fname = CONNECTX2; break;
			case 26448 : dev_fname = CONNECTX2; break;
			case 26458 : dev_fname = CONNECTX2; break;
			case 26468 : dev_fname = CONNECTX2; break;
			case 26478 : dev_fname = CONNECTX2; break;
			case 25408 : dev_fname = CONNECTX; break;
			case 25418 : dev_fname = CONNECTX; break;
			case 25428 : dev_fname = CONNECTX; break;
			case 25448 : dev_fname = CONNECTX; break;
			case 1824 : dev_fname = SKYHAWK; break;
			case 5684 : dev_fname = QLOGIC_E4; break;
			case 5700 : dev_fname = QLOGIC_E4; break;
			case 5716 : dev_fname = QLOGIC_E4; break;
			case 5718 : dev_fname = QLOGIC_E4; break;
			case 5734 : dev_fname = QLOGIC_E4; break;
			case 32880 : dev_fname = QLOGIC_AH; break;
			case 32881 : dev_fname = QLOGIC_AH; break;
			case 32882 : dev_fname = QLOGIC_AH; break;
			case 32883 : dev_fname = QLOGIC_AH; break;
			case 32912 : dev_fname = QLOGIC_AH; break;
			default : dev_fname = UNKNOWN;
		}
	}

	return dev_fname;
}

int ethernet_write_data(struct perftest_comm *comm, char *msg, size_t size)
{
	if (write(comm->rdma_params->sockfd, msg, size) != size) {
		perror("client write");
		fprintf(stderr, "Couldn't send reports\n");
		return 1;
	}
	return 0;
}

int ethernet_read_data(struct perftest_comm *comm, char *recv_msg, size_t size)
{
	if (read(comm->rdma_params->sockfd, recv_msg, size) != size) {
		fprintf(stderr, "ethernet_read_data: Couldn't read reports\n");
		return 1;
	}
	return 0;
}

int ctx_xchg_data_ethernet( struct perftest_comm *comm,
		void *my_data,
		void *rem_data,int size)
{
	if (comm->rdma_params->servername) {
		if (ethernet_write_data(comm, (char *) my_data, size)) {
			fprintf(stderr," Unable to write to socket/rdam_cm\n");
			return 1;
		}

		if (ethernet_read_data(comm, (char *) rem_data, size)) {
			fprintf(stderr," Unable to read from socket/rdam_cm\n");
			return 1;
		}

		/*Server side will wait for the client side to reach the write function.*/
	} else {

		if (ethernet_read_data(comm, (char *) rem_data, size)) {
			fprintf(stderr," Unable to read to socket/rdam_cm\n");
			return 1;
		}

		if (ethernet_write_data(comm, (char *) my_data, size)) {
			fprintf(stderr," Unable to write from socket/rdam_cm\n");
			return 1;
		}
	}
	return 0;
}


// -----------------------------------------------------------------------------


int ctx_xchg_data( struct perftest_comm *comm, void *my_data, void *rem_data, int size)
{
	ctx_xchg_data_ethernet(comm, my_data, rem_data, size);
	return 0;
}

int set_eth_mtu(struct perftest_parameters *user_param)
{
	if (user_param->mtu == 0) {
		user_param->mtu = 1518;
	}

	if(user_param->mtu >= MIN_MTU_RAW_ETERNET && user_param->mtu <= MAX_MTU_RAW_ETERNET) {
		user_param->curr_mtu = user_param->mtu;

	} else {

		fprintf(stderr, " Invalid MTU - %d \n", user_param->mtu);
		fprintf(stderr, " Please choose mtu form {64, 9600}\n");
		return -1;
	}

	return 0;
}

enum ibv_mtu set_mtu(struct ibv_context *context, uint8_t ib_port, int user_mtu)
{
	struct ibv_port_attr port_attr;
	enum ibv_mtu curr_mtu;

	if (ibv_query_port(context, ib_port, &port_attr)) {
		fprintf(stderr, " Error when trying to query port\n");
		exit(1);
	}

	/* User did not ask for specific mtu. */
	if (user_mtu == 0) {
		enum ctx_device current_dev = ib_dev_name(context);
		curr_mtu = port_attr.active_mtu;
		/* CX3_PRO and CX3 have a HW bug in 4K MTU, so we're forcing it to be 2K MTU */
		if (curr_mtu == IBV_MTU_4096 && (current_dev == CONNECTX3_PRO || current_dev == CONNECTX3))
			curr_mtu = IBV_MTU_2048;
	}

	else {
		switch (user_mtu) {
			case 256 : curr_mtu = IBV_MTU_256; break;
			case 512 : curr_mtu = IBV_MTU_512; break;
			case 1024 : curr_mtu = IBV_MTU_1024; break;
			case 2048 : curr_mtu = IBV_MTU_2048; break;
			case 4096 : curr_mtu = IBV_MTU_4096; break;
			default :
					fprintf(stderr, " Invalid MTU - %d \n", user_mtu);
					fprintf(stderr, " Please choose mtu from {256, 512, 1024, 2048, 4096}\n");
					fprintf(stderr, " Will run with the port active mtu - %d\n", port_attr.active_mtu);
					curr_mtu = port_attr.active_mtu;
		}

		if (curr_mtu > port_attr.active_mtu) {
			fprintf(stdout, "Requested mtu is higher than active mtu \n");
			fprintf(stdout, "Changing to active mtu - %d\n", port_attr.active_mtu);
			curr_mtu = port_attr.active_mtu;
		}
	}
	return curr_mtu;
}

static inline int valid_mtu_size(int mtu_size)
{
	return !(mtu_size < IBV_MTU_256 || mtu_size > IBV_MTU_4096);
}

static int get_best_gid_index (struct pingpong_context *ctx,
		  struct perftest_parameters *user_param,
		  struct ibv_port_attr *attr, int port)
{
	int gid_index = 0, i;
	union ibv_gid temp_gid, temp_gid_rival;
	int is_ipv4, is_ipv4_rival;

	for (i = 1; i < attr->gid_tbl_len; i++) {
		if (ibv_query_gid(ctx->context, port, gid_index, &temp_gid)) {
			return -1;
		}

		if (ibv_query_gid(ctx->context, port, i, &temp_gid_rival)) {
			return -1;
		}

		is_ipv4       = ipv6_addr_v4mapped((struct in6_addr *)temp_gid.raw);
		is_ipv4_rival = ipv6_addr_v4mapped((struct in6_addr *)temp_gid_rival.raw);

		if (is_ipv4_rival && !is_ipv4 && !user_param->ipv6)
			gid_index = i;
		else if (!is_ipv4_rival && is_ipv4 && user_param->ipv6)
			gid_index = i;
#ifdef HAVE_GID_ATTR
		else {
			int roce_version, roce_version_rival;
			struct ibv_exp_gid_attr gid_attr;

			gid_attr.comp_mask = IBV_EXP_QUERY_GID_ATTR_TYPE;
			if (ibv_exp_query_gid_attr(ctx->context, port, gid_index, &gid_attr))
				return -1;
			roce_version = gid_attr.type;

			if (ibv_exp_query_gid_attr(ctx->context, port, i, &gid_attr))
				return -1;
			roce_version_rival = gid_attr.type;

			if (check_better_roce_version(roce_version, roce_version_rival) == RIGHT_IS_BETTER)
				gid_index = i;
		}
#endif
	}

	return gid_index;
}

uint16_t ctx_get_local_lid(struct ibv_context *context, int port)
{
	struct ibv_port_attr attr;

	if (ibv_query_port(context, port, &attr))
		return 0;

	return attr.lid;
}


// -----------------------------------------------------------------------------


static int ethernet_write_keys(struct pingpong_dest *my_dest,
		struct perftest_comm *comm)
{
	if (my_dest->gid_index == -1) {

		char msg[KEY_MSG_SIZE];

		sprintf(msg, KEY_PRINT_FMT, my_dest->lid, my_dest->out_reads,
				my_dest->qpn, my_dest->psn, my_dest->rkey, my_dest->vaddr, my_dest->srqn);

		if (write(comm->rdma_params->sockfd, msg, sizeof msg) != sizeof msg) {
			perror("client write");
			fprintf(stderr, "Couldn't send local address\n");
			return 1;
		}

	} else {
		char msg[KEY_MSG_SIZE_GID];
		sprintf(msg, KEY_PRINT_FMT_GID, my_dest->lid, my_dest->out_reads,
				my_dest->qpn, my_dest->psn, my_dest->rkey, my_dest->vaddr,
				my_dest->gid.raw[0], my_dest->gid.raw[1],
				my_dest->gid.raw[2], my_dest->gid.raw[3],
				my_dest->gid.raw[4], my_dest->gid.raw[5],
				my_dest->gid.raw[6], my_dest->gid.raw[7],
				my_dest->gid.raw[8], my_dest->gid.raw[9],
				my_dest->gid.raw[10], my_dest->gid.raw[11],
				my_dest->gid.raw[12], my_dest->gid.raw[13],
				my_dest->gid.raw[14], my_dest->gid.raw[15],
				my_dest->srqn);

		if (write(comm->rdma_params->sockfd, msg, sizeof msg) != sizeof msg) {
			perror("client write");
			fprintf(stderr, "Couldn't send local address\n");
			return 1;
		}

	}

	return 0;
}

/******************************************************************************
 *
 ******************************************************************************/
static int ethernet_read_keys(struct pingpong_dest *rem_dest,
		struct perftest_comm *comm)
{
	if (rem_dest->gid_index == -1) {

		int parsed;
		char msg[KEY_MSG_SIZE];

		if (read(comm->rdma_params->sockfd, msg, sizeof msg) != sizeof msg) {
			fprintf(stderr, "ethernet_read_keys: Couldn't read remote address\n");
			return 1;
		}

		parsed = sscanf(msg, KEY_PRINT_FMT, (unsigned int*)&rem_dest->lid,
				&rem_dest->out_reads, &rem_dest->qpn,
				&rem_dest->psn, &rem_dest->rkey, &rem_dest->vaddr, &rem_dest->srqn);

		if (parsed != 7) {
			fprintf(stderr, "Couldn't parse line <%.*s>\n", (int)sizeof msg, msg);
			return 1;
		}

	} else {

		char msg[KEY_MSG_SIZE_GID];
		char *pstr = msg, *term;
		char tmp[120];
		int i;

		if (read(comm->rdma_params->sockfd, msg, sizeof msg) != sizeof msg) {
			fprintf(stderr, "ethernet_read_keys: Couldn't read remote address\n");
			return 1;
		}

		term = strpbrk(pstr, ":");
		memcpy(tmp, pstr, term - pstr);
		tmp[term - pstr] = 0;
		rem_dest->lid = (int)strtol(tmp, NULL, 16); /*LID*/

		pstr += term - pstr + 1;
		term = strpbrk(pstr, ":");
		memcpy(tmp, pstr, term - pstr);
		tmp[term - pstr] = 0;
		rem_dest->out_reads = (int)strtol(tmp, NULL, 16); /*OUT_READS*/

		pstr += term - pstr + 1;
		term = strpbrk(pstr, ":");
		memcpy(tmp, pstr, term - pstr);
		tmp[term - pstr] = 0;
		rem_dest->qpn = (int)strtol(tmp, NULL, 16); /*QPN*/

		pstr += term - pstr + 1;
		term = strpbrk(pstr, ":");
		memcpy(tmp, pstr, term - pstr);
		tmp[term - pstr] = 0;
		rem_dest->psn = (int)strtol(tmp, NULL, 16); /*PSN*/

		pstr += term - pstr + 1;
		term = strpbrk(pstr, ":");
		memcpy(tmp, pstr, term - pstr);
		tmp[term - pstr] = 0;
		rem_dest->rkey = (unsigned)strtoul(tmp, NULL, 16); /*RKEY*/

		pstr += term - pstr + 1;
		term = strpbrk(pstr, ":");
		memcpy(tmp, pstr, term - pstr);
		tmp[term - pstr] = 0;

		rem_dest->vaddr = strtoull(tmp, NULL, 16); /*VA*/

		for (i = 0; i < 15; ++i) {
			pstr += term - pstr + 1;
			term = strpbrk(pstr, ":");
			memcpy(tmp, pstr, term - pstr);
			tmp[term - pstr] = 0;

			rem_dest->gid.raw[i] = (unsigned char)strtoll(tmp, NULL, 16);
		}

		pstr += term - pstr + 1;

		strcpy(tmp, pstr);
		rem_dest->gid.raw[15] = (unsigned char)strtoll(tmp, NULL, 16);


		pstr += term - pstr + 4;

		term = strpbrk(pstr, ":");
		memcpy(tmp, pstr, term - pstr);
		tmp[term - pstr] = 0;
		rem_dest->srqn = (unsigned)strtoul(tmp, NULL, 16); /*SRQN*/

	}
	return 0;
}


// -----------------------------------------------------------------------------


static int ethernet_client_connect(struct perftest_comm *comm)
{
	struct addrinfo *res, *t;
	struct addrinfo hints;
	/* char *service; */

	int sockfd = -1;
	memset(&hints, 0, sizeof hints);
	hints.ai_family   = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	/* if (check_add_port(&service, comm->rdma_params->port, comm->rdma_params->servername, &hints, &res)) { */
		/* fprintf(stderr, "Problem in resolving basic address and port\n"); */
		/* return 1; */
	/* } */

	for (t = res; t; t = t->ai_next) {
		sockfd = socket(t->ai_family, t->ai_socktype, t->ai_protocol);

		if (sockfd >= 0) {
			if (!connect(sockfd, t->ai_addr, t->ai_addrlen))
				break;
			close(sockfd);
			sockfd = -1;
		}
	}

	freeaddrinfo(res);

	if (sockfd < 0) {
		fprintf(stderr, "Couldn't connect to %s:%d\n",comm->rdma_params->servername,comm->rdma_params->port);
		return 1;
	}

	comm->rdma_params->sockfd = sockfd;
	return 0;
}

/******************************************************************************
 *
 ******************************************************************************/
static int ethernet_server_connect(struct perftest_comm *comm)
{
	struct addrinfo *res, *t;
	struct addrinfo hints;
	/* char *service; */
	int n;

	int sockfd = -1, connfd;
	memset(&hints, 0, sizeof hints);
	hints.ai_flags    = AI_PASSIVE;
	hints.ai_family   = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	/* if (check_add_port(&service, comm->rdma_params->port, NULL, &hints, &res)) { */
		/* fprintf(stderr, "Problem in resolving basic address and port\n"); */
		/* return 1; */
	/* } */

	for (t = res; t; t = t->ai_next) {
		sockfd = socket(t->ai_family, t->ai_socktype, t->ai_protocol);

		if (sockfd >= 0) {
			n = 1;
			setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &n, sizeof n);
			if (!bind(sockfd, t->ai_addr, t->ai_addrlen))
				break;
			close(sockfd);
			sockfd = -1;
		}
	}
	freeaddrinfo(res);

	if (sockfd < 0) {
		fprintf(stderr, "Couldn't listen to port %d\n", comm->rdma_params->port);
		return 1;
	}

	listen(sockfd, 1);
	connfd = accept(sockfd, NULL, 0);

	if (connfd < 0) {
		perror("server accept");
		fprintf(stderr, "accept() failed\n");
		close(sockfd);
		return 1;
	}
	close(sockfd);
	comm->rdma_params->sockfd = connfd;
	return 0;
}


// -----------------------------------------------------------------------------


int create_comm_struct(struct perftest_comm *comm,
		struct perftest_parameters *user_param)
{
	ALLOCATE(comm->rdma_params, struct perftest_parameters, 1);
	memset(comm->rdma_params, 0, sizeof(struct perftest_parameters));

	comm->rdma_params->port            = user_param->port;
	comm->rdma_params->sockfd          = -1;
	comm->rdma_params->gid_index       = user_param->gid_index;
	comm->rdma_params->gid_index2      = user_param->gid_index2;
	comm->rdma_params->use_rdma_cm     = OFF;
	comm->rdma_params->servername      = user_param->servername;
	comm->rdma_params->machine         = user_param->machine;
	comm->rdma_params->side            = LOCAL;
	comm->rdma_params->verb            = user_param->verb;
	comm->rdma_params->use_mcg         = user_param->use_mcg;
	comm->rdma_params->duplex          = user_param->duplex;
	comm->rdma_params->tos             = DEF_TOS;
	comm->rdma_params->use_xrc         = user_param->use_xrc;
	comm->rdma_params->connection_type = user_param->connection_type;
	comm->rdma_params->output          = user_param->output;
	comm->rdma_params->report_per_port = user_param->report_per_port;
	comm->rdma_params->retry_count     = user_param->retry_count;
	comm->rdma_params->mr_per_qp       = user_param->mr_per_qp;
	comm->rdma_params->dlid            = user_param->dlid;

	return SUCCESS;
}

int establish_connection(struct perftest_comm *comm)
{
	int (*ptr)(struct perftest_comm*);

	ptr = comm->rdma_params->servername ? &ethernet_client_connect : &ethernet_server_connect;

	if ((*ptr)(comm)) {
		fprintf(stderr, "Unable to open file descriptor for socket connection");
		return 1;
	}

	return 0;
}

void exchange_versions(struct perftest_comm *user_comm, struct perftest_parameters *user_param)
{
	if (!user_param->dont_xchg_versions) {
		if (ctx_xchg_data(user_comm, (void*)(&user_param->version), (void*)(&user_param->rem_version), sizeof(user_param->rem_version))) {
			fprintf(stderr, " Failed to exchange data between server and clients\n");
			exit(1);
		}
	}
}

void check_sys_data(struct perftest_comm *user_comm, struct perftest_parameters *user_param)
{
	int rem_cycle_buffer = 0;
	int rem_cache_line_size = 0;

	int m_cycle_buffer = hton_int(user_param->cycle_buffer);
	int m_cache_line_size = hton_int(user_param->cache_line_size);

	/*keep compatibility between older versions, without this feature.*/
	/* if ( !(atof(user_param->rem_version) >= 5.32) ) { */
		/* return; */
	/* } */

	if (!user_param->dont_xchg_versions) {
		if (ctx_xchg_data(user_comm, (void*)(&m_cycle_buffer), (void*)(&rem_cycle_buffer), sizeof(user_param->cycle_buffer))) {
			fprintf(stderr, " Failed to exchange Page Size data between server and client\n");
			exit(1);
		}
		if (ctx_xchg_data(user_comm, (void*)(&m_cache_line_size), (void*)(&rem_cache_line_size), sizeof(user_param->cache_line_size))) {
			fprintf(stderr, " Failed to exchange Cache Line Size data between server and client\n");
			exit(1);
		}
	}

	rem_cycle_buffer    = ntoh_int(rem_cycle_buffer);
	rem_cache_line_size = ntoh_int(rem_cache_line_size);

	/*take the max and update user_param*/
	user_param->cycle_buffer = (rem_cycle_buffer > user_param->cycle_buffer) ? rem_cycle_buffer : user_param->cycle_buffer;
	user_param->cache_line_size = (rem_cache_line_size > user_param->cache_line_size) ? rem_cache_line_size : user_param->cache_line_size;
}

int check_mtu(struct ibv_context *context, struct perftest_parameters *user_param, struct perftest_comm *user_comm)
{
	int curr_mtu=0, rem_mtu=0;
	char cur[2];
	char rem[2];
	int size_of_cur;
	float rem_vers = atof(user_param->rem_version);

	if (user_param->connection_type == RawEth) {
		if (set_eth_mtu(user_param) != 0 ) {
			fprintf(stderr, " Couldn't set Eth MTU\n");
			return FAILURE;
		}
	} else {
		curr_mtu = (int) (set_mtu(context, user_param->ib_port, user_param->mtu));
		if (!user_param->dont_xchg_versions) {
			/*add mtu set in remote node from version 5.1 and above*/
			if (rem_vers >= 5.1 ) {
				sprintf(cur, "%d", curr_mtu);

				/*fix a buffer overflow issue in ppc.*/
				size_of_cur = (rem_vers >= 5.31) ? sizeof(char[2]) : sizeof(int);

				if (ctx_xchg_data(user_comm, (void*)(cur), (void*)(rem), size_of_cur)) {
					fprintf(stderr, " Failed to exchange data between server and clients\n");
					exit(1);
				}
				rem_mtu = (int) strtol(rem, (char **)NULL, 10);
				user_param->curr_mtu = (enum ibv_mtu)((valid_mtu_size(rem_mtu) && (curr_mtu > rem_mtu)) ? rem_mtu : curr_mtu);
			} else {
				user_param->curr_mtu = (enum ibv_mtu)(curr_mtu);
			}
		} else {
			user_param->curr_mtu = (enum ibv_mtu)(curr_mtu);
		}
	}

	if (user_param->connection_type == UD && user_param->size > MTU_SIZE(user_param->curr_mtu)) {

		if (user_param->test_method == RUN_ALL) {
			fprintf(stderr, " Max msg size in UD is MTU %lu\n", MTU_SIZE(user_param->curr_mtu));
			fprintf(stderr, " Changing to this MTU\n");
		}
		user_param->size = MTU_SIZE(user_param->curr_mtu);
	}
	/*checking msg size in raw ethernet*/
	if (user_param->connection_type == RawEth){
		if (user_param->size > user_param->curr_mtu) {
			fprintf(stderr, " Max msg size in RawEth is MTU %d\n", user_param->curr_mtu);
			fprintf(stderr, " Changing msg size to this MTU\n");
			user_param->size = user_param->curr_mtu;
		} else if (user_param->size < RAWETH_MIN_MSG_SIZE) {
			printf(" Min msg size for RawEth is 64B - changing msg size to 64 \n");
			user_param->size = RAWETH_MIN_MSG_SIZE;
		}
	}

	return SUCCESS;
}

int set_up_connection(struct pingpong_context *ctx,
		struct perftest_parameters *user_param,
		struct pingpong_dest *my_dest)
{
	int num_of_qps = user_param->num_of_qps;
	int num_of_qps_per_port = user_param->num_of_qps / 2;
	int i;
	union ibv_gid temp_gid;
	union ibv_gid temp_gid2;
	struct ibv_port_attr attr;

	srand48(getpid() * time(NULL));

	/* In xrc with bidirectional, there are send qps and recv qps. The actual
	 * number of send/recv qps is num_of_qps / 2. */
	if ((user_param->connection_type == DC || user_param->use_xrc) && (user_param->duplex || user_param->tst == LAT)) {
		num_of_qps /= 2;
		num_of_qps_per_port = num_of_qps / 2;
	}

	if (user_param->gid_index != -1) {
		if (ibv_query_port(ctx->context, user_param->ib_port, &attr))
			return 0;

		if (user_param->use_gid_user) {
			if (ibv_query_gid(ctx->context, user_param->ib_port, user_param->gid_index, &temp_gid))
				return -1;
		} else {
			user_param->gid_index = get_best_gid_index(ctx, user_param, &attr, user_param->ib_port);
			if (user_param->gid_index < 0)
				return -1;
			if (ibv_query_gid(ctx->context, user_param->ib_port, user_param->gid_index, &temp_gid))
				return -1;
		}
	}

	if (user_param->dualport == ON) {
		if (user_param->gid_index2 != -1) {
			if (ibv_query_port(ctx->context, user_param->ib_port2, &attr))
				return 0;

			if (user_param->use_gid_user) {
				if (ibv_query_gid(ctx->context, user_param->ib_port2, user_param->gid_index, &temp_gid2))
					return -1;
			} else {
				user_param->gid_index2 = get_best_gid_index(ctx, user_param, &attr, user_param->ib_port2);
				if (user_param->gid_index2 < 0)
					return -1;
				if (ibv_query_gid(ctx->context, user_param->ib_port2, user_param->gid_index2, &temp_gid2))
						return -1;
			}
		}
	}

	for (i = 0; i < user_param->num_of_qps; i++) {

		if (user_param->dualport == ON) {
			/*first half of qps are for ib_port and second half are for ib_port2
			in xrc with bidirectional, the first half of qps are xrc_send qps and
			the second half are xrc_recv qps. the first half of the send/recv qps
			are for ib_port1 and the second half are for ib_port2
			*/
			if (i % num_of_qps < num_of_qps_per_port) {
				my_dest[i].lid = ctx_get_local_lid(ctx->context, user_param->ib_port);
				my_dest[i].gid_index = user_param->gid_index;
			} else {
				my_dest[i].lid = ctx_get_local_lid(ctx->context, user_param->ib_port2);
				my_dest[i].gid_index = user_param->gid_index2;
			}
			/*single-port case*/
		} else {
			my_dest[i].lid = ctx_get_local_lid(ctx->context, user_param->ib_port);
			my_dest[i].gid_index = user_param->gid_index;
		}

		my_dest[i].qpn = ctx->qp[i]->qp_num;
		my_dest[i].psn = lrand48() & 0xffffff;
		my_dest[i].rkey = ctx->mr[i]->rkey;

		/* Each qp gives its receive buffer address.*/
		my_dest[i].out_reads = user_param->out_reads;
		if (user_param->mr_per_qp)
			my_dest[i].vaddr = (uintptr_t)ctx->buf[i] + BUFF_SIZE(ctx->size, ctx->cycle_buffer);
		else
			my_dest[i].vaddr = (uintptr_t)ctx->buf[0] + (user_param->num_of_qps + i)*BUFF_SIZE(ctx->size, ctx->cycle_buffer);
		if (user_param->dualport==ON) {
			if (i % num_of_qps < num_of_qps_per_port)
				memcpy(my_dest[i].gid.raw, temp_gid.raw , 16);
			else
				memcpy(my_dest[i].gid.raw, temp_gid2.raw , 16);
		} else {
			memcpy(my_dest[i].gid.raw, temp_gid.raw , 16);
		}

		/*
		We do not fail test upon lid above RoCE.
		if ( (user_param->gid_index < 0) || ((user_param->gid_index2 < 0) && (user_param->dualport == ON)) ){
			if (!my_dest[i].lid) {
				fprintf(stderr, " Local lid 0x0 detected. Is an SM running? \n");
				return -1;
			}
		}
		*/
	}

	#ifdef HAVE_XRCD
	if (user_param->use_xrc) {
		for (i=0; i < user_param->num_of_qps; i++) {
			if (ibv_get_srq_num(ctx->srq, &(my_dest[i].srqn))) {
				fprintf(stderr, "Couldn't get SRQ number\n");
				return 1;
			}
		}
	}
	#endif

	#ifdef HAVE_DC
	if(user_param->machine == SERVER || user_param->duplex || user_param->tst == LAT) {
		if (user_param->connection_type == DC) {
			for (i=0; i < user_param->num_of_qps; i++) {
				if (ibv_get_srq_num(ctx->srq, &(my_dest[i].srqn))) {
					fprintf(stderr, "Couldn't get SRQ number\n");
					return 1;
				}
			}
		}
	}
	#endif
	return 0;
}

void ctx_print_pingpong_data(struct pingpong_dest *element,
		struct perftest_comm *comm)
{
	int is_there_mgid, local_mgid, remote_mgid;

	/* use dlid value from user (if user specified and only on the remote side) */
	uint16_t dlid = (comm->rdma_params->dlid && comm->rdma_params->side) ?
				comm->rdma_params->dlid : element->lid;

	if (comm->rdma_params->output != FULL_VERBOSITY)
		return;
	/*First of all we print the basic format.*/
	printf(BASIC_ADDR_FMT, sideArray[comm->rdma_params->side], dlid, element->qpn, element->psn);

	switch (comm->rdma_params->verb) {
		case 2 : printf(READ_FMT, element->out_reads);
		case 1 : printf(RDMA_FMT, element->rkey, element->vaddr);
		default : ;
	}

	if (comm->rdma_params->use_xrc) {
		printf(XRC_FMT, element->srqn);
	} else if (comm->rdma_params->connection_type == DC){
		printf(DC_FMT, element->srqn);
	}

	putchar('\n');

	local_mgid    = (comm->rdma_params->side == 0) && (comm->rdma_params->machine == 0);
	remote_mgid   = (comm->rdma_params->side == 1) && (comm->rdma_params->machine == 1);
	is_there_mgid = (comm->rdma_params->duplex || remote_mgid || local_mgid);

	if ((comm->rdma_params->gid_index > -1 || (comm->rdma_params->use_mcg && is_there_mgid)) && comm->rdma_params->connection_type != RawEth) {
		printf(PERF_GID_FMT, gidArray[comm->rdma_params->use_mcg && is_there_mgid],
				element->gid.raw[0], element->gid.raw[1],
				element->gid.raw[2], element->gid.raw[3],
				element->gid.raw[4], element->gid.raw[5],
				element->gid.raw[6], element->gid.raw[7],
				element->gid.raw[8], element->gid.raw[9],
				element->gid.raw[10], element->gid.raw[11],
				element->gid.raw[12], element->gid.raw[13],
				element->gid.raw[14], element->gid.raw[15]);
	}
}

int ctx_hand_shake(struct perftest_comm *comm,
		struct pingpong_dest *my_dest,
		struct pingpong_dest *rem_dest)
{
	int (*read_func_ptr) (struct pingpong_dest*, struct perftest_comm*);
	int (*write_func_ptr)(struct pingpong_dest*, struct perftest_comm*);

	read_func_ptr  = &ethernet_read_keys;
	write_func_ptr = &ethernet_write_keys;

	rem_dest->gid_index = my_dest->gid_index;
	if (comm->rdma_params->servername) {
		if ((*write_func_ptr)(my_dest, comm)) {
			fprintf(stderr, " Unable to write to socket/rdam_cm\n");
			return 1;
		}
		if ((*read_func_ptr)(rem_dest, comm)) {
			fprintf(stderr, " Unable to read from socket/rdam_cm\n");
			return 1;
		}

		/*Server side will wait for the client side to reach the write function.*/
	} else {

		if ((*read_func_ptr)(rem_dest, comm)) {
			fprintf(stderr, " Unable to read to socket/rdam_cm\n");
			return 1;
		}
		if ((*write_func_ptr)(my_dest, comm)) {
			fprintf(stderr, " Unable to write from socket/rdam_cm\n");
			return 1;
		}
	}

	return 0;
}

int ctx_check_gid_compatibility(struct pingpong_dest *my_dest,
		struct pingpong_dest *rem_dest)
{
	int gid_type1, gid_type2;

	/*ipv4 - 1 , ipv6 - 0 */
	gid_type1 = ipv6_addr_v4mapped((struct in6_addr *)my_dest->gid.raw);
	gid_type2 = ipv6_addr_v4mapped((struct in6_addr *)rem_dest->gid.raw);

	if (gid_type1 != gid_type2)
		return 1;

	return 0;
}

void xchg_bw_reports(struct perftest_comm *comm, struct bw_report_data *my_bw_rep,
		struct bw_report_data *rem_bw_rep, float remote_version)
{
	struct bw_report_data temp;
	int size;

	temp.size = hton_long(my_bw_rep->size);

	if (remote_version >= 5.33)
		temp.iters = hton_long(my_bw_rep->iters);
	else
		temp.iters = hton_int(my_bw_rep->iters);

	temp.bw_peak        = hton_double(my_bw_rep->bw_peak);
	temp.bw_avg         = hton_double(my_bw_rep->bw_avg);
	temp.bw_avg_p1      = hton_double(my_bw_rep->bw_avg_p1);
	temp.bw_avg_p2      = hton_double(my_bw_rep->bw_avg_p2);
	temp.msgRate_avg    = hton_double(my_bw_rep->msgRate_avg);
	temp.msgRate_avg_p1 = hton_double(my_bw_rep->msgRate_avg_p1);
	temp.msgRate_avg_p2 = hton_double(my_bw_rep->msgRate_avg_p2);

	/*******************Exchange Reports*******************/
	if (ctx_xchg_data(comm, (void*) (&temp.size), (void*) (&rem_bw_rep->size), sizeof(unsigned long))) {
		fprintf(stderr, " Failed to exchange data between server and clients\n");
		exit(1);
	}

	size = (remote_version >= 5.33) ? sizeof(uint64_t) : sizeof(int);

	if (ctx_xchg_data(comm, (void*) (&temp.iters), (void*) (&rem_bw_rep->iters), size)) {
		fprintf(stderr, " Failed to exchange data between server and clients\n");
		exit(1);
	}
	if (ctx_xchg_data(comm, (void*) (&temp.bw_peak), (void*) (&rem_bw_rep->bw_peak), sizeof(double))) {
		fprintf(stderr, " Failed to exchange data between server and clients\n");
		exit(1);
	}
	if (ctx_xchg_data(comm, (void*) (&temp.bw_avg), (void*) (&rem_bw_rep->bw_avg), sizeof(double))) {
		fprintf(stderr, " Failed to exchange data between server and clients\n");
		exit(1);
	}
	if (ctx_xchg_data(comm, (void*) (&temp.msgRate_avg), (void*) (&rem_bw_rep->msgRate_avg), sizeof(double))) {
		fprintf(stderr, " Failed to exchange data between server and clients\n");
		exit(1);
	}

	/*exchange data for report per port feature. should keep compatibility*/
	if (comm->rdma_params->report_per_port) {
		if (ctx_xchg_data(comm, (void*) (&temp.bw_avg_p1), (void*) (&rem_bw_rep->bw_avg_p1), sizeof(double))) {
			fprintf(stderr, " Failed to exchange data between server and clients\n");
			exit(1);
		}
		if (ctx_xchg_data(comm, (void*) (&temp.msgRate_avg_p1), (void*) (&rem_bw_rep->msgRate_avg_p1), sizeof(double))) {
			fprintf(stderr, " Failed to exchange data between server and clients\n");
			exit(1);
		}
		if (ctx_xchg_data(comm, (void*) (&temp.bw_avg_p2), (void*) (&rem_bw_rep->bw_avg_p2), sizeof(double))) {
			fprintf(stderr, " Failed to exchange data between server and clients\n");
			exit(1);
		}
		if (ctx_xchg_data(comm, (void*) (&temp.msgRate_avg_p2), (void*) (&rem_bw_rep->msgRate_avg_p2), sizeof(double))) {
			fprintf(stderr, " Failed to exchange data between server and clients\n");
			exit(1);
		}
	}

	rem_bw_rep->size = hton_long(rem_bw_rep->size);

	if ( remote_version >= 5.33 )
		rem_bw_rep->iters = hton_long(rem_bw_rep->iters);
	else
		rem_bw_rep->iters = hton_int(rem_bw_rep->iters);

	rem_bw_rep->bw_peak        = hton_double(rem_bw_rep->bw_peak);
	rem_bw_rep->bw_avg         = hton_double(rem_bw_rep->bw_avg);
	rem_bw_rep->bw_avg_p1      = hton_double(rem_bw_rep->bw_avg_p1);
	rem_bw_rep->bw_avg_p2      = hton_double(rem_bw_rep->bw_avg_p2);
	rem_bw_rep->msgRate_avg    = hton_double(rem_bw_rep->msgRate_avg);
	rem_bw_rep->msgRate_avg_p1 = hton_double(rem_bw_rep->msgRate_avg_p1);
	rem_bw_rep->msgRate_avg_p2 = hton_double(rem_bw_rep->msgRate_avg_p2);
}

int ctx_close_connection(struct perftest_comm *comm,
		struct pingpong_dest *my_dest,
		struct pingpong_dest *rem_dest)
{
	/*Signal client is finished.*/
	if (ctx_hand_shake(comm, my_dest, rem_dest)) {
		return 1;
	}

	if (write(comm->rdma_params->sockfd, "done", sizeof "done") != sizeof "done") {
		perror(" Client write");
		fprintf(stderr, "Couldn't write to socket\n");
		return -1;
	}

	close(comm->rdma_params->sockfd);

	return 0;
}



