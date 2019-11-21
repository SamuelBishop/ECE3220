/* ./p01/main.cc */

#include <iostream>
using namespace std;

/* compare(t1,t2)
 * Returns a value greater than zero when t1 > t2, or 
 * zero when t1 == t2, or a negative value when t1 < t2.
 */
template < typename T >
int
compare( const T &t1, const T &t2 )
{
    return ( t1 - t2 );
}

int main()
{
	// Template argument type is deduced
    cout << compare(5,2) << endl;         // T : ??
	cout << compare(1.2,3.4) << endl;     // T : ??
    cout << compare('a','x') << endl;     // T : ??

//	cout << compare('a',5) << endl;       // T : ??

    // Use C++'s static_cast operator to explicitly convert int 
    // to char and vice versa.
//	cout << compare('a',static_cast<char>(5)) << endl;  // T : ??
//	cout << compare(static_cast<int>('a'),5) << endl;   // T : ??

	// Explicitly specify template argument T's data type
//	cout << compare<char>('a',5) << endl;   // T : ??
//	cout << compare<int>('a',5) << endl;    // T : ??

    return 0;
}

