/* 
 * Copyright (c) 2015-2017 Contributors as noted in the AUTHORS file
 *
 * This file is part of Solo5, a unikernel base layer.
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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <unistd.h>

#define ETHERTYPE_IP	0x0800
#define ETHERTYPE_ARP	0x0806
#define	HLEN_ETHER	6
#define PLEN_IPV4	4
#define WAIT_TIME	1
#define MAX_WAIT_TIME	1000
#define PING_LIMIT	50

typedef struct {
	uint8_t target[HLEN_ETHER];
	uint8_t source[HLEN_ETHER];
	uint16_t type;
} ether_t;

typedef struct {
	uint16_t htype;
	uint16_t ptype;
	uint8_t hlen;
	uint8_t plen;
	uint16_t op;
	uint8_t sha[HLEN_ETHER];	//Source Header Address
	uint8_t spa[PLEN_IPV4];		
	uint8_t tha[HLEN_ETHER];	//Target Header Address
	uint8_t tpa[PLEN_IPV4];
} arp_t;

typedef struct {
	uint8_t version_ihl;
	uint8_t type;
	uint16_t length;
	uint16_t id;
	uint16_t flags_offset;
	uint8_t ttl;
	uint8_t proto;
	uint16_t checksum;
	uint8_t src_ip[PLEN_IPV4];
	uint8_t dst_ip[PLEN_IPV4];
} ip_t;

typedef struct {
	uint8_t type;
	uint8_t code;
	uint16_t checksum;
	uint16_t id;
	uint16_t seqnum;
	uint8_t data[0];
} ping_t;

typedef struct {
	ether_t ether;
	arp_t arp;
} arppkt_t;

typedef struct {
	ether_t ether;
	ip_t ip;
	ping_t ping;
} pingpkt_t;

static uint8_t buf[1526];
uint8_t ipaddr[4] = { 0x0a, 0x00, 0x05, 0x02 };		//  10.  0.  5.  2
uint8_t ipaddr_brdnet[4] = { 0x0a, 0x00, 0x05, 0xff };	//  10.  0.  5.255
uint8_t ipaddr_brdall[4] = { 0xff, 0xff, 0xff, 0xff };	// 255.255.255.255
uint8_t macaddr[HLEN_ETHER];
uint8_t macaddr_brd[HLEN_ETHER] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

//--------------------------- checksum ------------------------------//

/* Copied from https://tools.ietf.org/html/rfc1071 */
static uint16_t checksum(uint16_t *addr, size_t count)
{
    /* Compute Internet Checksum for "count" bytes
     * beginning at location "addr".*/
    register long sum = 0;

    while (count > 1)  {
        /*  This is the inner loop */
        sum += * (unsigned short *) addr++;
        count -= 2;
    }

    /* Add left-over byte, if any */
    if (count > 0)
        sum += * (unsigned char *) addr;

    /* Fold 32-bit sum to 16 bits */
    while (sum >> 16)
        sum = (sum & 0xffff) + (sum >> 16);

    return ~sum;
}

//--------------------------- dehex ---------------------------------//

static uint8_t dehex(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return 10 + (c - 'a');
	else if (c >= 'A' && c <= 'F')
		return 10 + (c - 'A');
	else
		return 0;
}

//--------------------------- htons ---------------------------------//
static uint16_t htons(uint16_t x)
{
	return (x << 8) + (x >> 8);
}
//--------------------------- handle ip -----------------------------//
handle_ip(uint8_t *buf) {
	pingpkt_t *p = (pingpkt_t *) buf;
	if (p->ip.version_ihl != 0x45)
		return 11;
	if (p->ip.type != 0x00)
		return 12;
	if (p->ip.proto != 0x01)
		return 13; // not ICMP
	if (memcmp(p->ip.dst_ip, ipaddr, PLEN_IPV4) &&
	    memcmp(p->ip.dst_ip, ipaddr_brdnet, PLEN_IPV4) &&
	    memcmp(p->ip.dst_ip, ipaddr_brdall, PLEN_IPV4))
		return 14; // not ip adressed to us
	if (p->ping.type != 0x08)
		return 15; // not an echo request
	if (p->ping.code != 0x00)
		return 16;
	// reorder ether net header addresses
	memcpy(p->ether.target, p->ether.source, HLEN_ETHER);
	memcpy(p->ether.source, macaddr, HLEN_ETHER);

	p->ip.id = 0;
	p->ip.flags_offset = 0;

	// reorder ip net header addresses
	memcpy(p->ip.dst_ip, p->ip.src_ip, PLEN_IPV4);
	memcpy(p->ip.src_ip, ipaddr, PLEN_IPV4);

	// recalculate ip checksum for return pkt
	p->ip.checksum = 0;
	p->ip.checksum = checksum((uint16_t *) &p->ip, sizeof(ip_t));

	p->ping.type = 0x0; // change into reply

	p->ping.checksum = 0;
	p->ping.checksum = checksum((uint16_t *) &p->ping, htons(p->ip.length) - sizeof(ip_t));
	return 0;
}

