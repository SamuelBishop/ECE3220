/* oct30.cc */

#include <iostream>
using namespace std;

class A {
public: // this is an access specifier.
    virtual void foo() { cout << "A::foo()" << endl; }
    void bar() { cout << "A::bar()" << endl; }
};

// B::A::foo() or B::foo() two different functions. Compiler can tell
// the difference because of the scope resolution operator.
class B : public A { // deriving class using access modifier
public:
    void foo() { cout << "B::foo()" << endl; } // if this was commented out then the A::foo() method would be called
    // this is called an override for derived class. Overrides only occur for virtual declaration.
    void bar() { cout << "B::bar()" << endl; }
};

int main()
{
    A a;
    A *pa;

    B b;
    B *pb;


    /*
    a.foo();
    b.foo(); // calls B::foo() innermost method declaration
    b.A::foo(); // calls A::foo() even though B::foo() exists
                // this is static binding and is done at compile time (before program is run)
    */

    // late binding is performed during runtime and is used with the "virtual" keyword
    // only used when pointers or references of a class object
    // virtual (runtime) lookup table is quite often called the vtable
    
    pa = &a;
    pa->foo(); // calls a's foo function. (virtual lookup, at runtime)
    pa->bar(); // calls A::bar() (ordinary, static call)

    pa = &b;
    pa->foo(); // calls b's foo function. (virtual lookup, at runtime)
               // even though using object of a class, can use the address of derived object
               // into a baseclass pointer. Polymorphism calls derived class method.
    pa->bar(); // calls A::bar() still because not polymorphic (ordinary, static call)

    // Can I cast an A pointer or reference object into a B pointer or reference obj???
    // ANSWER: Yes. In c and c++, you can take an obj and sometimes typecast it into a
    // different obj. Can't arbitrarily cast one thing into another.
    //
    // w/ dynamic_cast we can take a base class type and convert it into a derived class.
    // 
    // w/ reinterpret_cast will straight up just make one obj into another.
    //
    // w/ static_cast can cast char->int or any other non-polymorphic cast
    //
    // w/ const_cast to momentarily get rid of the const of the obj so that you can update it
    //
    {
        A &ra = b; // ra is an alternate name for b until end of scope. BINDING.
        ra.foo(); // calls B::foo(); (virtual lookup)
        ra.bar(); // calls A::bar(); (no virtual lookup)

    }


    return 0;
}
