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
    rpi3b_accessory(rpi3b_accessory const &) = delete;              // copy constructor
    rpi3b_accessory& operator=(rpi3b_accessory const &) = delete;   // copy assignment
    rpi3b_accessory(rpi3b_accessory &&) = delete;                   // move constructor
    rpi3b_accessory& operator=(rpi3b_accessory &&) = delete;        // move assignment

private:
 
    // Default constructor. This method must be private.
    rpi3b_accessory();


/*******************************************************************/
/*  Light-Emitting Diodes                                          */
/*******************************************************************/

public:

    // The value of each enumerator within the enumeration `led_type' is the
    // wPi virtual pin number that corresponds to the physical pin number
    // on the RPI3B's 40-pin header that's connected to the specified LED
    // color on the accessory board.
    //
    // HINT: At a command shell prompt type 'gpio readall' to display
    // diagram that shows the mapping between physical pin numbers and wPi
    // virtual pin numbers on the RPI3B's 40-pin header.
    //
    enum led_type {
        led_red     = 8,    // wPi virtual pin # for the red LED
        led_yellow  = 9,    // etc.
        led_green   = 7,
        led_blue    = 21
    };


    /** \brief Turns ON|OFF all LEDs on the accessory board. 
     * \param state [in] HIGH or 1 turns all LEDs ON. LOW or 0 turns all LEDs OFF.
     */
    void ledWriteAll ( int state );


    /** \brief Turns ON|OFF and individual LED on the accessory board.
     * \param color [in] Any one of this class's led_type enumerated values.
     * \param state [in] HIGH or 1 turns the LED ON. LOW or 0 turns the LED OFF.
     */
    inline void ledWrite ( led_type color, int state )
    {
        wiringPi::digitalWrite( color, state );
    }


    /** \brief Turns OFF the the specified LED color
     * \param color [in] Any one of this class's led_type enumerated values.
     */
    inline void ledOff( led_type color )
    {
        wiringPi::digitalWrite( color, LOW );
    }


    /** \brief Turns OFF all LEDs
     */
    inline void ledOffAll()
    {
        wiringPi::digitalWrite ( led_red,       LOW );
        wiringPi::digitalWrite ( led_green,     LOW );
        wiringPi::digitalWrite ( led_yellow,    LOW );
        wiringPi::digitalWrite ( led_blue,      LOW );
    }


    /** \brief Turns ON the the specified LED color
     * \param color [in] Any one of this class's led_type enumerated values.
     */
    inline void ledOn( led_type color )
    {
        wiringPi::digitalWrite ( led_red,       HIGH );
        wiringPi::digitalWrite ( led_green,     HIGH );
        wiringPi::digitalWrite ( led_yellow,    HIGH );
        wiringPi::digitalWrite ( led_blue,      HIGH );
    }

};  // class rpi3b_accessory

} // namespace ece3220

#endif // ECE3220_RPI3B_ACCESSORY_H

