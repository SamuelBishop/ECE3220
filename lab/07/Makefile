# Makefile

#SIMPLEST MAKEFILE POSSIBLE demo : 


# CXX

# Note the \ \ denotes a singular line
PROGRAM := demo

# Dependency folder
DEPS := deps

# Dependency flags (Td is temp .d file)
DEPFLAGS := -MT $@ -MMD -MF $(DEPDIR)/$*.Td

# C source code and object files
SOURCES.c := $(wildcard *.c)
OBJS.c := $(SOURCES.c:.c=.o) # when find .c replace with .o

# C++ source code and object files
SOURCES.cc :=  $(wildcard *.cc)
OBJS.cc := $(SOURCES.cc:.cc=.o)

OBJS := $(OBJS.c) $(OBJS.cc) # collects all the possible .c and .cc, .o files

# until we build the .o files don't exist. Cannot use wildcard. Have to use pattern substitution rule.

CPPFLAGS := $(DEPFLAGS)
CFLAGS := -std=c11 $(DEPFLAGS)
CXXFLAGS := -std=c++11 -O0 -ggdb $(DEPFLAGS)

.PHONY: all
all : $(PROGRAM)

# this first character on this recipe line must be a tab
# % is the filename placeholder
# %.o : %.c #.c to .o
# %.o : %.cc #.cc to .o
# $^ notates prerequisets and $@ notates target $< uses only the first prereq

$(PROGRAM) : $(OBJS) | $(DEPS) # figuring out all of the dependcies. Need to explicitly list them out. Not scalable (don't hardcode)
	$(CXX) $^ -o $@ 

$(DEPS) : 
	mkdir -p $@

# force make to use out rule to perform translation
%.o : %.c 
%.o : %.c | $(DEPS)
	# already contained within depflags $(CC) -MM $< >$(DEPS)/%.d
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c $< -o $@

%.o : %.cc
%.o : %.cc | $(DEPS)
	# $(CXX) -MM $< >$(DEPS)/%.d
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c $< -o $@

#bringing in all of the dependencies
include $(wildcard $(DEPS)/*.d)

#foo.o : foo.c foo.h
#main.o : main.cc
#rpab.o : rpab.cc

# semicolon starts the recipe early after the prereqs
.PHONY: clean
clean : 
	-rm -f $(PROGRAM) *.o
	-rm -fr $(DEPS)/*.d

# The purpose of putting a dash next to any command line is to ignore any instances that don't exist 
# If error, ignore error and continue on

# Don't need
# -include instructor.mk
