/*
 * Copyright (c)  2018       The University of Tennessee and The University
 *                           of Tennessee Research Foundation.  All rights
 *                           reserved.
 *
 *  $COPYRIGHT$
 *
 *  Additional copyrights may follow
 *
 */

#include <mpi.h>
#include <stdio.h>
#include <unistd.h>
#include "memory.h"

int main (int argc, char *argv[])
{
    int np;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int processor_name_len;
    int c, aflag, bflag, cflag;
    aflag=bflag=cflag=0;
    int tvalue =0;
    /* lvl 1: for requirment, 2 for interesting, 3 for optional */
    while ((c = getopt (argc, argv, "l:")) != -1)
        switch (c)
        {
            case 'l':
                if(optarg) tvalue = atoi(optarg);
                break;
            default:
                break;
        }
    switch(tvalue)
    {
        case 1:
            aflag = 1;
            break;
        case 2:
            aflag = bflag =1;
            break;
        case 3:
            aflag = bflag =cflag =1;
            break;
        default:
            break;
    }
    MPI_Init(&argc, &argv);
    MPI_Barrier(MPI_COMM_WORLD);

    get_memory_usage_kb(&meminfo);

    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &processor_name_len);
    print_info(aflag, bflag, cflag);
    sleep(3);

    MPI_Finalize();

    return 0;
}
