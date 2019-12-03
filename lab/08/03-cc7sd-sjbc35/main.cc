#include <cstdlib>
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
disp_valid_usr_input( rpi3b_accessory &a, const useconds_t sleep_time = 500000 )
{
	a.ledWriteAll( LOW );
	usleep( sleep_time );
	a.ledWrite( rpi3b_accessory::led_green, HIGH);
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

    ready_for_input( a );

    cin >> user_choice;
    while( user_choice != 20){
	    if( user_choice >= 0 && user_choice <= 9 ){
		disp_valid_usr_input( a );
	    }
	    else{
		disp_invalid_usr_input( a );
	    }
    }
    //a.displayOn();

    return exit_code;
}
