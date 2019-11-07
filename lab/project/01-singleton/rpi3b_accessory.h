#ifndef ECE3220_RPI3B_ACCESSORY_H
#define ECE3220_RPI3B_ACCESSORY_H

namespace wiringPi {
#include <wiringPi.h>
}

namespace ece3220 {

class rpi3b_accessory {

/*******************************************************************/
/*  Singleton Design Pattern                                       */
/*  See also [1] in file 'readme.txt'                              */
/*******************************************************************/

public:

    // Gets a reference to the singleton instance of the rpi3b_accessory
    // class.
    static rpi3b_accessory&  getInstance();


    // Destructor. This method must be public. 
    ~rpi3b_accessory();


    // Singleton design pattern.
    // Disable automatic synthesis of these class methods
    //
    // Note: Scott Meyers' /Effective Modern C++/ book states that deleted
    //       methods should be public because this usually yields more
    //       informative diagnostics from the C++ compiler.
    
    // Telling compiler, "Hey! Don't synthesize this!"
    rpi3b_accessory(rpi3b_accessory const &) = delete;              // copy constructor
    rpi3b_accessory& operator=(rpi3b_accessory const &) = delete;   // copy assignment
    rpi3b_accessory(rpi3b_accessory &&) = delete;                   // move constructor
    rpi3b_accessory& operator=(rpi3b_accessory &&) = delete;        // move assignment

private:
 
    // Default constructor. This method must be private.
    rpi3b_accessory(); // only the class itself is allowed to construct an instance of the class

public:

    // Miscellaneous functions
    void bar();
    void baz();
    void foo();

};  // class rpi3b_accessory

} // namespace ece3220

#endif // ECE3220_RPI3B_ACCESSORY_H

