#!/bin/sh

echo "ompi"
#default setting is to print only
#   VmRSS: Resident set size.  Note that the value here is the sum of RssAnon, RssFile, and RssShmem.
#    VmSize: Virtual memory size.

salloc -k -n 240 -N 60 mpirun ./check_memory -l 1

