#
#  File name   : Makefile
#  Version     : 03
#  Description : Using make's built-in CXXFLAGS variable to pass command
#                line options to the GNU g++ C++ compiler.
#

# (n.b. The last option is 'dash uppercase-oh zero')
CXXFLAGS := -std=c++11 -ggdb -Og

hello-world-cpp :
