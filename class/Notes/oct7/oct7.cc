
// RESOURCE ACQUISITION IS INITIALIZATION (RAII)
// Sometimes want to define a value that is common to all class instances:

class X{
public:
    // default ctor
    // X() : value( 0 ) { } get rid of default constructor to have the second constructor do both jobs

    // converting ctor
    // X( int v = 0 ): value( v ) { } // now the compiler doesn't know which constructor to call ( both accept no args )

    // Fix for array size init
    X(std::size_t asize = X::default_array_size ) // use constant valued variable to do the initialization
        : value(0), dvalue(0.0), array( new char[asize] ), array_size( asize ) { } // remember we use new instead of malloc in c++

    /* 
    Remember the destructor always starts w/ a tilde and there are never any arguments passed into the destructor
    In the real world no one ever declares the destuctor unless they are templating.
    ~X(){ // cleans up allocated memory
        delete[] array; // deletes an array
    }
    */
    ~X(){}

    int get_value() const; // non static const hides this ptr

private:
    int value; // whatever is in the private cronologically is the order of initialization
    double dvalue;
    char array[ 10 ];

    char* array;
    std::size_t array_size;
    // static keyword means the same across all instances of class
    // const keyword means that the variable cannot be changed after initialization
    static const std::size_t default_array_size; // this variable is used when indicating a size value for something. Unsigned value.
    // size_t is dynamic/modular. Can scale up or down as needed by the compiler.
    // declare this crazy variable but do not define without the setter function
}

// definition (static comes off)
const std::size_t X::default_array_size = 1000; // as is this variable will not be associated with the class. Need to use scope operator.

// destructor
X::~X(){ // how to declare class functions outside of the class

}

// someother function
X::get_value(int value){
    return this->value;
}

void foo( double d, int value = 123 ){ // this would be an error because both of the arguments need to have defaults
                                       // defaults must go at the end of the function declaration

}

int main()
{
    X x1; // takes the default ctor
    X x2{ 123 }; // using the same constructor

    x1.get_value();

    foo( 333.33, 999 );
    foo(); // value takes on the default
}

/* THE EXAM OCT 9

1. Short answer questions (4-5 maybe???)
2. Written coding exercise (15-20mins max)

- Everthing on the reading list is on the exam except for the smart pointers */
