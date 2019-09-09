CSOURCES := $(wildcard *.c)
CFLAGS := -std=c11
COBJS := $(CSOURCES:.c=.o)

CXXSOURCES := $(wildcard *.cc)
CXXFLAGS := -std=c++11
CXXOBJS := $(CXXSOURCES:.cc=.o)

OBJS := $(COBJS) $(CXXOBJS)

.PHONY : all
all : $(OBJS)
	nm $(OBJS)

.PHONY : clean
clean : ; rm -f $(OBJS)
