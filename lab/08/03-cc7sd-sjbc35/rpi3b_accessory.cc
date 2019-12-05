#include <memory>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <bitset>
#include "rpi3b_accessory.h"

namespace ece3220 {

/** \brief Default constructor
 */
rpi3b_accessory :: rpi3b_accessory ()
: displayState( displayBlanked )    // display is blanked (OFF) by default
{
    // wiringPi library setup() call
    wiringPi::wiringPiSetup();

    /* LEDs */

    // Configure the GPIO pins that are connected to the four LEDs on the
    // accessory board, and then turn OFF the LEDs.
    wiringPi::pinMode( led_red, OUTPUT );
    wiringPi::pinMode( led_yellow, OUTPUT );
    wiringPi::pinMode( led_green, OUTPUT );
    wiringPi::pinMode( led_blue, OUTPUT );
    ledOffAll();

    /* CD4511B and 7-Segment Display */

    // Configure the GPIO pins that are connected to the CD4511B
    // BCD-to-7-Segment Latch Decoder Driver on the accessory board, and to
    // the decimal point LED on the 7-segment display, and then turn OFF
    // all the segments and the decimal point on the 7-segment display.
    /* your code here ... */
	wiringPi::pinMode( display_bcd_a, OUTPUT );
    wiringPi::pinMode( display_bcd_b, OUTPUT );
    wiringPi::pinMode( display_bcd_c, OUTPUT );
    wiringPi::pinMode( display_bcd_d, OUTPUT );
    wiringPi::pinMode( display_dp, OUTPUT );
    wiringPi::pinMode( display_enable, OUTPUT );
	displayOff();
	displayDecimalPoint( LOW );
   
}


/** \brief Destructor
 */
rpi3b_accessory :: ~rpi3b_accessory()
{
    /*
     * Configure all GPIO pins as INPUTs
     */

    // LED GPIO pins
    wiringPi::pinMode( led_red, INPUT );
    wiringPi::pinMode( led_yellow, INPUT );
    wiringPi::pinMode( led_green, INPUT );
    wiringPi::pinMode( led_blue, INPUT );

    // CD4511B & 7-segment display decimal point GPIO pins
    /* Your code here... */
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
    static rpi3b_accessory  instance;
    return instance;
}


/** \brief Turns ON|OFF all LEDs on the accessory board. 
 *
 * \param state HIGH or 1 turns all LEDs ON. LOW or 0 turns all LEDs OFF.
 */
void
rpi3b_accessory :: ledWriteAll ( int state )
{
    // Write the value `state' to all LEDs
    ledWrite( led_red, state );
    ledWrite( led_yellow, state );
    ledWrite( led_green, state );
    ledWrite( led_blue, state );
}


/** \brief Writes a BCD value to the ABCD inputs on the CD4511B IC.
 * \param bcdValue [in] The four-bit binary coded decimal value to be
 *     written from the RPI to the ABCD inputs on the CD4511B IC.
 *
 * \throws std::runtime_error { Throws a std::runtime_error exception if
 * the condition '0 <= bcdValue <= 9' is false. }
 */
void
rpi3b_accessory :: displayWrite( const uint8_t bcdValue )
{
    // Value check: 0 <= bcdValue <= 9
    if ( bcdValue > 9 ) {
        std::ostringstream message;
        message << "rpi3b_accessory::displayWrite() - Inavlid bcdValue '" << bcdValue << "'";
        throw std::runtime_error( message.str() );
    }

    // Save the CD4511B's current blanking state
    /* your code here ... */
	displayState_type current_blanking_state = getDisplayBlankingState();

    // Ensure the 7-segment is blanked (OFF) before changing the BCD value
    // at the "ABCD" inputs on the CD4511B IC.
    /* your code here... */
	displayOff();

    // Output the BCD value specified by `bcdValue' to the CD4511B's ABCD
    // input pins.
    /* your code here... */
	std::string s = std::bitset<4>(bcdValue).to_string();	
	wiringPi::digitalWrite( display_bcd_a, ((int)s[3] - (int)'0') );
	wiringPi::digitalWrite( display_bcd_b, ((int)s[2] - (int)'0') );
	wiringPi::digitalWrite( display_bcd_c, ((int)s[1] - (int)'0') );
	wiringPi::digitalWrite( display_bcd_d, ((int)s[0] - (int)'0') );

    // Restore the CD4511B's saved blanking state
    /* your code here... */
	wiringPi::digitalWrite( display_enable, current_blanking_state );
}

} // namespace ece3220

