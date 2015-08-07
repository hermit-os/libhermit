; Copyright (c) 2012, Stefan Lankes, RWTH Aachen University
; All rights reserved.
;
; Redistribution and use in source and binary forms, with or without
; modification, are permitted provided that the following conditions are met:
;    * Redistributions of source code must retain the above copyright
;      notice, this list of conditions and the following disclaimer.
;    * Redistributions in binary form must reproduce the above copyright
;      notice, this list of conditions and the following disclaimer in the
;      documentation and/or other materials provided with the distribution.
;    * Neither the name of the University nor the names of its contributors
;      may be used to endorse or promote products derived from this
;      software without specific prior written permission.
;
; THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
; ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
; WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
; DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
; DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
; (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
; ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
; (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
; SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;

[BITS 64]
SECTION .text
global _start
extern __bss_start
extern _end
extern main
extern environ
extern __env
extern __do_global_dtors
extern __do_global_ctors
extern pthread_init
extern atexit
extern exit
phys equ 0x40200000
_start:
   ; initialize BSS
   mov rdi, __bss_start
   mov rcx, _end
   sub rcx, rdi
   xor rax, rax
   rep; stosb

   ; if available, we have to initialize the pthread library
   call pthread_init

   ; register a function to be called at normal process termination
   mov rdi, __do_global_dtors
   call atexit

   ; call init function
   call __do_global_ctors

   ; set default environment
   mov rax, environ
   mov rdx, [rsp+16]
   cmp rdx, 0
   je L3
   mov qword [rax], rdx
   jmp L4
L3:
   mov rdx, __env
   mov qword [rax], rdx
L4:

   ; arguments are already on the stack
   ; call the user's function
   pop rdi   ; argc
   pop rsi   ; argv pointer
   pop rdx   ; env pointer

   ; align stack
   and rsp, ~0xF

   call main

   ; call exit from the C library so atexit gets called, and the
   ; C++ destructors get run. This calls our exit routine below    
   ; when it's done.
   ; call "exit"
   mov rdi, rax
   call exit

   ; endless loop
   jmp $

extern _ftext
global get_cpufreq
get_cpufreq:
   mov rcx, phys - 0x1000 + 0x18
   xor rax, rax
   mov eax, dword [rcx]
   ret

global get_ticks
get_ticks:
   mov rcx, phys - 0x1000 + 0x24
   mov rax, qword [rcx]
   ret

SECTION .note.GNU-stack noalloc noexec nowrite progbits
