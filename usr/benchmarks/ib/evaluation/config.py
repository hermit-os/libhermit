import os


#  BENCHMARKS = ['ib_write_bw',
              #  'ib_write_lat',
              #  'ib_read_bw',
              #  'ib_read_lat']
BENCHMARKS = ['ib_write_bw']
OPTIONS   = ['-a --post_list 1',
             '-a --post_list 4',
             '-a --post_list 16']

TIMESTAMP = '18-02-01-18-46' # TODO: temporary while testing plots

NATIVE_SERVER_IP = '137.226.133.151'

HERMIT_PATH = '/home/wierichs'

HERMIT_SERVER_IP      = '10.0.5.3'
HERMIT_SERVER_GATEWAY = '10.0.5.1'
HERMIT_SERVER_TAPDEV  = 'tap100'

HERMIT_CLIENT_IP      = '10.0.6.3'
HERMIT_CLIENT_GATEWAY = '10.0.6.1'
HERMIT_CLIENT_TAPDEV  = 'tap200'

HERMIT_MASK           = '255.255.255.0'

HERMIT_RUN_SERVER = 'HERMIT_ISLE=uhyve \
                     HERMIT_VERBOSE=1 \
                     HERMIT_KVM=1 \
                     HERMIT_CPUS=1 \
                     HERMIT_IP="'      + HERMIT_SERVER_IP      + '" \
                     HERMIT_GATEWAY="' + HERMIT_SERVER_GATEWAY + '" \
                     HERMIT_MASK="'    + HERMIT_MASK           + '" \
                     HERMIT_NETIF='    + HERMIT_SERVER_TAPDEV  + ' ' + \
                     os.path.join(HERMIT_PATH, 'hermit/bin/proxy') + ' ' + \
                     os.path.join(HERMIT_PATH, 'hermit/x86_64-hermit/extra/benchmarks/')

HERMIT_RUN_CLIENT = 'HERMIT_ISLE=uhyve \
                     HERMIT_VERBOSE=1 \
                     HERMIT_KVM=1 \
                     HERMIT_CPUS=1 \
                     HERMIT_IP="'      + HERMIT_CLIENT_IP      + '" \
                     HERMIT_GATEWAY="' + HERMIT_CLIENT_GATEWAY + '" \
                     HERMIT_MASK="'    + HERMIT_MASK           + '" \
                     HERMIT_NETIF='    + HERMIT_CLIENT_TAPDEV  + ' ' + \
                     os.path.join(HERMIT_PATH, 'hermit/bin/proxy') + ' ' + \
                     os.path.join(HERMIT_PATH, 'hermit/x86_64-hermit/extra/benchmarks/')
