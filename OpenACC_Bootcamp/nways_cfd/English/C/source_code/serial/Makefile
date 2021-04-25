# Copyright (c) 2020 NVIDIA Corporation.  All rights reserved. 

CC=	nvc++
CFLAGS=	-lm -I/opt/nvidia/hpc_sdk/Linux_x86_64/20.11/cuda/11.0/include -L/opt/nvidia/hpc_sdk/Linux_x86_64/20.11/cuda/11.0/lib64 -lnvToolsExt
LFLAGS=


# System independent definitions

MF=	Makefile

EXE=	cfd

INC= \
	arraymalloc.h \
	boundary.h \
	cfdio.h \
	jacobi.h

SRC= \
	arraymalloc.cpp \
	boundary.cpp \
	cfd.cpp \
	cfdio.cpp \
	jacobi.cpp

#
# No need to edit below this line
#

.SUFFIXES:
.SUFFIXES: .cpp .o

OBJ=	$(SRC:.cpp=.o)

.cpp.o:
	$(CC) $(CFLAGS) -c $<

all:	$(EXE)

$(OBJ):	$(INC)

$(EXE):	$(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LFLAGS)

$(OBJ):	$(MF)

tar:
	tar cvf cfd.tar $(MF) $(INC) $(SRC)

clean:
	rm -f $(OBJ) $(EXE) velocity.dat colourmap.dat cfd.plt core
