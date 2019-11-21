/* rpi3b-accessory.h */

#ifndef ECE3220_RPI3B_ACCESSORY_H
#define ECE3220_RPI3B_ACCESSORY_H

/* NOTES
 * In-text references `[n]' used herein are defined at the end of file
 * `rpi3b-accessory.cpp'.
 */

namespace wiringPi {
#include <wiringPi.h>
#include <wiringPiSPI.h>
}

namespace ece3220 {

class rpi3b_accessory {
public:
    // Singleton design pattern.
    // See also [1] in file 'rpi3b-accessory.cpp'.
    static rpi3b_accessory& getInstance();

    // Destructor. This method must be public. 
    ~rpi3b_accessory();

    /****************************************************************/
    /* LEDs                                                         */
    /****************************************************************/

    // wPi virtual pin numbers for the four LEDs on the accessory board.
    // At a command prompt type 'gpio readall' to display a diagram that
    // shows the mapping between physical pins on the accessory board and
    // wPi virtual pin numbers.
    enum led_t {
        led_red     = 8,
        led_yellow  = 9,
        led_green   = 7,
        led_blue    = 21
    };

    /** @brief Turns ON|OFF all LEDs on the accessory board. 
     * @param state [in] HIGH or 1 turns all LEDs ON. LOW or 0 turns all LEDs OFF.
     */
    void ledWriteAll ( int state );

    /** @brief Turns ON|OFF and individual LED on the accessory board.
     * @param color [in] Any one of this class's led enumerated values.
     * @param state [in] HIGH or 1 turns the LED ON. LOW or 0 turns the LED OFF.
     */
    inline void ledWrite ( led_t color, int state )
    { wiringPi::digitalWrite(color,state); }

    /* added */
    /** @brief Turns OFF the the specified LED color
     * @param color [in] Any one of this class's led enumerated values.
     */
    inline void ledOff( led_t color )
    { wiringPi::digitalWrite(color,0); }

    /* added */
    inline void ledOffAll()
    { ledWriteAll(0); }

    /* added */
    /** @brief Turns ON the the specified LED color
     * @param color [in] Any one of this class's led enumerated values.
     */
    inline void ledOn( led_t color )
    { wiringPi::digitalWrite(color,1); }


    /****************************************************************/
    /* 7-Segment Display                                            */
    /****************************************************************/

    // CD4511 BCD-to-7-Segment Latch/Decoder/Driver IC
    // wPi virtual pin numbers for the BCD "A,B,C,D" (a.k.a., D0,D1,D2,D3)
    // inputs on the CD4511 IC, the DP (decimal point) LED on the 7-segment
    // display, and the 7-segment display ENABLE signal on the accessory board.
    // (n.b. On the accessory board the CD4511's latch enable /LE pin is always
    // logic LOW (latch disabled), its lamp test /LT pin is always logic HIGH
    // (lamp test disabled), and its blanking /BL pin is connected to the
    // ENABLE signal (logic LOW blanks (turns OFF) the 7-segment display).)
    //
    // At a command prompt type 'gpio readall' to display a diagram that shows
    // the mapping between physical pins on the accessory board and wPi virtual
    // pin numbers.
    enum display_t {
        display_bcd_a  = 5,
        display_bcd_b  = 6,
        display_bcd_c  = 25,
        display_bcd_d  = 2,
        display_dp     = 4,
        display_enable = 29
    };

    // The state of the BLANKING input on the CD4511B IC.
    enum displayBlankingState_t {
        displayBlanked,
        displayUnblanked
    };

    /** \brief Writes a BCD value to the ABCD inputs on the CD4511 IC.
     * \param bcdValue [in] The four-bit binary coded decimal value to be
     *     written from the RPI to the ABCD inputs on the CD4511 IC.
     * \throws std::runtime_error { Throws a std::runtime_error exception if
     * the condition '0 <= bcdValue <= 9' is false. }
     */
    void  displayWrite( const uint8_t bcdValue );

    /** @brief Turns OFF (disables, blanks) the 7-segment display.
     */
    inline void  displayOff()
    { wiringPi::digitalWrite(display_enable,0); }

    /** @brief Turns ON (enables, un-blanks) the 7-segment display.
     */
    inline void  displayOn()
    { wiringPi::digitalWrite(display_enable,1); }

    /** @brief Turns ON|OFF the decimal point LED on the 7-segment display.
     */
    inline void  displayDecimalPoint( int state )
    { wiringPi::digitalWrite(display_dp,state); }

    /** @brief Returns the CD4511B's current blanking state.
     */
    inline displayBlankingState_t  getDisplayBlankingState() const
    { return displayBlankingState ; }

private:
    // Stores the state of the BLANKING input on the CD4511B IC.
    displayBlankingState_t  displayBlankingState ;

public:
    /****************************************************************/
    /* MCP3004 Analog to Digital Converter (ADC) /dev/spidev.0.0    */
    /****************************************************************/

    enum adc_channel_t {
        adc_channel_0 = 0,    // ?? DEVICE ?? /* SEE SCHEMATIC */
        adc_channel_1 = 1,    // ?? DEVICE ??
        adc_channel_2 = 2,    // ?? DEVICE ??
        adc_channel_3 = 3,    // ?? DEVICE ??
    };

    /** @brief Performs a single-ended measurement at the specified input
     *         channel on the MCP3004 ADC IC.
     * @param adc_channel [in] The ADC input channel to be sampled.
     * @return The 10-bit value sampled at the specified input channel.
     */
    uint32_t adcSample( adc_channel_t  adc_channel );

private:
    // The Raspberry Pi has one SPI bus with two chip select (a.k.a., chip
    // enable) lines: CE0 (/dev/spidev.0.0) and CE1 (/dev/spidev.0.1). On
    // the accessory board the MCP3004's chip select line is connected to
    // ?? WHICH CHIP SELECT LINE ??.  /* <- YOUR ANSWER HERE */
    // chip enable 0 (CE0).
    static const int  spi_adc_csid; // static data members are not part of the obj. Shared.

    // The frequency, in Hertz, for the Raspberry Pi's SPI bus's SCLK line.
    // For the MCP3004 this frequency must be between [500000,32000000] (THIS IS 500KHz (min) - 3.6MHz (max) ON SPECS SHEET) Hz. Wiring pi library is supports 500k- 32M so our bounds are 500K-3.6M
    // chip enable 1 (CE1).
    static const int  spi_sclk_freq; // static variables are declared in (only one of the) cc files

private:
    // Default constructor
    //
    // Singleton design pattern.
    // See also [1] in file 'rpi3b-accessory.cpp'.
    rpi3b_accessory();

    // Copy constructor and copy assignment
    //
    // Singleton design pattern.
    // See also [1] in file 'rpi3b-accessory.cpp'.
    // Tell the C++ compiler it must not synthesize a copy constructor
    // method or a copy assignment operator method for this class.
    rpi3b_accessory(rpi3b_accessory const &) = delete;  // copy constructor
    void operator=(rpi3b_accessory const &) = delete;   // copy assignment
};

} // namespace ece3220

#endif // ECE3220_RPI3B_ACCESSORY_H

