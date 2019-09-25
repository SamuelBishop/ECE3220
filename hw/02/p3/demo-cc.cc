/* demo-cc.cc */

// function declaration
extern "C" void foo();

int main()
{
	foo();  // defined in the C source file demo-c.c
	return 0;
}
