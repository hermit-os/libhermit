#!/bin/bash

set -eu

rm -rf ./build || true
mkdir build
cd build && cmake .. && make

gcc -o client ../client.c

## HERMIT_ISLE=qemu HERMIT_APP_PORT=22000 /opt/hermit/bin/proxy ./build/server
