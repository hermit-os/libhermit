/* Copyright (c) 2017, RWTH Aachen University
 * Author(s): Annika Wierichs <annika.wierichs@rwth-aachen.de>
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose with or without fee is hereby granted, provided
 * that the above copyright notice and this permission notice appear
 * in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef UHYVE_IBV_H
#define UHYVE_IBV_H

#include <infiniband/verbs.h>		// Linux include
#include <linux/kvm.h>

#define MAX_NUM_OF_IBV_DEVICES 16

typedef enum {
	UHYVE_PORT_IBV_OPEN_DEVICE = 0x510,
	UHYVE_PORT_IBV_GET_DEVICE_LIST = 0x511,
	UHYVE_PORT_IBV_GET_DEVICE_NAME = 0x512,
	UHYVE_PORT_IBV_QUERY_PORT = 0x513,
	UHYVE_PORT_IBV_CREATE_COMP_CHANNEL = 0x514,
	UHYVE_PORT_KERNEL_IBV_LOG = 0x515,
} uhyve_ibv_t;


//inline unsigned get_data(struct kvm_run * run) {
	//return *((unsigned*)((size_t)run+run->io.data_offset));
//}


typedef struct {
	// Parameters:
	int * num_devices;
	// Return value:
	struct ibv_device * ret[MAX_NUM_OF_IBV_DEVICES];
} __attribute__((packed)) uhyve_ibv_get_device_list_t;

typedef struct {
	// Parameters:
	struct ibv_device * device;
	// Return value:
	struct ibv_context * ret;
} __attribute__((packed)) uhyve_ibv_open_device_t;

typedef struct {
	// Parameters:
	struct ibv_device * device;
	// Return value:
	const char * ret; // TODO Should this be const?
} __attribute__((packed)) uhyve_ibv_get_device_name_t;

typedef struct {
	// Parameters:
	struct ibv_context * context;
	uint8_t port_num;
	struct ibv_port_attr * port_attr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_query_port_t;

typedef struct {
	// Parameters:
	struct ibv_context * context;
	// Return value:
	struct ibv_comp_channel * ret;
} __attribute__((packed)) uhyve_ibv_create_comp_channel_t;


void call_ibv_open_device(struct kvm_run * run);
void call_ibv_get_device_name(struct kvm_run * run);
void call_ibv_query_port(struct kvm_run * run);
void call_ibv_create_comp_channel(struct kvm_run * run);
void call_ibv_get_device_list(struct kvm_run * run);

#endif // UHYVE_IBV_H
