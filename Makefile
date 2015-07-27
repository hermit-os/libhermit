HOMEDIR := $(shell pwd)
INITRAMFS=../busybox-1.23.2/initramfs/
#QEMU = qemu-system-x86_64
QEMU = qemu-kvm -cpu host
NJOBS = -j4

default:
	make -C hermit default

all:
	make -C hermit all

clean:
	make -C hermit clean

veryclean:
	make -C hermit veryclean

ramfs:
	touch myinitrd.cpio
	make -C linux $(NJOBS)
	make -C hermit $(NJOBS)
	cp hermit/hermit.bin $(INITRAMFS)
	cd $(INITRAMFS); \
	find . -print0 | cpio --null -ov --format=newc > $(HOMEDIR)/myinitrd.cpio

qemu:
	$(QEMU) -smp 4 -kernel linux/arch/x86/boot/bzImage -initrd myinitrd.cpio -append "root=/dev/ram0 rootfstype=ramfs init=init console=ttyS0 maxcpus=1" -net nic,model=rtl8139 -net user  -net dump -nographic -monitor telnet:127.0.0.1:1234,server,nowait -m 4G -numa node,nodeid=0,cpus=0-1 -numa node,nodeid=1,cpus=2-3
