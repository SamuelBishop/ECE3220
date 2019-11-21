# Makefile

PROGRAM := demo

SOURCES.cc := $(wildcard *.cc)

OBJS.cc := $(SOURCES.cc:%.cc=%.o)
OBJS := $(OBJS.cc)

CXXFLAGS := -std=c++11 -pedantic -O0
LINK.o = $(LINK.cc)

NM.command := nm -C $(OBJS) | grep compare

.PHONY: all
all : $(PROGRAM)
	@echo "$(NM.command)"
	@echo "--- compare template specializations ---------------------------"
	@$(NM.command) || true

$(PROGRAM) : $(OBJS)
	@$(LINK.o) $^ -o $@

.PHONY: clean distclean
clean distclean : ; -rm -f $(PROGRAM) $(OBJS)

