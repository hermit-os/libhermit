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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#include <hermit/ibv.h>	// Geht per cmake copy workaround

/* #define N	255 */

/* static void test_handler(int s) */
/* { */
	/* printf("Receive signal with number %d\n", s); */
/* } */

int main(int argc, char** argv)
{
	int i, random;
	FILE* file;

	// ---------------------------------------------------------------------------

	struct ibv_device **dev_list;
	int num_devices;

	printf("ib-test.c: before get dev list.\n");
	dev_list = ibv_get_device_list(&num_devices);
	printf("after get device list -- ib-test.c: num devices: %d\n", num_devices);
	printf("after get device list -- ib-test.c: ptr 1: %p\n",  dev_list[0]);
	printf("after get device list -- ib-test.c: ptr 2: %p\n",  dev_list[1]);
	printf("after get device list -- ib-test.c: name 1: %s\n", dev_list[0]->name);
	printf("after get device list -- ib-test.c: name 2: %s\n", dev_list[1]->name);

	printf("before get device name loop.\n");
	for (int i=0; i < num_devices; i++) {
		const char* dev_name = ibv_get_device_name(dev_list[i]);
		printf("after get device name -- Device name %d: %s\n", i, dev_name);
	}

	printf("before open_device\n");
	struct ibv_context * context = ibv_open_device(dev_list[0]);
	printf("after open device\n");



	return 0;
}

