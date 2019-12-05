/* main.cc */

#include "foo.h"
#include "main.h"
#include <wiringPi.h>

void bar() { /* ... */ }

int main()
{
    foo( 5 );   // defined in foo.c
    return 0;
}
