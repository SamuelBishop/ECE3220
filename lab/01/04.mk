#
#  File name   : Makefile
#  Version     : 04
#  Description : Phony target `clean' deletes the generated target file
#                `hello-world-cpp' (the executable image file). Ensure the
#                recipe line `-rm -fv hello-world-cpp' begins with a TAB
#                character.
#

CXXFLAGS := -std=c++11 -ggdb -Og

hello-world-cpp :

.PHONY : clean
clean :
	-rm -fv hello-world-cpp
