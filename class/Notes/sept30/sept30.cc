//"RINGS OF PROTECTION LEVELS"//
// Inner Ring: Private. Highest access allowed is private.
// Middle Ring: Protected. Highest access allowed is protected.
// Outer Ring: Public. Highest access allowed is public.

// Will usually declare object inheritance for derived objects with the public access specifier. This ensures access to every member and method.

// C++ 2011 uses a new syntax for initialization. Can use curly braces or parentheses. Older code will only have parentheses.


class X{
public: // everyone can use
	// default ctor
	X() : a(0), b(0), c(0) {}; // default values for the class members. Often times curly braces are nothing.

	// converting ctor
	X(int value) : a(value, b(value), c(value) {}; // can pass in a value to the constructor.

	// a copy ctor will be synthesized automatically even if not specified. Copies are always shallow. Deep copies you need your own function for.
	// X x2(x1); // copy ctor shallow (ptr->ptr)
	// x2 = x1; // shallow copy	(ptr->ptr)


	int a;
	void foo(); // this goes to show access specifiers work on methods too
protected: // subclasses can use
	int b;
private: // only the immediate object can use
	int c;
};


// NEED TO SPECIFY TYPE OF DERIVATION OFF DIFFERENT CLASS OR ELSE DEFAULTS TO PRIVATE. These are called access modifiers.
class Y : public X // Read as class y is derived from X. Related to inheritance, has all properties of X.
{ // Also inheriatance is private by default. Everything that used to be public in class X is now private in class Y.
public:
	// default ctor
	Y() : k(0) {}; // will automatically invoke the inherited constructor. Inherited construction takes place first.

	// converting ctor
	Y(int value) : X(value), k(value) {}; // if you don't specifiy an inherited constructor it will call the default by default.
				// ^ find the converting constructor from inherited classes
				// The flip flop of constructors are allowed however the base class inherited ctors will always be initialized first.
private:
	int k;
}
int main()
{
	X x1;
	x1.n = 123; // okay
	x1.b = 234; // error, not public
	x1.c = 345; // error, not public

	Y y1; // Y::X::a, Y::X::b, Y::X::c // all automatically gain access specifier type
	y1.a = 123; // requires access modifiers
	y1.b = 234;
	y1.c = 345;
}
