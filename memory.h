#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct mem_info
{
    long VmSize;
    long VmRss;

    long VmPin;
    long RssShmem;
    long RssAnon;
    long RssFile;

    long VmData;
    long VmStk;
    long VmExe;
    long VmLib;
    long VmPTE;
    long VmPMD;
    long VmSwap;
    char Cpus_allowed[256];
    char Cpus_allowed_list[256];
    char Mems_allowed[256];
    char Mems_allowed_list[256];
};

struct mem_info meminfo;

int get_memory_usage_kb(struct mem_info *meminfo);
void print_info(int a, int b, int c);
void parent_info();
