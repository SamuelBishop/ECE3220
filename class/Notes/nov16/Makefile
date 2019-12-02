# Makefile

# library is called wiringPi. In linux so files = Shared Objs

# libwiringPi.so.2.50 #lib+name+.so+.version
# could also use a link that points to where the software is located:
# EX: libwiringPi.so (softlink)


PROGRAM := demo

SOURCES.c := $(wildcard *.c)
SOURCES.cc := $(wildcard *.cc)

OBJS.c := $(SOURCES.c:.c=.o) # any .c file will be converted to .o
OBJS.cc := $(SOURCES.cc:.cc=.o) # any .cc file will be converted to .o
OBJS := $(OBJS.c) $(OBJS.cc) # all of the object code lumped into one


CPPFLAGS := -I /usr/local/include # This is the c/c++ preprocessor instruction set
			#Directory, location
			#Searches our included directories before the system directories

CFLAGS := -std=c11
CXXFLAGS := -std=c++11

LDFLAGS := -L /usr/local/lib # The linker will search these folders frist before the default
LDLIBS := -l wiringPi # linker looks for libwiringPi.so

LINK.o = $(LINK.cc) # This is to utilize the linker for c++ files

$(PROGRAM) : $(OBJS)
	$(LINK.o) $^ $(LDLIBS)-o $@ # $^ left and $@ is target $(LDLIBS) libraries are expanded and implemented

#ldd demo will show all of the linked libraries. Or can do some readelf thing.

.PHONY: clean
clean : ; rm -f $(PROGRAM) $(OBJS)
