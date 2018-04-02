#include <mpi.h>
#include <stdio.h>
#include <unistd.h>
#include "memory.h"

int main (int argc, char *argv[])
{
    int rank, np;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int processor_name_len;
    int c, aflag, bflag, cflag;
    aflag=bflag=cflag=0;
    int tvalue;
    rank =1;
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
    if(rank==0)
    {
        printf("Init: \n");
        print_info(aflag, bflag, cflag);
    }
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &processor_name_len);

    MPI_Barrier(MPI_COMM_WORLD);
    get_memory_usage_kb(&meminfo);
    if(rank==0)
    {
        printf("\nNprocs=%03d, My_rank=%03d, processor_name=%5s\n",
                np, rank, processor_name);
        print_info(aflag, bflag, cflag);
    }
    sleep(10);
    MPI_Finalize();
    get_memory_usage_kb(&meminfo);
    if(rank==0)
    {
        printf("Finalize: \n");
        print_info(aflag, bflag, cflag);
    }
    return 0;
}
