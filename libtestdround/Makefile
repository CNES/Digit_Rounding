
#
# Copyright (c) 2019, CNES.
#
# This source code is licensed under MIT-style license (found in the
# COPYING file in the root directory of this source tree).
#

NAME = testdround
LIBFILE = lib$(NAME).a

INCLUDES = -I./include

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -fPIC -W -Wall -ansi -std=c99 -pedantic

AR = ar
ARFLAGS = rcs

default: $(LIBFILE)

# Static library
$(LIBFILE): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) -c $^

clean:
	$(RM) -f *.o $(LIBFILE) $(OBJ)
	
.PHONY: default clean 
