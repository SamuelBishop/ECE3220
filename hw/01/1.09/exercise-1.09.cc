/*
 * Lippman text
 * Exercise 1.9: Write a program that uses a while to sum the numbers from 50 to 100.
 *
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
        int sum = 0;
	int count = 50;
	while( count <= 100 )
	{
		sum += count;
		count++;
	}
	std::cout << sum << std::endl;
        return 0;
}

