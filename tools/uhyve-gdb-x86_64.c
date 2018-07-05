/*
 * This file was adapted from the solo5/ukvm code base, initial copyright block
 * follows:
 */

/*
 * Copyright (c) 2015-2017 Contributors as noted in the AUTHORS file
 *
 * This file is part of ukvm, a unikernel monitor.
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

/*
 * Based on binutils-gdb/gdb/stubs/i386-stub.c, which is:
 * Not copyrighted.
 */

#ifdef __x86_64__
#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <err.h>
#include <inttypes.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>
#include <linux/kvm.h>

#include "uhyve.h"
#include "uhyve-gdb.h"
#include "queue.h"

struct breakpoint_t {
	gdb_breakpoint_type type;
	uint64_t addr;
	size_t len;
	uint32_t refcount;
	uint8_t saved_insn;	/* for software breakpoints */

	SLIST_ENTRY(breakpoint_t) entries;
};

SLIST_HEAD(breakpoints_head, breakpoint_t);
static struct breakpoints_head sw_breakpoints;
static struct breakpoints_head hw_breakpoints;

/* The Intel SDM specifies that the DR7 has space for 4 breakpoints. */
#define MAX_HW_BREAKPOINTS             4
static uint32_t nr_hw_breakpoints = 0;

/* Stepping is disabled by default. */
static bool stepping = false;
/* This is the trap instruction used for software breakpoints. */
static const uint8_t int3 = 0xcc;

static int socket_fd = 0;
static int portno = 1234;	/* Default port number */
static const char hexchars[] = "0123456789abcdef";

#define BUFMAX                         4096
static char in_buffer[BUFMAX];
static unsigned char registers[BUFMAX];

/* uhyve variables */
extern size_t guest_size;
extern uint8_t *guest_mem;

void *uhyve_checked_gpa_p(uint64_t gpa, size_t sz, uint8_t * chk_guest_mem,
			  size_t chk_guest_size, const char *file, int line);

/* The actual error code is ignored by GDB, so any number will do. */
#define GDB_ERROR_MSG                  "E01"

static int hex(unsigned char ch)
{
	if ((ch >= 'a') && (ch <= 'f'))
		return (ch - 'a' + 10);
	if ((ch >= '0') && (ch <= '9'))
		return (ch - '0');
	if ((ch >= 'A') && (ch <= 'F'))
		return (ch - 'A' + 10);

	return -1;
}

/*
 * Converts the (count) bytes of memory pointed to by mem into an hex string in
 * buf. Returns a pointer to the last char put in buf (null).
 */
static char *mem2hex(const unsigned char *mem, char *buf, size_t count)
{
	size_t i;
	unsigned char ch;

	for (i = 0; i < count; i++) {
		ch = *mem++;
		*buf++ = hexchars[ch >> 4];
		*buf++ = hexchars[ch % 16];
	}
	*buf = 0;
	return buf;
}

/*
 * Converts the hex string in buf into binary in mem.
 * Returns a pointer to the character AFTER the last byte written.
 */
static unsigned char *hex2mem(const char *buf, unsigned char *mem, size_t count)
{
	size_t i;
	unsigned char ch;

	assert(strlen(buf) >= (2 * count));

	for (i = 0; i < count; i++) {
		ch = hex(*buf++) << 4;
		ch = ch + hex(*buf++);
		*mem++ = ch;
	}
	return mem;
}

