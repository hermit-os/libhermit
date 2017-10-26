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

TODO: Documentation"""

src_file_path = 'function_prototypes.txt'

ibv_gen_path = 'ibv_gen.c'
uhyve_cases_gen_path = 'uhyve_gen.c'

with open(src_file_path, 'r') as f_src:
  with open(ibv_gen_path, 'w') as f_ibv, open(uhyve_cases_gen_path, 'w') as f_uhyve:
    # TODO: next: generate hyve stuff.
    for line in f_src:
      parens_split = line.split('(')

      ret_and_name = parens_split[0].split(' ')
      function_name = ret_and_name[-1]
      ret = ' '.join(ret_and_name[:-1])

      all_params = parens_split[-1][:-1]
      params = all_params.split(',')
      params[-1] = params[-1][:-1]

      # Struct
      struct_name = 'uhyve_{0}_t'.format(function_name)
      f_ibv.write('typedef struct {\n')
      if params:
        f_ibv.write('\t// Parameters:\n')
        for param in params:
          f_ibv.write('\t{0};\n'.format(param))

        if ret is not "void":
          f_ibv.write('\t// Return value:\n')
          f_ibv.write('\t{0} ret;\n'.format(ret))

        f_ibv.write('}} __attribute__((packed)) {0};\n\n'.format(struct_name))

        # Function
        params_single_string = ', '.join(params)
        f_ibv.write('{0} {1}({2}) {{\n'.format(ret, function_name,
                                                params_single_string))

        # Create uhyve_args and define parameters
        f_ibv.write('\t{0} uhyve_args;\n'.format(struct_name))
        for param in params:
          param_split = param.split(' ')
          param_type = ' '.join(param_split[:-1])
          param_name = param_split[-1]
          # Define struct members according to their type.
          if '**' in param_type:
            f_ibv.write('\t// TODO: Take care of ** parameter.\n')
          elif '*' in param_type:
            f_ibv.write('\tuhyve_args->{0} = ({1}) virt_to_phys((size_t) {2});\n'
                         .format(param_name, param_type, param_name))
          else:
            f_ibv.write('\tuhyve_args->{0} = {0};\n'.format(param_name))

        # Allocate memory for return value if it is a pointer.
        if '**' in ret:
          f_ibv.write('\n\t// TODO: Take care of return value.\n')
        elif '*' in ret:
          f_ibv.write('\n\tuhyve_args->ret = kmalloc(sizeof({0}));\n'.format(ret[:-2]))

        # call uhyve_send() using the respective port ID.
        port_name = 'UHYVE_PORT_' + function_name.upper()
        f_ibv.write('\n\tuhyve_send({0}, (unsigned) virt_to_phys((size_t) '
                     '&uhyve_args));\n\n'.format(port_name))

        f_ibv.write('\t// TODO: Fix pointers in returned data structures.\n')

        f_ibv.write('\treturn uhyve_args.ret;\n')
        f_ibv.write('}\n\n\n')
  
  with open(uhyve_cases_gen_path, 'w') as f_ibv:



# typedef struct {
	# // Parameters:
	# struct ibv_device *device;
	# // Return value:
	# struct ibv_context *ret;
# } __attribute__((packed)) uhyve_ibv_open_device_t;

# int ibv_open_device(struct ibv_device *device) {
	# uhyve_ibv_open_device_t uhyve_args;
    # uhyve_args.device = (struct ibv_device *) virt_to_phys((size_t) device);
	# uhyve_args->ret = kmalloc(sizeof(struct ibv_context));

	# uhyve_send(UHYVE_PORT_IBV_OPEN_DEVICE, (unsigned)virt_to_phys((size_t) &uhyve_args));

	# // Set all pointers contained in returned data structure to valid kernel space addresses.
	# uhyve_args->ret->device = device;

	# return uhyve_args.ret;
# }
