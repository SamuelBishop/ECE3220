
PROGRAM := homework

# Dependencies
DEPDIR := .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
# DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
DEPFLAGS = -MT $@ -MMD -MF $(DEPDIR)/$*.Td

# C compile options and command line
CFLAGS := -std=c11 -O0 -ggdb -I$(RPIFS)/usr/local/include
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c

# C++ compile options and command line
CXXFLAGS := -std=c++11 -O0 -ggdb -I$(RPIFS)/usr/local/include
COMPILE.cc = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c

# Linking and libraries
LDFLAGS = -L$(RPIFS)/usr/local/lib
LDLIBS =

# Post-compile
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

# Use make's wildcard function to find all of the C source files (.c) in the
# current working directory. Next, use a substitution reference to generate the
# list of C object files (.o) from the list of .c files. (See also make's
# patsubst function.)
CSOURCES := $(wildcard *.c)
COBJS := $(CSOURCES:.c=.o)

# Use make's wildcard function to find all of the C++ source files (.cc,.cpp)
# in the current working directory. Next, use a substitution reference to
# generate the list of C++ object files (.o) from the list of .cpp files. (See
# also make's patsubst function.)
CCSOURCES  := $(wildcard *.cc)
CCOBJS     := $(CCSOURCES:.cc=.o)
CPPSOURCES := $(wildcard *.cpp)
CPPOBJS    := $(CPPSOURCES:.cpp=.o)
CXXSOURCES := $(CCSOURCES) $(CPPSOURCES)
CXXOBJS := $(CCOBJS) $(CPPOBJS)

# Aggregate list of C/C++ sources and their object files.
SOURCES := $(CSOURCES) $(CXXSOURCES)
OBJS    := $(COBJS) $(CXXOBJS)

# Use make's wildcard function to find all of the header files (.h) in the
# current working directory.
HEADERS := $(wildcard *.h)


# The default target
.PHONY : all
all : $(PROGRAM)

# See "Linking a single object file" in [2]. In this case we're linking a set
# of one or more object files as specified by the make variable OBJS.
$(PROGRAM) : $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# Cancel make's implicit rule for .c -> .o translation and replace it with the
# one below that adds a dependency check.
%.o : %.c

# See reference [3] for definition $(OUTPUT_OPTION) == `-o $@'
%.o : %.c $(DEPDIR)/%.d
	$(COMPILE.c) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

# Cancel make's implicit rule for .cc -> .o translation and replace it with
# the one below that adds a dependency check.
%.o : %.cc

# See reference [3] for definition $(OUTPUT_OPTION) == `-o $@'
%.o : %.cc $(DEPDIR)/%.d
	$(COMPILE.cc) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

# Cancel make's implicit rule for .cpp -> .o translation and replace it with
# the one below that adds a dependency check.
%.o : %.cpp

# See reference [3] for definition $(OUTPUT_OPTION) == `-o $@'
%.o : %.cpp $(DEPDIR)/%.d
	$(COMPILE.cc) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

# Include the automatically-generated dependency rules from $(DEPDIR)
include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(SOURCES))))

.PHONY : clean
clean :
	rm -f $(OBJS) $(PROGRAM)
	rm -fr $(DEPDIR)
	find . -name tags -delete

.PHONY : vars
vars :
	$(foreach V, $(sort $(.VARIABLES)), $(if $(filter-out default automatic, $(origin $V)), $(warning $V=$($V) ($(value $V)))))

# References
# [1] http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/
# [2] "10.2 Catalog of Built-In Rules" in /GNU Make Manual/ [online].
#     Available:
#     https://www.gnu.org/software/make/manual/html_node/Catalogue-of-Rules.html#Catalogue-of-Rules
# [3] https://ftp.gnu.org/old-gnu/Manuals/make-3.79.1/html_chapter/make_10.html

