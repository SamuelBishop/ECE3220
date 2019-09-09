/* demo-cc.cc */

#include <iostream>

extern "C" void foo();

void foo()
{
	std::cout << "Hello, World!" << std::endl;
}
