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

#include "uhyve-net.h"

//-------------------------------------- ATTACH LINUX TAP -----------------------------------------//
int attach_linux_tap(const char *dev) {
	struct ifreq ifr;
	int fd, err;

	// @<number> indicates a pre-existing open fd onto the correct device.
	if (dev[0] == '@') {
		fd = atoi(&dev[1]);

		if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
			return -1;
		return fd;
	}

	fd = open("/dev/net/tun", O_RDWR | O_NONBLOCK);

	// Initialize interface request for TAP interface
	//printf("Initialize interface request for TAP interface\n");
	memset(&ifr, 0, sizeof(ifr));

	ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
	if (strlen(dev) > IFNAMSIZ) {
		errno = EINVAL;
		return -1;
	}
	strncpy(ifr.ifr_name, dev, IFNAMSIZ);

	// Try to create OR attach to an existing device. The Linux API has no way
	// to differentiate between the two

	// create before a tap device with these commands:
	//
	// sudo ip tuntap add <devname> mode tap user <user>
	// sudo ip addr add 10.0.5.1/24 dev <devname>
	// sudo ip link set dev <devname> up
	//

	//printf("Try to create OR attach to an existing device. The Linux API has no way\nto differentiate between the two\n");

	if (ioctl(fd, TUNSETIFF, (void *)&ifr) == -1) {
		err = errno;
		close(fd);
		errno = err;
		return -1;
	}
	// If we got back a different device than the one requested, e.g. because
	// the caller mistakenly passed in '%d' (yes, that's really in the Linux API)
	// then fail
	//printf("Got different device?");

	if (strncmp(ifr.ifr_name, dev, IFNAMSIZ) != 0) {
		close(fd);
		errno = ENODEV;
		return -1;
	}

	// Attempt a zero-sized write to the device. If the device was freshly created
	// (as opposed to attached to an existing ine) this will fail with EIO. Ignore
	// any other error return since that may indicate the device is up
	//
	// If this check produces a false positive then caller's later writes to fd will
	// fali with EIO, which is not great but at least we tried

	//printf("Device freshly created?");
	char buf[1] = { 0 };
	if (write(fd, buf, 0) == -1 && errno == EIO) {
		close(fd);
		errno = ENODEV;
		return -1;
	}
	printf("UHYVE is succesfully connected with %s\n", dev);
	return fd;
}

//---------------------------------- SET MAC ----------------------------------------------//

int set_ip() {
	int ip_is_set = 0;
	char* str = getenv("HERMIT_NETIF_IP");
	if (str)
	{
		const char *ipptr = str;
		const char *v_ipptr = ipptr;
		// checking str is a valid IP address
		int i = 0, s = 0;
		while(*v_ipptr) {
			if (isdigit(*v_ipptr)) {
				i = 1 ;
			} else if (i == 1 && *v_ipptr == '.') {
				s++;
				i = 0;
			} else {
				s = -1;
			}
			v_ipptr++;
		}
		if (i != 1 && s != 3) {
			warnx("Malformed ip address: %s\n", ipptr);
		} else {
			snprintf(netinfo.ip_str, sizeof(netinfo.ip_str), "%s", ipptr);
		}
	}
	if (!ip_is_set) {
		snprintf(netinfo.ip_str, sizeof(netinfo.mac_str), "%d.%d.%d.%d",
			 guest_ip[0], guest_ip[1], guest_ip[2],guest_ip[3]);
	}
	printf("IP address: %s\n", netinfo.ip_str);
	return 0;
}

int set_mac() {
	int mac_is_set = 0;
	uint8_t guest_mac[6];
	char* str = getenv("HERMIT_NETIF_MAC");
	if (str)
	{
		const char *macptr = str;
		const char *v_macptr = macptr;
		// checking str is a valid MAC address
		int i = 0;
		int s = 0;
		while(*v_macptr) {
			if(isxdigit(*v_macptr)) {
				i++;
			} else if (*v_macptr == ':') {
				if (i /2 - 1 != s++ )
					break;
			} else {
				s = -1;
			}
			v_macptr++;
		}
		if (i != 12 || s != 5) {
			warnx("Malformed mac address: %s\n", macptr);
		} else {
			snprintf(netinfo.mac_str, sizeof(netinfo.mac_str), "%s", macptr);
			mac_is_set = 1;
		}
	}

	if (!mac_is_set) {
		int rfd = open("/dev/urandom", O_RDONLY);
		if(rfd == -1)
			err(1, "Could not open /dev/urandom\n");
		int ret;
		ret = read(rfd, guest_mac, sizeof(guest_mac));
		// compare the number of bytes read with the size of guest_mac
		assert(ret == sizeof(guest_mac));
		close(rfd);

		guest_mac[0] &= 0xfe;	// creats a random MAC-address in the locally administered
		guest_mac[0] |= 0x02;	// address range which can be used without conflict with other public devices
		// save the MAC address in the netinfo
		// TODO2: save the MAC-address in the netinfo array for more netifs
		snprintf(netinfo.mac_str, sizeof(netinfo.mac_str),
			 "%02x:%02x:%02x:%02x:%02x:%02x",
	                 guest_mac[0], guest_mac[1], guest_mac[2],
			 guest_mac[3], guest_mac[4], guest_mac[5]);
		// TODO4: overwrite MAC-address, if MAC-address is given as argument or chechk before random MAC-address is generated
	}
	printf("MAC-address: %s\n", netinfo.mac_str);
	return 0;
}
//-------------------------------------- SETUP NETWORK ---------------------------------------------//
static int setup_network(int vcpufd, uint8_t *mem, char *hermit_netif)
{
	//LOG_INFO("Setting up UHYVE_NET interface");
	// TODO2: write an while loop for attaching more than one netif, which changes are necessary in uhyve.c?
	//	  how can we get more devices via HERMIT_NETIF? while loop in uhyve.c, which calls setup_network
	//	  for each netif, so we have not to change anything in this function.
	netif = hermit_netif;

        // TODO3: strncmp for different network interfaces for example tun/tap device or uhyvetap device
	// useful if? setup network is only called is HERMTI_NETIF is set
	if (netif == NULL) {
		err(1, "ERROR: no netif defined\n");
		return -1;
	}
	// attaching netif
	// TODO2: write an while loop for attaching more than one netif (necessary? see first Point of TODO2)
	// We compare only 9 chars of the string, so we can give the interfaces names like uhyve_net0
	// So we can create more than one interface
	if (strncmp("uhyve_net", netif, 9)) {
		//LOG_INFO("Attaching to host tap device %s (needs existing tap device)", netif);
		netfd = attach_linux_tap(netif);
	} else {
		// TODO5: write a uhyve_net function, which does not need sudo rights (tap)
		//LOG_INFO("Attaching to uhyve_tap %s", netif);
		printf("netfd = attach_uhyve_net(netif);");
	}
	if (netfd < 0) {
		err(1, "Could not attach interface: %s\n", netif);
		exit(1);
	}
//	printf("netfd: %i\n", netfd);
	set_mac();
	set_ip();
	//LOG_INFO("UHYVE_NET has MAC: %s", netinfo.mac_str);
	return netfd;
}
