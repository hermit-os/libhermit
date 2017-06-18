---
layout:     post
title:      Running HermitCore Unikernels on Cloud Platforms
author:     Stefan Lankes
tags: 	    tutorial
subtitle:   OpenStack, Google Compute Engine, ...
---

After our first presentation of HermitCore at [ROSS 2016](https://dl.acm.org/authorize?N04880), many things changed.
We started with the assumption to design an HPC kernel and combined it with unikernel features.
Unikernels are specialized, single-address-space machine images constructed by using library operating systems.

In high performance computing is one objective to reduce the overhead and the operating system noise to increase the scalability of the system.
One approach is to use a specialized light-weight kernel.
To get the flexibility of full-weight kernel (e.g. Linux) and their driver support, the light-weight kernels are often combined with full-weight kernel.
Im such an multi-kernel environment, light-weight kernels are running side-by-side to a full-weight kernel like Linux, which could be used as backup kernel to provide features, which aren't supported by the light-weight kernels (e.g. file systems).
Like in other the multi-kernel approaches (e.g. [McKernel](http://www-sys-aics.riken.jp/ResearchTopics/os/mckernel.html)), a subset of cores will be isolated by starting HPC applications from the Linux system and run bare-metal these cores.

HermitCore is a completely 64 bit multi-processor kernel and provides a comprehensive toolchain, which is based on the GCC and supports C/C++, Fortran, Go, Pthreads, and OpenMP.
For an improvement of the performance, it supports latest hardware feature (e.g. AVX512) and Intel’s OpenMP runtime is used instead of GCC’ per default.
Therefore, Intel’s C-Compiler icc could be used as well to build HermitCore applications.
A short tutorial is published in our [wiki](https://github.com/RWTH-OS/HermitCore/wiki/Using-Intel's-C--compiler).

In the last year, the HermitCore is continuously improved and supports also cloud computing platforms.
We have integrated a network interface, which based on the [Virtio PCI Specification](http://ozlabs.org/%7Erusty/virtio-spec/virtio-0.9.5.pdf).
Hereby, we are able to boot HermitCore applications on [OpenStack](https://github.com/RWTH-OS/HermitCore/wiki/Booting-HermitCore-from-an-ISO-image) and [Google Compute Platform](https://github.com/RWTH-OS/HermitCore/wiki/Boot-HermitCore-from-a-raw-image) because both platforms base on this interface.

In this tutorial, an image will be created for a minimal [web server](https://github.com/RWTH-OS/HermitCore/blob/master/usr/tests/server.go) and boot it on Google Compute Platform.
In principle, the image is also bootable on OpenStack.
The demo application is completely written in Go and response any http requests with its http request message.
This Go example was developed by Alan A. A. Donovan and Brian W. Kernighan for their book _The Go Programming Language_ and published at [http://www.gopl.io](http://www.gopl.io).

```go
// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// The original code was published at http://www.gopl.io, see page 21.

// This is an "echo" server that displays request parameters.

package main

import (
	"fmt"
	"log"
	"net/http"
)

func main() {
	fmt.Println("This is an \"echo\" server that displays request parameters.")
	fmt.Println("Start the server and send a http request to it (e.g.")
	fmt.Println("curl http://localhost:8000/help). The server uses port 8000.")
	fmt.Println("If KVM is implicitly started by our proxy, please open the port by")
	fmt.Println("setting the environment variable HERMIT_APP_PORT to 8000.")

	http.HandleFunc("/", handler)
	log.Fatal(http.ListenAndServe(":8000", nil))
}

// handler echoes the HTTP request.
func handler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "%s %s %s\n", r.Method, r.URL, r.Proto)
	for k, v := range r.Header {
		fmt.Fprintf(w, "Header[%q] = %q\n", k, v)
	}
	fmt.Fprintf(w, "Host = %q\n", r.Host)
	fmt.Fprintf(w, "RemoteAddr = %q\n", r.RemoteAddr)
	if err := r.ParseForm(); err != nil {
		log.Print(err)
	}
	for k, v := range r.Form {
		fmt.Fprintf(w, "Form[%q] = %q\n", k, v)
	}
}
```

The [Google Compute Platform](https://cloud.google.com/compute/docs/images/import-existing-image) supports only the raw image format as virtual hard disk.
Consequently, we have to create with `qemu-img` a 1 GB file in the raw format.
A size of 1 Gb is the smallest possible size for the Google Compute Platform and *large* enough for our web server.
(The file size of the server is  about 20 Mb).

```bash
$ qemu-img create -f raw disk.raw 1G
Formatting 'disk.raw', fmt=raw size=1073741824
```

Next lets load the kernel module _nbd_, and associate the previous image to one of the nbd devices.

```bash
sudo modprobe nbd max_part=16
sudo qemu-nbd -c /dev/nbd0 -f raw disk.raw
```

Like a normal hard disk, we have to partition the image.
The following command create one big partition.

```bash
$ echo ';' | sudo sfdisk /dev/nbd0
Checking that no-one is using this disk right now ... OK

Disk /dev/nbd0: 1 GiB, 1073741824 bytes, 2097152 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes

>>> Created a new DOS disklabel with disk identifier 0xe2111e23.
Created a new partition 1 of type 'Linux' and of size 1023 MiB.
/dev/nbd0p2:
New situation:

Device      Boot Start     End Sectors  Size Id Type
/dev/nbd0p1       2048 2097151 2095104 1023M 83 Linux

The partition table has been altered.
Calling ioctl() to re-read partition table.
Syncing disks.
```

Now, we are able to format our partition.
Please use `ext2` as filesystem because our bootloader depends on this filesystem.

```bash
$ sudo mkfs.ext2 /dev/nbd0p1
mke2fs 1.42.13 (17-May-2015)
Discarding device blocks: failed - Input/output error
Creating filesystem with 261888 4k blocks and 65536 inodes
Filesystem UUID: a49660c4-924e-4b4b-b867-8d081bd23484
Superblock backups stored on blocks:
	32768, 98304, 163840, 229376

Allocating group tables: done                            
Writing inode tables: done                            
Writing superblocks and filesystem accounting information: done
```

HermitCore adheres the [Multiboot specification](https://www.gnu.org/software/grub/manual/multiboot/multiboot.html) whereby the bootloader grub is able to boot HermitCore applications.
Consequently, we have to mount the partition, to install grub and our application on the virtual hard disk.

```bash
$ sudo mount /dev/nbd0p1 /mnt/
$ sudo grub-install --root-directory=/mnt --no-floppy --modules="normal part_msdos ext2 multiboot biosdisk" /dev/nbd0
$ sudo cp /opt/hermit/bin/ldhermit.elf /mnt/boot/
$ sudo cp /opt/hermit/x86_64-hermit/extra/tests/server /mnt/boot/
```

Finally, the configuration file `/mnt/boot/grub.cfg` has been created for the bootloader.
In this case, the configuration file looks as follows:

```bash
default=0
timeout=0

menuentry "echo server" {
	multiboot /boot/ldhermit.elf -uart=io:0x3f8
	module /boot/server
	boot
}
```

The kernel parameter (`-uart=io:0x3f8`) defines the serial IO port for all kernel messages.
Please unmount all devices to be sure that all changes are written the disk:

```bash
$ sudo umount /mnt
$ sudo qemu-nbd -d /dev/nbd0
```

Now, you have to pack the image with `tar -cSzf disk.tar.gz disk.raw` to a tar file.
To use this file on the Google Compute Platform, you have to create [Cloud Storage bucket](https://cloud.google.com/storage/docs/creating-buckets#storage-create-bucket-gsutil).

```bash
gsutil mb gs://[BUCKET_NAME]/
```

Please, replace `[BUCKET_NAME]` with an appropriate name and upload as follows the tar file to the cloud storage.

```bash
gsutil cp disk.tar.gz gs://[BUCKET_NAME]/
```

Create from this file an image, which we want to use as boot disk for the virtual machine.

```bash
gcloud compute --project "[PROJECT_ID]" images create "[IMAGE_NAME]" --description "echo server" --source-uri "https://storage.googleapis.com/[BUCKET_NAME]/disk.tar.gz"
```

Please, replace `[BUCKET_NAME]`, `[PROJECT_ID]` and `[IMAGE_NAME]` with an appropriate names of your Google Compute project.
Finally, we have to create a VM and to boot from this disk.

```bash
gcloud compute --project "[PROJECT_ID]" instances create "[VM_NAME]" --zone "us-central1-c" --machine-type "f1-micro" --subnet "default" --maintenance-policy "MIGRATE" --service-account "966551718477-compute@developer.gserviceaccount.com" --scopes "https://www.googleapis.com/auth/devstorage.read_only","https://www.googleapis.com/auth/logging.write","https://www.googleapis.com/auth/monitoring.write","https://www.googleapis.com/auth/servicecontrol","https://www.googleapis.com/auth/service.management.readonly","https://www.googleapis.com/auth/trace.append" --tags "http-server" --image "hermit" --image-project "[PROJECT_ID]" --boot-disk-size "10" --boot-disk-type "pd-standard" --boot-disk-device-name "[VM_NAME]"
```

The server is listening on port 8000 (tcp).
Consequently, we have to open this port and to create appropriate firewall rules.

```bash
gcloud beta compute --project "[PROJECT_ID]" firewall-rules create "allow-echo" --allow tcp:8000 --description "echo server" --direction "INGRESS" --priority "1000" --network "default" --source-ranges "0.0.0.0/0"
```

Afterwards we are able to send requests to this web server:

```bash
$ curl http://XX.XX.XX.XX:8000/hello
```

In this example, we assume that your server has the IP address `XX.XX.XX.XX`.
