AUTOMAKE_OPTIONS = cygnus
INCLUDES = $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS)
AM_CCASFLAGS = $(INCLUDES)
 
noinst_LIBRARIES = lib.a

NASM = @NASM@
NASMFLAGS = -felf64 

crt0.o: crt0.asm
	$(NASM) $(NASMFLAGS) -o $@ $<

if MAY_SUPPLY_SYSCALLS
extra_objs = chown.o dup2.o environ.o execve.o fork.o getpid.o init.o kill.o lseek.o pthread_init.o readlink.o stat.o times.o wait.o close.o dup.o errno.o _exit.o fstat.o gettod.o isatty.o link.o open.o read.o sbrk.o symlink.o unlink.o write.o
else
extra_objs =
endif
 
lib_a_SOURCES =
lib_a_LIBADD = $(extra_objs)
EXTRA_lib_a_SOURCES = chown.c dup2.c environ.c execve.c fork.c getpid.c init.c kill.c lseek.c pthread_init.c readlink.c stat.c times.c wait.c close.c dup.c errno.c _exit.c fstat.c gettod.c isatty.c link.c open.c read.c sbrk.c symlink.c unlink.c write.c
lib_a_DEPENDENCIES = $(extra_objs)
lib_a_CCASFLAGS = $(AM_CCASFLAGS)
lib_a_CFLAGS = $(AM_CFLAGS)
 
if MAY_SUPPLY_SYSCALLS
all: crt0.o
endif
 
ACLOCAL_AMFLAGS = -I ../../..
CONFIG_STATUS_DEPENDENCIES = $(newlib_basedir)/configure.host
