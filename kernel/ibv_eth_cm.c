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
#include <hermit/memory.h>
#include <hermit/logging.h>

#include <lwip/sockets.h>
#include <lwip/netdb.h>

#include <hermit/ibv_eth_cm.h>


#define KEY_MSG_SIZE (59)
#define KEY_PRINT_FMT "%04x:%04x:%06x:%06x:%08x:%016Lx:%08x"

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

int eth_read(int sockfd, struct eth_cm_dest *rem_dest)
{
  int parsed;
  char msg[KEY_MSG_SIZE];

  if (lwip_read(sockfd, msg, sizeof msg) != sizeof msg) {
    LOG_ERROR("eth_read: Couldn't read remote address.\n");
    return 1;
  }

	// TODO: Replace sscanf (not available in HC) or implement the function.
  parsed = sscanf(msg, KEY_PRINT_FMT,
                  (unsigned int *) &rem_dest->lid, &rem_dest->out_reads, &rem_dest->qpn,
                  &rem_dest->psn, &rem_dest->rkey, &rem_dest->vaddr, &rem_dest->srqn);

  if (parsed != 7) {
    LOG_ERROR("Couldn't parse line <%.*s>\n",(int)sizeof msg, msg);
    return 1;
  }

  return 0;
}

int eth_write(int sockfd, struct eth_cm_dest *local_dest)
{
  char msg[KEY_MSG_SIZE];
  ksprintf(msg, KEY_PRINT_FMT,
          local_dest->lid, local_dest->out_reads, local_dest->qpn, local_dest->psn,
          local_dest->rkey, local_dest->vaddr, local_dest->srqn);

  if (lwip_write(sockfd, msg, sizeof msg) != sizeof msg) {
    LOG_ERROR("Couldn't send local address.\n");
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

  return connfd;
}

int eth_client_exch_dest(int sockfd, struct eth_cm_dest *local_dest,
                         struct eth_cm_dest *rem_dest)
{
  if (eth_write(sockfd, local_dest)) {
    LOG_ERROR("Unable to write local destination information to socket.\n");
    return 1;
  }

  if (eth_read(sockfd, rem_dest)) {
    LOG_ERROR("Unable to read remote destination information from socket.\n");
    return 1;
  }

  return 0;
}

int eth_server_exch_dest(int sockfd, struct eth_cm_dest *local_dest,
                         struct eth_cm_dest *rem_dest)
{
  if (eth_read(sockfd, rem_dest)) {
    LOG_ERROR("Unable to read remote destination information from socket.\n");
    return 1;
  }

  if (eth_write(sockfd, local_dest)) {
    LOG_ERROR("Unable to write local destination information to socket.\n");
    return 1;
  }

  return 0;
}

int eth_close(int sockfd)
{
  if (lwip_close(sockfd)) {
    LOG_ERROR("Couldn't close socket.\n");
    return -1;
  }

  return 0;
}
