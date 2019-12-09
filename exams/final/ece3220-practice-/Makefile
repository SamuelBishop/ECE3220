# Sample Makefile for the practical portion of the final exam in ECE 3220.
#
# NB: Uses make's built-in rules to create/update the project's object code
# files (%.o) with respect to their corresponding source code files (%.cc).
#
# NB: Make's built-in rules DO NOT update the project's object code files (%.o)
# when a header file is edited/modified; therefore, a user-defined rule must be
# added to this Makefile that defines the desired header file dependencies with
# respect to the project's object code files.
#
# Copyright 2019 James D. Fischer, all rights reserved

PROGRAM := rpi

SOURCES := $(wildcard *.cc)
HEADERS := $(wildcard *.h)
OBJS := $(SOURCES:.cc=.o)

CPPFLAGS := -I /usr/local/include
CXXFLAGS := -std=c++11 -O3 -pthread
LDFLAGS  := -L /usr/local/lib
LDLIBS   := -l wiringPi

LINK.o = $(LINK.cc)

# Ensure the object code files (OBJS) are all up-to-date, and then create the
# program file from the object code files.
$(PROGRAM) : $(OBJS)
	$(LINK.o) $^ $(LDLIBS) -o $@

# Ensure the object code files are recompiled if any header file is modified.
$(OBJS) : $(HEADERS)

.PHONY: clean
clean : ; -rm -f $(PROGRAM) $(OBJS)

## Ensure this 'include' directive is the last line in your Makefile.
## DO NOT modify or delete this 'include' directive.
include dist.mk

