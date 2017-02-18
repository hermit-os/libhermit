/* Copyright (c) 2015, IBM
 * Author(s): Dan Williams <djwillia@us.ibm.com>
 *            Ricardo Koller <kollerr@us.ibm.com>
 * Copyright (c) 2017, RWTH Aachen University
 * Author(s): Stefan Lankes <slankes@eonerc.rwth-aachen.de>
 *            Tim van de Kamp <tim.van.de.kamp@rwth-aachen.de>
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

/* We used several existing projects as guides
 * kvmtest.c: http://lwn.net/Articles/658512/
 * lkvm: http://github.com/clearlinux/kvmtool
 */

/*
 * 15.1.2017: extend original version (https://github.com/Solo5/solo5)
 *            for HermitCore
 */


//TODO1: include one file with typedef and ports in netio.c and uhyve-net.c
#include <hermit/stddef.h>
#include <hermit/stdio.h>
#include <hermit/tasks.h>
#include <hermit/errno.h>
#include <hermit/syscall.h>
#include <hermit/spinlock.h>
#include <hermit/semaphore.h>
#include <hermit/time.h>
#include <hermit/rcce.h>
#include <hermit/memory.h>
#include <hermit/signal.h>
#include <hermit/logging.h>
#include <asm/io.h>
#include <sys/poll.h>

#include <lwip/sockets.h>
#include <lwip/err.h>
#include <lwip/stats.h>

/*		the constant must be changed in uhyve-net.h to		*/

#define UHYVE_PORT_NETINFO	0x505
#define UHYVE_PORT_NETWRITE	0x506
#define UHYVE_PORT_NETREAD	0x507

// UHYVE_PORT_NETINFO
typedef struct {
        /* OUT */
        char mac_str[18];
	char ip_str[15];
//	char subnet_str[15];
//	char gw_str[15];
} __attribute__((packed)) uhyve_netinfo_t;

// UHYVE_PORT_NETWRITE
typedef struct {
        /* IN */
        const void* data;
        size_t len;
        /* OUT */
        int ret;
} __attribute__((packed)) uhyve_netwrite_t;

// UHYVE_PORT_NETREAD
typedef struct {
        /* IN */
        void* data;
        /* IN / OUT */
        size_t len;
        /* OUT */
        int ret;
} __attribute__((packed)) uhyve_netread_t;

int hermit_net_write_sync(uint8_t *data, int n)
{
	volatile uhyve_netwrite_t uhyve_netwrite;
	uhyve_netwrite.data = (uint8_t*)virt_to_phys((size_t)data);
	uhyve_netwrite.len = n;
	uhyve_netwrite.ret = 0;

	outportl(UHYVE_PORT_NETWRITE, (unsigned)virt_to_phys((size_t)&uhyve_netwrite));

	return uhyve_netwrite.ret;
}
int hermit_net_read_sync(uint8_t *data, int *n)
{
	volatile uhyve_netread_t uhyve_netread;
	uhyve_netread.data = (uint8_t*)virt_to_phys((size_t)data);
	uhyve_netread.len = *n;
	uhyve_netread.ret = 0;
	outportl(UHYVE_PORT_NETREAD, (unsigned)virt_to_phys((size_t)&uhyve_netread));

	*n = uhyve_netread.len;
	return uhyve_netread.ret;
}

uhyve_netinfo_t hermit_netinfo(void)
{
	volatile uhyve_netinfo_t uhyve_netinfo;
	outportl(UHYVE_PORT_NETINFO, (unsigned)virt_to_phys((size_t)&uhyve_netinfo));
	return uhyve_netinfo;
}

static char mac_str[18];
char *hermit_net_mac_str(void)
{
	volatile uhyve_netinfo_t uhyve_netinfo;
	outportl(UHYVE_PORT_NETINFO, (unsigned)virt_to_phys((size_t)&uhyve_netinfo));
	memcpy(mac_str, (void *)&uhyve_netinfo.mac_str, 18);
	return mac_str;
}
static char ip_str[15];
char *hermit_net_ip_str(void)
{
	volatile uhyve_netinfo_t uhyve_netinfo;
	outportl(UHYVE_PORT_NETINFO, (unsigned)virt_to_phys((size_t)&uhyve_netinfo));
	memcpy(ip_str, (void *)&uhyve_netinfo.ip_str, 15);
	return ip_str;
}
