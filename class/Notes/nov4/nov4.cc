/* nov4.cc */

/*
TAKEAWAYS:
- A virtual function will always be virtual if declared that way. Even if not declared in derived classes.
- Override keyword makes it evident that a superclass function was overridden in a subclass.
- Each class has a virtual lookup table (vtable) to locate its methods.
- In visual mode -u is undo and Ctrl-r is redo
- In order to use the polymorphic traits the method names must exist in the base class in order to use them. 
*/

class A {
public:
    virtual void a1() { }   // virtual function declarations
    virtual void a2() { }
};

class B : public A {
public:
    void a1() override { }   // overrides A::a1(). OVERRIDE KEYWORD IS NECESSARY.
    virtual void b1() { }
    virtual void b2() { }
};

class C : public B {
public:
    void a2() override { }
    void b1() override { }
    virtual void c1() { }
    virtual void c2() { }
};

int main()
{
    A a;
    A *pa = &a; //has the address of a class A object

    pa->a1();   // call A::a1()
    pa->a2();   // call A::a2()

    B b;
    pa = &b;    // this is a base class pointer and additional class functions will be unavailable

    pa->a1();   // A::a1()
    pa->a2();   // A::a2()
    //pa->b1(); // error because we have an A pointer
    //pa->b2(); // compiler error
    
    C c;
    pa = &c;    // this is a base class pointer and additional class functions will be unavailable

    pa->a1();   // B::a1()
    pa->a2();   // A::a2()
    // pa->b1();   // error because we have an A pointer
    // pa->b2();   // compiler error
    // pa->c1();   // compiler error
    // pa->c2();   // compiler error

    B *pb = &b; // this is a base class pointer and additional class functions will be unavailable

    pb->a1();   // B::A::a1() at beginning of class but was overriden to be B::a1()
    pb->a2();   // A::a2()
    pb->b1();   // B::b1()
    pb->b2();   // B::b2()
 
    pb = &c; // this is a base class pointer and additional class functions will be unavailable

    pb->a1();   // B::A::a1() at beginning of class but was overriden to be B::a1()
    pb->a2();   // A::a2()
    pb->b1();   // B::b1()
    pb->b2();   // B::b2()
    // pb->c1();   // compiler error
    // pb->c2();   // compiler error




    return 0;
}
