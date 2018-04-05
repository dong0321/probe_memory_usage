/*
 * Copyright (c)  2018       The University of Tennessee and The University
 *                           of Tennessee Research Foundation.  All rights
 *                           reserved.
 *
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

/* parent pid */
int ppid, Ppid;

/* sum of RSS/PSS from /proc/pid/smaps */
int RssSum, PssSum, pRssSum, pPssSum;

/* parent Vmrss/vmsize */
long pVmRSS, pVmSize;


int get_memory_usage_kb(struct mem_info *meminfo)
{
    /* Get the the current process' status file from the proc filesystem */
    FILE* procfile = fopen("/proc/self/status", "r");

    long to_read = 8192;
    char buffer[to_read];
    if( !fread(buffer, sizeof(char), to_read, procfile) )
    {
       //printf("Read proc/self/status error");
       //return -1;
    }
    fclose(procfile);

    char* search_result;
    /* Look through proc status contents line by line */
    char delims[] = "\n";
    char* line = strtok(buffer, delims);
    while (line != NULL )
    {
        search_result = strstr(line, "VmRSS:");
        if (search_result != NULL)
        {
            sscanf(line, "%*s %ld", &meminfo->VmRss);
        }
        search_result = strstr(line, "VmSize:");
        if (search_result != NULL)
        {
            sscanf(line, "%*s %ld", &meminfo->VmSize);
        }

        search_result = strstr(line, "VmPin:");
        if (search_result != NULL)
        {
            sscanf(line, "%*s %ld", &meminfo->VmPin);
        }
        search_result = strstr(line, "RssShmem:");
        if (search_result != NULL)
        {
            sscanf(line, "%*s %ld", &meminfo->RssShmem);
        }
        search_result = strstr(line, "RssAnon:");
        if (search_result != NULL)
        {
            sscanf(line, "%*s %ld", &meminfo->RssAnon);
        }
        search_result = strstr(line, "RssFile:");
        if (search_result != NULL)
        {
            sscanf(line, "%*s %ld", &meminfo->RssFile);
        }

        search_result = strstr(line, "VmData:");
        if (search_result != NULL)
        {
            sscanf(line, "%*s %ld", &meminfo->VmData);
        }
        search_result = strstr(line, "VmStk:");
        if (search_result != NULL)
        {
            sscanf(line, "%*s %ld", &meminfo->VmStk);
        }
        search_result = strstr(line, "VmExe:");
        if (search_result != NULL)
        {
            sscanf(line, "%*s %ld", &meminfo->VmExe);
        }
        search_result = strstr(line, "VmLib:");
        if (search_result != NULL)
        {
            sscanf(line, "%*s %ld", &meminfo->VmLib);
        }
        search_result = strstr(line, "VmPTE:");
        if (search_result != NULL)
        {
            sscanf(line, "%*s %ld", &meminfo->VmPTE);
        }
        search_result = strstr(line, "VmPMD:");
        if (search_result != NULL)
        {
            sscanf(line, "%*s %ld", &meminfo->VmPMD);
        }
        search_result = strstr(line, "VmSwap:");
        if (search_result != NULL)
        {
            sscanf(line, "%*s %ld", &meminfo->VmSwap);
        }
        search_result = strstr(line, "Cpus_allowed:");
        if (search_result != NULL)
        {
            sscanf(line, "%*s %s", meminfo->Cpus_allowed);
        }
        search_result = strstr(line, "Cpus_allowed_list:");
        if (search_result != NULL)
        {
            sscanf(line, "%*s %s", meminfo->Cpus_allowed_list);
        }
        search_result = strstr(line, "Mems_allowed:");
        if (search_result != NULL)
        {
            sscanf(line, "%*s %s", meminfo->Mems_allowed);
        }
        search_result = strstr(line, "Mems_allowed_list:");
        if (search_result != NULL)
        {
            sscanf(line, "%*s %s", meminfo->Mems_allowed_list);
        }

       search_result = strstr(line, "PPid:");
       if (search_result != NULL)
       {
           sscanf(line, "%*s %d", &ppid);
       }
       line = strtok(NULL, delims);
    }
    smap_pss_rss(0);
    smap_pss_rss(ppid);
    parent_info();
    return 1;
}

