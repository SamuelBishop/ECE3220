#include <bitset>
#include <memory>
#include <sstream>
#include <stdexcept>
#include "rpi3b_accessory.h"

// To generate trace output as the program executes, define a preprocessor
// macro named `DEBUG_TRACE_LEVEL' and set its value to any positive integer.
// This can be done within specific translation units or universally via a
// makefile, e.g., 
//
//      .PHONY : debug
//      debug : CPPFLAGS += -DDEBUG_TRACE_LEVEL=1
//      debug : CFLAGS += -O0 -ggdb
//      debug : CXXFLAGS += -O0 -ggdb
//      debug : do_all
//
//      $ make debug
//
#ifndef DEBUG_TRACE_LEVEL
#define DEBUG_TRACE_LEVEL 0
#endif


// Byte swapping to accomodate little- and big-endian data storage
#ifdef __GNUG__
#define BSWAP16(n) __builtin_bswap16(n)
#define BSWAP32(n) __builtin_bswap32(n)
#else
#define BSWAP16(n) ((((n)>>8)&0x00FF)|(((n)<<8)&0xFF00))
#define BSWAP32(n) (BSWAP16((n)>>16)&0x0000FFFF)|((BSWAP16(n)<<16)&0xFFFF0000)
#endif

// function declaration
extern void ISR_pushbutton1_event(); // telling compiler what this name means, declared externally
extern void ISR_slider1_event();

namespace ece3220 {

/** \brief Default constructor
 */
rpi3b_accessory :: rpi3b_accessory ()
    : displayBlankingState { display_blanked } // display is blanked (OFF) by default
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
    wiringPi::pinMode( display_bcd_a, OUTPUT );
    wiringPi::pinMode( display_bcd_b, OUTPUT );
    wiringPi::pinMode( display_bcd_c, OUTPUT );
    wiringPi::pinMode( display_bcd_d, OUTPUT );
    wiringPi::pinMode( display_dp, OUTPUT );
    wiringPi::pinMode( display_enable, OUTPUT );
    displayOff();
    displayDecimalPoint(0);

    /* SPI Bus > MicroChip MCP3004 ADC */

    // Use the wiringPi library function `wiringPiSPISetup()' to initialize
    // the Raspberry Pi's SPI bus.  If successful, wiringPiSPISetup()
    // returns a file descriptor to the device tree file for the specified
    // SPI bus channel (/dev/spidev0.0 or /dev/spidev0.1). Otherwise,
    // wiringPiSPISetup() returns -1 on error.
    // (NB: The RPI uses the SPI bus to communicate with the Microchip
    // MCP3004 Analog-to-Digital Conversion (ADC) IC.)
    if ( wiringPi::wiringPiSPISetup( spibus_ce_adc, spiBusSclkFreq ) == -1)
    {
        throw std::runtime_error("[rpi3b_accessory()] Library call wiringPi::wiringPiSPISetup() returned error code -1");
    }

	/* Pushbutton/Slider pinMode setup */
	wiringPi::pinMode( pushbutton1, INPUT );
    wiringPi::pinMode( pushbutton2, INPUT );
    wiringPi::pinMode( pushbutton3, INPUT );
    wiringPi::pinMode( pushbutton4, INPUT );
    wiringPi::pinMode( pushbutton5, INPUT );
    wiringPi::pinMode( slider1, INPUT );
    wiringPi::pinMode( slider2, INPUT );

	/* Register ISRs for our switches */
	wiringPi::wiringPiISR( pushbutton1, INT_EDGE_RISING, &ISR_pushbutton1_event ); // setup button, detection state, and funct ptr
	// have to tell compiler what the function is within the .cc file
	// spawns another thread...

	wiringPi::wiringPiISR( slider1, INT_EDGE_BOTH, &ISR_slider1_event );
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
    wiringPi::pinMode( display_bcd_a, INPUT );
    wiringPi::pinMode( display_bcd_b, INPUT );
    wiringPi::pinMode( display_bcd_c, INPUT );
    wiringPi::pinMode( display_bcd_d, INPUT );
    wiringPi::pinMode( display_dp, INPUT );
    wiringPi::pinMode( display_enable, INPUT );

