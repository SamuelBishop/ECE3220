# ~/git/courses/ece3220/share/Makefile
# Copyright 2019 James D. Fischer, all rights reserved
#
# SYNOPSYS
# 	make {all|release|debug}
#
# DESCRIPTION
# 	The default build is `all' (a.k.a., `release').
#

# [Optional]  Create a makefile named `specs.mk' that provides program-specific
# specifications for this build--e.g., redefine PROGRAM with the desired
# program name; provide version information, and so on. 
ifneq ($(wildcard specs.mk),)
include specs.mk
endif

# The name of the program to be created.
PROGRAM ?= demo

# Determine the build mode: release or debug.  The default build mode is
# 'release'.
# 
# Here are some methods for selecting the 'debug' build mode:
#
#   # Option 1 (one time debug build)
# 	$ make debug
#
# 	# Option 2 (one time debug build)
# 	$ DEBUG=1 make
#
# 	# Option 3 (performs debug build while DEBUG is defined and set)
# 	$ export DEBUG=1
# 	$ make
#
# Note that if the variable DEBUG is defined and set in the environment,
# invoking any make target other than 'debug' yields undefined behavior.
#
ifeq ($(origin DEBUG),environment)
# See options 2 and 3 above
# See also: `.DEFAULT_GOAL' in 
# https://www.gnu.org/software/make/manual/html_node/Special-Variables.html
.DEFAULT_GOAL := debug
endif


# This makefile creates intermediate files (e.g., object files .o) and the
# program file within the folder specified by BUILDDIR. The default location
# for BUILDDIR is the current working directory.
#
BUILDDIR := 

# If BUILDDIR is defined, ensure BUILDDIR ends in '/'.
ifdef BUILDDIR
ifeq (,$(findstring */,$(BUILDDIR)))
BUILDDIR := $(BUILDDIR)/
endif
endif

PROGRAM := $(BUILDDIR)$(PROGRAM)

# DEPDIR is the folder that contains the dependency files %.d for this
# directory's object files %.o. Each object file in the current working
# directory will have an associated dependency file within folder DEPDIR--e.g.,
#    foo.o -> $(DEPDIR)foo.d
#
DEPDIR_NAME := deps
DEPDIR := $(BUILDDIR)$(DEPDIR_NAME)

# If DEPDIR is defined, ensure DEPDIR ends in '/'.
ifdef DEPDIR
ifeq (,$(findstring */,$(DEPDIR)))
DEPDIR := $(DEPDIR)/
endif
endif

# Use make's `wildcard' function to find all of the C source files (.c) in the
# current working directory. Next, use a substitution reference to generate the
# list of C object files (.o) to be created from the list of C source code
# files, as well as the list of dependency files (.d). Ditto for C++ source
# code files (.cc, .cpp). (See also make's `patsubst' function.)
SOURCES.c := $(wildcard *.c)
OBJS.c := $(SOURCES.c:%.c=$(BUILDDIR)%.o)
DEPS.c := $(SOURCES.c:%.c=$(DEPDIR)%.d)

SOURCES.cc := $(wildcard *.cc)
OBJS.cc := $(SOURCES.cc:%.cc=$(BUILDDIR)%.o)
DEPS.cc := $(SOURCES.cc:%.cc=$(DEPDIR)%.d)

SOURCES.cpp := $(wildcard *.cpp)
OBJS.cpp := $(SOURCES.cpp:%.cpp=$(BUILDDIR)%.o)
DEPS.cpp := $(SOURCES.cpp:%.cpp=$(DEPDIR)%.d)

# Aggregate lists of C/C++ source files, object files, and dependency files.
SOURCES := $(SOURCES.c) $(SOURCES.cc) $(SOURCES.cpp)
OBJS    := $(OBJS.c) $(OBJS.cc) $(OBJS.cpp)
DEPS 	:= $(DEPS.c) $(DEPS.cc) $(DEPS.cpp)

# Use make's wildcard function to retrieve the name of every header file in the
# current working directory.
HEADERS := $(wildcard *.h) $(wildcard *.hh) $(wildcard *.hpp) $(wildcard *.H)

# Use the preprocessor to generate files $(BUILDDIR)/$(DEPDIR)%.d that contain
# makefile-compatible dependency rules for each %.o file.
#
# NB: Variable CPP_DEPFLAGS must be a recursively expanded variable because it
# contains references to other variables `$@' and `$*' whose values are unknown
# at this point. These variables must be evaluated later, wherever variable
# CPP_DEPFLAGS is expanded. So use `=' here and not `:='. Ditto for variable
# CPPFLAGS (see below).
#
# -MT target
#  		Specifies a custom target for the makefile rule.
# -MMD
#  		List only user header files, not the system headers, in the makefile
#  		rule's dependency list. (See also: -MD)
# -MF file
#       Specifies the output file to write the makefile dependency rule into.
#
CPP_DEPFLAGS = -MT $@ -MMD -MF $(DEPDIR)$*.Td

