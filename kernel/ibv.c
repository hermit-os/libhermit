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
 */


#include <asm/page.h>
#include <asm/uhyve.h>
#include <hermit/stddef.h>
#include <hermit/stdio.h>
#include <hermit/stdlib.h>

#include <hermit/ibv.h>		// GEHT

// TODO: Can/should we separate ibv_get_device_list into two KVM exit IOs to
// allocate the right amount of memory?
#define MAX_NUM_OF_IBV_DEVICES 16	

typedef struct {
	int								*num_devices;
	struct ibv_device *dev_phys_ptr_list[MAX_NUM_OF_IBV_DEVICES];
	// TODO: Can we make the return type struct ibv_device**?
} __attribute__((packed)) uhyve_ibv_get_device_list_t;

struct ibv_device** h_ibv_get_device_list(int *num_devices)
{
	// num_devices can be mapped to physical memory right away.
	uhyve_ibv_get_device_list_t uhyve_args = {(int*) virt_to_phys((size_t) num_devices)};

	// Allocate memory for return value.
	struct ibv_device *devs = kmalloc(MAX_NUM_OF_IBV_DEVICES * sizeof(struct ibv_device));
	struct ibv_device **list_virt = kmalloc(MAX_NUM_OF_IBV_DEVICES * sizeof(struct ibv_device *));

	// We keep a list of the virtual addresses, so we can return it later, and map
	// to physical addresses for the args struct passed to uhyve.
	for (int i = 0; i < MAX_NUM_OF_IBV_DEVICES; i++) {
		struct ibv_device* device_address = devs + i;
		list_virt[i] = device_address;
		uhyve_args.dev_phys_ptr_list[i] = (struct ibv_device*) virt_to_phys((size_t) device_address);
	}

	uhyve_send(UHYVE_PORT_IBV_GET_DEVICE_LIST, (unsigned)virt_to_phys((size_t)&uhyve_args));
	return list_virt;
}

/*struct ibv_device** h_ibv_get_device_list(int *num_devices)*/
/*{*/
	/*struct ibv_device *devs = calloc(MAX_NUM_OF_IBV_DEVICES, sizeof(struct ibv_device));*/

	/*struct ibv_device **list_phys; */
	/*struct ibv_device **list_virt;*/
	/*list_phys = calloc(MAX_NUM_OF_IBV_DEVICES, sizeof(struct ibv_device *));	// NUM + 1 ???*/
	/*list_virt = calloc(MAX_NUM_OF_IBV_DEVICES, sizeof(struct ibv_device *));	// NUM + 1 ???*/
	/*for (int i = 0; i < MAX_NUM_OF_IBV_DEVICES; i++) {*/
		/*struct ibv_device* device_address = devs + i;*/
		/*list_virt[i] = device_address;*/
		/*list_phys[i] = (struct ibv_device*) virt_to_phys((size_t) device_address);*/
		/*[>list_phys[i] = calloc(1, sizeof(struct ibv_device));<]*/
	/*}*/
	/*uhyve_ibv_get_device_list_t uhyve_args =*/
			/*{(int*) virt_to_phys((size_t) num_devices), (struct ibv_device**) virt_to_phys((size_t) list_phys)};*/

	/*uhyve_send(UHYVE_PORT_IBV_GET_DEVICE_LIST, (unsigned)virt_to_phys((size_t)&uhyve_args));*/
	/*return list_virt;*/
/*}*/

/*void h_ibv_get_device_list(int *num_devices)*/
/*{*/
	/*uhyve_ibv_get_device_list_t uhyve_args = {(int*) virt_to_phys((size_t) num_devices)};*/
	/*uhyve_args.first_device = (struct ibv_device*) virt_to_phys((size_t) uhyve_args.devices);*/
	/*[>&uhyve_args.devices = (struct ibv_device*) virt_to_phys((size_t) uhyve_args.devices);<]*/

	/*uhyve_send(UHYVE_PORT_IBV_GET_DEVICE_LIST, (unsigned)virt_to_phys((size_t)&uhyve_args));*/
/*}*/


typedef struct {
	struct ibv_device *device;
	char							*ret;
} __attribute__((packed)) uhyve_ibv_get_device_name_t;

const char* h_ibv_get_device_name(struct ibv_device *device)
{
	uhyve_ibv_get_device_name_t uhyve_args = {(struct ibv_device*) virt_to_phys((size_t) device)};
	uhyve_send(UHYVE_PORT_IBV_GET_DEVICE_NAME, (unsigned)virt_to_phys((size_t)&uhyve_args));
	return uhyve_args.ret;
}
