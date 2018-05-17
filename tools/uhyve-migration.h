#ifndef __UHYVE_MIGRATION_H__
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

/**
 * @author Simon Pickartz
 * @file tools/uhyve-migration.h
 * @brief Migration-related functions
 */

#define __UHYVE_MIGRATION_H__

#include <stdbool.h>

extern size_t guest_size;
extern uint8_t* guest_mem;

#define MIGRATION_PORT 1337

typedef enum {
	MIG_MODE_COMPLETE_DUMP = 1,
	MIG_MODE_INCREMENTAL_DUMP,
} mig_mode_t;

typedef enum {
	MIG_TYPE_COLD = 0,
	MIG_TYPE_LIVE,
} mig_type_t;

const static struct {
	mig_type_t mig_type;
	const char *str;
} mig_type_conv [] = {
	{MIG_TYPE_COLD, "cold"},
	{MIG_TYPE_LIVE, "live"},
};

typedef struct _mem_chunk {
	size_t size;
	uint8_t *ptr;
} mem_chunk_t;

typedef struct _migration_metadata {
	uint32_t ncores;
	size_t guest_size;
	uint32_t no_checkpoint;
	uint64_t elf_entry;
	bool full_checkpoint;
} migration_metadata_t;

void set_migration_type(const char *mig_type_str);
mig_type_t get_migration_type(void);

void wait_for_client(uint16_t listen_portno);
void set_migration_target(const char *ip_str, int port);
void connect_to_server(void);
void close_migration_channel(void);

int recv_data(void *buffer, size_t length);
int send_data(void *buffer, size_t length);

void send_guest_mem(mig_mode_t mode, bool final_dump, size_t mem_chunk_cnt, mem_chunk_t *mem_chunks);
void recv_guest_mem(size_t mem_chunk_cnt, mem_chunk_t *mem_chunks);
#endif /* __UHYVE_MIGRATION_H__ */



