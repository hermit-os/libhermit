#!/usr/bin/env python

import subprocess
from time import sleep
import os

from config import BENCHMARKS, OPTIONS, HERMIT_RUN_SERVER, NATIVE_PERFTEST_PATH

print('Run native benchmarks.\n')
for bm in BENCHMARKS:
  for opt in OPTIONS:

    print('Benchmark: ' + bm + ' ' + opt + '\n')
    subprocess.call("numactl --physcpubind 10".split() + [os.path.join(NATIVE_PERFTEST_PATH, bm)] + opt.split())


print('Run HermitCore benchmarks.\n')
for bm in BENCHMARKS:
  for opt in OPTIONS:

    print('Benchmark: ' + bm + ' ' + opt + '\n')
    subprocess.call(HERMIT_RUN_SERVER + bm + ' ' + opt, shell=True)
    sleep(1)
