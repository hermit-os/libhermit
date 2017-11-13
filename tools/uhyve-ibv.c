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

#include "uhyve-ibv.h"

#include <infiniband/verbs.h>		// Linux include


/*void call_ibv_get_device_list(struct kvm_run * run, uint8_t * guest_mem) {*/
	/*unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));*/
	/*uhyve_ibv_get_device_list_t* args = (uhyve_ibv_get_device_list_t*) (guest_mem+data);*/

	/*// Call IBV function from hypervisor*/
	/*int num_devices;*/
	/*struct ibv_device **temp_dev_list = ibv_get_device_list(&num_devices);*/

	/*// Copy number of devices to kernel memory	*/
	/*memcpy(guest_mem+(size_t)args->num_devices, &num_devices, sizeof(num_devices));*/

	/*for (int d = 0; d < num_devices; d++) {*/
		/*printf("uhyve.c: before memcpy list[d].\n");*/
		/*// Copy array entry containing ibv_device struct to kernel memory*/
		/*memcpy(guest_mem + (size_t)args->dev_phys_ptr_list[d], temp_dev_list[d], sizeof(struct ibv_device));*/
	/*}*/
/*}*/


struct ibv_context * ibv_open_device(struct ibv_device * device);
const char* ibv_get_device_name(struct ibv_device *device);
int ibv_query_port(struct ibv_context * context, uint8_t port_num, struct ibv_port_attr * port_attr);
struct ibv_comp_channel * ibv_create_comp_channel(struct ibv_context * context);


/*
 * ibv_open_device
 */

void call_ibv_open_device(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_open_device_t * args = (uhyve_ibv_open_device_t *) (guest_mem + data);

	struct ibv_context * host_ret = ibv_open_device(guest_mem+(size_t)args->device);
	memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
	// TODO: Convert ptrs contained in return value.
	free(host_ret);
}


/*
 * ibv_get_device_name
 */

void call_ibv_get_device_name(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_get_device_name_t * args = (uhyve_ibv_get_device_name_t *) (guest_mem + data);

	// TODO: Tricky because char ptr isn't allocated in called function.
	const char * host_ret = ibv_get_device_name(guest_mem+(size_t)args->device);
	memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
	// TODO: Convert ptrs contained in return value.
	// TODO: How to tell if ret needs to be deleted?
}


/*
 * ibv_query_port
 */

void call_ibv_query_port(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_query_port_t * args = (uhyve_ibv_query_port_t *) (guest_mem + data);

	int host_ret = ibv_query_port(guest_mem+(size_t)args->context, port_num, guest_mem+(size_t)args->port_attr);
	args->ret = host_ret;
}


/*
 * ibv_create_comp_channel
 */

/*void guest_to_host_ibv_create_comp_channel_t(struct uhyve_ibv_create_comp_channel_t * args, uint8_t * guest_mem) {*/
	/*[>args->context = (size_t)args->context + guest_mem;<]*/
	/*args->context = guest_to_host(args->context);*/
	/*args->ret = (size_t)args->ret + guest_mem;*/
/*}*/

/*void host_to_guest_ibv_create_comp_channel_t(struct uhyve_ibv_create_comp_channel_t * args, uint8_t * guest_mem) {*/
	/*args->context = (size_t)args->context - guest_mem;*/
	/*args->ret = (size_t)args->ret - guest_mem;*/
/*}*/

void call_ibv_create_comp_channel(struct kvm_run * run, uint8_t * guest_mem) {
	uhyve_ibv_create_comp_channel_t * args = (uhyve_ibv_create_comp_channel_t *) get_data(run, guest_mem);
	guest_to_host_ibv_create_comp_channel_t(args, guest_mem);

	/*args->context = (size_t)args->context + guest_mem;*/
	args->context = guest_to_host(args->context);
	args->ret = (size_t)args->ret + guest_mem;

	struct ibv_comp_channel * host_ret = ibv_create_comp_channel(args->context);
	memcpy(args->ret, host_ret, sizeof(host_ret)); // TODO: This will only work for ABI ver > 2.
	free(host_ret);

	args->context = (size_t)args->context - guest_mem;
	args->ret = (size_t)args->ret - guest_mem;
	/*host_to_guest_ibv_create_comp_channel_t(args, guest_mem);*/
}
