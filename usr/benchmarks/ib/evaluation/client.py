#!/usr/bin/env python

import subprocess
import os
import errno
from time import sleep
from datetime import datetime

#  from parse_results import parse_results
from config import \
BENCHMARKS, OPTIONS, NATIVE_SERVER_IP, HERMIT_RUN_CLIENT, HERMIT_SERVER_IP, NATIVE_PERFTEST_PATH


timestamp = datetime.now().strftime("%y-%m-%d-%H-%M")
directory = os.path.join('/home/wierichs/HermitCore/usr/benchmarks/ib/evaluation', timestamp)
try:
  os.makedirs(directory)
except OSError as e:
  if e.errno != errno.EEXIST:
    raise

# Native
print('Run native benchmarks.\n')
for bm in BENCHMARKS:
  for opt in OPTIONS:

    print('Benchmark: ' + bm + ' ' + opt + '\n')
    post_list = opt.split()[-1]
    file_name = 'native-' + bm + '-pl_' + post_list + '.log'

    with open(os.path.join(directory, file_name), "w+") as logfile:
      subprocess.call("numactl --physcpubind 10".split() + [os.path.join(NATIVE_PERFTEST_PATH, bm)] + opt.split() + [NATIVE_SERVER_IP], stdout = logfile)
      sleep(3)

# HermitCore
print('Run HermitCore benchmarks.\n')
for bm in BENCHMARKS:
  for opt in OPTIONS:

    print('Benchmark: ' + bm + ' ' + opt + '\n')
    post_list = opt.split()[-1]
    file_name = 'hermit-' + bm + '-pl_' + post_list + '.log'

    with open(os.path.join(directory, file_name), "w+") as logfile:
      subprocess.call(HERMIT_RUN_CLIENT + bm + ' ' + opt + ' ' + HERMIT_SERVER_IP,
                      shell=True, stdout=logfile)
      sleep(5)
