/* rpi3b-accessory.cc */

#include <sstream>
#include <stdexcept>
#include "rpi3b-accessory.h"


namespace ece3220 {

// The Raspberry Pi has one SPI bus with two chip select (a.k.a., chip
// enable) lines: CE0 (/dev/spidev.0.0) and CE1 (/dev/spidev.0.1). On the
// accessory board the MCP3004's chip select line is connected to 
// /* WHICH CHIP SELECT LINE??? WRITE YOUR ANSWER HERE */.
//
/* static */
const int rpi3b_accessory :: spi_adc_csid = 0;


//const int rpi3b_accessory :: spi_adc_csid = /* YOUR ANSWER HERE: 0 or 1 */ ;


// The frequency, in Hertz, for the Raspberry Pi's SPI bus's SCLK line.
// The wiringPi library supports what range of frequencies?
//     MIN = 500 kHz
//     MAX = 32 MHz
// The MCP3004 supports what range of clock frequencies?
//     MIN = unspecified
//     MAX = 3.2 MHz
//
// Given the clock frequency values above for the wiringPi library and
// MCP3004, what are the allowed clock frequencies for the accessory board:
//     MIN = 500 kHz
//     MAX = 3.2 MHz
//
// Specify a valid clock frequency for the static variable spi_sclk_freq.
//
/* static */
const int rpi3b_accessory :: spi_sclk_freq = 1500000 ; // start half way because wonkness


/** \brief Default constructor
 */
rpi3b_accessory :: rpi3b_accessory ()
: displayBlankingState( displayBlanked )    // display is blanked (OFF) by default
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

    /* SPI Bus */

    // Use the wiringPi library function `wiringPiSPISetup()' to initialize
    // the Raspberry Pi's SPI bus.  If successful, wiringPiSPISetup()
    // returns a file descriptor to the device tree file for the specified
    // SPI bus channel (/dev/spidev0.0 or /dev/spidev0.1). Otherwise,
    // wiringPiSPISetup() returns -1 on error.
    // (n.b. The RPI uses the SPI bus to communicate with the Microchip
    // MCP3004 Analog-to-Digital Conversion (ADC) IC.)
    if ( wiringPi::wiringPiSPISetup( spi_adc_csid, spi_sclk_freq ) == -1 )
        throw std::runtime_error("[rpi3b_accessory()] Library call wiringPi::wiringPiSPISetup() returned error code -1");
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
}


/** \brief Constructs a single, static instance of the rpi3b_accessory class.
 *  
 *  See also [1].
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
    displayBlankingState_t  savedDisplayBlankingState = getDisplayBlankingState();

    // Ensure the 7-segment is blanked (OFF) before changing the BCD value
    // at the "ABCD" inputs on the CD4511B IC.
    displayOff();

    // Output the BCD value specified by `bcdValue' to the CD4511B's ABCD
    // input pins.
    wiringPi::digitalWrite(display_bcd_a,bcdValue & 0x01);  // 2^0 LSB  A  D0
    wiringPi::digitalWrite(display_bcd_b,bcdValue & 0x02);  // 2^1      B  D1
    wiringPi::digitalWrite(display_bcd_c,bcdValue & 0x04);  // 2^2      C  D2
    wiringPi::digitalWrite(display_bcd_d,bcdValue & 0x08);  // 2^3 MSB  D  D3

    // Restore the CD4511B's saved blanking state
    if ( savedDisplayBlankingState == displayUnblanked ) displayOn();
}


/* See pages 19 and 21 in [2], and also [4] */
uint32_t
rpi3b_accessory :: adcSample( rpi3b_accessory::adc_channel_t  adc_channel )
{
    // The MCP3004's 17-bit command string (sent via the SPI bus MOSI
    // line).  Refer to table 5-1 and figure 6-1 in [2]. 
    //
    //          v---vvvvvvvv---vvvvvvvv- 17-bit command string
    // 0b00000001 0bMDDDXXXX 0bXXXXXXXX  // 'X' is a DON'T CARE bit
    //               ^^^---------------- D2, D1, D0  (input channel select bits)
    //              ^------------------- Measurement mode (differential or single-ended)
    //          ^----------------------- Command START bit
    //
    // n.b. The MCP3004 does not use the D2 bit; it's a DON'T CARE bit.
    //
    // The MCP3004's 11-bit response (received via the SPI bus MISO line).
    // 0b00000000 0b000000## 0b########
    //                   ^-------------- NUL bit
    //                    ^^---^^^^^^^^- 10-bit ADC value
    //
    // EXAMPLE COMMAND: Single-ended measurement at input CH1.
    // 0b00000001 0b1001XXXX 0bXXXXXXXX (0x019XXX)
    //               ^^^-- 001 == CH1
    //              ^----- 1 == single-ended measurement mode
    //          ^--------- Command START bit



    // Use a C++ "anonymous union" object named `spibuf' with which to map
    // the 17-bit ADC command/reply text and a 32-bit unsigned integer into
    // the same four bytes of storage.  See also [5].
    //
    // For the ADC command the 32-bit field is initialized as follows:
    //     bits 31..17 are zero padding
    //     bits 16..12 are the ADC command
    //     bits 11..0 are DON'T CARE bits (zero padded)
    // 
    // The MCP3004's response is mapped into the 32-bit field as follows:
    //     bits 31..11 are DON'T care bits (zero padded)
    //     bit 10 is zero
    //     bits 9..0 contain the 10-bit ADC value measured by the MCP3004
    //
    union {
        uint32_t adcReply;
        unsigned char adcBuffer[sizeof(adcReply)];
    } 
    spibuf = { __builtin_bswap32(0x00019000) }; // What is put into the union... RPI uses little endian so we have to do a byte swap.


    // Perform an analog-to-digital conversion on the MCP3004.  Note that
    // there is no need to send the most-significant byte (0x00) of the
    // four-byte adcCommand buffer. Send only the three least-significant
    // bytes.

    // Read/write transactions on the bus can be implemented using the WiringPi function
    // int wiringPiSPIDDataRW (int channel, unsigned char *data, int len);
    // in order to avoid starting at the 1st index of the char array we can use char properties to get that
    // first offset location
    wiringPi::wiringPiSPIDataRW( spi_adc_csid, &spibuf.adcBuffer[1], 3 ); // can send three bytes not rather than 4.

    spibuf.adcReply = __builtin_bswap32(spibuf.adcReply); // need to implement byteswap to get the rotated bytes back into the pi.

    return spibuf.adcReply ;
}

} // namespace ece3220

/*
References
[1]  M. York and T. B. Smith, "C++ Singleton Design Pattern", Sep. 4, 2018
     [online]. Available: https://stackoverflow.com/a/1008289
[2]  Microchip Technology, Inc., "7V 4-Channel/8-Channel 10-Bit A/D
     Converters with SPI Serial Interface", MCP3004/3008 data sheet, 2008
     [Online].  Available: http://ww1.microchip.com/downloads/en/DeviceDoc/21295d.pdf
[3]  G. Henderson, "SPI Library," /Wiring Pi/, 2019 [Online].
     Available: http://wiringpi.com/reference/spi-library/
[4]  G. Henderson, "Priority, Interrupts and Threads," /Wiring Pi/, 2019
     [Online]. Available: http://wiringpi.com/reference/priority-interrupts-and-threads/
[5]  "Struct and Union Initialization," C Language: Initialization, 2018
     [Online]. Available: https://en.cppreference.com/w/c/language/struct_initialization
*/
