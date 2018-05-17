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

#ifdef __x86_64__
#define _GNU_SOURCE

#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "uhyve-migration.h"
#include "uhyve.h"

static struct sockaddr_in mig_server;
static int com_sock = 0;
static int listen_sock = 0;

static mig_type_t mig_type = MIG_TYPE_COLD;

/**
 * \brief Returns the configured migration type
 */
mig_type_t
get_migration_type(void)
{
	return mig_type;
}

/**
 * \brief Sets the migration type
 *
 * \param mig_type_str A string defining the migration type
 */
void
set_migration_type(const char *mig_type_str)
{
	if (mig_type_str == NULL)
		return;

	int i;
	bool found_type = false;
	for (i=0; i<sizeof(mig_type_conv)/sizeof(mig_type_conv[0]); ++i) {
		if (!strcmp (mig_type_str, mig_type_conv[i].str)) {
			mig_type = mig_type_conv[i].mig_type;
			found_type = true;
		}
	}

	/* we do not know this migration type */
	if (!found_type) {
		fprintf(stderr, "ERROR: Migration type '%s' not supported. Fallback to 'cold'\n", mig_type_str);
	}

	return;
}

/**
 * \brief Closes a socket
 *
 * \param sock the socket to be closed
 */
static inline void
close_sock(int sock)
{
	if (close(sock) < 0) {
		fprintf(stderr,
		    	"ERROR: Could not close the communication socket "
			"- %d (%s). Abort!\n",
			errno,
			strerror(errno));
		exit(EXIT_FAILURE);
	}
}

/**
 * \brief Set the destination node for a migration
 *
 * \param ip_str a string containing the IPv4 addr of the destination
 * \param port the migration port
 */
void set_migration_target(const char *ip_str, int port)
{
	/* determine server address */
	memset(&mig_server, '0', sizeof(mig_server));
	mig_server.sin_family = AF_INET;
	mig_server.sin_port = htons(port);

	int res = inet_pton(AF_INET, ip_str, &mig_server.sin_addr);
	if (res == 0) {
		fprintf(stderr, "'%s' is not a valid server address\n", ip_str);
	} else if (res < 0) {
		fprintf(stderr, "An error occured while retrieving the migration server address\n");
		perror("inet_pton");
	}
}

/**
 * \brief Connects to a migration target via TCP/IP
 */
void connect_to_server(void)
{
	int res = 0;
	char buf[INET_ADDRSTRLEN];
	if (inet_ntop(AF_INET, (const void*)&mig_server.sin_addr, buf, INET_ADDRSTRLEN) == NULL) {
		perror("inet_ntop");
		exit(EXIT_FAILURE);
	}

	if((com_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

      	fprintf(stderr, "Trying to connect to migration server: %s\n", buf);
	if (connect(com_sock, (struct sockaddr *)&mig_server, sizeof(mig_server)) < 0) {
		perror("connect");
		exit(EXIT_FAILURE);
    	}
      	fprintf(stderr, "Successfully connected to: %s\n", buf);
}


/**
 * \brief Waits for a migration source to connect via TCP/IP
 *
 * \param listen_portno the port of the migration socket
 */
void wait_for_client(uint16_t listen_portno)
{
	int client_addr_len = 0, res = 0;
	struct sockaddr_in serv_addr;
	struct sockaddr_in client_addr;

	/* open migration socket */
	fprintf(stderr, "Waiting for incomming migration request ...\n");
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(listen_portno);

	bind(listen_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	listen(listen_sock, 10);

	client_addr_len = sizeof(struct sockaddr_in);
	if ((com_sock = accept(listen_sock, &client_addr, &client_addr_len)) < 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}
	char buf[INET_ADDRSTRLEN];
	if (inet_ntop(AF_INET, (const void*)&client_addr.sin_addr, buf, INET_ADDRSTRLEN) == NULL) {
		perror("inet_ntop");
		exit(EXIT_FAILURE);
	}
	fprintf(stderr, "Incomming migration from: %s\n", buf);
}

/**
 * \brief Receives data from the migration socket
 *
 * \param buffer the destination buffer
 * \param length the buffer size
 */
int recv_data(void *buffer, size_t length)
{
	size_t bytes_received = 0;
	while(bytes_received < length) {
		bytes_received += recv(
				com_sock,
				(void*)((uint64_t)buffer+bytes_received),
				length-bytes_received,
			       	0);
	}

	return bytes_received;
}

/**
 * \brief Sends data via the migration socket
 *
 * \param buffer the source buffer
 * \param length the buffer size
 */
int send_data(void *buffer, size_t length)
{
	size_t bytes_sent = 0;
	while(bytes_sent < length) {
		bytes_sent += send(
				com_sock,
				(void*)((uint64_t)buffer+bytes_sent),
				length-bytes_sent,
			       	0);
	}

	return bytes_sent;
}

/**
 * \brief Closes the TCP connection
 */
void close_migration_channel(void)
{
	if (listen_sock) {
		close_sock(listen_sock);
	}
	close_sock(com_sock);
}


#ifndef __RDMA_MIGRATION__
void send_guest_mem(mig_mode_t mode, bool final_dump, size_t mem_chunk_cnt, mem_chunk_t *mem_chunks)
{
	/* determine migration mode */
	switch (mode) {
	case MIG_MODE_INCREMENTAL_DUMP:
		fprintf(stderr, "ERROR: Incremental dumps currently not supported via TCP/IP. Fallback to complete dump!\n");
	case MIG_MODE_COMPLETE_DUMP:
		send_data(guest_mem, guest_size);
		break;
	default:
		fprintf(stderr, "ERROR: Unknown migration mode. Abort!\n");
		exit(EXIT_FAILURE);
	}

	fprintf(stderr, "Guest memory sent!\n");
}

void recv_guest_mem(size_t mem_chunk_cnt, mem_chunk_t *mem_chunks)
{
	recv_data(guest_mem, guest_size);
	fprintf(stderr, "Guest memory received!\n");
}
#endif /* __RDMA_MIGRATION__ */

#else

/* dummy implementation for aarch64 */

void set_migration_target(const char *ip_str, int port)
{
}

void set_migration_type(const char *mig_type_str)
{
}

#endif

