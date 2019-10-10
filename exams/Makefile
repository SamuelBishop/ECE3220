XXFLAGS := -std=c++11

PROGRAMS := allocator raii

.PHONY : all
all : $(PROGRAMS)

#
# type:  make allocator
#
allocator : midterm-allocator-$(USER).cc
    $(CXX) $(CXXFLAGS) $< -o $@

    #
    # type:  make raii
    #
    raii : midterm-raii-$(USER).cc
        $(CXX) $(CXXFLAGS) $< -o $@

        .PHONY : clean
        clean : ; -rm -f $(PROGRAMS) *.o
