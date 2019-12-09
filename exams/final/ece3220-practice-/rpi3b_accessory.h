/* rpi3b_accessory.h */

/*
    Practice Code for the Practical Portion of the Final Exam

    Copyright 2019 James D. Fischer, all rights reserved
*/


namespace wiringPi {
#include <wiringPi.h>
} // namespace wiringPi


namespace ece3220 {

//************************************************************************
// Software abstraction for the Raspberry Pi 3B accessory board.
// (Singleton design pattern)
//************************************************************************

class rpi3b_accessory {

/*******************************************************************/
/*  Pushbutton and Slider Switches                                 */
/*******************************************************************/

public:

    // The value of each enumerator within the enumeration `led_type' is
    // the wiringPi virtual pin number that corresponds to the physical
    // pin number on the RPI3B's 40-pin header that's connected to the
    // specified LED color on the accessory board.
    //
    // HINT: At a command shell prompt type 'gpio readall' to display a
    // diagram that shows the mapping between physical pin numbers and
    // wiringPi virtual pin numbers on the RPI3B's 40-pin header.
    //
    enum switch_type {
        switch_pushbutton1 = 27,    // wiringPi virtual pin # for BTN1
        switch_pushbutton5 = 28,    // wiringPi virtual pin # for BTN5
        switch_slider1     = 26,    // wiringPi virtual pin # for SW1
    };


    /** \brief Reads the present ON|OFF state of the specified switch.
     * \param sw [in] The switch whose state is to be read/returned.
     */
    inline int switchRead ( switch_type sw )
    {
        /* your code here... */
    }


/*******************************************************************/
/*  DO NOT MODIFY ANY CODE BELOW THIS LINE                         */
/*******************************************************************/

public:

    // Destructor. This method must be public. 
    ~rpi3b_accessory();

    // Accessor method that returns a reference to the singleton instance
    // of the rpi3b_accessory class.
    static rpi3b_accessory&  get_instance();

    
    // Singleton design pattern.
    // Disable automatic synthesis of these class methods
    rpi3b_accessory(rpi3b_accessory const &) = delete;              // copy constructor
    rpi3b_accessory& operator=(rpi3b_accessory const &) = delete;   // copy assignment
    rpi3b_accessory(rpi3b_accessory &&) = delete;                   // move constructor
    rpi3b_accessory& operator=(rpi3b_accessory &&) = delete;        // move assignment


    /** \brief Convenience/wrapper method for registering user-defined
     * interrupt service routine functions with the wiringPi library.
     *
     * \param pin [in] A wiringPi virtual pin number that identifies a
     *      Raspberry Pi general-purpose input/output (GPIO) pin.
     * \param edgeType [in] Any one of INT_EDGE_FALLING, INT_EDGE_RISING,
     *      INT_EDGE_BOTH or INT_EDGE_SETUP.
     * \param function [in] The function to be called when the specified
     *      edgeType event occurs on the specified INPUT pin.
     *
     * See also the description of function `wiringPiISR()' in the wiringPi
     * library's online documentation:
     * http://wiringpi.com/reference/priority-interrupts-and-threads/
     */
    inline void  RegisterISR( int pin, int edgeType, void (*function)(void))
    {
        wiringPi::wiringPiISR( pin, edgeType, function );
    }

private:

    // Default constructor. This method must be private.
    rpi3b_accessory();

/*******************************************************************/
/*  Light-Emitting Diodes                                          */
/*******************************************************************/

public:

    // The value of each enumerator within the enumeration `led_type' is
    // the wiringPi virtual pin number that corresponds to the physical
    // pin number on the RPI3B's 40-pin header that's connected to the
    // specified LED color on the accessory board.
    //
    // HINT: At a command shell prompt type 'gpio readall' to display a
    // diagram that shows the mapping between physical pin numbers and
    // wiringPi virtual pin numbers on the RPI3B's 40-pin header.
    //
    enum led_type {
        led_red     =  8,   // wiringPi virtual pin #s for the LED
        led_yellow  =  9,
        led_green   =  7,
        led_blue    = 21,
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
        wiringPi::digitalWrite(color,state);
    }

    /** \brief Reads and returns the present ON|OFF state of an individual
     * LED on the accessory board.
     * \param color [in] Any one of this class's led_type enumerated values.
     */
    inline int  ledRead ( led_type color )
    {
        return wiringPi::digitalRead( color );
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
    //
    // 2) The 7-segment display's decimal point LED is not controlled via
    //    the CD4511. It has a dedicated signal line `DP' on the RPI3B's
    //    40-pin header.
    //
    // HINT: At a command shell prompt type 'gpio readall' to display a
    // diagram that shows the mapping between physical pin numbers and
    // wiringPi virtual pin numbers on the RPI3B's 40-pin header.
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

    /** \brief Writes a BCD value between 0-9 inclusive to the ABCD inputs
     * on the CD4511 BCD-to-7-Segment Latch Decoder/Driver IC.
     * 
     * \param bcdValue [in] The four-bit binary coded decimal value to be
     *      written from the RPI to the ABCD inputs on the CD4511 IC.
     *
     * \throws std::runtime_error { Throws a std::runtime_error exception if
     * the condition '0 <= bcdValue <= 9' is false. }
     */
    void  displayWrite( const uint8_t bcdValue );


    /** \brief Turns OFF (disables, blanks) the A-G LED segments on the
     * 7-segment display.
     * 
     * Turns OFF the A-G LED segments on the 7-segment display.  This
     * method does not control the display's decimal point LED; see instead
     * the method `displayDecimalPoint(state)'.
     */
    inline void  displayOff()
    {
        wiringPi::digitalWrite( display_enable, 0 );
        displayBlankingState = display_blanked;
    }


    /** \brief Turns ON (enables, unblanks) the 7-segment display.
     *
     * Turns ON the A-G LED segments on the 7-segment display.  This method
     * does not control the display's decimal point LED; see instead the
     * method `displayDecimalPoint(state)'.
     */
    inline void  displayOn()
    {
        wiringPi::digitalWrite( display_enable, 1 );
        displayBlankingState = display_unblanked;
    }


    /** \brief Turns ON|OFF the decimal point LED on the 7-segment display.
     *
     * \param state [in] If state's value is zero, the display turns OFF;
     *      otherwise the display turns ON.
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

};

} // namespace ece3220

