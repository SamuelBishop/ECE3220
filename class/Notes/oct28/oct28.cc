
#include "bar.h" // use quotes to define these because it will look in your own directory <> is only used for system directories
#include "baz.h"

#if 0
void foo(){ bar(); baz(); } // preprocessor will only process this statement if condition is met
#endif

int main()
{
    return 0;
}
