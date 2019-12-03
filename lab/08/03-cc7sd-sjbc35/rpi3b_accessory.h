#ifndef ECE3220_RPI3B_ACCESSORY_H
#define ECE3220_RPI3B_ACCESSORY_H

#include <cstdint>

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
    // HINT: At a command shell prompt type 'gpio readall' to display a
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
        wiringPi::digitalWrite(color,state);
    }


    /** \brief Turns OFF the the specified LED color
     * \param color [in] Any one of this class's led_type enumerated values.
     */
    inline void ledOff( led_type color )
    {
        wiringPi::digitalWrite(color,0);
    }


    /** \brief Turns OFF all LEDs
     */
    inline void ledOffAll()
    {
        wiringPi::digitalWrite ( led_red,	LOW );
	wiringPi::digitalWrite ( led_green,	LOW );
	wiringPi::digitalWrite ( led_yellow,	LOW );
	wiringPi::digitalWrite ( led_blue,	LOW );
    }


    /** \brief Turns ON the the specified LED color
     * \param color [in] Any one of this class's led_type enumerated values.
     */
    inline void ledOn( led_type color )
    {
        wiringPi::digitalWrite ( led_red,	HIGH );
	wiringPi::digitalWrite ( led_green,	HIGH );
	wiringPi::digitalWrite ( led_yellow,	HIGH );
	wiringPi::digitalWrite ( led_blue,	HIGH );
 
    }


/*******************************************************************/
/*  7-Segment Display                                              */
/*******************************************************************/

private:

    // CD4511 BCD-to-7-Segment Latch/Decoder/Driver IC
    //
    // The value of each enumerator within the enumeration `display_type' is
    // the wPi virtual pin number that corresponds to the physical pin
    // number on the RPI3B's 40-pin header that's connected to the
    // specified BCD A,B,C,D inputs (a.k.a., D0,D1,D2,D3) on the CD4511
    // IC, the DP (decimal point) LED on the 7-segment display, and the
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
    enum display_type {
        display_bcd_a  = 5,
        display_bcd_b  = 6,
        display_bcd_c  = 25,
        display_bcd_d  = 2,
        display_dp     = 4,
        display_enable = 29
    };

 
    // The state of the accessory board's ENABLE signal (i.e., the state of
    // the BLANKING input on the CD4511B IC).
    //
    enum displayState_type {
        displayBlanked,
        displayEnabled
    };

    // Stores the current state of the accessory board's ENABLE signal
    // (i.e., the current state of the BLANKING input on the CD4511B IC).
    //
    displayState_type  displayState ;

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


    /** \brief Turns OFF (disables, blanks) the 7-segment display.
     */
    inline void  displayOff()
    {
        /* your code here... */
	wiringPi::digitalWrite ( display_bcd_a,	LOW );
	wiringPi::digitalWrite ( display_bcd_b,	LOW );
	wiringPi::digitalWrite ( display_bcd_c,	LOW );
	wiringPi::digitalWrite ( display_bcd_d,	LOW );
    }


    /** \brief Turns ON (enables, un-blanks) the 7-segment display.
     */
    inline void  displayOn()
    {
    	/* your code here... */
	wiringPi::digitalWrite ( display_bcd_a,	HIGH );
	wiringPi::digitalWrite ( display_bcd_b,	HIGH );
	wiringPi::digitalWrite ( display_bcd_c,	HIGH );
	wiringPi::digitalWrite ( display_bcd_d,	HIGH );
    
    }


    /** \brief Turns ON|OFF the decimal point LED on the 7-segment display.
     */
    inline void  displayDecimalPoint( int state )
    {
        /* your code here... */
	wiringPi::digitalWrite ( display_dp, state );
    }


    /** \brief Returns the CD4511B's current blanking state.
     */
    inline displayState_type  getDisplayBlankingState() const
    {
        /* your code here... */
	if ( display_bcd_a == LOW 
	     && display_bcd_b == LOW 
	     && display_bcd_c == LOW
     	     && display_bcd_d == LOW
	   )
	{ 
		return displayBlanked; 
	}
	else
	{ 
		return displayEnabled; 
	}	
    }

};  // class rpi3b_accessory

} // namespace ece3220

#endif // ECE3220_RPI3B_ACCESSORY_H
