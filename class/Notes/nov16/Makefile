# Makefile

CFLAGS := -std=c11
CXXFLAGS := -std=c++11

LINK.o = $(LINK.cc) # This is to utilize the linker

demo : nov16.o foo.o
	$(LINK.o) $^ -o $@ # $^ left and $@ is target

.PHONY: clean
clean : ; rm -f demo *.o
