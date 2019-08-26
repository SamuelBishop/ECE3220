R := ar

// Command line options, or "flags", for the 'ar' program:
// r - (option) Use replacement when inserting code into the library archive
// c - (option) Create the specified library archive file if it does not exist
// s - (modifier) Write an object-file index into the archive, or update the existing index
// v - (modifier) Requests verbose messaging to stdout for each operation performed
ARFLAGS := rcsv

// The object files whose contents are to be stored in a library archive file.
OBJS := x.o y.o z.o

// The library archive's file name is 'mylib.a'
mylib.a : $(OBJS)
	$(AR) $(ARFLAGS) $@ $^
	# ^--> expands to:  ar rcsv mylib.a x.o y.o z.o

# Where
$@ = mylib.a
$^ = $(OBJS) = x.o y.o z.o
