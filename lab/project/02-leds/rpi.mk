# ~/git/courses/ece3220/share/rpi.mk
# Copyright 2019 James D. Fischer, all rights reserved
#
#  rpi.mk
#
#  If you are using makefile `dep-makefile.mk' to build your code and you want
#  to cross compile that code to produced executable code for the Raspberry Pi,
#  create a hidden file named '.rpi' within the source code folder to enable
#  cross compiling for the Raspberry Pi. This also enables linking with the
#  wiringPi library.
#
#  2019-04-02 Jim Fischer <fischerjd@missouri.edu>
#

ifndef RPI_MK
RPI_MK = 1

# The program name
PROGRAM := rpi

# If the build system's CPU type is `armv7l', then assume Make was invoked on
# the Raspberry Pi (RPI) and we're building with the RPI's native toolchain.
# Otherwise, the build host is not the RPI--e.g., Make was invoked on a desktop
# computer--and therefore we're building with a cross toolchain.
#
BUILD_CPU_ARCH := $(shell lscpu | grep 'Architecture:' | sed 's/Architecture:[[:space:]]*//')
ifneq ($(BUILD_CPU_ARCH),armv7l)
	#
	# The BUILD CPU's architecture is NOT `armv7l'; therefore, use the cross
	# toolchain to perform the build.
	#

	# Cross toolchain installation path, bin directory, and program prefix
	RPICROSS_BASEDIR := /usr/local/rpicross
	RPICROSS_BINDIR  := $(RPICROSS_BASEDIR)/bin
	RPICROSS_PREFIX  := arm-linux-gnueabihf-

	# Redefine Make's implicit variables CC and CXX so that Make uses the cross
	# toolchain's C/C++ compilers, not the native toolchain's C/C++ compilers.
	CC := $(RPICROSS_BINDIR)/$(RPICROSS_PREFIX)gcc
	CXX := $(RPICROSS_BINDIR)/$(RPICROSS_PREFIX)g++

	# The path to the folder on the local computer where you've mounted the
	# root directory '/' of the RPI's filesystem.
	RPIFS := $(HOME)/rpifs
endif

endif # ifndef RPI_MK

