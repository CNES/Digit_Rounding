#
# Copyright (c) 2019, CNES.
#
# This source code is licensed under MIT-style license (found in the
# COPYING file in the root directory of this source tree).
#

# Requirements:
# - HDF5_PATH should point on the installation path of HDF5
# - HDF5_PLUGIN_PATH should point on the location where the plugin shall be installed 

NAME = H5Zdround
LIBFILE = lib$(NAME).so

INCLUDES = -I./include -I../libdround/include -I$(HDF5_PATH)/include
LIBS = ../libdround/libdround.a

SRC = $(wildcard src/*.c) $(wildcard ../libdround/src/*.c)
OBJ = $(SRC:.c=.o) 

CC = gcc
CFLAGS = -fPIC -W -Wall -ansi -std=c99 -pedantic

# Debug or optimization flag
ifeq ($(DEBUG), 1)
    CFLAGS += -g -DDEBUG
else
    CFLAGS += -O2
endif

default: $(LIBFILE)

$(LIBFILE): $(OBJ)
	$(CC) -shared $^ -o $@ $(LIBS)

%.o: %.c
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) -c $^
	
test: $(LIBFILE)
	@$(MAKE) -e -C $@ run
	
install: $(LIBFILE)	
	@[ -d $(HDF5_PLUGIN_PATH) ] || mkdir -p $(HDF5_PLUGIN_PATH)
	cp -f $(LIBFILE) $(HDF5_PLUGIN_PATH)
	
uninstall:
	rm -f $(HDF5_PLUGIN_PATH)/$(LIBFILE)

clean:
	@$(MAKE) -C test clean
	$(RM) -f *.o $(LIBFILE) $(OBJ)
	
.PHONY: default install uninstall test clean
