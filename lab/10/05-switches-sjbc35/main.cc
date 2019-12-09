#include <atomic>
#include <mutex>
#include <iostream>
#include <stdexcept>
#include "rpi3b_accessory.h"

// NOTES
// 1) On the accessory board, switch contact bounce is debounced in
//    hardware; therefore, there's no need to implement software debouncing
//    herein.
// 2) According to the wiringPi documentation this callback function "runs
//    concurrently with the main program", which implies this function
//    executes in a separate thread of exection from the main program.
// 3) When using the wiringPi library, user-defined "interrupt service
//    routines" (ISR) are not true ISRs--i.e., they do not execute within
//    the Linux kernel's execution context. These functions are, in fact,
//    application-layer callback functions that execute in a separate
//    thread of execution from the main() program thread.
// 4) It is entirely possible to have multiple threads executing the same
//    callback function concurrently.  Therefore, your callback function
//    must be written so that it is thread-safe.
//    See also: https://en.wikipedia.org/wiki/Thread_safety
//


using namespace ece3220;
using namespace std;

// need to make this atomic so that it gets written to ram. atomic is a built in C++ class
std::atomic<bool> g_pushbutton1_event_signal { false }; // signals an event has occured var
// atomic forces a complete read and write accross threads
std::atomic<bool> g_slider1_event_signal { false };

std::mutex cout_mutex;

void
ISR_pushbutton1_event(){ // inturrupt service routines are always run on a seperate thread of execution.
	//g_pushbutton1_event_signal = true; // an event has happened and we want to signal
	g_pushbutton1_event_signal.store( true ); // storing a val into atomic var
	//cout << __PRETTY_FUNCTION__ << endl; // pretty function is a gnu compiler thing

	{ // critical section

	// use the std::lock_guard namespace to regulate these errors
	std::lock_guard<std::mutex> lg { cout_mutex }; // when called constructor tries to lockmutex. No longer have to lock or unlock mutex manually.

	//cout_mutex.lock(); // if exception thrown here the whole program dies.
	cout << __PRETTY_FUNCTION__ << endl;
	//cout_mutex.unlock();
	}
	// that inserts its own function name
	
} // kills the thread that is running after usage

void
ISR_slider1_event(){ // inturrupt service routines are always run on a seperate thread of execution.
	//g_pushbutton1_event_signal = true; // an event has happened and we want to signal
	g_slider1_event_signal.store( true ); // storing a val into atomic var
	//cout << __PRETTY_FUNCTION__ << endl; // pretty function is a gnu compiler thing
	// that inserts its own function name

	{ // critical section
	std::lock_guard<std::mutex> lg { cout_mutex };
	//cout_mutex.lock();
	cout << __PRETTY_FUNCTION__ << endl;
	//cout_mutex.unlock();
	}
	
} // kills the thread that is running after usage

//========================================================================
//  main()
//========================================================================

int main()
{
    int exit_code = 0;

    rpi3b_accessory &a = rpi3b_accessory::getInstance();
	    try {
        /* YOUR CODE HERE */
		//a.ledWrite( rpi3b_accessory::led_green, wiringPi::digitalRead( rpi3b_accessory::pushbutton1 ) );
		a.ledWrite( rpi3b_accessory::led_red, wiringPi::digitalRead( rpi3b_accessory::slider1 ) );
	
	
		/*do {
			// .. push button pressed
				// main's responsibility to set the signal back to false
				// clear the slider 1 event signal
				g_pushbutton1_event_signal.store( false );
				
				// read the pushbutton gpio pin (high or low?)
				a.ledWrite( rpi3b_accessory::led_green, wiringPi::digitalRead( rpi3b_accessory::pushbutton1 ) );

		} while ( !g_pushbutton1_event_signal.load() ); //continue looping until event occured
*/	
		do {
			// ... when slider pushed
			// was the switch actuated???
			if( g_slider1_event_signal.load() ){
				// main's responsibility to set the signal back to false
				// clear the slider 1 event signal
				g_slider1_event_signal.store( false );
				
				// read the slider1 gpio pin (high or low?)
				a.ledWrite( rpi3b_accessory::led_red, wiringPi::digitalRead( rpi3b_accessory::slider1 ) );
			}
		} while ( !g_pushbutton1_event_signal.load() );
	 }
    catch ( std::runtime_error const &e ) {
        cerr << "\n:: ERROR :: " << e.what() << "; aborting...\n"; 
        exit_code = 1;
    }
    catch ( ... ) {
        cerr << "\n:: ERROR :: Unexpected exception thrown; aborting...\n";
        exit_code = 1;
    }

    return exit_code;
}

