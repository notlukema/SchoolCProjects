/*
123321是一个非常特殊的数，它从左边读和从右边读是一样的。
输入一个正整数n， 编程求所有这样的五位和六位十进制数，满足各位数字之和等于n 。

输入描述：
输入一行，包含一个正整数n。

输出描述：
按从小到大的顺序输出满足条件的整数，每个整数占一行。

样例输入：
52

样例输出：
899998
989989
998899

注释：
1<=n<=54。
本题目为填补程序题，只需填补所需的函数即可。
*/

#include <iostream>
#include <cmath> // The c++ version of math.h

int main()
{
	int n;
	std::cin >> n;
	if (n < 1 || n > 54)
	{
		std::cout << "n is not within a range that has any solutions!\n" <<
			"This is an error because the instructions specified that the range of n would be within [1, 54]";
		return 1;
	}
	
	// NOTE: The original assignment wanted me to define a pre-declared function, so this is just an optimization of the original assignment
	
	
	// To be able to print numbers from least to greatest, always start counting from 0 and from left to right
	
	// Five digit numbers must be within 45 (5 * 9)
	if (n <= 45)
	{
		// Loop through all possible first digits
		for (int i1 = 1; i1 < 10; i1++)
		{
			// Remainder after first digit
			int n2 = n - i1 * 2;
			
			// Is remainder too high to have a solution?
			if (n2 > 27)
			{
				continue;
			}
			
			// Is the remainder too low?
			if (n2 < 0)
			{
				break;
			}
			
			// Loop through all possible second digits
			for (int i2 = 0; i2 < 10; i2++)
			{
				// Remainder after second digit
				int n3 = n2 - i2 * 2;
				
				// Is the remainder too high?
				if (n3 > 9)
				{
					continue;
				}
				
				// Is the remainder too low?
				if (n3 < 0)
				{
					break;
				}
				
				// The third digit is a free digit in palindromes so no additional checks are required
				
				// Print
				std::cout << i1 << i2 << n3 << i2 << i1 << "\n";
			}
		}
	}
	
	// A more "elegant" solution is used for six digit numbers
	// Six digit numbers must be even because both sides match in a palindrome, resulting in a * 2 situation of only evens
	if (n % 2 == 0)
	{
		// Half value to be reached
		int n2 = n / 2;
		
		// Start from the lowest possible first number since the two numbers after can only add to a maximum of 18
		// Also bring in a ceiling to prevent negative target values
		for (int i1 = std::max(1, n2 - 18); i1 < std::min(10, n2 + 1); i1++)
		{
			// The number that needs to be reached with two digits
			int n3 = n2 - i1;
			
			// Start with the smallest possible second digit since the number after has a maximum of 9
			int i2 = std::max(0, n3 - 9);
			int i3 = n3 - i2; // Set the corresponding number (it is technically impossible for this number to be bigger than 9)
			
			// Loop through equal sum values until the second digit is greater than 9 or the third digit is less than 0
			// (Basically loop until either digit becomes invalid)
			while (i2 <= 9 && i3 >= 0)
			{
				// Print
				std::cout << i1 << i2 << i3 << i3 << i2 << i1 << "\n";
				i2++;
				i3--;
			}
		}
	}
	
	return 0;
}
