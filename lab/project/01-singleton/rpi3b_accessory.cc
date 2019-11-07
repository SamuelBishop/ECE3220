#include <iostream>
#include <memory>
#include "rpi3b_accessory.h"

namespace ece3220 {

//////////////////////////////////////////////////////////////////////////
// Default constructor
//
rpi3b_accessory :: rpi3b_accessory ()
{
    /* to do ... */
}


//////////////////////////////////////////////////////////////////////////
// Destructor
//
rpi3b_accessory :: ~rpi3b_accessory ()
{
    /* to do ... */
}


//////////////////////////////////////////////////////////////////////////
// getInstance()
//
// Returns a reference to the sole instance of the rpi3b_accessory class.
// See also [1].
// 
// Storage for the static object 'instance' is allocated in the .bss
// segment when the program is loaded from disk into memory.  The ojbect
// 'instance' is constructed (in place) the first time control reaches the
// declaration
//     static rpi3b_accessory  instance;
// in method getInstance().
//
rpi3b_accessory &
rpi3b_accessory :: getInstance()
{
    static rpi3b_accessory  instance; // if not static it's on the stack
                                      // otherwise it's just in the RAM .bss segment
                                      
    // .bss (block started by symbol S&G ) -> .data (STACK) -> .text (Read only)
    return instance;
}


//////////////////////////////////////////////////////////////////////////

// _FUNCTION_ will return function located in
// __PRETTY_FUNCTION__ contains the object and the namespace etc. Good for debugging.

void
rpi3b_accessory :: bar()
{ std::cout << __PRETTY_FUNCTION__ << std::endl; }


//////////////////////////////////////////////////////////////////////////
void
rpi3b_accessory :: baz()
{ std::cout << __PRETTY_FUNCTION__ << std::endl; }


//////////////////////////////////////////////////////////////////////////
void
rpi3b_accessory :: foo()
{ std::cout << __PRETTY_FUNCTION__ << std::endl; }

} // namespace ece3220


/*
References
[1]  M. York and T. B. Smith, "C++ Singleton Design Pattern", Sep. 4, 2018
     [online]. Available: https://stackoverflow.com/a/1008289/5051940
*/
