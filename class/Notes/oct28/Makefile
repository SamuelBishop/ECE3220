
# rules

hello : main.cc # sometimes make does pattern matching. % : %.cc

% : %.c
% : %.cc
% : %.f

# with some files we can no longer depend on the built in rules that make supplies to automatically work and need to specify our
# own compiler, etc.

hello : hello.cc # xyz abc
	# g++ -std=c++11 hello.cc -o hello # we can write this recipe line ourselves manually
	# OR WE CAN AUTO COMPILE
	g++ -std=c++11 $> -o $@
	# $> is prereqs and $@ is the targets
	# $^ means to include only the first thing in the list. If any things are newer than that then rebuild.
	# 


#FORMAT
#target : prequisites(s)
#	recipe ...
#	recipe ...