# C/C++ preprocessor flags
CPPFLAGS = $(CPP_DEPFLAGS)

# C compiler flags and "C compile" command line
CFLAGS.default := -std=c11
CFLAGS.release := -O3
CFLAGS.debug := -O0 -ggdb
CFLAGS := $(CFLAGS.default)

# C++ compiler flags and "C++ compile" command lines
CXXFLAGS.default := -std=c++11
CXXFLAGS.release := -O3
CXXFLAGS.debug := -O0 -ggdb
CXXFLAGS = $(CXXFLAGS.default)

# Use the C++ compiler, not the C compiler, to invoke the linking process [2].
# See also:
# 	$ make -p -f/dev/null | grep 'LINK.c ='
# 	$ make -p -f/dev/null | grep 'LINK.cc ='
# 	$ make -p -f/dev/null | grep 'LINK.o ='
# 	$ make -p -f/dev/null | grep '$(LINK.o)'
# NB: make invokes the link task using the command line:
#   $(LINK.o) $^ $(LOADLIBS) $(LDLIBS) -o $@
#
LINK.o = $(LINK.cc)

# Post-compile tasks
POSTCOMPILE = @mv -f $(DEPDIR)$*.Td $(DEPDIR)$*.d && touch $@

# [Optional]  If you are building software for the Raspberry Pi, store a copy
# of the makefile `rpi.mk' in the current working directory. The makefile
# `rpi.mk' provides cross compiling support when building your RPI3B programs
# on a desktop computer.
ifneq ($(wildcard rpi.mk),)
include rpi.mk
endif

# [Optional]  If you are building software for the Raspberry Pi, and that
# software usese the wiringPi library, store a copy of makefile `wiringPi.mk'
# in the current working directory. That makefile provides preprocessor,
# compiler, and linker options that ensure the wiringPi library is linked with
# your program.
ifneq ($(wildcard wiringPi.mk),)
include wiringPi.mk
endif

# [Optional]  If Linux pthreads support is required, add a makefile named
# `pthreads.mk' in the current working directory that contains the following
# variable assignments:
# 	CFLAGS   += -pthread
# 	CXXFLAGS += -pthread
# 	LDFLAGS  += -pthread
ifneq (,$(wildcard pthreads.mk))
include pthreads.mk
endif

# [Optional]  Additional variable customizations for this build should be
# defined in a makefile named `variables.mk' located in the current working
# directory.
ifneq ($(wildcard variables.mk),)
include variables.mk
endif


# Builds a 'release' version of the program without debugging support.
# This is the default goal.
#
# See also "6.11 Target-specific Variable Values" in the GNU Make manual.
#
DEFAULT_GOALS := all release
.PHONY : $(DEFAULT_GOALS)
$(DEFAULT_GOALS) : BUILD_MODE := release
$(DEFAULT_GOALS) : DEBUG :=
$(DEFAULT_GOALS) : CFLAGS += $(CFLAGS.release)
$(DEFAULT_GOALS) : CXXFLAGS += $(CXXFLAGS.release)
$(DEFAULT_GOALS) : build_project


# Builds a 'debug' version of the program.
#
# NOTE: As stated in the gcc manual, "If you use multiple -O options, with or
# without level numbers, the last such option is the one that is effective."
#
# See also "6.11 Target-specific Variable Values" in the GNU Make manual.
#
.PHONY : debug
debug : BUILD_MODE := debug
debug : DEBUG := 1
debug : DEBUG_TRACE_LEVEL ?= 1
debug : CPPFLAGS += -DDEBUG=1 -DDEBUG_TRACE_LEVEL=$(DEBUG_TRACE_LEVEL)
debug : CFLAGS += $(CFLAGS.debug)
debug : CXXFLAGS += $(CXXFLAGS.debug)
debug : build_project


# This rule performs the LINK task which links together all the object code
# files (.o) and any libraries, as specified via the LDLIBS variable, into an
# executable image whose name is specified via the PROGRAM variable.
$(PROGRAM) : $(OBJS)
	$(LINK.o) $^ $(LDLIBS) -o $@

