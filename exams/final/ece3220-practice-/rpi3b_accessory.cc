/* rpi3b_accessory.cc */

/*
    Practice Code for the Practical Portion of the Final Exam

    Copyright 2019 James D. Fischer, all rights reserved
*/

#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>

#include "rpi3b_accessory.h"


namespace ece3220 {


//************************************************************************
//  rpi3b_accessory()
//************************************************************************

rpi3b_accessory :: rpi3b_accessory()
{
    // Initialize the wiringPi library. Use the wiringPi library's
    // virtual pin numbering scheme.
    wiringPi::wiringPiSetup();

    /* Light-Emitting Diodes */

    // Use the wiringPi library to configure the GPIO pins that are
    // connected to the LEDs. These LED GPIO pins must be configured as
    // OUTPUT pins.
    wiringPi::pinMode( led_red, OUTPUT );
    wiringPi::pinMode( led_yellow, OUTPUT );
    wiringPi::pinMode( led_green, OUTPUT );
    wiringPi::pinMode( led_blue, OUTPUT );
    ledWriteAll( 0 );

    /* CD4511B and 7-Segment Display */

    // Configure the GPIO pins that are connected to the CD4511B
    // BCD-to-7-Segment Latch Decoder Driver on the accessory board, and to
    // the decimal point LED on the 7-segment display, and then turn OFF
    // all the segments and the decimal point on the 7-segment display.
    wiringPi::pinMode( display_bcd_a, OUTPUT );
    wiringPi::pinMode( display_bcd_b, OUTPUT );
    wiringPi::pinMode( display_bcd_c, OUTPUT );
    wiringPi::pinMode( display_bcd_d, OUTPUT );
    wiringPi::pinMode( display_dp, OUTPUT );
    wiringPi::pinMode( display_enable, OUTPUT );
    displayOff();
    displayDecimalPoint(0);

    /* Switches */

    // Use the wiringPi library to configure the GPIO pins that are
    // connected to pushbutton switches 1 and 5 (BTN1, BTN5) and slider
    // switch 1 (SW1).  These switch GPIO pins must be configured as
    // INPUT pins.

    wiringPi::pinMode( switch_pushbutton1, INPUT );
}


//************************************************************************
//  ~rpi3b_accessory()
// HINT: Resource acquisition is initialization (RAII).
//************************************************************************

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
    wiringPi::pinMode( display_bcd_a, INPUT );
    wiringPi::pinMode( display_bcd_b, INPUT );
    wiringPi::pinMode( display_bcd_c, INPUT );
    wiringPi::pinMode( display_bcd_d, INPUT );
    wiringPi::pinMode( display_dp, INPUT );
    wiringPi::pinMode( display_enable, INPUT );

    // Switches

    /* Your code here... */
    wiringPi::pinMode( switch_pushbutton1, INPUT );
    
}


//************************************************************************
//   DO NOT MODIFY ANY CODE BELOW THIS LINE
//************************************************************************


//************************************************************************
//  get_instance()
//
// Returns a reference to the singleton instance of the rpi3b_accessor
// class.
//************************************************************************

rpi3b_accessory &
rpi3b_accessory :: get_instance()
{
    /* DO NOT MODIFY THE CODE IN THIS METHOD */
    static std::unique_ptr<rpi3b_accessory>  instance( new rpi3b_accessory );
    return  *instance ;
}


//************************************************************************
//  ledWriteAll()
//
// Turns ON | OFF all leds.
//************************************************************************

void
rpi3b_accessory :: ledWriteAll( int state )
{
    /* DO NOT MODIFY THE CODE IN THIS METHOD */
    ledWrite( led_red, state );
    ledWrite( led_yellow, state );
    ledWrite( led_green, state );
    ledWrite( led_blue, state );
}


//************************************************************************
//  displayWrite()
//************************************************************************
/** \brief Writes a BCD value to the ABCD inputs on the CD4511B 7-Segment
 *     Display Decoder/Driver IC.
 * \param bcdValue [in] The four-bit binary coded decimal value to be
 *     written from the RPI to the ABCD inputs on the CD4511B IC.
 *
 * \throws std::runtime_error { Throws a std::runtime_error exception if
 * the condition '0 <= bcdValue <= 9' is false. }
 */
void
rpi3b_accessory :: displayWrite( const uint8_t bcdValue )
{
    /* DO NOT MODIFY THE CODE IN THIS METHOD */

    // Value check: 0 <= bcdValue <= 9
    if ( bcdValue > 9 ) {
        std::ostringstream message;
        message << "rpi3b_accessory::displayWrite() - Inavlid bcdValue '" << bcdValue << "'";
        throw std::runtime_error( message.str() );
    }

    // Save the CD4511B's current blanking state
    DisplayBlankingState  savedDisplayBlankingState = getDisplayBlankingState();

    // Ensure the 7-segment is blanked (OFF) before changing the BCD value
    // at the "ABCD" inputs on the CD4511B IC.
    displayOff();

    // Output the BCD value specified by `bcdValue' to the CD4511B's ABCD
    // input pins.
    wiringPi::digitalWrite( display_bcd_a, bcdValue & 0x01 );  // 2^0 LSB  A  D0
    wiringPi::digitalWrite( display_bcd_b, bcdValue & 0x02 );  // 2^1      B  D1
    wiringPi::digitalWrite( display_bcd_c, bcdValue & 0x04 );  // 2^2      C  D2
    wiringPi::digitalWrite( display_bcd_d, bcdValue & 0x08 );  // 2^3 MSB  D  D3

    // Restore the CD4511B's saved blanking state
    if ( savedDisplayBlankingState != display_blanked ) displayOn();
}

} // namespace ece3220

