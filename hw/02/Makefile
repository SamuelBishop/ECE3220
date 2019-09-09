COURSE        := ece3220
CATEGORY      := hw
ASSIGNMENT_ID := 02
ASSIGNMENT    := $(COURSE)-$(CATEGORY)$(ASSIGNMENT_ID)
USER_MODULE   := $(ASSIGNMENT)-$(USER)
DELIVERABLE	  := $(USER_MODULE).tar.gz

HANDOUT := $(ASSIGNMENT)-handout.odt
CWD := $(notdir $(PWD))
SUBDIRS := $(shell find . -mindepth 1 -type d)

.PHONY : dist
dist : $(DELIVERABLE)

$(DELIVERABLE) : check clean
	tar -czf ../$@ -C .. $(CWD) --transform="s:^$(CWD):$(USER_MODULE):" 
	mv ../$@ .

.PHONY : check
check :
	@if ! [ -f $(HANDOUT) ]; then \
		>&2 echo "Required file '$(HANDOUT)' is missing. Aborting..."; \
		exit 1; \
	fi

.PHONY : clean
clean :
	-rm -f $(DELIVERABLE)
	@for m in $(SUBDIRS); do \
		if [ -d "$$m" ] && [ -f "$$m/Makefile" ]; then \
			$(MAKE) -s -k -C $$m $@; \
		fi; \
	done