//--------------------------- handle arp ----------------------------//
handle_arp(uint8_t *buf) {
	arppkt_t *p = (arppkt_t *)buf;
	if (p->arp.htype != htons(1))
		return 21;
	if (p->arp.ptype != htons(ETHERTYPE_IP))
		return 22;
	if (p->arp.hlen != HLEN_ETHER || p->arp.plen != PLEN_IPV4)
		return 23;
	if (p->arp.op != htons(1))
		return 24;
	if (memcmp(p->arp.tpa, ipaddr, PLEN_IPV4))
		return 25;
	// reorder ether net header addresses
	memcpy(p->ether.target, p->ether.source, HLEN_ETHER);
	memcpy(p->ether.source, macaddr, HLEN_ETHER);
	memcpy(p->arp.tha, p->arp.sha, HLEN_ETHER);
	memcpy(p->arp.sha, macaddr, HLEN_ETHER);
	// request -> reply
	p->arp.op = htons(2);
	// spa -> tpa
	memcpy(p->arp.tpa, p->arp.spa, PLEN_IPV4);
	// our ip -> spa
	memcpy(p->arp.spa, ipaddr, PLEN_IPV4);
	return 0;
}

//--------------------------- send garp -----------------------------//
static void send_garp(void)
{
	arppkt_t p;
	uint8_t zero[HLEN_ETHER] = { 0 };

	// Send gratuitous ARP packet announcing our MAC address
	memcpy(p.ether.source, macaddr, HLEN_ETHER);
	memcpy(p.ether.target, macaddr_brd, HLEN_ETHER);
	p.ether.type = htons(ETHERTYPE_ARP);
	p.arp.htype = htons(1);
	p.arp.ptype = htons(ETHERTYPE_IP);
	p.arp.hlen = HLEN_ETHER;
	p.arp.plen = PLEN_IPV4;
	p.arp.op = htons(1);
	memcpy(p.arp.sha, macaddr, HLEN_ETHER);
	memcpy(p.arp.tha, zero, HLEN_ETHER);
	memcpy(p.arp.spa, ipaddr, PLEN_IPV4);
	memcpy(p.arp.tpa, ipaddr, PLEN_IPV4);

	if(hermit_net_write_sync((uint8_t *)&p, sizeof(p)) == -1)
		puts("Could not send GARP packet\n");
}

//--------------------------- ping serve ----------------------------//

static void ping_serve(int verbose, int limit)
{
	unsigned long received = 0;

	char *hermit_mac = hermit_net_mac_str();

	for (int i = 0; i < HLEN_ETHER; i++) {			// for example first 3 elemts are D7:
		macaddr[i] = dehex(*hermit_mac++) << 4;		// D = 1101 =>  11010000 = D0 (left shift with 4)
		macaddr[i] |= dehex(*hermit_mac++);		// 7 =    	00000111 =  7
		hermit_mac++;					// with |=	11010111 = D7
	}							// with ++ : is ignored and the next elemts will bestored in i+1

	printf("Serving max. %i pings, with MAC: %s\n", limit, hermit_net_mac_str());
	printf("Sending gratuitous ARP packet.\n");
	send_garp();

	for(;;) {
		ether_t *p = (ether_t *)&buf;
		int len = sizeof(buf);
		int i = 0;
		int border = MAX_WAIT_TIME/WAIT_TIME;
		while(hermit_net_read_sync(buf, &len) != 0 && i < border) {
			timer_wait(WAIT_TIME);
			i++;
		}
		if (i >= border) {
//			printf("No packet received\n");
			continue;
		}
		if (memcmp(p->target, macaddr, HLEN_ETHER) && memcmp(p->target, macaddr_brd, HLEN_ETHER))
			continue;
		int errornum = 0;
		switch (htons(p->type)) {
			case ETHERTYPE_ARP:
				if((errornum = handle_arp(buf)) != 0)
					goto out;
				if(verbose)
					printf("Received arp request, sending reply\n");
				break;
			case ETHERTYPE_IP:
				if((errornum = handle_ip(buf)) != 0)
					goto out;
				if(verbose)
					printf("Received ping, sending reply\n");
				break;
			default:
				goto out;
		}
		if (hermit_net_write_sync(buf, len) == -1)
			printf("Write error\n");
		received++;
		if (received > limit) {
			printf("Limit reached, exiting\n");
			break;
		}

		continue;

		out:
			printf("Received non-ping or unsupported packet, dropped. ERROR: %i\n", errornum);
	}

}

//--------------------------- main ----------------------------------//
int main(int argc, char** argv) 
{
	int verbose = 1;
	int limit = PING_LIMIT;

	printf("\n=====================\n");
	printf("HermitCore ping serve\n");

	if (0) {
		// TODO1: check arguments to set or unset verbose and limit
		// first wie will work with predefined verbose and limit
	}

	ping_serve(verbose, limit);

	printf("SUCCESS!\n");
	printf("=====================\n");

	return 1;
}
