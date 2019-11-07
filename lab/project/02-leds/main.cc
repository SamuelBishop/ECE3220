#include <cstdlib>
#include <unistd.h>
#include "rpi3b_accessory.h"

using namespace ece3220;

void
led_blink_sequential( rpi3b_accessory &a, const useconds_t on_time = 250000 )
{
    usleep(on_time);
    
    // Blink the red LED
    a.ledWrite( rpi3b_accessory::led_red, HIGH );
    usleep(on_time);
    a.ledWrite( rpi3b_accessory::led_red, LOW );
    
    // Blink the yellow LED
    a.ledWrite( rpi3b_accessory::led_yellow, HIGH );
    usleep(on_time);
    a.ledWrite( rpi3b_accessory::led_yellow, LOW );
    
    // Blink the green LED
    a.ledWrite( rpi3b_accessory::led_green, HIGH );
    usleep(on_time);
    a.ledWrite( rpi3b_accessory::led_green, LOW );
    
    // Blink the blue LED
    a.ledWrite( rpi3b_accessory::led_blue, HIGH );
    usleep(on_time);
    a.ledWrite( rpi3b_accessory::led_blue, LOW );
}

void
led_lamp_test( rpi3b_accessory &a, const useconds_t on_time = 2000000 )
{

    // Perform a "lamp test" by cycling all LEDs OFF > ON > OFF
    a.ledWriteAll( LOW );
    usleep( on_time );
    a.ledWriteAll( HIGH );
    usleep( on_time );
    a.ledWriteAll( LOW );
}

int main()
{
    int exit_code = EXIT_SUCCESS ;
    rpi3b_accessory &a = rpi3b_accessory::getInstance();
    led_lamp_test( a );
    led_blink_sequential( a );
    return exit_code;
}

