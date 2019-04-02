#
# Copyright (c) 2019, CNES.
#
# This source code is licensed under MIT-style license (found in the
# COPYING file in the root directory of this source tree).
#

EXEC = test_dround

INCLUDES = -I../include -I../../libtestdround/include
LIBS = -lm ../libdround.a ../../libtestdround/libtestdround.a

CC = gcc
CFLAGS = -fPIC -W -Wall -ansi -std=c99 -pedantic

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

default: all

all: $(EXEC)

run: $(EXEC)
	@./$(EXEC)
	
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) -c $^

clean:
	$(RM) -f $(OBJ) $(EXEC)
	
.PHONY: default all run clean
