from __future__ import print_function

import numpy as np
import os

import matplotlib
from matplotlib import pyplot as plt

from config import BENCHMARKS, TIMESTAMP, OPTIONS

matplotlib.rcParams['font.family'] = 'serif'
matplotlib.rcParams['mathtext.default'] = 'regular'
matplotlib.rcParams['xtick.major.pad'] = '8' # TODO: do this separately

#  matplotlib.rcParams['font.sans-serif'] = ['Tahoma']
#  matplotlib.rcParams['figure.figsize'] = 30, 10

MACHINE_TYPES = ['hermit', 'native']

bw_metrics = ['num_bytes',
              'iterations',
              'peak',
              'avg',
              'msg_rate']

lat_metrics = ['num_bytes',
               'iterations',
               't_min',
               't_max',
               't_typical',
               't_avg',
               's_stddev',
               'percentile_99',
               'percentile_99_9']

labels = {metric: '' for metric in bw_metrics[2:] + lat_metrics[2:] }

labels[bw_metrics [2]] = 'Peak Bandwidth [MB/sec]'
labels[bw_metrics [3]] = 'Average Bandwidth [MB/sec]'
labels[bw_metrics [4]] = 'Message Rate [Mpps]'

labels[lat_metrics[2]] = 'Min. Latency [${\mu}sec$]'
labels[lat_metrics[3]] = 'Max. Latency [${\mu}sec$]'
labels[lat_metrics[4]] = 'Typical Latency [${\mu}sec$]'
labels[lat_metrics[5]] = 'Average Latency [${\mu}sec$]'
labels[lat_metrics[6]] = 'Latency Standard Deviation [${\mu}sec$]'
labels[lat_metrics[7]] = '99 % Percentile [${\mu}sec$]'
labels[lat_metrics[8]] = '99.9 % Percentile [${\mu}sec$]'


def parse_results(directory):
  """ blabla
  """
  # Examples: results['native']['ib_write_bw -a' ]['4' ]['peak' ]
  #           results['hermit']['ib_write_lat -a']['16']['t_avg']
  num_wrs_list = [opt.split()[-1] for opt in OPTIONS]
  results = {machine:
             {bm_name:
              {num_wrs:
               {metric: []
                for metric in (bw_metrics if 'bw' in bm_name
                               else lat_metrics)}
               for num_wrs in num_wrs_list}
              for bm_name in BENCHMARKS}
             for machine in MACHINE_TYPES}

  for machine in MACHINE_TYPES:
    for bm in BENCHMARKS:
      for num_wrs in num_wrs_list:

        print('Benchmark: ' + machine + ' --- ' + bm + ' WRs: ' + num_wrs)

        #  if bm.endswith("lat") and not num_wrs == '1':
          #  continue

        read_line = False
        file_name = machine + '-' + bm + '-pl_' + num_wrs + '.log'
        file_path = os.path.join(directory, file_name)

        with open(file_path, "r") as logfile:
          for line in logfile:
            if line.startswith(' #bytes'):
              read_line = True
              continue
            elif read_line and line.startswith('------'):
              break

            if read_line:
              values = line.split()
              for metric, val in zip(bw_metrics if 'bw' in bm else lat_metrics,
                                     values):
                final_value = 0
                if 'inf' not in val:
                  final_value = float(val) if '.' in val else int(val)

                results[machine][bm][num_wrs][metric].append(final_value)

  return results

def plot_results(results, directory):
  """ blabla
  """
  num_wrs_list = [opt.split()[-1] for opt in OPTIONS]

  line_color = {'native':
                {num_wrs: (float(200 - r*40)/256, 0, 0)
                 for r, num_wrs in zip(range(len(num_wrs_list)), num_wrs_list)},
                'hermit':
                {num_wrs: (0, float(170 - g*40)/256, 0)
                 for g, num_wrs in zip(range(len(num_wrs_list)), num_wrs_list)}}

  for bm in BENCHMARKS:
    for metric in (bw_metrics[2:] if 'bw' in bm else lat_metrics[2:]):

      file_name = bm + '-' + metric + ('-MULTI' if len(num_wrs_list) > 1 else '') +  '.pdf'
      file_path = os.path.join(directory, file_name)

      fig, ax = plt.subplots(figsize=(10, 5))

      ax.grid()

      # Axis labels
      ax.set_xlabel('Message Size [B]')
      ax.set_ylabel(labels[metric])

      # Axis ticks and scale (x: log2 / y: log2 for latency)
      ax.set_xscale('log', basex=2)
      ax.set_xticks(np.power(2, range(
          1, len(results['native'][bm][num_wrs_list[0]]['num_bytes']) + 1)))
      if 'lat' in bm:
        ax.set_yscale('log', basey=2)
        ax.get_yaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())

      # Plot, save and then clear figure
      for num_wrs in num_wrs_list:
        label_end = ' (' + num_wrs + ' work request' + \
                    (')' if num_wrs is '1' else 's)') if len(num_wrs_list) > 1 else ""
        ax.plot(results['native'][bm][num_wrs]['num_bytes'],
                results['native'][bm][num_wrs][metric],
                'o-', color = line_color['native'][num_wrs], label = 'Native' + label_end,
                linewidth = 2, markersize = 6)
        label = 'HermitCore (' + num_wrs + ' work requests)'
        ax.plot(results['hermit'][bm][num_wrs]['num_bytes'],
                results['hermit'][bm][num_wrs][metric],
                'o-', color = line_color['hermit'][num_wrs], label = 'HermitCore' + label_end,
                linewidth = 2, markersize = 6)

      plt.legend(fontsize = 10, ncol = 3, loc = 'lower right',
                 bbox_to_anchor = [1, 1.05])

      plt.savefig(file_path, bbox_inches = 'tight')
      plt.gcf().clear()

