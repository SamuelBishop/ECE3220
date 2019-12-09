#
# DO NOT MODIFY OR DELETE THIS MAKEFILE
#

ifndef DIST_MK
DIST_MK := 1

ECE3220_PRACTICE_RPIFS_HOMEDIR := $(HOME)/rpifs/home/pi
ECE3220_PRACTICE_DIRNAME := ece3220-practice-$(USER)
ECE3220_PRACTICE_SRCDIR := $(ECE3220_PRACTICE_RPIFS_HOMEDIR)/$(ECE3220_PRACTICE_DIRNAME)
ECE3220_PRACTICE_TARBALL_FNAME := $(ECE3220_PRACTICE_DIRNAME).tar.gz
ECE3220_PRACTICE_TARBALL := $(HOME)/$(ECE3220_PRACTICE_TARBALL_FNAME)

ifeq (,$(shell uname -m | grep armv7l))
ECE3220_PRACTICE_SOURCES := $(shell find $(ECE3220_PRACTICE_SRCDIR) -type f)
ECE3220_PRACTICE_SOURCES += $(shell find $(ECE3220_PRACTICE_SRCDIR) -type l -exec readlink -f {} \;)
endif

# Creates on the desktop computer (not on the Raspberry Pi), within the
# student's $HOME directory, a gzip-compressed tarball file named
# 'ece3220-practice-${USER}.tar.gz' that contains the student's Makefile(s)
# and C++ source code files from the practice folder.
.PHONY: dist
dist : check_machine $(ECE3220_PRACTICE_TARBALL)
	@echo "-------------------------------------------------------------------------------"
	tar tvf "$(ECE3220_PRACTICE_TARBALL)"

.PHONY: check_machine
check_machine :
	@if uname -m | grep -q armv7l; then \
		clear; \
		echo "-------------------------------------------------------------"; \
		echo ":: ERROR :: Do not invoke 'make dist' on the Raspberry Pi."; \
		echo "-------------------------------------------------------------"; \
		cat .make-dist-howto; \
		exit 1; \
	fi

$(ECE3220_PRACTICE_TARBALL): $(ECE3220_PRACTICE_SOURCES)
	tar -czf "$@" -C $(ECE3220_PRACTICE_RPIFS_HOMEDIR) \
		--exclude-from=$(ECE3220_PRACTICE_SRCDIR)/.tar-excludes \
		--exclude=$(PROGRAM) \
		$(ECE3220_PRACTICE_DIRNAME)

.PHONY: clean
clean :

.PHONY: distclean
distclean : clean
	-rm -f "$(ECE3220_PRACTICE_TARBALL)"

endif # DIST_MK

