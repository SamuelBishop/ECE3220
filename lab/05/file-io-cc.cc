// file-io-cc.cc
// Authors: Luis Rivera, Jim Fischer

// This program expects the user to supply two command line arguments like this:
//
//      ./file-io-cc -n NUMBER
//
// where 'NUMBER' is a non-negative integer value in the range 0 - 99.
//
// The program then tries to open a file named read-NN.txt, where 'NN' is a
// zero-padded representation of NUMBER--e.g., read-02.txt, read-44.txt, etc.
//
// The file `read-NN.txt' must contain zero or more integer values.
//
// Use the file `read-01.txt' that I provided on Canvas with this lab
// assignment as your starting point for experimenting with this code.
//

// Gnu C++ Compiler flags
// CXXFLAGS := -std=c++11 -O0 -ggdb

#include <iostream>     // C++ iostreams (cin,cout,cerr,clog)
#include <string>       // C++ strings
#include <sstream>      // C++ string iostreams
#include <fstream>      // C++ file iostreams
#include <iomanip>      // C++ iostream manipulators
#include <stdexcept>    // C++ exception classes
#include <vector>       // C++ vector class
#include <cstdlib>      // C library strtol() function
#include <cstring>      // C library strcmp() function

// C++ "using declaration"
using namespace std;

const char * program_name = nullptr; // nullptr is specific to c++. Guarenteed to do the right thing across all types of pointers. Super helpful.

void	// This is the method that tells the user the proper way to use the program
usage()
{
    cout << "\nUsage:  " << program_name << " -n NUMBER\nwhere 'NUMBER' is an integer between 0 and 99 inclusive.\n" << endl;
}

// 'argc' := argument count
// 'argv' := argument vector (array of character pointers)

