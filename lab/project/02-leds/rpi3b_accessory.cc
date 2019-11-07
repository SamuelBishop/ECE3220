#include "rpi3b_accessory.h"

namespace ece3220 {

/** \brief Default constructor
 */
rpi3b_accessory :: rpi3b_accessory ()
{
    // wiringPi library setup() call
    wiringPiSetup();

    /* LEDs */
   
    // Configure the GPIO pins that are connected to the four LEDs on the
    // accessory board, and then turn OFF the LEDs.
    wiringPi::pinMode( led_red,     OUTPUT  );
    wiringPi::pinMode( led_green,   OUTPUT  );
    wiringPi::pinMode( led_yellow,  OUTPUT  );
    wiringPi::pinMode( led_blue,    OUTPUT  );
}


/** \brief Destructor
 */
rpi3b_accessory :: ~rpi3b_accessory()
{
    /*
     * Configure all GPIO pins as INPUTs
     */
    wiringPi::pinMode( led_red,     INPUT );
    wiringPi::pinMode( led_green,   INPUT );
    wiringPi::pinMode( led_yellow,  INPUT );
    wiringPi::pinMode( led_blue,    INPUT );
}

/** \brief Gets a reference to the singleton instance of the rpi3b_accessory class.
 *  
 *  The singleton instance of the rpi3b_accessory class is constructed the
 *  first time this method is called. See also [1] in `readme.txt'.
 * 
 *  \return Reference to the static sintleton instance.
 */
rpi3b_accessory &
rpi3b_accessory :: getInstance()
{
#if 1
    static rpi3b_accessory  instance;
    return instance;
#else
    // If an object of class `rpi3b_accessory' occupies a large amount of
    // storage, that storage should be allocated dynamically from the
    // system heap at runtime via C++'s `new' operator. The address
    // returned by the new operator should be stored within a C++
    // `unique_ptr<>' smart pointer object having static storage duration
    // within the getInstance() method.
    static std::unique_ptr< rpi3b_accessory >  instance( new rpi3b_accessory );
    return  *instance ;
#endif
}


/** \brief Turns ON|OFF all LEDs on the accessory board. 
 *
 * \param state HIGH or 1 turns all LEDs ON. LOW or 0 turns all LEDs OFF.
 */
void
rpi3b_accessory :: ledWriteAll ( int state )
{
    // Write the value `state' to all four LEDs
    ledWrite( led_red,      state );
    ledWrite( led_yellow,   state );
    ledWrite( led_green,    state );
    ledWrite( led_blue,     state );
}

} // namespace ece3220

