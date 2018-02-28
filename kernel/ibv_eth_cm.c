/*
 * Copyright (c) 2018, Annika Wierichs, RWTH Aachen University.
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

#include <hermit/stdio.h>
#include <hermit/stddef.h>
#include <hermit/stdlib.h>
#include <hermit/memory.h>
#include <hermit/logging.h>

#include <lwip/sockets.h>
#include <lwip/netdb.h>

#include <hermit/ibv_eth_cm.h>


/* #define KEY_MSG_SIZE (59) */
/* #define KEY_PRINT_FMT "%04x:%04x:%06x:%06x:%08x:%016Lx:%08x" */

#define KEY_MSG_SIZE_GID (108)
#define KEY_PRINT_FMT_GID "%04x:%04x:%06x:%06x:%08x:%016Lx:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%08x:"


/*
 * Helper functions:
 */

int check_add_port(char **service, int port, const char *server_ip, struct addrinfo *hints,
                   struct addrinfo **res)
{
  int str_size_max = 6;
  *service = kmalloc(str_size_max);
	memset(*service, 0, sizeof str_size_max);

	if (ksnprintf(*service, str_size_max, "%05d", port) < 0) {
		return 1;
	}

	if (lwip_getaddrinfo(server_ip, *service, hints, res) < 0) {
    LOG_ERROR("Error for %s:%d\n", server_ip, port);
		return 1;
	}

	return 0;
}


/*
 * Exposed functions:
 */

int eth_client_connect(const char *server_ip, int port)
{
	struct addrinfo *res, *t;
	struct addrinfo hints;
	char *service;
  int sockfd = -1;

	memset(&hints, 0, sizeof hints);
	hints.ai_family   = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if (check_add_port(&service, port, server_ip, &hints, &res)) {
		LOG_ERROR("Problem in resolving basic address and port\n");
		return -1;
	}

	for (t = res; t; t = t->ai_next) {
		sockfd = lwip_socket(t->ai_family, t->ai_socktype, t->ai_protocol);

		if (sockfd >= 0) {
			if (!lwip_connect(sockfd, t->ai_addr, t->ai_addrlen))
				break; // Success.

			lwip_close(sockfd);
			sockfd = -1;
		}
	}

	lwip_freeaddrinfo(res);

	if (sockfd < 0) {
		LOG_ERROR("Couldn't connect to %s:%d\n", server_ip, port);
		return -1;
	}

  return sockfd;
}

int eth_server_connect(int port)
{
  struct addrinfo *res, *t;
  struct addrinfo hints;
  char *service;
  int n;
  int sockfd = -1, connfd;

  memset(&hints, 0, sizeof hints);
  hints.ai_flags    = AI_PASSIVE;
  hints.ai_family   = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  if (check_add_port(&service, port, NULL, &hints, &res)) {
    LOG_ERROR("Problem in resolving basic address and port\n");
    return -1;
  }

  for (t = res; t; t = t->ai_next) {
    sockfd = lwip_socket(t->ai_family, t->ai_socktype, t->ai_protocol);

    if (sockfd >= 0) {
      n = 1;
      lwip_setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &n, sizeof n);

      if (!lwip_bind(sockfd, t->ai_addr, t->ai_addrlen))
        break; // Success

      lwip_close(sockfd);
      sockfd = -1;
    }
  }
  lwip_freeaddrinfo(res);

  if (sockfd < 0) {
    LOG_ERROR("Couldn't listen to port %d\n", port);
    return -1;
  }

  lwip_listen(sockfd, 1);
  connfd = lwip_accept(sockfd, NULL, 0);

  if (connfd < 0) {
    LOG_ERROR("accept() failed\n");
    lwip_close(sockfd);
    return -1;
  }

	lwip_close(sockfd);
  return connfd;
}


