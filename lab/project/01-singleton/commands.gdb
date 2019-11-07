# commands.gdb
# vim: set ft=gdb:
#
# Create a debug build of the `rpi' program:
#
#   $ make clean debug
#
# The resulting program `rpi' runs on the Raspberry Pi (not on the desktop PC).
# On the Raspberry pi, use gdb's `-x' command line option to automatically run
# this debug script when invoking a gdb debugging session on the program `rpi'.
#
#   $ gdb -x commands.gdb rpi
#
# The gdb commands in this file can also be sourced into a running gdb session:
#  $ gdb rpi
# (gdb) source -v commands.gdb
#
set print demangle
break rpi3b_accessory.cc:11
break rpi3b_accessory.cc:26
run
p /x instance
#p &instance
#x 20/x <ADDRESS>
next
frame
step
p /x instance
#x 20/x <ADDRESS>
c
c 3
quit

