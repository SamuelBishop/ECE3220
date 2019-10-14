//T
//T& (Wont have to worry about any of this copy bs when messing with references or pointers)
//T*

class X{
    double d;

public:
    // X& THE RETURN VALUE IS TYPICALLY A REFERENCE. DEFINED BEHAVIOR....
    // X x1, x2, x3;
    // x1 = x2 = x3;    // copy assignment from right to left
    // ----------
    // x1 = x2;         // copy assignment
    // ----------
    //     x1

    X() = default; // Please synthesize the default constructor
    X( const &X ) = delete; // Do not synthesize the copy constructor
    X& operator=( const X &xobj ) = 
    {
        this->d = xobj.d; // these exist whether we see them or not
        return this;
    }; // tells the compiler not to synthesize the assignment operators
       //    int n;
}

// Would use reference if we want to modify something from a different funct and return that same thing.
// This kind of thing is done a lot with stream objects.
//EX:
ostream &
operator << ( ostream &out,const X &xobj )
{
    return out;
} // makes it possible to chain these calls together

    int n;

    n;

    X x1, x2;
    cout << x1 << x2 << endl;
    // operator << (cout,x1)
    // => cout
    // operator << (cout,x2)
    // => cout
    // ...
    // => cout


X foo() { // This will make a copy of n into its stack
    X n; // var comes into existence. Automatic storage class allocates to the stack
    // ...
    //
    return n;

    // Using references and pointers will not guarentee static return value. Here a pass by value is the only acceptable function.
}

void goo() { // performs a shallow copy of the contents of n over to m
    X m; // default constructor
    m = foo(); // the integer lifetime is for this one statement. Temporary is then popped off the stack.
                // n hat is the notation for a coppied variable where n is the variable

}