int eth_recv_remote_dest(int sockfd, struct eth_cm_dest *rem_dest)
{
	char msg[KEY_MSG_SIZE_GID];

	if (lwip_read(sockfd, msg, sizeof msg) != sizeof msg) {
		LOG_ERROR("Ethernet_read_keys: Couldn't read remote address\n");
		return 1;
	}

	uint32_t vaddr_hi, vaddr_lo; // See comment in send function.
	sscanf(msg, KEY_PRINT_FMT_GID,
	       (unsigned int*) &rem_dest->lid, &rem_dest->out_reads, &rem_dest->qpn,
			   &rem_dest->psn, &rem_dest->rkey, &vaddr_hi, &vaddr_lo,
			   &rem_dest->gid.raw[ 0], &rem_dest->gid.raw[ 1],
			   &rem_dest->gid.raw[ 2], &rem_dest->gid.raw[ 3],
			   &rem_dest->gid.raw[ 4], &rem_dest->gid.raw[ 5],
			   &rem_dest->gid.raw[ 6], &rem_dest->gid.raw[ 7],
			   &rem_dest->gid.raw[ 8], &rem_dest->gid.raw[ 9],
			   &rem_dest->gid.raw[10], &rem_dest->gid.raw[11],
			   &rem_dest->gid.raw[12], &rem_dest->gid.raw[13],
			   &rem_dest->gid.raw[14], &rem_dest->gid.raw[15],
			   &rem_dest->srqn);

	rem_dest->vaddr = ((unsigned long long) vaddr_hi << 32) |
										((unsigned long long) vaddr_lo);

  return 0;
}

int eth_send_local_dest(int sockfd, struct eth_cm_dest *local_dest)
{
	char msg[KEY_MSG_SIZE_GID];

	// TODO: This somehow did not work for a normal 64bit vaddr, IIRC. Check why.
	unsigned long long host_vaddr = (unsigned	long long) guest_to_host((size_t) local_dest->vaddr);
	uint32_t vaddr_hi, vaddr_lo;
	unsigned long long vaddr_hi_shfd = host_vaddr >> 32;
	memcpy(&vaddr_hi, &vaddr_hi_shfd,  sizeof(uint32_t));
	memcpy(&vaddr_lo, &host_vaddr,     sizeof(uint32_t));

	ksprintf(msg, KEY_PRINT_FMT_GID,
			local_dest->lid, local_dest->out_reads, local_dest->qpn, local_dest->psn, local_dest->rkey,
			vaddr_hi, vaddr_lo,
			local_dest->gid.raw[ 0], local_dest->gid.raw[ 1],
			local_dest->gid.raw[ 2], local_dest->gid.raw[ 3],
			local_dest->gid.raw[ 4], local_dest->gid.raw[ 5],
			local_dest->gid.raw[ 6], local_dest->gid.raw[ 7],
			local_dest->gid.raw[ 8], local_dest->gid.raw[ 9],
			local_dest->gid.raw[10], local_dest->gid.raw[11],
			local_dest->gid.raw[12], local_dest->gid.raw[13],
			local_dest->gid.raw[14], local_dest->gid.raw[15],
			local_dest->srqn);

  if (lwip_write(sockfd, msg, sizeof msg) != sizeof msg) {
    LOG_ERROR("Couldn't send local address.\n");
    return 1;
  }

  return 0;
}


int eth_close(int connfd)
{
  if (lwip_close(connfd)) {
    LOG_ERROR("Couldn't close socket.\n");
    return -1;
  }

  return 0;
}


/* int eth_client_exch_dest(int connfd, struct eth_cm_dest *local_dest, */
                         /* struct eth_cm_dest *rem_dest) */
/* { */
  /* if (eth_write(connfd, local_dest)) { */
    /* LOG_ERROR("Unable to write local destination information to socket.\n"); */
    /* return 1; */
  /* } */

  /* if (eth_read(connfd, rem_dest)) { */
    /* LOG_ERROR("Unable to read remote destination information from socket.\n"); */
    /* return 1; */
  /* } */

  /* return 0; */
/* } */

/* int eth_server_exch_dest(int connfd, struct eth_cm_dest *local_dest, */
                         /* struct eth_cm_dest *rem_dest) */
/* { */
  /* if (eth_read(connfd, rem_dest)) { */
    /* LOG_ERROR("Unable to read remote destination information from socket.\n"); */
    /* return 1; */
  /* } */

  /* if (eth_write(connfd, local_dest)) { */
    /* LOG_ERROR("Unable to write local destination information to socket.\n"); */
    /* return 1; */
  /* } */

  /* return 0; */
/* } */

