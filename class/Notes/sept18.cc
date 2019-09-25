
struct X{
	// default constructor (when constructing without passing in variable. Goal is to initialize all class data.)
	X(){ l = new int(0); }
	
	// constructor (initializes l with a val)
	X( int lval ){ l = new int(lval); } 

	// destructor method
	~X(){ if (l) delete l; };

	// data member
	int *l;
}

int value = 1234;

int main()
{
	// if memory allocation fails then delete the bum varaibles
	try {
		// non adt construction/ resource aquisition

		X x1; // this is some sort of struct that contains member l. x1.l = new int(5)
		      // this statement invokes the default constuctor
			
		X x2(5); // uses non-default constructor to initialize values

		X x3, x4(10); // can also do this, this works as well
	
		int p = new int(5);	// question: what does this new function do?
		int pa = new[] int[10]; // question: what is happening in this line of code?
	}
	catch( const std::bad_alloc&err ){
		// non adt destruction example

		// destruction of members within objects happen automatically.		

		if ( p ) delete p; 	// if p != null, delete
		if ( pa ) delete[] pa;
	}
}

