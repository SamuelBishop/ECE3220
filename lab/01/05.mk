#
#  File name   : Makefile
#  Version     : 05
#  Description : Phony target `all' to build both C and C++ `hello world'
#                targets. Ensure each recipe line begins with a TAB
#                character.
#

CFLAGS := -std=c11 -ggdb -Og
CXXFLAGS := -std=c++11 -ggdb -Og

# The prerequisites for the phony target `all' are the real targets
# `hello-world-c' and `hello-world-cpp', the executable image files we want
# make to create from the corresponding .c and .cpp source code files.

.PHONY : all
all : hello-world-c hello-world-cpp

.PHONY : clean
clean :
	-rm -f hello-world-c hello-world-cpp
