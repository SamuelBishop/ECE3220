/* main.cc */

// IMPORTANT NOTES
// echo $? after a run will return the exit code
// ps as | grep firefox to show all of the processes running
// kill -9 to kill it the process. 

// imported libraries
#include <string>		// probably a good idea to alphabetize these if this was production code
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

// namespace
using namespace std;

//==========GLOBAL VARIABLES==============

/* -n */
bool cloFilenum = false;
int cloFilenumValue = 0;

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
void display_help_message()
{

    // lowercase u is undo in visual mode
    // :set will allow you to view your bash settings
    /* formatting
    1. :set tw=65
    2. visual line mode and select
    3. gq
    */

    // how to edit bash script
    // :e~/.vimrc

    // This will be a multiline string literal
    const char* help_message = R"(
SYNOPSYS
    lab6 -n FILENUM [-a OFFSET] [-d DATADIR] [-s SCALE_FACTOR]
    lab6 -h

OPTIONS
    -a OFFSET
        The specified OFFSET value is added to each sample data
        value read from input file raw-data-NN.txt. The transformed
        data values are written into a file named
        offset-data-NN.txt, where NN is a two digit, zero-padded
        integer value whose value is specified by the -n option. For
        example, for -n 3, NN’s value is 03, and program lab6 writes
        the transformed data into a file named offset-data-03.txt.

    -d DATA_DIR
        If the raw data files raw-data-NN.txt do not reside in the
        current working directory, use this option to specify the
        path to the directory where the files reside. If this
        program generates new files that contain transformed data,
        those new files will be stored in the DATA_DIR directory.

    -h HELP
        Displays a useful message that describes how to use this
        program.

    -n FILENUM
        FILENUM is an integer value between 1 and 99 inclusive.
        Program lab6 reads data from a text file named
        raw-data-NN.txt where NN is a two digit, zero-padded
        integer value whose value is specified by FILENUM. For
        ECE 3220 Software Design in C and C++, 2019 Fall 4
        example, if FILENUM’s value is 3, then NN’s value is 03, and
        program lab6 reads from file raw-data-03.txt.

    -s SCALE_FACTOR
        Each sample data value read from input file raw-data-NN.txt
        is multiplied by the specified SCALE_FACTOR value. The
        transformed data values are written into a file named
        scaled-data-NN.txt, where NN is a two digit, zero-padded
        integer value whose value is specified by the -n option. For
        example, for -n 3, NN’s value is 03, and program lab6 writes
        the transformed data into a file named scaled-data-03.txt.
)";

    cout << help_message << endl;
}

//========================================

// Stream buff looks at file as a sequence of characters. Just a glorified array. can parse out the space, and newline ascii chars.

void
open_and_process_the_data_file( const string &fname, vector<int> &data_values ) // pass by reference, (temporarily refer to passed in type object by different name)
{
    ifstream ifs; // This is an automatic storage class the compiler creates on the stack
    ifs.open(fname); // equivalent of fopen
    
    if( !ifs.is_open() ){ // checks if the file is open
	    ostringstream msg;
		msg << "Failed to open input file " << fname << ".";
		throw runtime_error( msg.str() ); // destructor is actually called! File is closed upon out of scope! Destructor is called upon thrown error message. Resource Aquisition is Initialization (RAII).
    }

    int data_set_size;
    ifs >> data_set_size; // this read could fail so we need to check the failbit (read fails), badbit (read fails as result of issues w/buffer), eofbit
    if( !ifs ){ // checks the fail and bad bits 
	    ostringstream msg;
		msg << "Failed to read the dataset size from file" << fname << ".";
		throw runtime_error( msg.str() );
    }

    int upper_limit_val;
    ifs >> upper_limit_val;
    if( !ifs ){ // checks the fail and bad bits 
	    ostringstream msg;
		msg << "Failed to read the upper limit size from file" << fname << ".";
		throw runtime_error( msg.str() );
    }

    int data_value;
    for(int i = 0; i < data_set_size; i++){
        ifs >> data_value;
        if( !ifs ){ // checks the fail and bad bits 
            ostringstream msg;
            msg << "Failed to read data value fropen_and_process_the_data_file(om #" << (i+1) << "from file" << fname << ".";
            throw runtime_error( msg.str() );
        }

        if( data_value < 0 || data_value > upper_limit_val ){
            ostringstream msg;
            msg << "Invalid data value '" << data_value << "' read from input file" << fname << ".";
            throw runtime_error( msg.str() );
        }

        // Store the data value in our vector
        data_values.push_back(data_value);
    }

    // POSIX always ends a file with a newline char. Need to check for this.
    char end;
    ifs >> skipws >> end;

    // check for eof
    if ( !ifs.eof() ){ 
        ostringstream msg;
        msg << "Extraneous data found after reading the last data value from file " << fname << ".";
        throw runtime_error( msg.str() );
    }
    
}