int main(int argc, char *argv[])
{
    int exit_code = 0; // Need to start using the correct exit codes in my assignments

    program_name = argv[0];

    try {
        // The command line should have exactly three arguments
        // 1) This program's name
        // 2) "-n"
        // 3) "<NON_NEGATIVE_INTEGER>"
        // Example: argv[0]="file-io-cc", argv[1]="-n", argv[2]="2"
        if (argc != 3)
            throw runtime_error("Invalid number of command line arguments.");

        // Ensure the second command line argument is the string "-n"
        if( strcmp(argv[1],"-n") != 0 ) {
            ostringstream  error_msg;
            error_msg << "Invalid option '" << argv[1] << "'" << ends;
            throw runtime_error(error_msg.str());
        }

        // The character pointer in argv[2] points to a C-style string that
        // /should/ contain a contiguous sequence of one or more numeric
        // digit characters that form a non-negative integer value, e.g.,
        // "2" or "349" or whatever.  Using the standard library's strtol()
        // function, attempt to convert that string's value into a binary
        // integer value. Note that strtol() stores in 'endptr' the address
        // of the character where scanning stops, which in this case
        // /should/ be the null termination character '\0' at the end of
        // the digit sequence:
        //    "2" -> '2', '\0'                      // valid integer
        //                 ^-- *endptr
        //    "349" -> '3', '4', '9', '\0'          // valid integer
        //                             ^-- *endptr
        //    "56ab" -> '5', '6', 'a', 'b', '\0'    // invalid integer
        //                         ^-- *endptr
        char *endptr = nullptr; // This is the address of the character where we stopped scanning
        int nValue = strtol(argv[2], &endptr, 10); // ASCII table string to long conversion. No need to reinvent the wheel.
        if ( *endptr != '\0' ) { // If the ptr does not conclude on a null terminator
            ostringstream error_msg;
            error_msg << "Invalid numeric argument '" << argv[2] << "' for option -n" << ends;
            throw runtime_error(error_msg.str());
        }
        // Ensure the user-supplied integer falls between 0 and 99, inclusive.
        if ( (nValue < 0) || (nValue > 99) ) {
            ostringstream error_msg;
            error_msg << "Invalid numeric argument '" << argv[2] << "' for option -n" << ends;
            throw runtime_error(error_msg.str());
        }

        // Use a C++ output string string object to build the input file name
        // string `read-01.txt'
        ostringstream fname;
        fname << "read-" << setw(2) << setfill('0') << nValue << ".txt" << ends;
        cout << "read fname  : '" << fname.str() << '\'' << endl;

        // Open the input file that contains the data we want to read.
        ifstream ifs;
        ifs.open(fname.str());
        if ( !ifs ) {
            ostringstream error_msg;
            error_msg << "Failed to open input file " << fname.str() << ends;
            throw runtime_error(error_msg.str());
        }

        // Read integer values from the input file and store these values in a
        // C++ vector object.
        vector<int> file_values;
        while ( 1 ) {
            int value;

            // Attempt to read an integer from the input file stream
            ifs >> value;

            // Check: Did the read attempt set the input file stream's failbit
            // or badbit flags?
            if ( !ifs ) {  // ifs.operator!(), see also std::ios::fail()

                // If the read failed because end-of-file was detected, that's
                // okay. For this case just break out of the while() loop.
                // Otherwise, some other error condition was detected--e.g.,
                // invalid data, stream buffer failure, etc. Respond to these
                // "other" errors by throwing an exception.
                if ( ifs.eof() ) break;
                else {
                    // Whoops; something went horribly wrong. Create an error
                    // message and throw a runtime_error exception.
                    ostringstream error_msg;
                    error_msg << "Read failed from input file " << fname.str() << ends;
                    throw runtime_error( error_msg.str() );
                }
            }

            // If control reaches this point, the read attempt was successful.
            // Store the read-in value into the integer vector object
            // 'file_values'.
            file_values.push_back( value );

        };   // while(1)

        ifs.close();	// Close the input file


        // The vector object `file_values' now contains the integer values that
        // were read successfully from the input file. Write the vector's data
        // into an output file named `write-cc-nn.txt' where 'nn' is the
        // same two-digit padded value we used for the input file name
        // `read-nn.txt'.
        //
        // We'll reuse the output string stream object 'fname' to build the
        // name of the output file name `write-cc-nn.txt'.  Note that
        // 'fname' currently contains the input file name 'read-nn.txt', so
        // we must first a) reset fname's value to the empty string ("")
        // and b) clear its status flags (failbit, badbit, eofbit) before
        // reusing fname to build the output file name string. If we forget
        // to reset fname's value and state, any text we write into fname
        // would be appended to the existing "read-nn.txt" string:
        //    fname << "write-cc-nn.txt"  
        //    =>  fname.str() == "read-nn.txtwrite-cc-nn.txt"
        //
        fname.str("");  // clear the file name string
        fname.clear();  // clear the error reporting flags (failbit, badbit, eofbit)
        fname << "write-cc-" << setw(2) << setfill('0') << nValue << ".txt" << ends;
        cout << "write fname : '" << fname.str() << '\'' << endl;
        
        // Open the output file to be written into.
        ofstream ofs;
        ofs.open( fname.str() );
        if ( !ofs ) {
            ostringstream error_msg;
            error_msg << "Failed to open output file " << fname.str() << ends;
            throw runtime_error(error_msg.str());
        }

        // Write the values from the vector object 'file_values' into the
        // output file.
        for ( auto value : file_values )  {  // <- C++11 "range for" loop
						// vector is a container class. C++ implements the "range" method for iterating
						// over container objects
						// Auto keyword means: 
					    // this is the same thing as all elements in range! for(int i = 0; i < len; i++)
            ofs << "Data " << setfill(' ')
                << setw(12) << right << dec << value << ':'
                << setw(12) << value
                << setw(12) << setprecision(2) << fixed << (value + 0.5)
                << "   0x" << setw(8) << setfill('0') << nouppercase << hex << value
                << endl;
        }
        ofs.close();	// Close the file
        
        cout << "Done! (C++ style)" << endl;

    } // try { }

    catch ( const std::runtime_error &err ) {
        cerr << "\n:: ERROR :: " << err.what() << endl; // this what method is called infomation hiding. the only way to access data elements is through methods. Lets data be proprietary and properly formatted.
        usage(); // learn what this does
        exit_code = 1;
    }

    // If the try block throws an exception that is not caught/handled by any
    // other catch block in this try-catch group, then this "..." catch block
    // catches and handles the exception.
    catch ( ... ) {
        cerr << "\n:: ERROR :: Unexpected exception thrown" << endl;
        exit_code = 2;
    }
	
	return exit_code;
}
