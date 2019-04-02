#
# Copyright (c) 2019, CNES.
#
# This source code is licensed under MIT-style license (found in the
# COPYING file in the root directory of this source tree).
#

EXEC = test_h5dround

INCLUDES = -I../include -I../../libdround/include -I../../libtestdround/include -I$(HDF5_PATH)/include
LIBS = -L$(HDF5_PATH)/lib -L.. -lm -lhdf5 -lH5Zdround ../../libtestdround/libtestdround.a

CC = gcc
CFLAGS = -fPIC -W -Wall -ansi -std=c99 -pedantic

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

default: all

all: $(EXEC)

run: $(EXEC)
	@HDF5_PLUGIN_PATH=.. ./$(EXEC)
	
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIBS) -Wl,-rpath=..

%.o: %.c
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) -c $^

clean:
	$(RM) -f $(OBJ) $(EXEC) sample.h5
	
.PHONY: default all run clean
