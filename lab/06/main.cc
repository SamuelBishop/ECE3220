/* main.cc */

// imported libraries

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
double clofScaledValue = 0.0;

/* -h */
bool cloHelp = false;

/* -d */
bool cloDataDir = false;
string cloDataDirValue;

//==========FUNCTION DECLARATION==========

double // Note these are called stub functions
read_from_command_line(char *p)
{
	double value = 0.0;
	// ... fill this in later
	return value;
}

//========================================

int // Note these are called stub functions
read_from_command_line(char *p)
{
	int value = 0;
	// ... fill this in later
	return value;
}

//=======================================

string
read_from_command_line(char *p)
{
	string value;
	// ... fill this in later
	return value;
}
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

				if( arv[i][0] != '-'){
					throw runtime_error("One or more of the proper args required did not include a '-'.");
				}

				if( argv[i][1] == 'n' ){
					// EXECUTE a code
					cloOffset = true;
					++i; // Bump up I to the next argument and then examine the value past it
					if( i >= argc ){
						throw runtime_error("ERROR: Missing required argument for option '-n'.");
					}
					cloOffsetValue = read_double_from_command_line( argv[i] );
				}

				else if( argv[i][1] == 'a' ){
					// EXECUTE a code
					cloOffset = true;
					++i; // Bump up I to the next argument and then examine the value past it
					if( i >= argc ){
						throw runtime_error("ERROR: Missing required argument for option '-a'.");
					}
					cloOffsetValue = read_double_from_command_line( argv[i] );
				}

				else if( argv[i][1] == 's' ){
					// EXECUTE a code
					cloOffset = true;
					++i; // Bump up I to the next argument and then examine the value past it
					if( i >= argc ){
						throw runtime_error("ERROR: Missing required argument for option '-s'.");
					}
					cloOffsetValue = read_double_from_command_line( argv[i] );
				}

				else if( argv[i][1] == 'h' ){
					// EXECUTE a code
					cloOffset = true;
					++i; // Bump up I to the next argument and then examine the value past it
					if( i >= argc ){
						throw runtime_error("ERROR: Missing required argument for option '-h'.");
					}
					cloOffsetValue = read_double_from_command_line( argv[i] );
				}

				else if( argv[i][1] == 'd' ){
					// EXECUTE a code
					cloOffset = true;
					++i; // Bump up I to the next argument and then examine the value past it
					if( i >= argc ){
						throw runtime_error("ERROR: Missing required argument for option '-d'.");
					}
					cloOffsetValue = read_double_from_command_line( argv[i] );
				}

				else{
					throw runtime_error( "Invalid command line option ???" ); // make a ostringstream here later so user can see what's going on
				}
		}
	}

	// Catch all of our thrown errors
	catch ( const std::runtime_error &err ){ // He made a big deal that we will always catch by reference in class
		cerr << "\n:: ERROR :: " << err.what() << endl; // this what method is called infomation hiding. the only way to access data elements is through methods. Lets data be proprietary and properly formatted.
        usage(); // learn what this does
        exit_code = 1;
	}

	// Catch all of the errors that we did not throw
	catch ( ... ) {
        cerr << "\n:: ERROR :: Unexpected exception thrown" << endl;
        exit_code = 2;
    }

	return exit_code;
}
