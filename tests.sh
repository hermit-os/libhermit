#!/bin/bash

OS_NAME=$1
OS_VERSION=$2

if [ "$OS_NAME" = "centos" ]; then

# Clean the yum cache
yum -y clean all
yum -y clean expire-cache

# First, install all the needed packages.
yum install -y wget gettext flex bison binutils gcc gcc-c++ texinfo kernel-headers rpm-build kernel-devel boost-devel cmake git tar gzip make autotools

wget http://checkinstall.izto.org/files/source/checkinstall-1.6.2.tar.gz
tar xzvf checkinstall-1.6.2.tar.gz
cd checkinstall-1.6.2
./configure
make
make install
cd ..
rm -rf checkinstall*

mkdir -p build
cd build
../configure --target=x86_64-hermit --prefix=/opt/hermit --disable-shared --disable-nls --disable-gdb --disable-libdecnumber --disable-readline --disable-sim --disable-libssp --enable-tls --disable-multilib
make
checkinstall -R -y --exclude=build --pkggroup=main --maintainer=stefan@eonerc.rwth-aachen.de --pkgsource=https://hermitcore.org --pkgname=newlib-hermit --pkgversion=2.30.51 --pkglicense=GPL2 make install

else

export DEBIAN_FRONTEND="noninteractive"

apt-get -qq update
apt-get install -y cmake wget curl gnupg checkinstall gawk dialog apt-utils flex bison binutils texinfo gcc g++ libmpfr-dev libmpc-dev libgmp-dev libisl-dev packaging-dev build-essential libtool autotools-dev autoconf pkg-config apt-transport-https nasm

echo "deb [trusted=yes] https://dl.bintray.com/hermitcore/ubuntu bionic main" | tee -a /etc/apt/sources.list
apt-get update
apt-get install -y --allow-unauthenticated binutils-hermit newlib-hermit pte-hermit gcc-hermit-bootstrap
export PATH=/opt/hermit/bin:$PATH

mkdir -p build
cd build
cmake -DTOOLCHAIN_BIN_DIR=/opt/hermit/bin -DCMAKE_INSTALL_PREFIX=/opt/hermit -DBOOTSTRAP=true ..
make hermit-bootstrap
checkinstall -D -y --exclude=build --pkggroup=main --maintainer=stefan@eonerc.rwth-aachen.de --pkgsource=https://hermitcore.org --pkgname=libhermit --pkgversion=0.2.8 --pkglicense=BSD-2-Clause make hermit-bootstrap-install

cd ..
mkdir -p tmp
dpkg-deb -R build/libhermit_0.2.8-1_amd64.deb tmp
rm -f build/newlib-hermit_0.2.8-1_amd64.deb

fi
