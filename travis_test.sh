#!/bin/bash
#
# do not use this script
# it is written only for internal tests via Travis CI

FILES="usr/tests/hello usr/tests/hellof usr/tests/hello++ usr/tests/thr_hello usr/tests/pi usr/benchmarks/stream usr/benchmarks/basic"
PROXY=/opt/hermit/bin/proxy

export HERMIT_ISLE=qemu
export HERMIT_CPUS=1
export HERMIT_MEM="512M"
export HERMIT_KVM="1"
export HERMIT_VERBOSE="1"

for file in $FILES
do
	if [ -x $file ] && [ -f $file ]
	then
		echo "check $file ..."
		$PROXY $(readlink -f $file) || exit 1
	fi
done

# test echo server at port 8000
#HERMIT_APP_PORT=8000 $PROXY usr/tests/server &
#sleep 10
#curl http://127.0.0.1:8000/help
#sleep 1

# kill server
#kill $!
