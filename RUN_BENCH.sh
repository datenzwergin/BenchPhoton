#!/bin/bash

# output cpu data and run local benchmarks
# Run like:
#    $ bash -x RUN_BENCH.sh
#
OUTFILE=RESULTS-photon-`hostname`.txt

echo "Running benchmarks..."

date > $OUTFILE ;
lscpu >> $OUTFILE ;
cat /proc/cpuinfo >> $OUTFILE ;
./bench >> $OUTFILE ;

echo "Done. Results in "$OUTFILE
