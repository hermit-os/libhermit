"""Copyright (c) 2018, Annika Wierichs, RWTH Aachen University

All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   * Neither the name of the University nor the names of its contributors
     may be used to endorse or promote products derived from this
     software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
"""

"""
This file contains custom address conversion routines for specific functions
that cannot be generated automatically. If additional functions requiring custom
code are added to the verbs API in future releases, these snippets may be added
here (also add the function name to the list of supported functions).

The code for 3 different post_recv functions can be reused as their parameters
are the same and therefore require the same pointer conversions:
ibv_post_recv    (..., struct ibv_recv_wr* recv_wr, struct ibv_recv_wr** bad_recv_wr)
ibv_post_wq_recv (..., struct ibv_recv_wr* recv_wr, struct ibv_recv_wr** bad_recv_wr)
ibv_post_srq_recv(..., struct ibv_recv_wr* recv_wr, struct ibv_recv_wr** bad_recv_wr)

TODO: These snippets currently use spaces (not tabs) at the start of lines, fix.
"""

supported_functions = ["ibv_post_send",
                       "ibv_post_recv",
                       "ibv_post_srq_recv",
                       "ibv_post_wq_recv",
                       "ibv_create_rwq_ind_table"]

CONVERT = 2
REVERT = 1

#
# ibv_post_recv, ibv_post_srq_recv, ibv_post_wq_recv
#
# (These functions may use the same backup/convert/revert routines in HermitCore since their
#  prototypes are equal.)
#

post_recv_convert = \
"""  struct ibv_recv_wr * curr_wr;
  int num_sges_max;
  int num_wrs;

  // Number of work requests in linked list and SGEs in each WR
  num_wrs = 0;
  num_sges_max = 0;
  for (curr_wr = recv_wr; curr_wr; curr_wr = curr_wr->next) {
    num_wrs++;
    if (num_sges_max < curr_wr->num_sge) {
      num_sges_max = curr_wr->num_sge;
    }
  }

  // Backup arrays for original guest memory pointers
  struct ibv_recv_wr * wr__next         [num_wrs];
  struct ibv_sge *     wr__sg_list      [num_wrs];
  uint64_t             wr__sg_list__addr[num_wrs][num_sges_max];

  curr_wr = recv_wr;
  for (int w = 0; w < num_wrs; w++) {
    // Next pointer
    wr__next[w] = curr_wr->next;
    curr_wr->next = (struct ibv_recv_wr *) guest_to_host((size_t) curr_wr->next);

    // SGE array
    for (int s = 0; s < curr_wr->num_sge; s++) {
      wr__sg_list__addr[w][s] = curr_wr->sg_list[s].addr;
      curr_wr->sg_list[s].addr = (uint64_t) guest_to_host((size_t) curr_wr->sg_list[s].addr);
    }

    wr__sg_list[w] = curr_wr->sg_list;
    curr_wr->sg_list = (struct ibv_sge *) guest_to_host((size_t) curr_wr->sg_list);

    curr_wr = wr__next[w];
  }
"""

post_recv_revert = \
"""  if (*bad_recv_wr && *bad_recv_wr == uhyve_args.recv_wr) {
    *bad_recv_wr = recv_wr;
  }

  curr_wr = recv_wr;
  for (int w = 0; w < num_wrs; w++) {
    if (*bad_recv_wr && *bad_recv_wr == curr_wr->next) {
      *bad_recv_wr = wr__next[w];
    }

    curr_wr->next    = wr__next[w];
    curr_wr->sg_list = wr__sg_list[w];
    for (int s = 0; s < curr_wr->num_sge; s++) {
      curr_wr->sg_list[s].addr = wr__sg_list__addr[w][s];
    }

    curr_wr = curr_wr->next;
  }

"""

#
# ibv_post_send
#

