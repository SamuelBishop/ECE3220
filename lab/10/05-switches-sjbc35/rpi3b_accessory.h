#ifndef ECE3220_RPI3B_ACCESSORY_H
#define ECE3220_RPI3B_ACCESSORY_H

#include <cstdint>
#include <iostream>

namespace wiringPi {
#include <wiringPi.h>
#include <wiringPiSPI.h>
}

namespace ece3220 {


///////////////////////////////////////////////////////////////////////////
// 
//   class  rpi3b_accessory
//
class rpi3b_accessory {

/*******************************************************************/
/*  Singleton Design Pattern                                       */
/*  See also [1] in file 'readme.txt'                              */
/*******************************************************************/

public:

    // Accessor method that returns a reference to the singleton instance
    // of the rpi3b_accessory class.
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

    // The value of each enumerator within the enumeration `GpioLed' is the
    // wPi virtual pin number that corresponds to the physical pin number
    // on the RPI3B's 40-pin header that's connected to the specified LED
    // color on the accessory board.
    //
    // HINT: At a command shell prompt type 'gpio readall' to display a
    // diagram that shows the mapping between physical pin numbers and wPi
    // virtual pin numbers on the RPI3B's 40-pin header.
    //
    enum GpioLed {
        led_red     = 8,
        led_yellow  = 9,
        led_green   = 7,
        led_blue    = 21,
    };


    /** \brief Turns ON|OFF all LEDs on the accessory board. 
     * \param state [in] HIGH or 1 turns all LEDs ON. LOW or 0 turns all LEDs OFF.
     */
    void ledWriteAll ( int state );


    /** \brief Turns ON|OFF and individual LED on the accessory board.
     * \param led_color [in] Any one of this class's GpioLed enumerated values.
     * \param state [in] HIGH or 1 turns the LED ON. LOW or 0 turns the LED OFF.
     */
    inline void ledWrite ( GpioLed led_color, int state )
    {
        wiringPi::digitalWrite( led_color, state );
    }


    /** \brief Turns OFF the the specified LED color
     * \param led_color [in] Any one of this class's GpioLed enumerated values.
     */
    inline void ledOff( GpioLed led_color )
    {
        wiringPi::digitalWrite( led_color, 0 );
    }


    /** \brief Turns OFF all LEDs
     */
    inline void ledOffAll()
    {
        ledWriteAll(0);
    }


    /** \brief Turns ON the the specified LED color
     * \param led_color [in] Any one of this class's GpioLed enumerated values.
     */
    inline void ledOn( GpioLed led_color )
    {
        wiringPi::digitalWrite( led_color, 1 );
    }


/*******************************************************************/
/*  7-Segment Display                                              */
/*******************************************************************/

private:

    // CD4511 BCD-to-7-Segment Latch/Decoder/Driver IC
    //
    // Each enumerator value within enumeration `GpioDisplay' is the
    // wiringPi virtual pin number that corresponds to the physical pin
    // number on the RPI3B's 40-pin header that's connected to the
    // specified BCD A,B,C,D inputs (a.k.a., D0,D1,D2,D3) on the CD4511 IC,
    // the DP (decimal point) LED on the 7-segment display, and the
    // 7-segment display ENABLE signal on the accessory board.
    //
    // NOTES
    // 1) On the accessory board the CD4511's latch enable /LE pin is
    //    always logic LOW which disables the CD4511's latches, thereby
    //    making CD4511's outputs transparent to the BCD inputs--i.e.,
    //    changes at the BCD inputs propagate immediately through the
    //    CD4511 to its a-g outputs. The CD4511's lamp test /LT input is
    //    always logic HIGH (lamp test disabled), and its blanking /BL
    //    input is connected to the accessory board's ENABLE signal.
    //    Setting ENABLE LOW "blanks" (turns OFF) the a-g outputs, thereby
    //    turning OFF the 7-segment display (but not the display's decimal
    //    point; see note 2 below).
    // 2) The 7-segment display's decimal point LED is not controlled via
    //    the CD4511. It has a dedicated signal line `DP' on the RPI3B's
    //    40-pin header.
    //
    // HINT: At a command shell prompt type 'gpio readall' to display a
    // diagram that shows the mapping between physical pin numbers and wPi
    // virtual pin numbers on the RPI3B's 40-pin header.
    //
    enum GpioDisplay {
        display_bcd_a = 5,
        display_bcd_b = 6,
        display_bcd_c = 25,
        display_bcd_d = 2,
        display_dp = 4,
        display_enable = 29,
        display_blanking = display_enable,
    };

 
    // The state of the accessory board's ENABLE signal (i.e., the state of
    // the BLANKING input on the CD4511B IC).
    //
    enum DisplayBlankingState {
        display_blanked,
        display_unblanked,
    };

    // Stores the current state of the accessory board's ENABLE signal
    // (i.e., the current state of the BLANKING input on the CD4511B IC).
    //
    DisplayBlankingState  displayBlankingState ;

public:

    /** \brief Writes a BCD value to the ABCD inputs on the CD4511 IC.
     * 
     * \param bcdValue [in] The four-bit binary coded decimal value to be
     *     written from the RPI to the ABCD inputs on the CD4511 IC.
     *
     * \throws std::runtime_error { Throws a std::runtime_error exception if
     * the condition '0 <= bcdValue <= 9' is false. }
     */
    void  displayWrite( const uint8_t bcdValue );


    /** \brief Turns OFF (disables, blanks) the 7-segment display (but not
     * the decimal point).
     * 
     * Turns off the a-g segment LEDs on the 7-segment display.  This
     * method does not control the 7-segment display's decimal point LED;
     * see instead the method `displayDecimalPoint(state)'.
     */
    inline void  displayOff()
    {
        wiringPi::digitalWrite( display_enable, 0 );
    }


