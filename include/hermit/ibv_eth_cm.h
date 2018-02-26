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

/*
 * This is a first implementation of a lightweight Ethernet Connection Manager
 * that helps to exchange destination information before a data exchange via RDMA.
 * LwIP socket-functions are used.
 */

#ifndef __IBV_ETH_CM__
#define __IBV_ETH_CM__

#include <hermit/verbs.h>


struct eth_cm_dest {
	int                lid;
	int                out_reads;
	int                qpn;
	int                psn;
	unsigned           rkey;
	unsigned long long vaddr;
	union ibv_gid      gid;
	unsigned           srqn;
	int                gid_index;
};

/*
 * Connect to a remote end node via ethernet sockets, given its IP address and a port number. This
 * function creates a socket, connects to the server and returns the socket file descriptor.
 *
 * server_ip: Server IP address given as string.
 * port:      Port number.
 *
 * Returns:   Socket file descriptor on success and -1 on failure.
 */
int eth_client_connect(const char *server_ip, int port);

/*
 * Accept connection from a remote end node via ethernet sockets given a port number. This function
 * creates a socket, binds it and listens to it, then accepts the connection with the client trying
 * to connect.
 *
 * port:      Port number.
 *
 * Returns:   Socket file descriptor on success and -1 on failure.
 */
int eth_server_connect(int port);


int eth_client_exch_dest(int sockfd, struct eth_cm_dest *local_dest,
                         struct eth_cm_dest *rem_dest);

int eth_server_exch_dest(int sockfd, struct eth_cm_dest *local_dest,
                         struct eth_cm_dest *rem_dest);

/*
 * Close the connection to the remote end node. This function calls close.
 *
 * sockfd:    Socket file descriptor to close.
 *
 * Returns:   0 on success and -1 on failure.
 */
int eth_close(int sockfd);

#endif // __IBV_ETH_CM__
