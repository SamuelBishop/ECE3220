/* main.cc */

/* NOTE: I was NOT paying great attention today. Seeing as it was the day after the Hackathon and I'm very sleep deprived I decided to take it easy.
 * I'll definetly have to go back and review these. However, this class didn't seem too hard so I won't have missed out on much. */

// act of converting template into type is called instantiation

template <typename T>
int
compare( const T &t1, const T &t2 ) // remember to make these const unless there is a reason for these not to be const
{
    return ( t1 - t2 ); // simple approach
    // used to return an r value (intermediate value that is calculated along the way). a + b + c example.
    // if the compared r value is the correct type then the compiler is allowed to return the r value.
    //
}

class X {
public:
    // Converting constructor
    X( double v ) : value{v} { }

    // Overload the subtraction operator '-' for class X
    X operator - ( const X& rhs ) const; // when compiler uses the overload it calls the x1.operator-(x2)
                                         //                                              ^ this ptr
    // Type conversion from X into int
    operator int () const; // type cast

private:
    double value ;
};

X // return type for the operator
X :: operator - (const X& rhs ) const
{
    return X{ this->value - rhs.value };
}

// there is no return type for typecasts because the return is the type being cast to
X :: operator int () const
{
    return static_cast<int>( this->value ); // in c++ static casting is better than the c style type cast. Not brute force.
}

int main()
{
    X x1{1.2}, x2{3.4};

    compare( 2, 5 ); // uses deduction to figure out what type it is comparing
    compare( 'z', '*' ); // nm -C nov11.o analyzes the output file
    compare( 5.5, 3.2 );
    //compare( 'z', 5 ); // will throw error because function will not allow you to pass in two different data types
    compare( x1, x2 ); // can work, but there is no - operator defined for class X
    return 0;
}
