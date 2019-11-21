/* ./p04/main.cc */

//
// Explicit specialization of a function template.
// Deduction of type template parameter T.
// Explicit specification of type template parameter T.
//

#include <iostream>
#include <string>
using namespace std;

/* compare(t1,t2)
 * Returns a value greater than zero when t1 > t2, or returns zero when
 * t1 == t2, or returns a negative value when t1 < t2.
 */
template < typename T >
int
compare( const T &t1, const T &t2 )
{
    return ( t1 - t2 );
}

///////////////////////////////////////////////////////////////////
class X {
public:
    // converting constructor
    X( double v ) : value{v} { }

private:
    double value ;

friend int compare<X>(const X&, const X&);
};
///////////////////////////////////////////////////////////////////

// Explicit specialization of the template function `compare' for use with
// class X objects. T's type is deduced.
template<>
int
compare( const X &x1, const X &x2 )
{
    double result = x1.value - x2.value;
    return (result > 0.0 ? 1 : (result < 0.0 ? -1 : 0));
}


// Explicit specialization of the template function `compare' for use with
// std::string objects, with its template argument T explicitly specified as
// `std::string'.
template<>
int
compare<std::string>( const std::string &s1, const std::string &s2 )
{
    return s1.compare(s2);
}


int main()
{
    X  x1{1.02},  x2{1.01};
    cout << compare(x1,x2) << endl;     // T : ??

    std::string  s1{"Hello"}, s2{"World"};
    cout << compare(s1,s2) << endl;     // T : ??
    
    return 0;
}

