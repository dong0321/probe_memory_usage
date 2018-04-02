#include <stdio.h>
#include <unistd.h>
#include "memory.h"
#define K (1024)
int main (int argc, char *argv[])
{
    int c, aflag, bflag, cflag;
    int tvalue = 1 ;
    aflag=bflag=cflag=0;
    /* a: for requirment, b for interesting, c for optional */
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
    sleep(3);
    get_memory_usage_kb(&meminfo);
    printf("Init: \n");
    print_info(aflag, bflag, cflag);

    char *p1;
    p1=malloc(40*K);
    sleep(3);
    get_memory_usage_kb(&meminfo);
    print_info(aflag, bflag, cflag);

    free(p1);
    sleep(3);
    get_memory_usage_kb(&meminfo);
    print_info(aflag, bflag, cflag);

    return 0;
}
