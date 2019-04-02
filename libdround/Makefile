#
# Copyright (c) 2019, CNES.
#
# This source code is licensed under MIT-style license (found in the
# COPYING file in the root directory of this source tree).
#

NAME = dround
SHARED_LIB = lib$(NAME).so
STATIC_LIB = lib$(NAME).a

INCLUDES = -I./include

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -fPIC -W -Wall -ansi -std=c99 -pedantic

# Debug or optimization flag
ifeq ($(DEBUG), 1)
    CFLAGS += -g -DDEBUG
else
    CFLAGS += -O2
endif

AR = ar
ARFLAGS = rcs

default: $(STATIC_LIB)

test: $(STATIC_LIB)
	@$(MAKE) -e -C $@ run

# Create a static library which can be embeded in libh5dround
$(STATIC_LIB): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^
	
# Shared library
$(SHARED_LIB): $(OBJ)
	$(CC) -shared $^ -o $@

%.o: %.c
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) -c $^

clean:
	@$(MAKE) -C test clean
	$(RM) -f *.o $(STATIC_LIB) $(SHARED_LIB) $(OBJ)
	
.PHONY: default test clean 