post_send_convert = \
"""  struct ibv_send_wr * curr_wr;
  int num_wrs;
  int num_sges_max;
  int is_bind_mw, is_tso;

  // Number of work requests in linked list and SGEs in each WR
  num_wrs = 0;
  num_sges_max = 0;
  for (curr_wr = wr; curr_wr; curr_wr = curr_wr->next) {
    num_wrs++;
    if (num_sges_max < curr_wr->num_sge) {
      num_sges_max = curr_wr->num_sge;
    }
  }

  // Backup arrays for original guest memory pointers
  struct ibv_send_wr * wr__next                    [num_wrs];
  struct ibv_sge *     wr__sg_list                 [num_wrs];
  uint64_t             wr__sg_list__addr           [num_wrs][num_sges_max];
  uint64_t             wr__bind_mw__bind_info__addr[num_wrs];
  void *               wr__tso__hdr                [num_wrs];

  curr_wr = wr;
  for (int w = 0; w < num_wrs; w++) {
    is_bind_mw = curr_wr->opcode == IBV_WR_BIND_MW;
    is_tso     = curr_wr->opcode == IBV_WR_TSO;

    // union: bind_mw and tso
    if (is_bind_mw) {
      wr__bind_mw__bind_info__addr[w] = curr_wr->bind_mw.bind_info.addr;
      curr_wr->bind_mw.bind_info.addr = (uint64_t) guest_to_host((size_t) curr_wr->bind_mw.bind_info.addr);
    } else if (is_tso) {
      wr__tso__hdr[w] = curr_wr->tso.hdr;
      curr_wr->tso.hdr = (void *) guest_to_host((size_t) curr_wr->tso.hdr);
    }

    // Next pointer and SGE array
    wr__next[w] = curr_wr->next;
    curr_wr->next = (struct ibv_send_wr *) guest_to_host((size_t) curr_wr->next);

    for (int s = 0; s < curr_wr->num_sge; s++) {
      wr__sg_list__addr[w][s] = curr_wr->sg_list[s].addr;
      curr_wr->sg_list[s].addr = (uint64_t) guest_to_host((size_t) curr_wr->sg_list[s].addr);
    }

    wr__sg_list[w] = curr_wr->sg_list;
    curr_wr->sg_list = (struct ibv_sge *) guest_to_host((size_t) curr_wr->sg_list);

    curr_wr = wr__next[w];
  }

"""

post_send_revert = \
"""  if (*bad_wr && *bad_wr == uhyve_args.wr) {
    *bad_wr = wr;
  }

  curr_wr = wr;
  for (int w = 0; w < num_wrs; w++) {
    is_bind_mw = curr_wr->opcode == IBV_WR_BIND_MW;
    is_tso     = curr_wr->opcode == IBV_WR_TSO;

    // union: bind_mw and tso
    if (is_bind_mw) {
       curr_wr->bind_mw.bind_info.addr = wr__bind_mw__bind_info__addr[w];
    } else if (is_tso) {
       curr_wr->tso.hdr = wr__tso__hdr[w];
    }

    // Bad request
    if (*bad_wr && *bad_wr == curr_wr->next) {
      *bad_wr = wr__next[w];
    }

    // Next pointer and SGE array
    curr_wr->next = wr__next[w];
    curr_wr->sg_list = wr__sg_list[w];
    for (int s = 0; s < curr_wr->num_sge; s++) {
      curr_wr->sg_list[s].addr = wr__sg_list__addr[w][s];
    }

    curr_wr = curr_wr->next;
  }

"""

#
# ibv_create_rwq_ind_table
#

create_rwq_ind_table_convert = \
"""  // TODO: Entries of the list should be universal references residing in the IB memory pool.
  // Confirm this.
  struct ibv_wq ** init_attr__ind_tbl = init_attr->ind_tbl;
  init_attr->ind_tbl = (struct ibv_wq **) guest_to_host((size_t) init_attr->ind_tbl);

"""

create_rwq_ind_table_revert = \
"""  init_attr->ind_tbl = init_attr__ind_tbl;

"""

def generate(name, part):
  if name == "ibv_post_send":
    if part == CONVERT:
      return post_send_convert
    else:
      return post_send_revert

  elif name == "ibv_post_wq_recv" or name == "ibv_post_recv" or name == "ibv_post_srq_recv":
    if part == CONVERT:
      return post_recv_convert
    else:
      return post_recv_revert

  elif name == "ibv_create_rwq_ind_table":
    if part == CONVERT:
      return create_rwq_ind_table_convert
    else:
      return create_rwq_ind_table_revert


