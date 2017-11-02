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


void call_ibv_open_device(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_open_device_t * args = (uhyve_ibv_open_device_t *) (guest_mem + data);

	struct ibv_context * host_ret = 	(guest_mem+(size_t)args->device);
	memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
	// TODO: Convert ptrs contained in return value.
	// TODO: Delete host_ret data structure.
}

void call_ibv_open_device(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_get_device_list_t* args = (uhyve_ibv_get_device_list_t*) (guest_mem+data);

	// Call IBV function from hypervisor
	int num_devices;
	struct ibv_device **temp_dev_list = ibv_get_device_list(&num_devices);

	// Copy number of devices to kernel memory	
	memcpy(guest_mem+(size_t)args->num_devices, &num_devices, sizeof(num_devices));

	for (int d = 0; d < num_devices; d++) {
		printf("uhyve.c: before memcpy list[d].\n");
		// Copy array entry containing ibv_device struct to kernel memory
		memcpy(guest_mem + (size_t)args->dev_phys_ptr_list[d], temp_dev_list[d], sizeof(struct ibv_device));
	}
}

void call_ibv_get_device_name(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_get_device_name_t * args = (uhyve_ibv_get_device_name_t *) (guest_mem + data);

	const char * host_ret = 	(guest_mem+(size_t)args->device);
	memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
	// TODO: Convert ptrs contained in return value.
	// TODO: Delete host_ret data structure.
}

void call_ibv_query_port(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_query_port_t * args = (uhyve_ibv_query_port_t *) (guest_mem + data);

	int host_ret = 	(guest_mem+(size_t)args->context, port_num, guest_mem+(size_t)args->port_attr);
	args->ret = host_ret;
}

void call_ibv_create_comp_channel(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_create_comp_channel_t * args = (uhyve_ibv_create_comp_channel_t *) (guest_mem + data);

	struct ibv_comp_channel * host_ret = 	(guest_mem+(size_t)args->context);
	memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
	// TODO: Convert ptrs contained in return value.
	// TODO: Delete host_ret data structure.
}

void call_ibv_alloc_pd(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_alloc_pd_t * args = (uhyve_ibv_alloc_pd_t *) (guest_mem + data);

	struct ibv_pd * host_ret = 	(guest_mem+(size_t)args->context);
	memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
	// TODO: Convert ptrs contained in return value.
	// TODO: Delete host_ret data structure.
}

void call_ibv_reg_mr(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_reg_mr_t * args = (uhyve_ibv_reg_mr_t *) (guest_mem + data);

	struct ibv_mr * host_ret = 	(guest_mem+(size_t)args->pd, guest_mem+(size_t)args->addr, length, access);
	memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
	// TODO: Convert ptrs contained in return value.
	// TODO: Delete host_ret data structure.
}

void call_ibv_create_cq(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_create_cq_t * args = (uhyve_ibv_create_cq_t *) (guest_mem + data);

	struct ibv_cq * host_ret = 	(guest_mem+(size_t)args->context, cqe, guest_mem+(size_t)args->cq_context, guest_mem+(size_t)args->channel, comp_vector);
	memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
	// TODO: Convert ptrs contained in return value.
	// TODO: Delete host_ret data structure.
}

void call_ibv_create_qp(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_create_qp_t * args = (uhyve_ibv_create_qp_t *) (guest_mem + data);

	struct ibv_qp * host_ret = 	(guest_mem+(size_t)args->pd, guest_mem+(size_t)args->qp_init_attr);
	memcpy(guest_mem+(size_t)args->ret, host_ret, sizeof(host_ret));
	// TODO: Convert ptrs contained in return value.
	// TODO: Delete host_ret data structure.
}

void call_ibv_query_qp(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_query_qp_t * args = (uhyve_ibv_query_qp_t *) (guest_mem + data);

	int host_ret = 	(guest_mem+(size_t)args->qp, guest_mem+(size_t)args->attr, attr_mask, guest_mem+(size_t)args->init_attr);
	args->ret = host_ret;
}

void call_ibv_modify_qp(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_modify_qp_t * args = (uhyve_ibv_modify_qp_t *) (guest_mem + data);

	int host_ret = 	(guest_mem+(size_t)args->qp, guest_mem+(size_t)args->attr, attr_mask);
	args->ret = host_ret;
}

void call_ibv_destroy_qp(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_destroy_qp_t * args = (uhyve_ibv_destroy_qp_t *) (guest_mem + data);

	int host_ret = 	(guest_mem+(size_t)args->qp);
	args->ret = host_ret;
}

void call_ibv_destroy_cq(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_destroy_cq_t * args = (uhyve_ibv_destroy_cq_t *) (guest_mem + data);

	int host_ret = 	(guest_mem+(size_t)args->cq);
	args->ret = host_ret;
}

void call_ibv_dereg_mr(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_dereg_mr_t * args = (uhyve_ibv_dereg_mr_t *) (guest_mem + data);

	int host_ret = 	(guest_mem+(size_t)args->mr);
	args->ret = host_ret;
}

void call_ibv_dealloc_pd(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_dealloc_pd_t * args = (uhyve_ibv_dealloc_pd_t *) (guest_mem + data);

	int host_ret = 	(guest_mem+(size_t)args->pd);
	args->ret = host_ret;
}

void call_ibv_destroy_comp_channel(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_destroy_comp_channel_t * args = (uhyve_ibv_destroy_comp_channel_t *) (guest_mem + data);

	int host_ret = 	(guest_mem+(size_t)args->channel);
	args->ret = host_ret;
}

void call_ibv_close_device(struct kvm_run * run, uint8_t * guest_mem) {
	unsigned data = *((unsigned*)((size_t)run+run->io.data_offset));
	uhyve_ibv_close_device_t * args = (uhyve_ibv_close_device_t *) (guest_mem + data);

	int host_ret = 	(guest_mem+(size_t)args->context);
	args->ret = host_ret;
}
