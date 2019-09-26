PROGRAM := generate
CFLAGS := -std=c11 -ggdb -O0
$(PROGRAM) : generate.c

.PHONY : clean
clean : ; -rm -f $(PROGRAM)

