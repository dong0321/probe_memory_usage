# default values for NERSC Cori
MPICC?=~/ompi/fast.build/bin/mpicc
MPICFLAGS?=-dynamic
GCC?=gcc


all: be_true check_memory

be_true: CC=$(GCC)
be_true: be_true.c memory.c

check_memory: CC=$(MPICC)
check_memory: CFLAGS+=$(MPICFLAGS)
check_memory: check_memory.c memory.c
