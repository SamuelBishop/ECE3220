# 
# 2019-04-02 Jim Fischer <fischerjd@missouri.edu>
#

# The name of the program to be created.
PROGRAM := demo

# This Makefile enables GNU GDB runtime debugging support by default. To create
# a "release" build without built-in debugging support, create a hidden file
# named `.release' within the current working directory.
GDB_FLAG := -ggdb
ifneq ($(wildcard ./.release),)
GDB_FLAG :=
endif

# The directory wherein the auto-generated dependency files reside.
DEPDIR := .d
$(shell mkdir -p $(DEPDIR) >/dev/null)

# Automatic creation of dependency rules (via the C preprocessor).
# -MT target
#  		Specifies a custom target for the makefile rule.
# -MMD
#  		List only user header files, not the system headers, in the makefile
#  		rule's dependency list. (See also: -MD)
# -MF file
#       Specifies the output file to write the makefile dependency rule into.
#
DEPFLAGS = -MT $@ -MMD -MF $(DEPDIR)/$*.Td

# C compile
CFLAGS := -std=c11 -O0 $(GDB_FLAG)
COMPILE.c = $(CC) $(DEPFLAGS) $(CPPFLAGS) $(CFLAGS) $(TARGET_ARCH) -c

# C++ compile
CXXFLAGS := -std=c++11 -O0 $(GDB_FLAG)
COMPILE.cc = $(CXX) $(DEPFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(TARGET_ARCH) -c

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
CCSOURCES := $(wildcard *.cc)
CCOBJS := $(CCSOURCES:.cc=.o)
CPPSOURCES := $(wildcard *.cpp)
CPPOBJS += $(CPPSOURCES:.cpp=.o)

# Aggregate list of C/C++ sources and their object files.
SOURCES := $(CSOURCES) $(CCSOURCES) $(CPPSOURCES)
OBJS    := $(COBJS) $(CCOBJS) $(CPPOBJS)

# Use make's wildcard function to find all of the header files (.h) in the
# current working directory.
HEADERS := $(wildcard *.h) $(wildcard *.hh) $(wildcard *.hpp) $(wildcard *.H)

# [Optional]  If you are building software for the Raspberry Pi, store a copy
# of the makefile `rpi.mk' in the current working directory.
ifneq ($(wildcard rpi.mk),)
include rpi.mk
endif

# [Optional]  Any other desired customizations for this build should be defined
# in a makefile named `customize.mk'.
ifneq ($(wildcard customize.mk),)
include customize.mk
endif

# The default build target: `all'
.PHONY : all
all : do_all

$(PROGRAM) : $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)


# Cancel make's implicit rule for .c -> .o translation and replace it with the
# one below.
%.o : %.c

# See reference [2] for $(OUTPUT_OPTION) == `-o $@'
# See reference [4] "Make ignoring Prerequisite that doesn't exist"
$(COBJS) : %.o : %.c $(DEPDIR)/%.d
	$(COMPILE.c) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

# Cancel make's implicit rule for .cc -> .o translation and replace it with the
# one below.
%.o : %.cc

# See reference [2] for $(OUTPUT_OPTION) == `-o $@'
# See reference [4] "Make ignoring Prerequisite that doesn't exist"
$(CCOBJS) : %.o : %.cc $(DEPDIR)/%.d
	$(COMPILE.cc) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

# Cancel make's implicit rule for .cpp -> .o translation and replace it with
# the one below.
%.o : %.cpp

# See reference [2] for $(OUTPUT_OPTION) == `-o $@'
# See reference [4] "Make ignoring Prerequisite that doesn't exist"
$(CPPOBJS) : %.o : %.cpp $(DEPDIR)/%.d
	$(COMPILE.cc) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

# See the section "Avoiding 'No rule to make target ...' Errors" in [1].
$(DEPDIR)/%.d: ;

# "Mark the dependency files precious to make, so they won't be automatically
# deleted as intermediate files" [1].
.PRECIOUS: $(DEPDIR)/%.d

# Include the automatically-generated dependency rules from $(DEPDIR)
include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(SOURCES))))

# Housekeeping
.PHONY : clean
clean :
	rm -f $(OBJS) $(PROGRAM)
	rm -fr $(DEPDIR)

# Print the values of the environment variables and makefile variables (useful
# for debugging the makefile).
# Example:  $ make vars | less
.PHONY : vars
vars :
	$(foreach V, $(sort $(.VARIABLES)), $(if $(filter-out default automatic, $(origin $V)), $(info $V=$($V) ($(value $V)))))

# [Optional] If you want to perform additional tasks after the PROGRAM is
# built, create in the current working directory a makefile named
# `postbuild.mk'.  In that makefile define a make variable `POSTBUILD' whose
# value is `postbuild'. Then define a .PHONY rule named `postbuild' whose first
# prerequisite is `$(PROGRAM)' followed by other prerequisites that should
# be satisfied after the $(PROGRAM) program prerequisite is satisfied, e.g.,
#
# 		POSTBUILD := postbuild
# 		.PHONY : postbuild
# 		postbuild : $(PROGRAM) ...
#
POSTBUILD_MAKEFILE := ./postbuild.mk
ifneq ($(wildcard $(POSTBUILD_MAKEFILE)),)
include $(POSTBUILD_MAKEFILE)
endif

# Helper rule
.PHONY : do_all
do_all : $(PROGRAM) $(POSTBUILD)

# REFERENCES
# [1]  http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/
# [2]  https://ftp.gnu.org/old-gnu/Manuals/make-3.79.1/html_chapter/make_10.html
# [3]  https://www.gnu.org/software/make/manual/html_node/Empty-Recipes.html
# [4]  https://stackoverflow.com/a/34983297/5051940
# [5]  https://www.gnu.org/software/make/manual/html_node/Static-Usage.html#Static-Usage