//========================================

double add_offset( const double lhs, const double rhs ){
    return (lhs + rhs);
}

double add_scale ( const double lhs, const double rhs ){
    return (lhs * rhs);
}


// We might now want to use the function pointers in order to work on the file
void
create_modified_output_file( 
const string &fname, 
const vector<int> data_values, 
const double offset,  
double (*operation) (const double, const double) // This is how one declares a function pointer
) // Can do this with function pointers
{
   ofstream ofs;
   ofs.open(fname);

   if(! ofs.is_open()){
       ostringstream msg;
       msg << "Failed to open output file' " << fname << "' for writing.";
       throw runtime_error( msg.str() );
   }

   ofs << data_values.size();
   ofs << ' ' << offset << '\n';

   // ready to write the modified values to the output file
   for( auto value : data_values ){ // auto's type is determined from what is stored in the container. Range for loop.
        ofs << (*operation)(value, offset) << "\n"; // do either operation to all of the values in the vector
   }
}

//========================================

// by passing by reference you save space on the stack because you don't have to make a copy of the variable
// he said convering constructor to convert a string literal into a C++ string object for the second arg

string
create_file_path( const string datadir, const string &fname_prefix, const int filenumValue ){
    // flesh out later
    ostringstream fpath;

    if( !datadir.empty() ){
    // Write the path to the directory that contains the dat files.
    fpath << datadir;

    // The user might specify the path string one of two ways:
    //  -d path
    //  -d path/
    // So we need to add a '/' if it's not already present in the user-supplied path string
    if( datadir.back() != '/' ){
        fpath << '/';
    }

    }

    // Write the file name prefix string
    fpath << fname_prefix;

    // Write the file numer as a zero-padded value in a two character wide
    // field.
    fpath << setw(2) << setfill('0') << filenumValue; // do not set fill without the single quotes

    // Write the ".txt" file extension
    fpath << ".txt";

    cerr << "fpath.str() = |" << fpath.str() << "|\n"; // remember you can view cerr by: 

    return fpath.str();
 }

//========================================

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
					//if( i >= argc ){
					//	throw command_line_error("Missing required argument for option '-h'.");
					//}
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
					throw command_line_error( msg.str() ); // make a ostringstream here later so user can see what's going onV
				}
		}

        //
        // Validate the command line
        //

       
        if ( cloHelp ) {
            // Option 1) ./lab6 -h
            display_help_message();
        }
        else if ( cloFilenum ) {
            // Option 2) ./lab6 -n FILENUM [-a OFFSET] [-d DATADIR] [-s SCALE_FACTOR ]
         
            // Need to create a vector to store data values
            vector<int> data_values;
            
            // Create a string to hold the path name
            string fname;
            

            // Given the user-specified command line options, create the file
            // path string for the file we want to read from.
            //
            // Note we want something like this: /read-raw-NN.txt
            //                                   ^1 ^2     ^3 ^4
            fname = create_file_path( cloDataDirValue, "raw_data_", cloFilenumValue );

            open_and_process_the_data_file( fname, data_values );
            if ( cloOffset ){
                // Given the user-specified command line options, create the file
                // path string for the file we want to write into.
                fname = create_file_path( cloDataDirValue, "offset-data", cloFilenumValue );

                create_modified_output_file( fname, data_values, cloOffsetValue, &add_offset);
            }
            if ( cloScaled ) { 
                // Given the user-specified command line options, create the file
                // path string for the file we want to write into.
                fname = create_file_path( cloDataDirValue, "scaled-data", cloFilenumValue);

                create_modified_output_file( fname, data_values, cloScaledValue, &add_scale);
            }
        }
        else{
            // throw_command_line_error("Invaid command line.");
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

    printf("exit code: %d\n\n", exit_code);
	return exit_code;
}

//Functions that we need eventually
// strtol: string to long -> converts a ascii number to a long int
