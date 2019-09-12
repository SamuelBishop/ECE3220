SRCDIR := ./source
HDIR := ./header

CSOURCES := $(wildcard $(SRCDIR)*.c)
CXXSOURCES := $(wildcard $(SRCDIR)*.cc)
SOURCES := $(CSOURCES) $(CXXSOURCES)
HEADERS := $(wildcard $(HDIR)*.h)
CFLAGS := -std=c11 -O0 -ggdb

#target : prerequisite(s)
#	recipe1
#	recipe2
#	...

hello_world : $(CSOURCES) $(HEADERS)

.PHONY: clean
clean : ; rm -f hello_world

#shortcut ctrl + w + v = vertical split
#         ctrl + w + h = horizonal split	
