/* main.cc */

// imported libraries
#include <string>		// probably a good idea to alphabetize these if this was production code
#include <stdexcept>
#include <iostream>
#include <sstream>

// namespace
using namespace std;

//==========GLOBAL VARIABLES==============

/* -n */
bool cloFilenum = false;
bool cloFilenumValue = 0;

/* -a */
bool cloOffset = false;
double cloOffsetValue = 0.0;

/* -s */
bool cloScaled = false;
double cloScaledValue = 0.0;

/* -h */
bool cloHelp = false;

/* -d */
bool cloDataDir = false;
string cloDataDirValue;
//========================================

class command_line_error : public std::runtime_error {
public:
	// ctors
	// default constructor first calls the other class the construct all of the things in that class
	// without specification the compiler will invoke the default constructor for the base class
	command_line_error ( const std::string& what_arg ) : std::runtime_error( what_arg ) { }
												       //^ How to tell it to class the runtime_error constructor
	command_line_error ( const char* what_arg ) : std::runtime_error( what_arg ) { }
	
	// There is always one and only one destructor for a class. They do the same thing but in reverse
	// destructs nearest class first and then goes up the class heirarchy
};

//==========FUNCTION DECLARATION==========

double // Note these are called stub functions
read_double_from_command_line(char *option, char *arg)
{
	double value = 0.0;
	char *endptr = nullptr;
	value = strtod( arg, &endptr );
	if ( *endptr != '\0' ){
		ostringstream msg;
		msg << "Invalid integer argument '" << arg << "' for option " << option << '.';
		throw command_line_error( msg.str() );
	}
	return value;
}

//========================================

int // Note these are called stub functions
read_int_from_command_line(char *option, char *arg)
{
	int value = 0;
	char *endptr = nullptr;
	value = strtol( arg, &endptr, 10 );
	if ( *endptr != '\0' ){
		ostringstream msg;
		msg << "Invalid integer argument '" << arg << "' for option " << option << '.';
		throw command_line_error( msg.str() );
	}
	return value;
}

//=======================================

string
read_string_from_command_line(char *option, char *arg) 
{
	//string value( arg ); // access the constructor of the string class
                         // because of the way the destructor works then we return a temp copy of the value
	//return value;

    // Or simply do this
    return string( arg );
}

//string x;
//x = read_string_from_command_line( ... );
//========================================

int main ( int argc, char* argv[] ){
	int exit_code = 0; // start assuming everything will be fine

	try{
		// Sidenote: pass by value means carbon copy. Pass by reference means passing the address.
		if( argc > 10 ){ // Error checking the number of args. Hardcoded to 10 currently
			throw runtime_error("Invalid number of command line arguments.");
		}

		// Ensure the second command line argument is the string "-n"
		// Start at one because the first argument is just the name of the program
		for(int i = 1; i < argc; i++){	

				// Remnants of me wanting to go fast
				//if( strcmp(argv[i],"-h") == 0 ) { // we need to check for the -h first
				//	cout << "SYSNOPSYS" << endl << "/t lab6 -n FILENUM [-a OFFSET] [-s SCALE_FACTOR]" << endl << "lab6 -h" << endl
				//  break;
				//}

				if( argv[i][0] != '-'){
					throw command_line_error("One or more of the proper args required did not include a '-'.");
				}

				if( argv[i][1] == 'n' ){
					// EXECUTE a code
					cloFilenum = true;
					++i; // Bump up I to the next argument and then examine the value past it
					if( i >= argc ){
						throw command_line_error("Missing required argument for option '-n'.");
					}
					cloFilenumValue = read_int_from_command_line( argv[i - 1], argv[i] ); //it to invoke the command_line_error ( argv[i] );
				}

				else if( argv[i][1] == 'a' ){
					// EXECUTE a code
					cloOffset = true;
					++i; // Bump up I to the next argument and then examine the value past it
					if( i >= argc ){
						throw command_line_error("Missing required argument for option '-a'.");
					}
					cloOffsetValue = read_double_from_command_line( argv[i - 1], argv[i] );
				}

				else if( argv[i][1] == 's' ){
					// EXECUTE a code
					cloScaled = true;
					++i; // Bump up I to the next argument and then examine the value past it
					if( i >= argc ){
						throw command_line_error("Missing required argument for option '-s'.");
					}
					cloScaledValue = read_double_from_command_line( argv[i - 1], argv[i] );
				}

				else if( argv[i][1] == 'h' ){
					// EXECUTE a code
					cloHelp = true;
					++i; // Bump up I to the next argument and then examine the value past it
					if( i >= argc ){
						throw command_line_error("Missing required argument for option '-h'.");
					}
				}

				else if( argv[i][1] == 'd' ){
					// EXECUTE a code
					cloDataDir = true;
					++i; // Bump up I to the next argument and then examine the value past it
					if( i >= argc ){
						throw command_line_error("Missing required argument for option '-d'.");
					}
					cloDataDirValue = read_string_from_command_line( argv[i - 1], argv[i] );
				}

				else{
					ostringstream msg;
					msg << "Invalid command line option'" << argv[i] << "'.";
					throw command_line_error( msg.str() ); // make a ostringstream here later so user can see what's going on
				}
		}
	}
	// block replacement: In visual mode select the lines hit : and the type s/string_to_replace/string_replacing/g (global)

	// Need to put our derrived class first because of polymorphism	
	catch (const command_line_error &err ){
		cerr << ":: ERROR :: " << err.what() << endl;
		exit_code = 2;
	}

	// Catch all of our thrown errors
	catch ( const std::runtime_error &err ){ // He made a big deal that we will always catch by reference in class
		cerr << "\n:: ERROR :: " << err.what() << endl; // this what method is called infomation hiding. the only way to access data elements is through methods. Lets data be proprietary and properly formatted.
        exit_code = 1;
	}

	// Catch all of the errors that we did not throw
	catch ( ... ) {
        cerr << "\n:: ERROR :: Unexpected exception thrown" << endl;
        exit_code = 3;
    }

    printf("exit code: %d\n", exit_code);
	return exit_code;
}

//Functions that we need eventually
// strtol: string to long -> converts a ascii number to a long int
