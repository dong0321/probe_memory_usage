#include <stdio.h>
#include <unistd.h>
#include "memory.h"

int main (int argc, char *argv[])
{
    int c, aflag, bflag, cflag;
    aflag=bflag=cflag=0;
    /* a: for requirment, b for interesting, c for optional */
    while ((c = getopt (argc, argv, "abc")) != -1)
        switch (c)
        {
            case 'a':
                aflag = 1;
                break;
            case 'b':
                bflag = 1;
                break;
            case 'c':
                cflag = 1;
                break;
            default:
                break;
        }

    get_memory_usage_kb(&meminfo);
    printf("Init: \n");
    print_info(aflag, bflag, cflag);

    return 0;
}
