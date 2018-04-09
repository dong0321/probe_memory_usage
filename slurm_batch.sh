#!/bin/sh

echo "Rank,VmRSS(status),VmSize,Rss(smaps),Pss,Ppid,pVmRSS(status),pVmSize,pRss(smaps),pPss,mapwr,pmapwr" >> memory_info.csv
#default setting is to print only
#   VmRSS: Resident set size.  Note that the value here is the sum of RssAnon, RssFile, and RssShmem.
#   VmSize: Virtual memory size.
#   Pss
#   mapwr is the sum of read/write memory in /proc/pid/maps
salloc -k -n 24 -N 6 mpirun ./check_memory >> memory_info.csv

