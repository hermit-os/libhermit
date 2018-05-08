#Download base image ubuntu 16.04
FROM ubuntu:16.04

# Update Software repository
RUN apt-get -qq update

# add https support
RUN apt-get install -y apt-transport-https

# add path to hermitcore packets
RUN echo "deb https://dl.bintray.com/rwth-os/hermitcore vivid main" | tee -a /etc/apt/sources.list

# Update Software repository
RUN apt-get -qq update

# Install required packets from ubuntu repository
RUN apt-get install -y curl cmake bsdmainutils wget vim nano git binutils autoconf automake make cmake qemu-system-x86 nasm gcc
RUN apt-get install -y --allow-unauthenticated binutils-hermit libhermit newlib-hermit pthread-embedded-hermit gcc-hermit

RUN wget https://cmake.org/files/v3.7/cmake-3.7.2.tar.gz
RUN tar xzvf https://cmake.org/files/v3.7/cmake-3.7.2.tar.gz
RUN cd cmake-3.7.2
RUN ./bootstrap
RUN make
RUN make install
RUN cd ..
RUN rm -rf cmake*

ENV PATH="/opt/hermit/bin:${PATH}"
ENV EDITOR=vim

CMD echo "This is a HermitCore's toolchain!"; /bin/bash
