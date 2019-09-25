// Go home and read about this stuff online. I'm too tired to pay attention to this right now.


// The three types of access specifiers
// public
// protected
// private


#include <iostream>
using namespace std;

struct X{ // will default to public if not specified
public:
	int n;
};

// Example of a setter/getter class
class Y{ // Prevents the storage of bogus data
public:
	// default ctor
	Y() : n(0), mc(5), dp(new double(1.23)) { } // This is the initializer for Y

	// converting ctor
	Y(int value) : n(value), mc(5), dp(new double(...)) { } // What are the ellipses???

	// copy ctor
									// Two ways to copy a pointer: Shallow copy, deep copy
									// ^ this is also calling a constructor. Shallow copy.
	Y( const Y &yobj ) : n(yobj.n), mc(yobj.mc), dp(yobj.dp)  // cannot pass by value for this. Must pass by reference.
					      // post colon is the member initialization section
	// Example of deep copy:
	// Y( const Y &yobj ) : n(yobj.n), mc(yobj.mc), dp(new double(*yobj.dp)) // deep copy

	// copy assignment
	operator = ( const Y &rhs ) {
		this->n = rhs.n;	// shallow copy
		this->mc = rhs.mc;	// shallow copy
		*(this->dp) = *rhs.dp; // this will be a deep copy
	}

	// destructor (dtor)
	~Y() { if (dp != nullptr) delete dp; }

	Y y1 = 5;

	// set 'accessor' method
	void set_n(int value){
		if (value < 0 ) value = 0;
		else if (value > 5) value = 5;
		this->n = value;
	}

	// get 'accessor' method
	int gen_n(){ return n; }

	private:
	int n; // assume we need a bounds between [0..5]
}

class Y{ // will default to private if not specified (usually data of class needs to be protected or private)
// Need a setter or getter function in order to utilize a private class
private:
	int n;
	myclass mc;
}

int main(){
	X x1; // default constructor
	Y y1; // default constructor
	Y y2(y1); // copy ctor (clone y1 into y2)
	y1 = y2; // assignment operation
	Y y3;

	y2.set_n( 3 );
	y3.set_n( 3 );

	x1.n = 134;
	y1.set_n(234);
	cout << y1.get_n() << endl;
	return 0;
}
