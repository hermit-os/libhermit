#!/bin/bash
#
# do not use this script
# it is written only for internal tests via Travis CI

TDIR=build/local_prefix/opt/hermit/x86_64-hermit/extra
FILES="$TDIR/tests/hello $TDIR/tests/hellof $TDIR/tests/hello++ $TDIR/tests/thr_hello $TDIR/tests/pi $TDIR/benchmarks/stream $TDIR/benchmarks/basic $TDIR/tests/signals $TDIR/tests/test-malloc $TDIR/tests/test-malloc-mt $TDIR/tests/argv_envp"
PROXY=build/local_prefix/opt/hermit/bin/proxy

for f in $FILES; do echo "check $f..."; HERMIT_ISLE=qemu HERMIT_CPUS=1 HERMIT_KVM=0 HERMIT_VERBOSE=1 timeout --kill-after=5m 5m $PROXY $f || exit 1; done

for f in $FILES; do echo "check $f..."; HERMIT_ISLE=qemu HERMIT_CPUS=2 HERMIT_KVM=0 HERMIT_VERBOSE=1 timeout --kill-after=5m 5m $PROXY $f || exit 1; done

# test echo server at port 8000
HERMIT_ISLE=qemu HERMIT_CPUS=1 HERMIT_KVM=0 HERMIT_VERBOSE=1 HERMIT_APP_PORT=8000 $PROXY $TDIR/tests/server &
sleep 10
curl http://127.0.0.1:8000/help
sleep 1
curl http://127.0.0.1:8000/hello
sleep 1

# kill server
kill $!

# test connection via netio
wget http://web.ars.de/wp-content/uploads/2017/04/netio132.zip
unzip netio132.zip
HERMIT_ISLE=qemu HERMIT_CPUS=2 HERMIT_KVM=0 HERMIT_VERBOSE=1 HERMIT_APP_PORT=18767 $PROXY $TDIR/benchmarks/netio &
sleep 1
chmod a+rx bin/linux-x86_64
bin/linux-x86_64 -t -b 4k localhost
sleep 1

# kill server
kill $!
