me   : Makefile
#  Version     : 07
#  Description : Rule `dist' creates the gzipped tarball file (the deliverable)
#                for this lab. Rule `distcheck' lists the contents of the
#                gzipped tarball file.
#

COURSE      := ece3220
CATEGORY    := lab
ASSIGNMENT  := 01
MODULE_ID   := $(COURSE)-$(CATEGORY)$(ASSIGNMENT)-$(USER)
DELIVERABLE := $(MODULE_ID).tar.gz

# The name of the current working directory
CWD := $(notdir $(PWD))

CFLAGS := -std=c11 -ggdb -Og
CXXFLAGS := -std=c++11 -ggdb -Og

SOURCES := \
	hello-world-c.c \
	hello-world-cpp.cpp

PROGS := $(basename $(SOURCES))

.PHONY : all
all : $(PROGS)

# Create the assignment tarball file
.PHONY : dist
dist : distclean $(DELIVERABLE)

$(DELIVERABLE) : *.mk $(SOURCES)
	tar -czf $@ --transform="s@^@$(MODULE_ID)/@" $(sort $^)

# List the contents of the assignment tarball file
.PHONY : distcheck
distcheck : $(DELIVERABLE)
	tar -tzf $(DELIVERABLE)

.PHONY : clean
clean :
	-rm -f $(PROGS) *.o

.PHONY : distclean
distclean : clean
	-rm -f $(DELIVERABLE)

.PHONY : vars
vars :
	$(foreach V, $(sort $(.VARIABLES)), $(if $(filter-out default automatic, $(origin $V)), $(info $V=$($V) ($(value $V)))))
