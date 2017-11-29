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
"""

from __future__ import print_function
import pyparsing as pp


VERBS_H_PATH = "verbs-0.h"


def generate_struct_conversions():

  word = pp.Word(pp.alphas+"_", bodyChars=pp.alphanums+"_")

  struct_header = (pp.Literal("struct").suppress() + word +
                   pp.Literal("{").suppress())
  struct_footer = pp.Literal("};").suppress()

  member_var = word + pp.Literal(";").suppress()
  member_type = (pp.Combine(pp.OneOrMore(word + ~pp.FollowedBy(pp.Literal(";"))),
                            joinString=" ", adjacent=False)
                 + pp.ZeroOrMore("*") + pp.FollowedBy(member_var))

  member = pp.Group(member_type + member_var)
  body = pp.OneOrMore(member)

  struct = struct_header + body + struct_footer

  # TODO: Not bullet proof yet.
  comment = pp.Or([pp.Literal("/*") + pp.SkipTo(pp.Literal("*/")),
                   pp.Literal("//") + pp.SkipTo(pp.LineEnd())])
  struct.ignore(comment)

  with open(VERBS_HEADER_PATH, "r") as f_verbs:
    code = f_verbs.read()

  # for result, _, _ in struct.scanString(code):
    # print("{0}".format(result))

