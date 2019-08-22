#  File name   : Makefile
#  Version     : 02
#  Description : Using make's built-in CFLAGS variable to pass command line
#                options to the GNU gcc C compiler.
#

# (n.b. The right-most option string is 'dash uppercase-oh zero').
CFLAGS := -std=c11 -ggdb -Og

hello-world-c :
