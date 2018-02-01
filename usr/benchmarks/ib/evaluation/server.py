#!/usr/bin/env python

import subprocess

from config import BENCHMARKS, OPTIONS, HERMIT_RUN_SERVER

print('Run native benchmarks.')
for bm in BENCHMARKS:
  print('Benchmark: ' + bm)
  for opt in OPTIONS:
    subprocess.call([bm] + opt.split())

print('\nRun HermitCore benchmarks.')
for bm in BENCHMARKS:
  print('Benchmark: ' + bm)
  for opt in OPTIONS:
    #  subprocess.call((HERMIT_RUN_SERVER + bm).split() + opt.split())
    subprocess.call(HERMIT_RUN_SERVER + bm + ' ' + opt, shell=True)
