/* ./p02/main.cc */

#include <iostream>
using namespace std;

/* compare(t1,t2)
 * Returns an int value greater than zero when t1 > t2, or returns
 * zero when t1 == t2, or returns a negative value when t1 < t2.
 */
template < typename T1, typename T2 >
int
compare( const T1 &t1, const T2 &t2 )
{
    return ( t1 - t2 );
}

int main()
{
    // Template types T1 and T2 are deduced
    cout << compare(5,2) << endl;     // T1 : ??, T2 : ??
    cout << compare(1.2,3) << endl;   // T1 : ??, T2 : ??
    cout << compare('a',5) << endl;   // T1 : ??, T2 : ??

    // Tempate type T1 is explicit, and type T2 is deduced
    cout << compare<int>('a',23.45) << endl;   // T1 : ??, T2 : ??

    // Template types T1 and T2 are explicit
    cout << compare<double,char>('a',5) << endl;   // T1 : ??, T2 : ??
    return 0;
}

