#!/bin/bash

BUSYBOX_VERSION=1.23.2
BUSYBOX_URL=https://busybox.net/downloads/busybox-$BUSYBOX_VERSION.tar.bz2
BUSYBOX_ARCHIVE="$(basename $BUSYBOX_URL)"

# first argument or default
OUTPUT_INITRAMFS="$(readlink -f ${1:-initrd.cpio})"

# will be created on every run
BUSYBOX_BUILDDIR="$(readlink -f busybox-build)"
INITRAMFS_BUILDDIR="$(readlink -f initrd)"


if [ ! $UID -eq 0 ]; then
    echo "You need to be root, but fakeroot is okay too ..."
    echo
    echo "\$ fakeroot $0"
    exit 1
fi

# for debugging
#set -x

######## BusyBox ########

if [ -d "$BUSYBOX_BUILDDIR" ]; then
    echo "[BUSYBOX] Already built, skipping. Make veryclean to build again"
else
	# download busybox if not yet there
	if [ ! -f "$BUSYBOX_ARCHIVE" ]; then
		# download busybox
		echo "[BUSYBOX] Archive not found, so downloading it ..."
		wget --quiet $BUSYBOX_URL

		if [ ! -f "$BUSYBOX_ARCHIVE" ]; then
		    echo "[BUSYBOX] Download failed, we have problem here!"
		    exit 1
		fi
	fi

	# extract busybox and move to build folder
	echo "[BUSYBOX] Extract archive"
	tar xf "$BUSYBOX_ARCHIVE"
	mv "$(basename "${BUSYBOX_ARCHIVE}" .tar.bz2)" "$BUSYBOX_BUILDDIR"
	cd "$BUSYBOX_BUILDDIR"

	echo "[BUSYBOX] Configure"

	# create initial default config
	make defconfig &> /dev/null

	# proposed by busybox/INSTALL
	sed -e 's/.*FEATURE_PREFER_APPLETS.*/CONFIG_FEATURE_PREFER_APPLETS=y/' -i .config
	sed -e 's/.*FEATURE_SH_STANDALONE.*/CONFIG_FEATURE_SH_STANDALONE=y/' -i .config

	# config according to https://techblog.lankes.org/2015/05/01/My-Memo-to-build-a-custom-Linux-Kernel-for-Qemu/
	sed -e 's/.*CONFIG_DESKTOP.*/CONFIG_DESKTOP=n/' -i .config
	sed -e 's/.*CONFIG_EXTRA_CFLAGS.*/CONFIG_EXTRA_CFLAGS="-m64"/' -i .config
	sed -e 's/.*CONFIG_EXTRA_LDFLAGS.*/CONFIG_EXTRA_LDFLAGS="-m64"/' -i .config

	echo "[BUSYBOX] Building now ..."
	make -j4 &> /dev/null
	make install &> /dev/null
	cd ..

fi

######## Assemble initram fs ########

mkdir -p "$INITRAMFS_BUILDDIR"
cd "$INITRAMFS_BUILDDIR"

mkdir -p bin lib dev etc mnt proc root sbin sys tmp

echo "[INITRAMFS] Populate /dev"
cd dev
mknod ram0 b 1 0  # all one needs is ram0
mknod ram1 b 1 1
ln -s ram0 ramdisk
mknod initrd b 1 250
mknod mem c 1 1
mknod kmem c 1 2
mknod null c 1 3
mknod port c 1 4
mknod zero c 1 5
mknod core c 1 6
mknod full c 1 7
mknod random c 1 8
mknod urandom c 1 9
mknod aio c 1 10
mknod kmsg c 1 11
mknod sda b 8 0
mknod tty0 c 4 0
mknod ttyS0 c 4 64
mknod ttyS1 c 4 65
mknod tty c 5 0
mknod console c 5 1
mknod ptmx c 5 2
mknod ttyprintk c 5 3
ln -s ../proc/self/fd fd
ln -s ../proc/self/fd/0 stdin # process i/o
ln -s ../proc/self/fd/1 stdout
ln -s ../proc/self/fd/2 stderr
ln -s ../proc/kcore     kcore
cd ..

echo "[INITRAMFS] Copy busybox"
cp -aR $BUSYBOX_BUILDDIR/_install/* .

echo "[INITRAMFS] Add /init"
cat <<EOF > init
#!/bin/sh
/bin/mount -t proc none /proc
/bin/mount -t sysfs sysfs /sys
/bin/mount /dev/cdrom /hermit
/sbin/mdev -s
/sbin/ifconfig lo 127.0.0.1 netmask 255.0.0.0 up
/sbin/ifconfig eth0 up 10.0.2.15 netmask 255.255.255.0 up
/sbin/ifconfig mmnif up 192.168.28.1 netmask 255.255.255.0 up
/sbin/route add default gw 10.0.2.2
/bin/hostname -F /etc/hostname

echo 'Welcome to HermitCore (http://rwth-os.github.io/HermitCore/)!'

/usr/bin/setsid /bin/cttyhack /bin/sh
exec /bin/sh
EOF
chmod 755 init

echo "[INITRAMFS] Roll compressed image"
find . -print0 | cpio --null -o --format=newc > "$OUTPUT_INITRAMFS" 2> /dev/null

######## Clean up ########

echo "Cleaning up ..."
rm -r "${INITRAMFS_BUILDDIR}"
