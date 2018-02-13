#!/usr/bin/env python
"""Copyright (c) 2017, Annika Wierichs, RWTH Aachen University

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

TODO, docs
"""

# TODO: Add ibv_resolve_eth_l2_from_gid function back in. Not linking right now.
# TODO: void * as well

from __future__ import print_function
from parser import generate_struct_conversions


# Path of the input file containing function prototypes.
SRC_PATH = "function-prototypes.txt"

# Paths of the files that are generated by the script.
KERNEL_GEN_PATH           = "GEN-kernel.c"
KERNEL_HEADER_GEN_PATH    = "GEN-kernel-header.h"
UHYVE_CASES_GEN_PATH      = "GEN-tools-uhyve.c"
UHYVE_IBV_HEADER_GEN_PATH = "GEN-tools-uhyve-ibv-ports.h"
INCLUDE_STDDEF_GEN_PATH   = "GEN-include-hermit-stddef.h"
UHYVE_HOST_FCNS_GEN_PATH  = "GEN-tools-uhyve-ibv.c"

# Starting number of the sequence used for IBV ports.
PORT_NUMBER_START = 0x610

#  VERBS_HEADER_PATH = "verbs-0.h"
#  UHYVE_IBV_HEADER_STRUCTS_GEN_PATH = "GEN-tools-uhyve-ibv-structs.h"

restricted_resources = ["struct ibv_send_wr",
                        "struct ibv_recv_wr",
                        "struct ibv_sge",
                        "struct ibv_xrcd_init_attr",
                        "struct ibv_rwq_ind_table_init_attr",
                        "struct ibv_mw_bind_info",
                        "struct ibv_rx_hash_conf"]

lib_owned_resources = ["struct ibv_pd",
                       "struct ibv_cq",
                       "struct ibv_cq_ex",
                       "struct verbs_context",
                       "struct ibv_device",
                       "struct ibv_context",
                       "struct ibv_context_ops",
                       "struct ibv_flow",
                       "struct ibv_xrcd",
                       "struct ibv_mr",
                       "struct ibv_mw",
                       "struct ibv_comp_channel",
                       "struct ibv_srq",
                       "struct ibv_qp",
                       "struct ibv_wq",
                       "struct ibv_rwq_ind_table",
                       "struct ibv_ah"]

app_owned_resources = restricted_resources + \
                      ["struct ibv_device_attr",
                       "struct ibv_device_attr_ex",
                       "struct ibv_port_attr",
                       "struct ibv_ah_attr",
                       "struct ibv_srq_attr",
                       "struct ibv_wq_attr",
                       "struct ibv_qp_attr",
                       "struct ibv_poll_cq_attr",
                       "struct ibv_flow_attr",
                       "struct ibv_global_route",
                       "struct ibv_packet_pacing_caps",
                       "struct ibv_qp_cap",
                       "struct ibv_odp_caps",
                       "struct ibv_tso_caps",
                       "struct ibv_rss_caps",
                       "struct ibv_flow_eth_filter",
                       "struct ibv_flow_spec_eth",
                       "struct ibv_flow_ipv4_filter",
                       "struct ibv_flow_spec_ipv4",
                       "struct ibv_flow_ipv4_ext_filter",
                       "struct ibv_flow_spec_ipv4_ext",
                       "struct ibv_flow_ipv6_filter",
                       "struct ibv_flow_spec_ipv6",
                       "struct ibv_flow_tcp_udp_filter",
                       "struct ibv_flow_spec_tcp_udp",
                       "struct ibv_flow_tunnel_filter",
                       "struct ibv_flow_spec_tunnel",
                       "struct ibv_flow_spec_action_tag",
                       "struct ibv_flow_spec_action_drop",
                       "struct ibv_query_device_ex_input",
                       "struct ibv_wc",
                       "struct ibv_grh",
                       "struct ibv_mw_bind",
                       "struct ibv_flow_spec",
                       "struct ibv_values_ex",
                       "struct ibv_rwq_ind_table_init_attr",
                       "struct ibv_xrcd_init_attr",

                       # Universal deep resources (contain valid ib_mem_pool pointers):
                       "struct ibv_wq_init_attr",
                       "struct ibv_qp_init_attr",
                       "struct ibv_qp_init_attr_ex",
                       "struct ibv_srq_init_attr_ex",
                       "struct ibv_srq_init_attr",
                       "struct ibv_qp_open_attr",
                       "struct ibv_cq_init_attr_ex",
                       "struct ibv_async_event"]


# int ibv_resolve_eth_l2_from_gid(uint8_t [6] eth_mac,uint16_t * vid)
# struct ibv_device * dev
# int * num_devices
# int ret
# char[NUM]

# ----------------------------------------------------------------------------
# CLASSES
# ----------------------------------------------------------------------------

