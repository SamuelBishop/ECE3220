// Code to compile from Oct 23

/* BIG TAKEAWAYS:
 * 1) I really need to review my notes and understand what is going on in this class.
 * 2) Way easier to call C++ code in C. But harder to call C in C++, not a whole lot of support to incorporate C into other programming langs.
 * 3) Storage duration is a tricky subject and storage class specifiers can change the lifespan of a variable.
 */

#ifndef DELETEME_H // if the macro (header file) is not defined
#define DELETEME_H // define it

class X {
public:
    static int value; // This data member is shared by all instances of the class
    static void foo();
    void something();
};

// ordinary class method
void
X :: something()
{
    static int m { 333 }; // without static m would be an automatic storage class. However m is not automatic and persists when static.
    // m is only constructed once upon the first call of function something.
  
    // What happens with an obj
    static X xobj { 333 }; // Allocates the memory prior to main for the xobj but doesn't construct it at all. Only constructs when it hits this line of code.
}

// definition of static method X::foo()
void 
X :: foo()
{
    // there is no 'this' pointer in here...
}

// X::foo(); // C has no idea what the scope operator is!

// If we compile C++ need to use the extern C
#ifdef __cplusplus
extern "C" { // Can tell that we don't want the name mangled because we import the fuctions from external source. Usuall uses {} for scope
#endif

void foo(); // requires C linkage from external source. This name cannot be mangled.

#ifdef __cplusplus
int foo(int);
X xobj;
void X::some_method(int);
xobj.some_method(5);

#endif

#ifdef __cplusplus
}
#endif

/*
 * REVIEW OF NAME MANGLING:
 * f()
 * f(int)
 * f(double)
 * f(x)
 *
 * overloaded functions are renamed in c++
 * become -> vfv, ifi, vfd, dfx
 */

#endif // otherwise do nothing!
