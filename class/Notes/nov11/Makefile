# Makefile

PROGRAM := nov11

SOURCES.cc := $(wildcard *.cc)
OBJS.cc := $(SOURCES.cc:.cc=.o) # changing the suffix from .cc to .o using pattern sub

CXXFLAGS := -std=c++11 -O0

.PHONY: all
all : $(PROGRAM)

$(PROGRAM) : $(OBJS.cc)

.PHONY: clean
clean : ; -rm -f $(PROGRAM) $(OBJS.cc)


