#!/bin/sh

#default setting is to print only
#   VmRSS: Resident set size.  Note that the value here is the sum of RssAnon, RssFile, and RssShmem.
#   VmSize: Virtual memory size.
#   Pss
#   mapwr is the sum of read/write memory in /proc/pid/maps
salloc -k -n 24 -N 6 mpirun ./check_memory >> memory_info_orgin.csv
salloc -k -n 24 -N 6 mpirun --mca btl tcp,self ./check_memory >> memory_info.csv
salloc -k -n 24 -N 6 mpirun --mca btl ^vader ./check_memory >> memory_info1.csv
