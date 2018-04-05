#!/bin/sh

echo "Rank,VmRSS(status),VmSize,Rss(smaps),Pss,Ppid,pVmRSS(status),pVmSize,pRss(smaps),pPss" >> memory_info.csv
echo "ompi"
#default setting is to print only
#   VmRSS: Resident set size.  Note that the value here is the sum of RssAnon, RssFile, and RssShmem.
#   VmSize: Virtual memory size.
#   Pss
salloc -k -n 24 -N 6 mpirun ./check_memory -l 1 >> memory_info.csv

