COURSE      := ece3220
CATEGORY	:= hw
ASSIGNMENT  := 01
USER_MODULE := $(COURSE)-$(CATEGORY)$(ASSIGNMENT)-$(USER)
DELIVERABLE := $(USER_MODULE).tar.gz

# The name of the current working directory
CWD := $(notdir $(PWD))

SUBDIRS := 1.03 1.09 1.11 1.16

.PHONY : all
all :
	@for m in $(SUBDIRS); do \
		if [ -d "$$m" ]; then $(MAKE) -C $$m $@; fi; \
	done

# Create the assignment tarball file
.PHONY : dist
dist : clean $(DELIVERABLE)
$(DELIVERABLE) :
	tar -czf ../$(@) --exclude=$(@) --exclude=.*.swp -C .. --transform="s/$(CWD)/$(USER_MODULE)/" $(CWD)
	mv ../$(@) .

# List the contents of the assignment tarball file
.PHONY : dist-check
dist-check : $(DELIVERABLE)
	tar -tzf $(<)

.PHONY : clean
clean :
	-rm -f $(DELIVERABLE)
	@for m in $(SUBDIRS); do \
		if [ -d "$$m" ]; then $(MAKE) -C $$m $@; fi; \
	done

.PHONY : vars
vars :
	$(foreach V, $(sort $(.VARIABLES)), $(if $(filter-out default automatic, $(origin $V)), $(warning $V=$($V) ($(value $V)))))