void parent_info()
{
    char* search_result;
    char pfilename[50];
    long prt_to_read = 8192;
    char prt_buffer[prt_to_read];
    Ppid=ppid;
    /* Look through proc status contents line by line */
    char delims[] = "\n";

    snprintf(pfilename, sizeof pfilename, "/proc/%d/status", ppid);
    FILE* pfile = fopen(pfilename, "r");
    if( !fread(prt_buffer, sizeof(char), prt_to_read, pfile))
    {
        //printf("Read /proc/parent/status/ error");
    }
    fclose(pfile);

    char* pline = strtok(prt_buffer, delims);
    while (pline != NULL )
    {
        search_result = strstr(pline, "VmRSS:");
        if (search_result != NULL)
        {
            sscanf(pline, "%*s %ld", &pVmRSS);
        }
        search_result = strstr(pline, "VmSize:");
        if (search_result != NULL)
        {
            sscanf(pline, "%*s %ld", &pVmSize);
        }
        pline = strtok(NULL, delims);
    }
}

void smap_pss_rss(int pid)
{
    char pfilename[50];
    FILE *procfile;

    if( pid==0 )
    {
        procfile = fopen("/proc/self/smaps", "r");
    }
    else
    {
        snprintf(pfilename, sizeof pfilename, "/proc/%d/smaps", pid);
        procfile = fopen(pfilename, "r");
    }
    long to_read = 500000;
    char buffer[to_read];
    if( !fread(buffer, sizeof(char), to_read, procfile) )
    {
        //printf("Read /proc/pid/smaps error");
    }
    fclose(procfile);
    int Rss, Pss;
    char* search_result;
    /* Look through proc status contents line by line */
    char delims[] = "\n";
    char* line = strtok(buffer, delims);
    while (line != NULL )
    {
        search_result = strstr(line, "Rss:");
        if (search_result != NULL)
        {
            sscanf(line, "%*s %d", &Rss);
            if( pid==0 )
            {
                RssSum = RssSum + Rss;
            }
            else
            {
                pRssSum = pRssSum + Rss;
            }
        }
        search_result = strstr(line, "Pss:");
        if (search_result != NULL)
        {
            sscanf(line, "%*s %d", &Pss);
            if( pid==0 )
            {
                PssSum = PssSum + Pss;
            }
            else
            {
                pPssSum = pPssSum + Pss;
            }
        }
        line = strtok(NULL, delims);
    }
}
void print_info(int aflag, int bflag, int cflag)
{
    if(aflag)
    {
        printf("%6d,  %6ld, %6ld, %6d, %6d, %6d, %6ld, %6ld, %6d, %6d", rank, meminfo.VmRss, meminfo.VmSize, RssSum, PssSum, Ppid, pVmRSS, pVmSize, pRssSum, pPssSum);
    }

    if(bflag)
    {
        printf("    VmPin: %6ld KB, RssAnon: %6ld KB, RssFile: %6ld KB, RssShmem: %6ld KB\n", meminfo.VmPin, meminfo.RssAnon, meminfo.RssFile, meminfo.RssShmem);
    }

    if(cflag)
    {
        printf("    VmData: %6ld KB, VmStk: %6ld KB, VmExe: %6ld KB, VmLib: %6ld KB, VmPTE: %6ld KB, VmPMD: %6ld KB, VmSwap: %6ld KB\n",
                meminfo.VmData, meminfo.VmStk, meminfo.VmExe, meminfo.VmLib, meminfo.VmPTE, meminfo.VmPMD, meminfo.VmSwap);

        printf("    Cpus_allowed: %s, Cpus_allowed_list: %s, Mems_allowed: %s, Mems_allowed_list: %s\n",
                meminfo.Cpus_allowed, meminfo.Cpus_allowed_list, meminfo.Mems_allowed, meminfo.Mems_allowed_list);
    }
    printf("\n");
}
