/* ./p03/main.cc */

#include <iostream>
using namespace std;

/* compare(t1,t2)
 * Returns a value greater than zero when t1 > t2, or
 * zero when t1 == t2, or a negative value when t1 < t2.
 */
template < typename T >
int  compare( const T &t1, const T &t2 )
{
    return ( t1 - t2 );

}

class X {
public:
    // converting constructor
    X( double v ) : value{v} { }

    // overloaded subtraction operator '-'
    X operator - ( const X &rhs ) const;

    // typecast operator (converts X to int)
    inline operator int () const
    { return static_cast<int>(value); }

private:
    double value ;
};

// Overloaded subtraction operator '-' for class X
X
X :: operator - ( const X &rhs ) const
{
    return X{ this->value - rhs.value };
}

int main()
{
    X  x1{1.02},  x2{1.01};
    cout << compare(x1,x2) << endl;
    return 0;
}

