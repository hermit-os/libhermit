#ifndef __UHYVE_NET_H__
#define __UHYVE_NET_H__

#endif

#include <linux/kvm.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <unistd.h>

#include <sys/select.h>


/* network interface */
#include <sys/socket.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <err.h>

#include "uhyve-cpu.h"

int guest_ip[4] = {10, 0, 5, 2};
static char *netif;
static int netfd;

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


/* TODO2: create an array or equal for more then one netif */
uhyve_netinfo_t netinfo;
