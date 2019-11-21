/* main.cc */

#include <iostream>
#include <stdexcept>
#include "rpi3b-accessory.h"

using namespace ece3220;
using namespace std;

int main()
{
    int exit_code = 0;
    uint32_t adc_reply;

    rpi3b_accessory  &a = rpi3b_accessory::getInstance();

    try {
        // Sample the analog voltage at ADC input 1 (the potentiometer output)
        // and print the digitized value to stdout.
        adc_reply = a.adcSample( rpi3b_accessory::adc_channel_1 );

        cout << "adc_reply = " << adc_reply << endl;
        /* your code here ... */

    }
    catch ( std::runtime_error const &e ) {
        cerr << "\n:: ERROR :: " << e.what() << '\n'; 
        exit_code = 1;
    }
    catch ( ... ) {
        cerr << "\n:: ERROR :: Unexpected exception thrown; aborting...\n";
        exit_code = 1;
    }

    return exit_code;
}
