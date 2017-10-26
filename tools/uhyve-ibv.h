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

#define MAX_NUM_OF_IBV_DEVICES 16

typedef enum {
	UHYVE_PORT_IBV_GET_DEVICE_LIST	= 0x510,
	UHYVE_PORT_IBV_GET_DEVICE_NAME	= 0x511,
	UHYVE_PORT_IBV_OPEN_DEVICE = 0x512,
	UHYVE_PORT_IBV_CREATE_COMP_CHANNEL = 0x513,
	UHYVE_PORT_IBV_ALLOC_PD = 0x514,
	UHYVE_PORT_IBV_REG_MR = 0x515,
	UHYVE_PORT_IBV_CREATE_CQ = 0x516,
	UHYVE_PORT_IBV_CREATE_QP = 0x517,
	UHYVE_PORT_IBV_QUERY_QP = 0x518,
	UHYVE_PORT_IBV_MODIFY_QP = 0x519,
	//UHYVE_PORT_IBV_CREATE_AH = 0x520,
} uhyve_ibv_t;

typedef struct {
	// In:
	int								*num_devices;
	// Out:
	//struct ibv_device devices[MAX_NUM_OF_IBV_DEVICES];
	struct ibv_device *dev_phys_ptr_list[MAX_NUM_OF_IBV_DEVICES];
	//struct ibv_device **device_list;
} __attribute__((packed)) uhyve_ibv_get_device_list_t;

typedef struct {
	// Parameters:
	struct ibv_qp *qp;
	struct ibv_qp_attr *attr;
	int attr_mask;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_modify_qp_t;

typedef struct {
	// Parameters:
	struct ibv_pd *pd;
	struct ibv_ah_attr *attr;
	// Return value:
	struct ibv_ah *ret;
} __attribute__((packed)) uhyve_ibv_create_ah_t;

//typedef struct {
	//struct ibv_device *device;
	//char							*ret;
//} __attribute__((packed)) uhyve_ibv_get_device_name_t;


#endif // UHYVE_IBV_H
