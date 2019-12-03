#include <sstream>
#include <iostream>
#include <unistd.h>
#include "rpi3b_accessory.h"

using namespace ece3220;
using namespace std;

/* Steps 1 and 2 in the lab document
 * Turns off the LEDs, and then flashes the blue LED to prompt input.
 */
void
ready_for_input( rpi3b_accessory &a, const useconds_t sleep_time = 500000 )
{
    a.ledWriteAll( LOW ); // turning off all the physical leds
    a.displayOff();	  // turning off the 7 segment display
    usleep( sleep_time );
    a.ledWrite( rpi3b_accessory::led_blue, HIGH); // indicating wait for user input
}

void
disp_valid_usr_input( rpi3b_accessory &a, int user_input, const useconds_t sleep_time = 500000 )
{
	a.ledWriteAll( LOW );
	usleep( sleep_time );
	a.ledWrite( rpi3b_accessory::led_green, HIGH);
	a.displayOn();
	a.displayWrite( user_input );
	usleep( sleep_time );
}

void
disp_invalid_usr_input( rpi3b_accessory &a, const useconds_t sleep_time = 500000 )
{
	a.ledWriteAll( LOW );
	a.displayOff();
	usleep( sleep_time );
	a.ledWrite( rpi3b_accessory::led_red, HIGH);
	usleep( sleep_time );
}

int main()
{
    int exit_code = 0;

    rpi3b_accessory  &a = rpi3b_accessory::getInstance();

    /* your code here ... */
    // local variables
    int user_choice;
    const useconds_t sleep_time = 500000;

	// ready for input
	try{   
		while( user_choice != 20){
			ready_for_input( a );						// steps 1 & 2
			cin >> user_choice;
			// check if CTRL+D					
			if( cin.eof() ){							// step 3
				break; 									// will always return an exit code of 0
			}
			// check if non-integer value
			if( !cin >> user_choice ){					// step 6
				ostringstream msg;
				msg << "Received input of non-integer data type.";
				throw runtime_error( msg.str() );
			}
			if( user_choice >= 0 && user_choice <= 9 ){	// step 4
				disp_valid_usr_input( a, user_choice );
			}
			else{										// step 5
				disp_invalid_usr_input( a );
			}
		}
	}

	// catch runtime errors
	catch ( const std::runtime_error &err ){
		cerr << "\n:: ERROR :: " << err.what() << endl;
        exit_code = 1;
	}

	// catch general errors
	catch ( ... ) {
        cerr << "\n:: ERROR :: Unexpected exception thrown" << endl;
        exit_code = 3;
	}
    

    return exit_code;
}
