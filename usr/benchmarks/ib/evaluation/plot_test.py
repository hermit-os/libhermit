#!/usr/bin/env python

from __future__ import print_function
import os

from parse_results import parse_results, plot_results
from config import BENCHMARKS, TIMESTAMP


directory = os.path.join('/home/anni/swarm1/HermitCore/usr/benchmarks/ib/evaluation', TIMESTAMP)
results = parse_results(directory)
plot_results(results, directory)