static int wait_for_connect(void)
{
	int listen_socket_fd;
	struct sockaddr_in server_addr, client_addr;
	struct protoent *protoent;
	struct in_addr ip_addr;
	socklen_t len;
	int opt;

	listen_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_socket_fd == -1) {
		err(1, "Could not create socket");
		return -1;
	}

	opt = 1;
	if (setsockopt(listen_socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		err(1, "setsockopt(SO_REUSEADDR) failed");

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(portno);

	if (bind(listen_socket_fd, (struct sockaddr *)&server_addr,
		 sizeof(server_addr)) == -1) {
		err(1, "bind failed");
		return -1;
	}

	if (listen(listen_socket_fd, 0) == -1) {
		err(1, "listen failed");
		return -1;
	}

	warnx("Waiting for a debugger. Connect to it like this:");
	warnx("\tgdb --ex=\"target remote localhost:%d\" UNIKERNEL", portno);

	len = sizeof(client_addr);
	socket_fd =
	    accept(listen_socket_fd, (struct sockaddr *)&client_addr, &len);
	if (socket_fd == -1) {
		err(1, "accept failed");
		return -1;
	}

	close(listen_socket_fd);

	protoent = getprotobyname("tcp");
	if (!protoent) {
		err(1, "getprotobyname (\"tcp\") failed");
		return -1;
	}

	opt = 1;
	if (setsockopt(socket_fd, protoent->p_proto, TCP_NODELAY, &opt,
		       sizeof(opt)) == -1)
		err(1, "setsockopt(TCP_NODELAY) failed");

	ip_addr.s_addr = client_addr.sin_addr.s_addr;
	warnx("Connection from debugger at %s", inet_ntoa(ip_addr));

	return 0;
}

static inline int send_char(char ch)
{
	/* TCP is already buffering, so no need to buffer here as well. */
	return send(socket_fd, &ch, 1, 0);
}

static char recv_char(void)
{
	unsigned char ch;
	int ret;

	ret = recv(socket_fd, &ch, 1, 0);
	if (ret < 0) {
		return -1;
	} else if (ret == 0) {
		/* The peer has performed an orderly shutdown (from "man recv"). */
		warnx("GDB: Connection closed from client");
		close(socket_fd);
		socket_fd = -1;
		return -1;
	} else {
		assert(ret == 1);
	}

	/* All GDB remote packets are encoded in ASCII. */
	assert(isascii(ch));

	return (char)ch;
}

/*
 * Scan for the sequence $<data>#<checksum>
 * Returns a null terminated string.
 */
static char *recv_packet(void)
{
	char *buffer = &in_buffer[0];
	unsigned char checksum;
	unsigned char xmitcsum;
	char ch;
	int count;

	while (1) {
		/* wait around for the start character, ignore all other characters */
		do {
			ch = recv_char();
			if (ch == -1)
				return NULL;
		}
		while (ch != '$');

 retry:
		checksum = 0;
		xmitcsum = -1;
		count = 0;

		/* now, read until a # or end of buffer is found */
		while (count < BUFMAX - 1) {
			ch = recv_char();
			if (ch == -1)
				return NULL;
			if (ch == '$')
				goto retry;
			if (ch == '#')
				break;
			checksum = checksum + ch;
			buffer[count] = ch;
			count = count + 1;
		}
		/* Let's make this a C string. */
		buffer[count] = '\0';

		if (ch == '#') {
			ch = recv_char();
			if (ch == -1)
				return NULL;
			xmitcsum = hex(ch) << 4;
			ch = recv_char();
			if (ch == -1)
				return NULL;
			xmitcsum += hex(ch);

			if (checksum != xmitcsum) {
				warnx("Failed checksum from GDB. "
				      "My count = 0x%x, sent=0x%x. buf=%s",
				      checksum, xmitcsum, buffer);
				if (send_char('-') == -1)
					/* Unsuccessful reply to a failed checksum */
					err(1,
					    "GDB: Could not send an ACK to the debugger.");
			} else {
				if (send_char('+') == -1)
					/* Unsuccessful reply to a successful transfer */
					err(1,
					    "GDB: Could not send an ACK to the debugger.");

				/* if a sequence char is present, reply the sequence ID */
				if (buffer[2] == ':') {
					send_char(buffer[0]);
					send_char(buffer[1]);

					return &buffer[3];
				}

				return &buffer[0];
			}
		}
	}
}

/*
 * Send packet of the form $<packet info>#<checksum> without waiting for an ACK
 * from the debugger. Only send_response
 */
static void send_packet_no_ack(char *buffer)
{
	unsigned char checksum;
	int count;
	char ch;

	/*
	 * We ignore all send_char errors as we either: (1) care about sending our
	 * packet and we will keep sending it until we get a good ACK from the
	 * debugger, or (2) not care and just send it as a best-effort notification
	 * when dying.
	 */

	send_char('$');
	checksum = 0;
	count = 0;

	ch = buffer[count];
	while (ch) {
		send_char(ch);
		checksum += ch;
		count += 1;
		ch = buffer[count];
	}

	send_char('#');
	send_char(hexchars[checksum >> 4]);
	send_char(hexchars[checksum % 16]);
}

/*
 * Send a packet and wait for a successful ACK of '+' from the debugger.
 * An ACK of '-' means that we have to resend.
 */
static void send_packet(char *buffer)
{
	char ch;

	for (;;) {
		send_packet_no_ack(buffer);
		ch = recv_char();
		if (ch == -1)
			return;
		if (ch == '+')
			break;
	}
}

#define send_error_msg()   do { send_packet(GDB_ERROR_MSG); } while (0)

#define send_not_supported_msg()   do { send_packet(""); } while (0)

#define send_okay_msg()   do { send_packet("OK"); } while (0)

/*
 * This is a response to 'c' and 's'. In other words, the VM was
 * running and it stopped for some reason. This message is to tell the
 * debugger that whe stopped (and why). The argument code can take these
 * and some other values:
 *    - 'S AA' received signal AA
 *    - 'W AA' exited with return code AA
 *    - 'X AA' exited with signal AA
 * https://sourceware.org/gdb/onlinedocs/gdb/Stop-Reply-Packets.html
 */
static void send_response(char code, int sigval, bool wait_for_ack)
{
	char obuf[BUFMAX];
	snprintf(obuf, sizeof(obuf), "%c%02x", code, sigval);
	if (wait_for_ack)
		send_packet(obuf);
	else
		send_packet_no_ack(obuf);
}

static void gdb_handle_exception(int vcpufd, int sigval)
{
	char *packet;
	char obuf[BUFMAX];

	/* Notify the debugger of our last signal */
	send_response('S', sigval, true);

	for (;;) {
		uint64_t addr = 0, result;
		gdb_breakpoint_type type;
		size_t len;
		int command, ret;

		packet = recv_packet();
		if (packet == NULL)
			/* Without a packet with instructions with what to do next there is
			 * really nothing we can do to recover. So, dying. */
			errx(1,
			     "GDB: Exiting as we could not receive the next command from "
			     "the debugger.");

		/*
		 * From the GDB manual:
		 * "At a minimum, a stub is required to support the ‘g’ and ‘G’
		 * commands for register access, and the ‘m’ and ‘M’ commands
		 * for memory access. Stubs that only control single-threaded
		 * targets can implement run control with the ‘c’ (continue),
		 * and ‘s’ (step) commands."
		 */
		command = packet[0];
		switch (command) {
		case 's':
			{
				/* Step */
				if (sscanf(packet, "s%" PRIx64, &addr) == 1) {
					/* not supported, but that's OK as GDB will retry with the
					 * slower version of this: update all registers. */
					send_not_supported_msg();
					break;	/* Wait for another command. */
				}
				if (uhyve_gdb_enable_ss(vcpufd) == -1) {
					send_error_msg();
					break;	/* Wait for another command. */
				}
				return;	/* Continue with program */
			}

		case 'c':
			{
				/* Continue (and disable stepping for the next instruction) */
				if (sscanf(packet, "c%" PRIx64, &addr) == 1) {
					/* not supported, but that's OK as GDB will retry with the
					 * slower version of this: update all registers. */
					send_not_supported_msg();
					break;	/* Wait for another command. */
				}
				if (uhyve_gdb_disable_ss(vcpufd) == -1) {
					send_error_msg();
					break;	/* Wait for another command. */
				}
				return;	/* Continue with program */
			}

		case 'm':
			{
				/* Read memory content */
				if (sscanf(packet, "m%" PRIx64 ",%zx", &addr, &len) != 2) {
					send_error_msg();
					break;
				}
				/* translate addr into guest phys first. it is
				 * needed if the address falls into the non directly mapped
				 * part of the virtual address space (ex: heap/stack) */
				uint64_t phys_addr;

				if (uhyve_gdb_guest_virt_to_phys(vcpufd, addr, &phys_addr)) {
					send_error_msg();
				} else {
					mem2hex(guest_mem + phys_addr, obuf, len);
					send_packet(obuf);
				}
				break;	/* Wait for another command. */
			}

		case 'M':
			{
				/* Write memory content */
				uint64_t phys_addr;

				assert(strlen(packet) <= sizeof(obuf));
				if (sscanf(packet, "M%" PRIx64 ",%zx:%s", &addr, &len, obuf) != 3) {
					send_error_msg();
					break;
				}

				/* translate to guest physical address first */
				if (uhyve_gdb_guest_virt_to_phys(vcpufd, addr, &phys_addr)) {
					send_error_msg();
				} else {
					hex2mem(obuf, guest_mem + phys_addr,
						len);
					send_okay_msg();
				}
				break;	/* Wait for another command. */
			}

		case 'g':
			{
				/* Read general registers */
				len = BUFMAX;
				if (uhyve_gdb_read_registers(vcpufd, registers, &len) == -1) {
					send_error_msg();
				} else {
					mem2hex(registers, obuf, len);
					send_packet(obuf);
				}
				break;	/* Wait for another command. */
			}

		case 'G':
			{
				/* Write general registers */
				len = BUFMAX;
				/* Call read_registers just to get len (not very efficient). */
				if (uhyve_gdb_read_registers(vcpufd, registers, &len) == -1) {
					send_error_msg();
					break;
				}
				/* Packet looks like 'Gxxxxx', so we have to skip the first char */
				hex2mem(packet + 1, registers, len);
				if (uhyve_gdb_write_registers
				    (vcpufd, registers, len) == -1) {
					send_error_msg();
					break;
				}
				send_okay_msg();
				break;	/* Wait for another command. */
			}

		case '?':
			{
				/* Return last signal */
				send_response('S', sigval, true);
				break;	/* Wait for another command. */
			}

		case 'Z':
			/* Insert a breakpoint */
		case 'z':
			{
				/* Remove a breakpoint */
				packet++;
				if (sscanf
				    (packet, "%" PRIx32 ",%" PRIx64 ",%zx",
				     &type, &addr, &len) != 3) {
					send_error_msg();
					break;
				}
				uint64_t phys_addr;
				if (uhyve_gdb_guest_virt_to_phys
				    (vcpufd, addr, &phys_addr)) {
					send_error_msg();
				} else {
					if (command == 'Z')
						ret =
						    uhyve_gdb_add_breakpoint
						    (vcpufd, type, phys_addr,
						     len);
					else
						ret =
						    uhyve_gdb_remove_breakpoint
						    (vcpufd, type, phys_addr,
						     len);

					if (ret == -1)
						send_error_msg();
					else
						send_okay_msg();
				}
				break;
			}

		case 'k':
			{
				warnx("Debugger asked us to quit");
				send_okay_msg();
				break;
			}

		case 'D':
			{
				warnx("Debugger detached");
				send_okay_msg();
				return;
			}

		default:
			send_not_supported_msg();
			break;
		}
	}
}

void uhyve_gdb_handle_exception(int vcpufd, int sigval)
{
	gdb_handle_exception(vcpufd, sigval);
}

static void gdb_stub_start(int vcpufd)
{
	wait_for_connect();
	gdb_handle_exception(vcpufd, GDB_SIGNAL_FIRST);
}

int uhyve_gdb_init(int vcpufd)
{
	/*
	 * GDB clients can change memory, and software breakpoints work by
	 * replacing instructions with int3's.
	 */
	if (mprotect(guest_mem, guest_size,
		     PROT_READ | PROT_WRITE | PROT_EXEC) == -1)
		err(1, "GDB: Cannot remove guest memory protection");

	/* Notify the debugger that we are dying. */
	atexit(uhyve_gdb_handle_term);

	gdb_stub_start(vcpufd);

	return 0;
}

void uhyve_gdb_handle_term(void)
{
	/* TODO: this is graceful shutdown forcing the return value to zero,
	 * any way to pass an error code when things go wrong ? */
	send_response('W', 0, true);
}

static int kvm_arch_insert_sw_breakpoint(struct breakpoint_t *bp)
{
	uint8_t *insn = bp->addr + guest_mem;
	bp->saved_insn = *insn;
	/*
	 * We just modify the first byte even if the instruction is multi-byte.
	 * The debugger keeps track of the length of the instruction. The
	 * consequence of this is that we don't have to set all other bytes as
	 * NOP's.
	 */
	*insn = int3;
	return 0;
}

static int kvm_arch_remove_sw_breakpoint(struct breakpoint_t *bp)
{
	uint8_t *insn = bp->addr + guest_mem;
	assert(*insn == int3);
	*insn = bp->saved_insn;
	return 0;
}

static int uhyve_gdb_update_guest_debug(int vcpufd)
{
	struct kvm_guest_debug dbg = { 0 };
	struct breakpoint_t *bp;
	const uint8_t type_code[] = {
		/* Break on instruction execution only. */
		[GDB_BREAKPOINT_HW] = 0x0,
		/* Break on data writes only. */
		[GDB_WATCHPOINT_WRITE] = 0x1,
		/* Break on data reads only. */
		[GDB_WATCHPOINT_READ] = 0x2,
		/* Break on data reads or writes but not instruction fetches. */
		[GDB_WATCHPOINT_ACCESS] = 0x3
	};
	const uint8_t len_code[] = {
		/*
		 * 00 — 1-byte length.
		 * 01 — 2-byte length.
		 * 10 — 8-byte length.
		 * 11 — 4-byte length.
		 */
		[1] = 0x0,[2] = 0x1,[4] = 0x3,[8] = 0x2
	};
	int n = 0;

	if (stepping)
		dbg.control = KVM_GUESTDBG_ENABLE | KVM_GUESTDBG_SINGLESTEP;

	if (!SLIST_EMPTY(&sw_breakpoints))
		dbg.control |= KVM_GUESTDBG_ENABLE | KVM_GUESTDBG_USE_SW_BP;

	if (!SLIST_EMPTY(&hw_breakpoints)) {
		dbg.control |= KVM_GUESTDBG_ENABLE | KVM_GUESTDBG_USE_HW_BP;

		/* Enable global breakpointing (across all threads) on the control
		 * debug register. */
		dbg.arch.debugreg[7] = 1 << 9;
		dbg.arch.debugreg[7] |= 1 << 10;
		SLIST_FOREACH(bp, &hw_breakpoints, entries) {
			assert(bp->type != GDB_BREAKPOINT_SW);
			dbg.arch.debugreg[n] = bp->addr;
			/* global breakpointing */
			dbg.arch.debugreg[7] |= (2 << (n * 2));
			/* read/write fields */
			dbg.arch.debugreg[7] |=
			    (type_code[bp->type] << (16 + n * 4));
			/* Length fields */
			dbg.arch.debugreg[7] |=
			    ((uint32_t) len_code[bp->len] << (18 + n * 4));
			n++;
		}
	}

	kvm_ioctl(vcpufd, KVM_SET_GUEST_DEBUG, &dbg);

	return 0;
}

static struct breakpoint_t *bp_list_find(gdb_breakpoint_type type,
					 uint64_t addr, size_t len)
{
	struct breakpoint_t *bp;

	switch (type) {
	case GDB_BREAKPOINT_SW:
		SLIST_FOREACH(bp, &sw_breakpoints, entries) {
			if (bp->addr == addr && bp->len == len)
				return bp;
		}
		break;

	case GDB_BREAKPOINT_HW:
	case GDB_WATCHPOINT_WRITE:
	case GDB_WATCHPOINT_READ:
	case GDB_WATCHPOINT_ACCESS:
		/* We only support hardware watchpoints. */
		SLIST_FOREACH(bp, &hw_breakpoints, entries) {
			if (bp->addr == addr && bp->len == len)
				return bp;
		}
		break;

	default:
		assert(0);
	}

	return NULL;
}

/*
 * Adds a new breakpoint to the list of breakpoints.  Returns the found or
 * created breakpoint. Returns NULL in case of failure or if we reached the max
 * number of allowed hardware breakpoints (4).
 */
static struct breakpoint_t *bp_list_insert(gdb_breakpoint_type type,
					   uint64_t addr, size_t len)
{
	struct breakpoint_t *bp;

	bp = bp_list_find(type, addr, len);
	if (bp) {
		bp->refcount++;
		return bp;
	}

	bp = malloc(sizeof(struct breakpoint_t));
	if (bp == NULL)
		return NULL;

	bp->addr = addr;
	bp->type = type;
	bp->len = len;
	bp->refcount = 1;

	switch (type) {
	case GDB_BREAKPOINT_SW:
		SLIST_INSERT_HEAD(&sw_breakpoints, bp, entries);
		break;

	case GDB_BREAKPOINT_HW:
	case GDB_WATCHPOINT_WRITE:
	case GDB_WATCHPOINT_READ:
	case GDB_WATCHPOINT_ACCESS:
		/* We only support hardware watchpoints. */
		if (nr_hw_breakpoints == MAX_HW_BREAKPOINTS)
			return NULL;
		nr_hw_breakpoints++;
		SLIST_INSERT_HEAD(&hw_breakpoints, bp, entries);
		break;

	default:
		assert(0);
	}

	return bp;
}

/*
 * Removes a breakpoint from the list of breakpoints.
 * Returns -1 if the breakpoint is not in the list.
 */
static int bp_list_remove(gdb_breakpoint_type type, uint64_t addr, size_t len)
{
	struct breakpoint_t *bp = NULL;

	bp = bp_list_find(type, addr, len);
	if (!bp)
		return -1;

	bp->refcount--;
	if (bp->refcount > 0)
		return 0;

	switch (type) {
	case GDB_BREAKPOINT_SW:
		SLIST_REMOVE(&sw_breakpoints, bp, breakpoint_t, entries);
		break;

	case GDB_BREAKPOINT_HW:
	case GDB_WATCHPOINT_WRITE:
	case GDB_WATCHPOINT_READ:
	case GDB_WATCHPOINT_ACCESS:
		/* We only support hardware watchpoints. */
		SLIST_REMOVE(&hw_breakpoints, bp, breakpoint_t, entries);
		nr_hw_breakpoints--;
		break;

	default:
		assert(0);
	}

	free(bp);

	return 0;
}

int uhyve_gdb_read_registers(int vcpufd, uint8_t * registers, size_t * len)
{
	struct kvm_regs kregs;
	struct kvm_sregs sregs;
	struct uhyve_gdb_regs *gregs = (struct uhyve_gdb_regs *)registers;
	int ret;

	kvm_ioctl(vcpufd, KVM_GET_REGS, &kregs);
	kvm_ioctl(vcpufd, KVM_GET_SREGS, &sregs);

	if (*len < sizeof(struct uhyve_gdb_regs))
		return -1;

	*len = sizeof(struct uhyve_gdb_regs);

	gregs->rax = kregs.rax;
	gregs->rbx = kregs.rbx;
	gregs->rcx = kregs.rcx;
	gregs->rdx = kregs.rdx;

	gregs->rsi = kregs.rsi;
	gregs->rdi = kregs.rdi;
	gregs->rbp = kregs.rbp;
	gregs->rsp = kregs.rsp;

	gregs->r8 = kregs.r8;
	gregs->r9 = kregs.r9;
	gregs->r10 = kregs.r10;
	gregs->r11 = kregs.r11;

	gregs->rip = kregs.rip;
	gregs->eflags = kregs.rflags;

	gregs->cs = sregs.cs.selector;
	gregs->ss = sregs.ss.selector;
	gregs->ds = sregs.ds.selector;
	gregs->es = sregs.es.selector;
	gregs->fs = sregs.fs.selector;
	gregs->gs = sregs.gs.selector;

	return 0;
}

int uhyve_gdb_write_registers(int vcpufd, uint8_t * registers, size_t len)
{
	struct kvm_regs kregs;
	struct kvm_sregs sregs;
	struct uhyve_gdb_regs *gregs = (struct uhyve_gdb_regs *)registers;
	int ret;

	/* Let's read all registers just in case we miss filling one of them. */
	kvm_ioctl(vcpufd, KVM_GET_REGS, &kregs);
	kvm_ioctl(vcpufd, KVM_GET_SREGS, &sregs);

	if (len < sizeof(struct uhyve_gdb_regs))
		return -1;

	kregs.rax = gregs->rax;
	kregs.rbx = gregs->rbx;
	kregs.rcx = gregs->rcx;
	kregs.rdx = gregs->rdx;

	kregs.rsi = gregs->rsi;
	kregs.rdi = gregs->rdi;
	kregs.rbp = gregs->rbp;
	kregs.rsp = gregs->rsp;

	kregs.r8 = gregs->r8;
	kregs.r9 = gregs->r9;
	kregs.r10 = gregs->r10;
	kregs.r11 = gregs->r11;

	kregs.rip = gregs->rip;
	kregs.rflags = gregs->eflags;

	/* XXX: not sure if just setting .selector is enough. */
	sregs.cs.selector = gregs->cs;
	sregs.ss.selector = gregs->ss;
	sregs.ds.selector = gregs->ds;
	sregs.es.selector = gregs->es;
	sregs.fs.selector = gregs->fs;
	sregs.gs.selector = gregs->gs;

	kvm_ioctl(vcpufd, KVM_SET_REGS, &kregs);
	kvm_ioctl(vcpufd, KVM_SET_SREGS, &sregs);

	return 0;
}

int uhyve_gdb_add_breakpoint(int vcpufd, gdb_breakpoint_type type,
	uint64_t addr, size_t len)
{
	struct breakpoint_t *bp;

	assert(type < GDB_BREAKPOINT_MAX);

	if (bp_list_find(type, addr, len))
		return 0;

	bp = bp_list_insert(type, addr, len);
	if (bp == NULL)
		return -1;

	if (type == GDB_BREAKPOINT_SW)
		kvm_arch_insert_sw_breakpoint(bp);

	if (uhyve_gdb_update_guest_debug(vcpufd) == -1)
		return -1;

	return 0;
}

int uhyve_gdb_remove_breakpoint(int vcpufd, gdb_breakpoint_type type,
	uint64_t addr, size_t len)
{
	struct breakpoint_t *bp;

	assert(type < GDB_BREAKPOINT_MAX);

	if (type == GDB_BREAKPOINT_SW) {
		bp = bp_list_find(type, addr, len);
		if (bp)
			kvm_arch_remove_sw_breakpoint(bp);
	}

	if (bp_list_remove(type, addr, len) == -1)
		return -1;

	if (uhyve_gdb_update_guest_debug(vcpufd) == -1)
		return -1;

	return 0;
}

int uhyve_gdb_enable_ss(int vcpufd)
{
	stepping = true;

	if (uhyve_gdb_update_guest_debug(vcpufd) == -1)
		return -1;

	return 0;
}

int uhyve_gdb_disable_ss(int vcpufd)
{
	stepping = false;

	if (uhyve_gdb_update_guest_debug(vcpufd) == -1)
		return -1;

	return 0;
}

/* Convert a guest virtual address into the correspondign physical address */
int uhyve_gdb_guest_virt_to_phys(int vcpufd, const uint64_t virt, uint64_t * phys)
{
	struct kvm_translation kt;

	kt.linear_address = virt;
	kvm_ioctl(vcpufd, KVM_TRANSLATE, &kt);

	*phys = kt.physical_address;
	return 0;
}

#endif
