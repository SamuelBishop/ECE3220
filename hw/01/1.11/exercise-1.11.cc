/*
 * Lippman text
 * Exercise 1.11:  Write a program that prompts the user for two integers.
 * Print each number in the range specified by those two integers.
 */

// Samuel Bishop
// Professor Fischer
// ECE 3220: Software Dev in C/C++
// August 24, 2019

/* GENERAL INCLUDES */
#include <stdio.h>
#include <iostream>

/* CONSTANT DECLARATIONS */

/* FUNCTION DECLARATIONS */

/* MAIN */
int main()
{
        int int1, int2;
	std::cout << "Enter two integers: ";
	std::cin >> int1 >> int2;
	for(int1; int1 <= int2; int1++)
	{
		std::cout << int1 << std::endl;
	}
        return 0;
}
