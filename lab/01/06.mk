#
#  File name   : Makefile
#  Version     : 06
#  Description : Create executable image files whose file names are
#                different from their source code files' names. Create a
#                user-defined variable `PROGS' for convenience and
#                reliability. Ensure each recipe line begins with a TAB
#                character.
#

CFLAGS := -std=c11 -ggdb -Og
CXXFLAGS := -std=c++11 -ggdb -Og

PROGS := \
	my-hello-c \
	my-hello-cpp

.PHONY : all
all : $(PROGS)

my-hello-c : hello-world-c.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^

my-hello-cpp : hello-world-cpp.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^

.PHONY : clean
clean :
	-rm -f $(PROGS)

