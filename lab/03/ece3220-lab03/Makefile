# Samuel Bishop
# Fischer
# Software Dev in C/C++
# September 5, 2019


CPPFLAGS := # This is how you would apply rules to preprocessor flags
CFLAGS := -std=c11 -ggdb -O0 # Additional instrumentation that applies when compiling c code
CXXFLAGS := -std=c++11 --ggdb -O0 # Additional instrumentation that applies when compiling c++ code
LDD := # This is how you would provide linker instructions

PROGRAMS :=
	SegFault_Example

$(PROGRAMS): 

.PHONY : all 		# Gets rid of executable at runtime so you don't have to retouch the c file every make
clean : ; rm -f $(PROGRAMS)

#SegFault_Example:	# This is how you turn the .c file -> .o file -> executable