	/* Pushbutton/Slider pinMode destuct */
	wiringPi::pinMode( pushbutton1, INPUT );
    wiringPi::pinMode( pushbutton2, INPUT );
    wiringPi::pinMode( pushbutton3, INPUT );
    wiringPi::pinMode( pushbutton4, INPUT );
    wiringPi::pinMode( pushbutton5, INPUT );
    wiringPi::pinMode( slider1, INPUT );
    wiringPi::pinMode( slider2, INPUT );
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
    ledWrite( led_red,    state );
    ledWrite( led_yellow, state );
    ledWrite( led_green,  state );
    ledWrite( led_blue,   state );
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


/** \brief Triggers the MCP3004 to sample the voltage ad the specified ADC
 * input using single-ended measurement mode.
 *
 * See pages 19 and 21 in [2], and also [4]
 *
 * \return An unsigned integer whose value is between 0..1023 (the 10-bit
 * ADC value).
 */
uint32_t
rpi3b_accessory :: adcSample( 
        rpi3b_accessory::AdcChannelNumber  adcChannelNumber,
        rpi3b_accessory::AdcMeasurementMode  adcMeasurementMode /* = adc_single_ended */
        )
{
    // The MCP3004's 17-bit command string is sent via the SPI bus's MOSI line.
    // Refer to table 5-1 and figure 6-1 in [2].  (NB: The program must store
    // either zero or one in each of the DON'T CARE bit 'X'.  I'm choosing to
    // store zero in each DON'T CARE bit.)
    //
    //          v---vvvvvvvv---vvvvvvvv- 17-bit command string
    // 0b00000001 0bMDDDXXXX 0bXXXXXXXX  // 'X' is a DON'T CARE bit
    //               ^^^---------------- D2, D1, D0  (input channel select bits)
    //              ^------------------- Measurement mode (differential or single-ended)
    //          ^----------------------- Command START bit
    //
    // n.b. The MCP3004 does not use the D2 bit, so it's a DON'T CARE bit.
    //
    // The MCP3004's 11-bit response (received via the SPI bus MISO line).
    // 0b00000000 0b000000## 0b########
    //                   ^-------------- NUL bit
    //                    ^^---^^^^^^^^- 10-bit ADC value
    //
    // EXAMPLE COMMAND: Perform a single-ended measurement at input CH1.
    // 0b00000001 0b1001XXXX 0bXXXXXXXX (0x019XXX)
    //               ^^^-- 001 == CH1
    //              ^----- 1 == single-ended measurement mode
    //          ^--------- Command START bit
    //
    // After replacing DON'T CARE bits 'X' with zeros:
    // 0b00000001 0b10010000 0b00000000 (0x019000) => 0x019000

    // The (user-defined) C++ union `SpiBusBuffer' defines a four-byte
    // buffer. The union lets the program treat those four bytes as either
    // a four-element array of unsigned char named `adcCommand', or as a
    // 32-bit unsigned integer value named `adcSampleValue'.
    //
    SpiBusBuffer  spibuf = { 
        .adcCommand = {
            0x00,   // padding
            0x01,
            static_cast<unsigned char>( adcMeasurementMode |
                    (adcChannelNumber<<4) ),
            0x00,
        }
    };


#if DEBUG_TRACE_LEVEL > 0
    std::clog << "spibuf.adcCommand=|" << spibuf << "| (big endian)" << std::endl;
#endif


    // Command the MCP3004 to perform an analog-to-digital conversion at the
    // specified input channel.  Note that there is no need to send the
    // most-significant byte (the "padding" byte) 0x00 in the four-byte
    // adcCommand buffer. Send only the three least-significant bytes.
    wiringPi::wiringPiSPIDataRW( spibus_ce_adc, &spibuf.adcCommand[1], 3 );


#if DEBUG_TRACE_LEVEL > 0
    std::clog << "spibuf.adcSampleValue=|" << spibuf << "| (big endian)" << std::endl;
#endif

    // At this point the 32-bit value in spibuf.adcSampleValue is stored with
    // big-endian byte ordering, but it needs to be stored with little-endian
    // byte ordering so that the 32-bit value will be properly evaluated as a
    // 32-bit unsigned int on the RPI3B.  So perform a 32-bit byte swap of the
    // buffer's contents:
    //      0x12AB34CD -> 0xCD34AB12
    spibuf.adcSampleValue = BSWAP32( spibuf.adcSampleValue );

    // Ensure spibuf.adcSampleValue is the 10-bit ADC value and nothing else. Do this
    // by masking out (setting to zero) all bits that do not provide the 10-bit
    // ADC value.
    spibuf.adcSampleValue &= 0x000003FF ;

#if DEBUG_TRACE_LEVEL > 0
    std::clog << "spibuf.adcSampleValue=|" << spibuf << "| (little endian)" << std::endl;
#endif

    return spibuf.adcSampleValue ;
}


// Overloaded output stream insertion operator '<<' for use with objects of the
// union type 'SpiBusBuffer'.  (n.b. This is an ordinary function not a class
// method, and this function's definition must appear within the `ece3220'
// namespace.)
//
std::ostream &
operator << ( std::ostream &os, const rpi3b_accessory::SpiBusBuffer &spibuf )
{
    os << std::bitset<8>( spibuf.adcCommand[0] ) << ' '
       << std::bitset<8>( spibuf.adcCommand[1] ) << ' '
       << std::bitset<8>( spibuf.adcCommand[2] ) << ' '
       << std::bitset<8>( spibuf.adcCommand[3] );
    return os;
}

} // namespace ece3220

