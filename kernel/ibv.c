/*
 * Copyright (c) 2017, Annika Wierichs, RWTH Aachen University
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
 *
 * TODO: Documentation
 *
 */


#include <asm/page.h>
#include <asm/uhyve.h>
#include <hermit/stddef.h>
#include <hermit/stdio.h>
#include <hermit/stdlib.h>

#include <hermit/ibv.h>
#include <hermit/ibv_guest_host.h>


// TODO: Can/should we separate ibv_get_device_list into two KVM exit IOs to
// allocate the right amount of memory?
#define MAX_NUM_OF_IBV_DEVICES 16	


static void * ret_guest_ptr;


/*
 * ibv_open_device
 */

typedef struct {
	// Parameters:
	struct ibv_device * device;
	// Return value:
	struct ibv_context * ret;
} __attribute__((packed)) uhyve_ibv_open_device_t;

struct ibv_context * ibv_open_device(struct ibv_device * device) {
	uhyve_ibv_open_device_t uhyve_args;
	uhyve_args.device = guest_to_host_ibv_device(device);

	ret_guest_ptr = kmalloc(sizeof(struct ibv_context));
	uhyve_args.ret = (struct ibv_context *) guest_to_host((size_t) ret_guest_ptr);

	uhyve_send(UHYVE_PORT_IBV_OPEN_DEVICE, (unsigned)guest_to_host((size_t)&uhyve_args));

	host_to_guest_ibv_device(device);
	uhyve_args.ret = (struct ibv_context *) ret_guest_ptr;
	// TODO: Fix pointers in returned data structures.

	return uhyve_args.ret;
}


/*
 * ibv_get_device_name
 */

typedef struct {
	// Parameters:
	struct ibv_device * device;
	// Return value:
	const char * ret;
} __attribute__((packed)) uhyve_ibv_get_device_name_t;

const char * ibv_get_device_name(struct ibv_device * device) {
	uhyve_ibv_get_device_name_t uhyve_args;
	uhyve_args.device = guest_to_host_ibv_device(device);

	uhyve_send(UHYVE_PORT_IBV_GET_DEVICE_NAME, (unsigned) guest_to_host((size_t) &uhyve_args));

	host_to_guest_ibv_device(device);
	// Lookup return address in hash map created earlier. Found? convert back.
	// Hack for testing:
	uhyve_args.ret = uhyve_args.device->name;

	return uhyve_args.ret;
}


/*
 * ibv_query_port
 */

typedef struct {
	// Parameters:
	struct ibv_context * context;
	uint8_t port_num;
	struct ibv_port_attr * port_attr;
	// Return value:
	int ret;
} __attribute__((packed)) uhyve_ibv_query_port_t;

int ibv_query_port(struct ibv_context * context, uint8_t port_num, struct ibv_port_attr * port_attr) {
	uhyve_ibv_query_port_t uhyve_args;
	uhyve_args.context   = guest_to_host_ibv_context(context);
	uhyve_args.port_num  = port_num;
	uhyve_args.port_attr = guest_to_host_ibv_port_attr(port_attr);

	uhyve_send(UHYVE_PORT_IBV_QUERY_PORT, (unsigned) guest_to_host((size_t) &uhyve_args));

	host_to_guest_ibv_context(context);
	host_to_guest_ibv_port_attr(port_attr);

	return uhyve_args.ret;
}


/*
 * ibv_create_comp_channel
 */

typedef struct {
	// Parameters:
	struct ibv_context * context;
	// Return value:
	struct ibv_comp_channel * ret;
} __attribute__((packed)) uhyve_ibv_create_comp_channel_t;

struct ibv_comp_channel * ibv_create_comp_channel(struct ibv_context * context) {
	uhyve_ibv_create_comp_channel_t uhyve_args;
	uhyve_args.context = guest_to_host_ibv_context(context);

	ret_guest_ptr = kmalloc(sizeof(struct ibv_comp_channel));
	uhyve_args.ret = (struct ibv_comp_channel *) guest_to_host((size_t) ret_guest_ptr);

	uhyve_send(UHYVE_PORT_IBV_CREATE_COMP_CHANNEL, (unsigned) guest_to_host((size_t) &uhyve_args));

	host_to_guest_ibv_context(context);
	uhyve_args.ret = (struct ibv_comp_channel *) ret_guest_ptr;

	return uhyve_args.ret;
}



/*typedef struct { // CHECKED*/
	/*// Parameters:*/
	/*int						,		*num_devices;*/
	/*// Return value:*/
	/*struct ibv_device *dev_phys_ptr_list[MAX_NUM_OF_IBV_DEVICES];*/
	/*// TODO: Can we make the return type struct ibv_device**?*/
/*} __attribute__((packed)) uhyve_ibv_get_device_list_t;*/

/*struct ibv_device** ibv_get_device_list(int *num_devices) {*/
	/*// num_devices can be mapped to physical memory right away.*/
	/*uhyve_ibv_get_device_list_t uhyve_args = {*/
			/*(int*) virt_to_phys((size_t) num_devices)*/
	/*};*/

	/*// Allocate memory for return value.*/
	/*struct ibv_device *devs = kmalloc(MAX_NUM_OF_IBV_DEVICES * sizeof(struct ibv_device));*/
	/*struct ibv_device **list_virt = kmalloc(MAX_NUM_OF_IBV_DEVICES * sizeof(struct ibv_device *));*/

	/*// We keep a list of the virtual addresses, so we can return it later, and map*/
	/*// to physical addresses for the args struct passed to uhyve.*/
	/*for (int i = 0; i < MAX_NUM_OF_IBV_DEVICES; i++) {*/
		/*struct ibv_device* device_address = devs + i;*/
		/*list_virt[i] = device_address;*/
		/*uhyve_args.dev_phys_ptr_list[i] = (struct ibv_device*) virt_to_phys((size_t) device_address);*/
	/*}*/

	/*uhyve_send(UHYVE_PORT_IBV_GET_DEVICE_LIST, (unsigned)virt_to_phys((size_t)&uhyve_args));*/
	/*return list_virt;*/
/*}*/
