# ~/git/courses/ece3220/share/wiringPi.mk
# Copyright 2019 James D. Fischer, all rights reserved
#
#  wiringPi.mk
#
# When building with a cross toolchain, the toolchain requires access to the
# wiringPi header files and library files which are installed on the RPI's
# filesystem. The easiest way to manage this is to mount the root directory '/'
# of the RPI's filesystem onto any convenient folder within the local
# computer's filesystem--e.g., ${HOME}/rpifs/. (n.b. This must be performed
# prior to invoking `make'. See also: man mount.rpifs).  Define a makefile
# variable `RPIFS' whose value is the path to the folder on the local
# filesystem where you've mounted the RPS's filesystem (the "mount point").
#
# Within this Makefile prepend the makefile variable expansion $(RPIFS) to any
# path string that defines the path to a folder within the RPI's filesystem
# that contains the wiringPi header files or library files:
#
#	wiringPi header files  > $(RPIFS)/usr/local/include/
#	wiringPi library files > $(RPIFS)/usr/local/lib/
#
# Note that when building with the RPI's native toolchain the variable RPIFS
# must be undefined so that it expands to the empty string:
#
# BUILDING WITH A CROSS TOOLCHAIN		BUILDING ON THE RPI
# $(RPIFS)=="${HOME}/ripfs"             $(RPIFS)==""
# ===============================       ===================
# ${HOME}/rpifs/usr/local/include       /usr/local/include
# ${HOME}/rpifs/usr/local/lib           /usr/local/lib
#

ifndef WIRINGPI_MK
WIRINGPI_MK = 1

WIRINGPI_MK_INCLUDEDIR := $(RPIFS)/usr/local/include
WIRINGPI_MK_LIBDIR := $(RPIFS)/usr/local/lib

# Preprocessor options.  Specify the path to the folder where the wiringPi
# library's header files are stored.
CPPFLAGS += -I$(WIRINGPI_MK_INCLUDEDIR)

# GCC linker/loader (ld) options
# -L Specify the path to the folder that contains the library file
#  `libwiringPi.so.*'.
# -pthread Link the program with Linux's pthread library.
# -l Specify the name of the library we want to link our program to.  The
#  wiringPi library's file name is `libwiringPi.so'; therefore, the library's
#  name is `wiringPi' (strip off the `lib' prefix and the `.so.*' suffix).
LDFLAGS += -L$(WIRINGPI_MK_LIBDIR)
LDLIBS += -lwiringPi

# The wiringPi library requires Linux pthreads support
ifneq (,$(wildcard pthreads.mk))
include pthreads.mk
endif

endif # WIRINGPI_MK