class Resource:
  def __init__(self, string, is_ret=False):
    if "**" in string:
      string.replace("**", " ** ")
    elif "*" in string:
      string.replace("*", " * ")

    self.components = string.split()
    if is_ret:
      self.components += [""]

    self.full_expression  = " ".join(self.components)
    self.type             = " ".join(self.components[:-1])
    self.name             = self.components[-1]
    self.struct_name      = self.components[1] if self.components[0] is "struct" else ""
    self.type_wo_asterisk = (self.type[:-3] if self.is_ptr_ptr()
                                            else self.type[:-2] if self.is_ptr()
                                                                else self.type)

  def is_struct(self):
    return self.components[0] == "struct"

  def is_ptr(self):
    return "*" in self.full_expression

  def is_ptr_ptr(self):
    return "**" in self.full_expression

  def is_char_arr(self):
    return self.is_ptr() and "char" in self.components

  def is_void(self):
    return self.type == "void"

  def is_app_owned(self):
    return self.type_wo_asterisk in app_owned_resources

  def is_lib_owned(self):
    return self.type_wo_asterisk in lib_owned_resources

  def is_restricted(self):
    return self.type_wo_asterisk in restricted_resources


class Function:
  def __init__(self, string):
    parens_split = string.split("(")
    ret_and_name = parens_split[0].split(" ")
    params_single_string = parens_split[-1].split(")")[0]
    params_strings = params_single_string.split(",") if params_single_string else []

    # Basic members (return type, function name, parameters)
    self.ret    = Resource(" ".join(ret_and_name[:-1]), is_ret=True)
    self.name   = ret_and_name[-1]
    self.params = [Resource(p) for p in params_strings]

    # Helper members, constructed from basic members
    self.params_str       = ", ".join([param.full_expression for param in self.params])
    self.param_types      = [param.type for param in self.params]
    self.args_struct_name = "uhyve_{0}_t".format(self.name)
    self.args_struct      = self.__generate_args_struct()
    self.port_name        = "UHYVE_PORT_" + self.name.upper()
    self.uhyve_fnc_name   = "call_{0}".format(self.name)
    self.uhyve_fnc_decl   = ("void {0}(struct kvm_run * run, uint8_t * guest_mem);\n"
                             .format(self.uhyve_fnc_name))
    self.fnc_decl         = "{} {}({});".format(self.ret.type, self.name, self.params_str)

  def __generate_args_struct(self):
    """Generates the arguments struct to hold a function's parameters and return value.

    Returns:
      Generated struct [string].
    """
    code = "typedef struct {\n"

    if len(self.params) > 0:
      code += "\t// Parameters:\n"
      for param in self.params:
        code += "\t{0};\n".format(param.full_expression)

    if not self.ret.is_void():
      code += "\t// Return value:\n"
      code += "\t{0} ret;\n".format(self.ret.type)

    code += "}} __attribute__((packed)) {0};\n\n".format(self.args_struct_name)
    return code

# ----------------------------------------------------------------------------
# HELPER
# ----------------------------------------------------------------------------

def generate_pretty_comment(string):
  """Generates a 3 line pretty comment of the given string."""
  return "/*\n * {0}\n */\n\n".format(string)

# ----------------------------------------------------------------------------
# CODE GENERATION: Expecting list of all functions
# ----------------------------------------------------------------------------

def generate_hermit_function_declarations(functions):
  """Generates all HermitCore function declarations for the ibv.h header.

  Args:
    functions: List of all Functions [class Function].
  """
  code = ""
  for fnc in functions:
    code += fnc.fnc_decl + "\n"
  return code

def generate_port_enum(functions):
  """Generates the enum mapping KVM exit IO port names to port numbers.

  Args:
    functions: List of all Functions [class Function].
  Returns:
    Entire enum [string].
  """
  code = "typedef enum {\n"
  code += "\tUHYVE_PORT_SET_IB_POOL_ADDR = 0x{0},\n".format(format(PORT_NUMBER_START, "X"))
  for num, fnc in enumerate(functions, PORT_NUMBER_START + 1):
    code += "\t{0} = 0x{1},\n".format(fnc.port_name, format(num, "X"))
  code += "} uhyve_ibv_t;"

  return code

def generate_port_macros(functions):
  """Generates the compiler macros mapping KVM exit IO port names to port numbers.

  Args:
    functions: List of all Functions [class Function].
  Returns:
    Generated list of compiler macros [string].
  """
  code = "#define UHYVE_PORT_SET_IB_POOL_ADDR 0x{0}\n".format(format(PORT_NUMBER_START, "X"))
  for num, fnc in enumerate(functions, PORT_NUMBER_START + 1):
    code += "#define {0} 0x{1}\n".format(fnc.port_name, format(num, "X"))
  return code