# [Optional]  Additional rule customizations for this build should be
# defined in a makefile named `rules.mk' located in the current working
# directory.
ifneq ($(wildcard rules.mk),)
include rules.mk
endif


# Disable make's implicit rule for %.c -> %.o translation [3] and then define
# an implicit rule to perform %.c to %.o translation with file $(DEPDIR)%.d
# declared as a prerequisite. Ditto for %.cc to %.o translation.
#
# Also, declare folder $(DEPDIR) as an order-only prerequisite, and define a
# separate rule to create folder $(DEPDIR) if it doesn't exist.
#
# See reference [4] for $(OUTPUT_OPTION) == `-o $@'
# See reference [5] "Make ignoring Prerequisite that doesn't exist"
# See reference [6] "4.12.1 Syntax of Static Pattern Rules"
# See also "order-only prerequisites" in the GNU Make manual.
# See "Avoid Re-exec of make' in [1], and in particular this section is key:
#     Let's address the first problem above: the re-invocation of make. If you
#     think about it, this re-invocation is really not necessary. Since we know
#     some prerequisite of the target changed, we must rebuild the [%.o] target;
#     having a more up-to-date list won't affect that decision. What we really
#     need is to ensure that the prerequisite list is up-to-date for the next
#     invocation of make, when we need to decide whether to update [the %.o
#     target] again.
#
%.o : %.c
$(BUILDDIR)%.o : %.c $(DEPDIR)%.d | $(BUILDDIR) $(DEPDIR)
	$(COMPILE.c) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

%.o : %.cc
$(BUILDDIR)%.o : %.cc $(DEPDIR)%.d | $(BUILDDIR) $(DEPDIR)
	$(COMPILE.cc) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

%.o : %.cpp
$(BUILDDIR)%.o : %.cpp $(DEPDIR)%.d | $(BUILDDIR) $(DEPDIR)
	$(COMPILE.cpp) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)


# Create the build directory if it doesn't exist.
$(BUILDDIR) : ; @mkdir -p $@ >/dev/null

# Create the dependency directory if it doesn't exist.
$(DEPDIR) : ; @mkdir -p $@ >/dev/null

# If a dependency file $(DEPDIR)%.d is identified as a prerequisite AND file
# $(DEPDIR)%.d does not exist, this rule tells make to treat the non-existent
# prerequisite file as "up-to-date".  See also the section "Avoiding 'No rule
# to make target ...' Errors" in [1]. See also [7].
$(DEPS):

# Include the automatically-generated dependency rules from folder DEPDIR
include $(wildcard $(DEPS))

# House cleaning
.PHONY : clean
clean ::
	-rm -f $(OBJS) $(DEPS) $(PROGRAM)
	-@if [ -n "$(DEPDIR)" -a -d "$(DEPDIR)" ]; then rm -frv $(DEPDIR); fi

.PHONY : distclean
distclean :: clean
	-@rm -f tags
	-@if [ -n "$(BUILDDIR)" -a -d "$(BUILDDIR)" ]; then rm -frv $(BUILDDIR); fi

# Print the value of each environment variable and makefile variable (useful
# for debugging the makefile).
# Example:  $ make vars | less
.PHONY : vars
vars :
	$(foreach V, $(sort $(.VARIABLES)), $(if $(filter-out default automatic, $(origin $V)), $(info $V=$($V) ($(value $V)))))


# [Optional] If you want to perform "check" tasks after the PROGRAM is built,
# create in the current working directory a makefile named `check.mk'.  In that
# makefile define a .PHONY rule named `check' whose first prerequisite is
# `$(PROGRAM)' followed by other prerequisites that should be satisfied after
# the $(PROGRAM) program prerequisite is satisfied, e.g.,
#
# 		.PHONY : check
# 		check : $(PROGRAM) ...
#
CHECK_MAKEFILE := ./check.mk
ifneq ($(wildcard $(CHECK_MAKEFILE)),)
include $(CHECK_MAKEFILE)
endif

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
.PHONY : build_project
build_project : $(PROGRAM) $(POSTBUILD)

# REFERENCES
# [1]  http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/
# [2]  https://stackoverflow.com/a/13375395
# [3]  https://www.gnu.org/software/make/manual/make.html#Match_002dAnything-Rules
# [4]  https://ftp.gnu.org/old-gnu/Manuals/make-3.79.1/html_chapter/make_10.html
# [5]  https://stackoverflow.com/a/34983297/5051940
# [6]  https://www.gnu.org/software/make/manual/html_node/Static-Usage.html#Static-Usage
# [7]  https://www.gnu.org/software/make/manual/html_node/Empty-Recipes.html
#
