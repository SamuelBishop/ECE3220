/* main.cc */

/*
    Practice Code for the Practical Portion of the Final Exam

    Copyright 2019 James D. Fischer, all rights reserved
*/

#include <atomic>
#include <iostream>
#include <mutex>
#include <stdexcept>

#include "rpi3b_accessory.h"


using namespace ece3220 ;
using namespace std ;


//************************************************************************
//  Global variables
//************************************************************************

// Define global variables for signaling user interactions ("events")
// with pushbutton switches 1 and 5 (BTN1, BTN5) and slider switch 1 (SW1).
// HINT:  std::atomic<bool>  or std::atomic_bool
// HINT:  #include <atomic>

/* Your code here... */

std::atomic<bool>  g_pushbutton1_event_signal { false };


// Within the global namespace, define the mutex objects your program will
// use to serialze access to resources that must be shared across multiple
// threads of execution.

std::mutex  cout_mutex ;


//************************************************************************
//  Interrupt Service Routine (ISR) for pushbutton switch #1 (BTN1)
//  (the left pushbutton)
//
// HINT: Use the rpi3b_accessory class method 'RegisterISR()' to register
// this interrupt in function main (see also `rpi3b_accessory.h').
//************************************************************************

/* Your code here... */

void
ISR_Pushbutton1_Event()
{
    // Inform the other threads that pushbutton 1 was pressed.
    g_pushbutton1_event_signal.store( true );

    { // critical section
        std::lock_guard<std::mutex>  lg ( cout_mutex );
        cout << __PRETTY_FUNCTION__ << endl;
    }
}


//************************************************************************
//  Interrupt Service Routine (ISR) for pushbutton switch #5 (BTN5)
//  (the right pushbutton)
//
// HINT: Use the rpi3b_accessory class method 'RegisterISR()' to register
// this interrupt in function main (see also `rpi3b_accessory.h').
//************************************************************************

/* Your code here... */


//************************************************************************
//  Interrupt Service Routine (ISR) for slider switch #1 (SW1)
//  (the left slider switch)
//
// HINT: Use the rpi3b_accessory class method 'RegisterISR()' to register
// this interrupt in function main (see also `rpi3b_accessory.h').
//************************************************************************

/* Your code here... */


//************************************************************************
//  main()
//************************************************************************

int main()
{
    int  exit_status = 0 ;

    try {
        // Create a reference named 'a' that references the singleton
        // instance of the rpi3b_accessory class.
        auto &a = rpi3b_accessory::get_instance();


        // Register the interrupt service routine(s)
        a.RegisterISR( rpi3b_accessory::switch_pushbutton1,
                INT_EDGE_RISING, &ISR_Pushbutton1_Event );


        // Loop until the user presses pushbutton 1 (BTN1)
        do {

            /* Your code here... */

        } while ( ! g_pushbutton1_event_signal.load() );

    }
    catch ( const std::runtime_error &err ) {
        cerr << ":: ERROR :: " << err.what() << "; aborting...\n";
        exit_status = 1;
    }
    catch ( ... ) {
        cerr << ":: ERROR :: Unexpected exception thrown; aborting...\n";
        exit_status = 1;
    }

    return exit_status ;
}