def generate_uhyve_cases(functions):
  """ Generates all switch-cases for the given verbs functions for uhyve's KVM exit IO.

  Args:
    functions: List of all Functions [class Function].
  Returns:
    Generated switch-cases [string]
  """
  code  = "\t\t\tcase UHYVE_PORT_SET_IB_POOL_ADDR: {\n"
  code += "\t\t\t\t\tunsigned data = *((unsigned*)((size_t)run+run->io.data_offset));\n"
  code += "\t\t\t\t\tuint64_t * temp = (uint64_t*)(guest_mem + data);\n"
  code += "\t\t\t\t\tib_pool_addr = (uint8_t*) *temp;\n"
  code += "\t\t\t\t\tib_pool_top = ib_pool_addr;\n"
  code += "\t\t\t\t\tbreak;\n"
  code += "\t\t\t}\n\n"

  for fnc in functions:
    code += "\t\t\tcase {0}:\n".format(fnc.port_name)
    code += "\t\t\t\t{0}(run, guest_mem);\n".format(fnc.uhyve_fnc_name)
    code += "\t\t\t\tbreak;\n"

  return code

# ----------------------------------------------------------------------------
# CODE GENERATION: Expecting a single function
# ----------------------------------------------------------------------------

def generate_hermit_function_definition(fnc):
  """Generates the given verbs API function for HermitCore.

  The function performs guest->host address conversions for all application owned resources that
  are not restricted deep resources, i.e. that require no further processing of references.
  It writes the arguemnts struct to the function's KVM I/O port, causing a KVM exit in uhyve.

  Returns:
    Generated full function definition [string].
  """
  code = "{0} {1}({2}) {{\n".format(fnc.ret.type, fnc.name, fnc.params_str)
  code += "\t{0} uhyve_args;\n".format(fnc.args_struct_name)

  for param in fnc.params:
    if param.is_ptr() and not param.is_lib_owned():
      code += "\tuhyve_args.{0} = ({1}) guest_to_host((size_t) {0});".format(
        param.name, param.type)
      if param.is_ptr_ptr():
        code += " // TODO: Check ** param here."
      code += "\n"
    else:
      code += "\tuhyve_args.{0} = {0};\n".format(param.name)
  code += "\n"

  for param in fnc.params:
    if param.is_restricted():
      code += "\t// TODO: Take care of pointer conversions in " + param.name + ".\n"
      code += "\n" if param is fnc.params[-1] else ""

  code += ("\tuhyve_send({0}, (unsigned) virt_to_phys((size_t) &uhyve_args));\n\n"
           .format(fnc.port_name))

  for param in fnc.params:
    if param.is_restricted():
      code += "\t// TODO: Take care of reverse pointer conversions in " + param.name + ".\n"
      code += "\n" if param is fnc.params[-1] else ""

  if not fnc.ret.is_void():
    code += "\treturn uhyve_args.ret;\n"
  code += "}\n\n"

  return code

def generate_uhyve_function(fnc):
  """Generates the uhyve function definition including the native library call.

  Args:
    fnc: A verbs function [class Function].
  Returns:
    Full function definition.
  """
  code  = generate_pretty_comment(fnc.name)
  code += "void call_{0}(struct kvm_run * run, uint8_t * guest_mem) {{\n".format(fnc.name)
  code += "\tprintf(\"LOG: UHYVE - call_{0}\\n\");\n".format(fnc.name)
  code += "\tunsigned data = *((unsigned*) ((size_t) run + run->io.data_offset));\n"
  code += "\t{0} * args = ({0} *) (guest_mem + data);\n\n".format(fnc.args_struct_name)
  code += "\tuse_ib_mem_pool = true;\n"

  code += "\t" + ("args->ret = " if not fnc.ret.is_void() else "") + "{0}(".format(fnc.name)
  if len(fnc.params) > 0:
    for param in fnc.params[:-1]:
      code += "args->{}, ".format(param.name)
    code += "args->{}".format(fnc.params[-1].name)
  code += ");\n"

  code += "\tuse_ib_mem_pool = false;\n}\n\n\n"
  return code

# ----------------------------------------------------------------------------
# MAIN
# ----------------------------------------------------------------------------

if __name__ == "__main__":
  functions = []

  # Parse the input file containing all verbs function declarations (one per line).
  with open(SRC_PATH, "r") as f:
    for line in f:
      if line:
        functions.append(Function(line))

  # Generate code in different 'GEN-' files corresponding to actual source files.
  with open(UHYVE_CASES_GEN_PATH, "w") as f:
    f.write(generate_uhyve_cases(functions))

  with open(INCLUDE_STDDEF_GEN_PATH, "w") as f:
    f.write(generate_port_macros(functions))

  with open(KERNEL_HEADER_GEN_PATH, "w") as f:
    f.write(generate_hermit_function_declarations(functions))

  with open(UHYVE_IBV_HEADER_GEN_PATH, "w") as f:
    f.write(generate_port_enum(functions))
    f.write("\n\n")

    for fnc in functions:
      f.write(fnc.args_struct)
    f.write("\n\n")

    for fnc in functions:
      f.write(fnc.uhyve_fnc_decl)

  with open(UHYVE_HOST_FCNS_GEN_PATH, "w") as f:
    for fnc in functions:
      f.write(generate_uhyve_function(fnc))

  with open(KERNEL_GEN_PATH, "w") as f:
    for fnc in functions:
      f.write(generate_pretty_comment(fnc.name))
      f.write(fnc.args_struct)
      f.write(generate_hermit_function_definition(fnc))
      f.write("\n")
