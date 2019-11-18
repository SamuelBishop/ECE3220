/* main.cc */

#include "foo.h"
#include "main.h"

void bar() { /* ... */ }

int main()
{
    foo( 5 );   // defined in foo.c
    return 0;
}