    /** \brief Turns ON (enables, un-blanks) the 7-segment display.
     */
    inline void  displayOn()
    {
        wiringPi::digitalWrite( display_enable, 1 );
    }


    /** \brief Turns ON|OFF the decimal point LED on the 7-segment display.
     */
    inline void  displayDecimalPoint( int state )
    {
        wiringPi::digitalWrite( display_dp, state );
    }


    /** \brief Returns the CD4511B's current state.
     */
    inline DisplayBlankingState  getDisplayBlankingState() const
    {
        return  displayBlankingState ;
    }


/*******************************************************************/
/*  MCP3004 Analog to Digital Converter (ADC) /dev/spidev0.0       */
/*******************************************************************/

public:

    // The value of each enumerator within the enumeration
    // `AdcChannelNumber' identifies an analog input channel number (CH#)
    // on the MCP3004 analog-to-digital converter IC on the accessory
    // board. The MCP3004 has four single-ended analog input channels:
    // CH0..CH3.
    //
    enum AdcChannelNumber {
        adc_ch0 = 0,    // Photodiode
        adc_ch1 = 1,    // Potentiometer
        adc_ch2 = 2,    // ADC header, A2 pin
        adc_ch3 = 3,    // ADC header, A3 pin
        adc_photodiode = adc_ch0,
        adc_potentiometer = adc_ch1,
    };

    enum AdcMeasurementMode {
        adc_differential = 0x00,
        adc_single_ended  = 0x80,
    };

    /** \brief Performs a single-ended measurement at the specified input
     *         channel on the MCP3004 ADC IC.
     * \param adcChannelNumber [in] The ADC input channel to be sampled.
     * \param adcMeasurementMode [in] Single-ended or differential.
     * \return The 10-bit value sampled at the specified input channel.
     */
    uint32_t adcSample ( 
            AdcChannelNumber adcChannelNumber, 
            AdcMeasurementMode adcMeasurementMode = adc_single_ended
            );


/*******************************************************************/
/*  Serial Peripheral Interface (SPI) Bus                          */
/*******************************************************************/

private:

    // The Raspberry Pi 3 Model B(+) has one SPI bus with two chip enable
    // (a.k.a., chip select, slave select) lines: CE0 (/dev/spidev0.0) and CE1
    // (/dev/spidev0.1). On the accessory board, chip select line CE0 is
    // assigned to the MCP3004 analog-to-digital converter (ADC) IC.
    //
    enum SpiBusChipEnable {
        spibus_ce0,
        spibus_ce1,
        spibus_ce_adc = spibus_ce0,
    };


    // Create a four-byte buffer that will be used when communicating with
    // the MCP3004 ADC IC via the RPI's SPI bus.  The bits in this buffer
    // will be sequentially clocked out/in via the SPI bus's MOSI/MISO
    // lines.  These four bytes must store and represent two distinct data
    // types--a four-element array of unsigned characters, and a 32-bit
    // unsigned integer. Therefore, a C++ union is used to map these two
    // data types onto the same four bytes of storage.
    //
    union  SpiBusBuffer {
        uint32_t  adcSampleValue ;
        unsigned char  adcCommand[ sizeof(adcSampleValue) ];
    };


    // Overload the output stream insertion operator '<<' for use with
    // objects of the union type 'SpiBusBuffer'.  (n.b. This is an ordinary
    // function, not a class method, and this function's definition must
    // appear within the `ece3220' namespace.)
    //
    friend std::ostream &
    operator << ( std::ostream &o, const SpiBusBuffer &spibuf );


    // The clock frequency in Hertz for the Raspberry Pi's SPI bus's
    // SCLK line when communicating with the MCP3004.  The SCLK
    // frequency fsclk must fall within the range
    //      fmin <= fsclk <= fmax
    // where the values `fmin' and `fmax' are constrained by the
    // supported min/max SCLK frequencies for the wiringPi library and
    // the MCP3004 IC.
    //
    // The wiringPi library supports what range of frequencies?
    //     MIN = 500 kHz
    //     MAX = 32 MHz
    //
    // The MCP3004 supports what range of clock frequencies? (NB: The Raspberry Pi
    // uses 3v3 logic.)
    //     MIN = 10 kHz
    //     MAX = 1.35 MHz
    //
    // Given the clock frequency values above for the wiringPi library and
    // MCP3004, what are the values for `fmin' and `fmax'?
    //     fmin = 500 kHz
    //     fmax = 1.35 MHz
    //
    static const int  spiBusSclkFreq { 1350000 };


/*******************************************************************/
/*  Pushbutton and Slider Switches                                 */
/*******************************************************************/

public:

    // The value of each enumerator within the enumeration `GpioSwitch' is
    // the wiringPi virtual pin number that corresponds to the physical pin
    // number on the RPI3B's 40-pin header that's connected to the
    // specified switch on the accessory board.
    //
    // HINT: At a command shell prompt type 'gpio readall' to display a
    // diagram that shows the mapping between physical pin numbers and wPi
    // virtual pin numbers on the RPI3B's 40-pin header.
    //
    enum GpioSwitch {
        pushbutton1 =  27,   // left-most pushbutton
        pushbutton2 =  0,
        pushbutton3 =  1,
        pushbutton4 =  24,
        pushbutton5 =  28,   // right-most pushbutton
        slider1     =  26,   // left slider switch
        slider2     =  23,   // right slider switch
    };

};  // class rpi3b_accessory

} // namespace ece3220

#endif // ECE3220_RPI3B_ACCESSORY_H

