#include "rpi3b_accessory.h"

using namespace ece3220;

int main()
{
    int exit_code = 0;

    // Singleton design pattern
    
    // The class method getInstance() returns a modifiable lvalue reference to
    // the one and only instance of the rpi3b_accessory class.  That reference
    // provides access to the class's member data and methods.
    //
    // NB: An lvalue is an expression that identifies a non-temporary object,
    // bit-field, or function. See also:
    // https://en.cppreference.com/w/cpp/language/value_category
    // https://docs.microsoft.com/en-us/cpp/cpp/lvalues-and-rvalues-visual-cpp
    //
    rpi3b_accessory::getInstance().bar(); // constructs instance so we can use that reference to
                                          // that instance for the rest of the program.
    rpi3b_accessory::getInstance().baz();
    rpi3b_accessory::getInstance().foo();

    // The syntax above is clumsy. If you need to perform multiple tasks with
    // the singleton instance, make life easier by naming the lvalue reference,
    // and then use the name to interact with the class's member data and
    // methods.  (Recall that a C++ reference is an alternative name (an alias)
    // for an existing object.)
    rpi3b_accessory  &rpab = rpi3b_accessory::getInstance();
    rpab.foo();
    rpab.baz();
    rpab.bar();

    return exit_code;
}
