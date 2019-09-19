// command-line-args.cpp
// Authors: Luis Rivera, Jim Fischer

// CFLAGS := -std=c11 -O0 -ggdb
// CXXFLAGS := -std=c++11 -O0 -ggdb

#include <cstring>
#include <iostream>
#include <string>

using namespace std;

// 'argc' holds the count of command line arguments (argc := argument count),
// including the program name. argc's value is always >= 1 (one). The first
// command line argument is always the file name of the invoked program.
//
// 'argv' is a vector (an array) of pointers to null-terminated C-strings (argv
// := arguments vector). The char pointer at vector offset zero `argv[0]'
// points to a null-terminated C-string whose value is the file name of the
// invoked program.
//
// $ ./program-name  -c  5  -option=xyz  abcd
//   ^^^^^^^^^^^^^^  ^^  ^  ^^^^^^^^^^^  ^^^^
//   |               |   |  |            `-- argv[4]
//   |               |   |  `--------------- argv[3]
//   |               |   `------------------ argv[2]
//   |               `---------------------- argv[1]
//   `-------------------------------------- argv[0]
//   argc == 5 (five arguments)
//
// Try invoking this program without parameters, with one parameter, two, etc.
// Compare the two approaches.

int main(int argc, char *argv[]) // argc = args present on the command line. argv = each command
{
	int i = 0, count;

//
// --- Using a C-style char array ---------------------------------------------
//

	// the strlen function in c uses an iterative function o(n)
	for ( int i = 0;  i < argc; ++i ) {
		cout << "argv[" << i << "] = " << argv[i] << '\n'
             << "strlen(argv[" << i << "] = " << strlen(argv[i]) << '\n'
             << endl;
	}
	
	cout << "=========================================================" << endl;
	
//
// --- Using a C++ string -----------------------------------------------------
//

    // class s has an internal length buffer making operation o(1)
    string s;
	for ( int i = 0;  i < argc; ++i ) {
		s = argv[i]; // convert the C-string into a string
		cout << "argv[" << i << "] = " << s << '\n'
             << "s.length(): " << s.length() << '\n'
             << endl;
	}

	return 0;
}


// To do a change withing selected region :'<, '>s/program-name/xyz/gc (start through end of selection
// replace program-name string with xyz string, not sure what gc does)
