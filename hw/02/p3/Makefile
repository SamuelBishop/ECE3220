PROGRAM := demo

CSOURCES := $(wildcard *.c)
CFLAGS := -std=c11
COBJS := $(CSOURCES:.c=.o)

CXXSOURCES := $(wildcard *.cc)
CXXFLAGS := -std=c++11
CXXOBJS := $(CXXSOURCES:.cc=.o)

OBJS := $(COBJS) $(CXXOBJS)

.PHONY : all
all : $(PROGRAM)

# Note that I am using the C++ compiler $(CXX) to perform the linking step!
$(PROGRAM) : $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LOADLIBES) $(LDLIBS)

.PHONY : clean
clean : ; rm -f $(PROGRAM) $(OBJS)
