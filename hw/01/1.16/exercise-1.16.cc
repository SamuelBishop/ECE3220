/*
 * Lippman text
 * Exercise 1.16:  Write your own version of a program that prints the sum of a
 * set of integers read from cin.
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
        int value = 0;
	int sum = 0;
	std::cout << "NOTE: To show the sum off all numbers one must input a non integer value" <<std::endl << "EXAMPLE:" << std::endl << "1" << std::endl << "2" << std::endl << "done" << std::endl << "The sum is : 3" << std::endl << std::endl;
	while(std::cin >> value)
		sum += value;
	std::cout << "The sum is : " << sum << std::endl;
        return 0;
}
