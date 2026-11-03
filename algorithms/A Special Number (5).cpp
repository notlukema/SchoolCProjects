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

// Given code
#include <iostream>

using namespace std;
bool checkSpecial(int i, int n);

int main() {
	int n;
	cin >> n;
	for (int i = 10000; i < 1000000; i ++) {
		if (checkSpecial(i, n)) {
			cout << i << endl;
		}
	}
	return 0;
}

bool checkSpecial(int i, int n)
{
	// ------------------------------ New Code ------------------------------
	// Initial checks
	if (i < 100000)
	{
		// Five digit numbers have a highest n of 45
		if (n > 45)
		{
			return false;
		}
		
		// Extract digits
		int i1 = i / 10000 % 10;
		int i2 = i / 1000 % 10;
		int i3 = i / 100 % 10;
		
		// With palindrome requirements in mind, test for sum validity first
		if ((i1 + i2) * 2 + i3 != n)
		{
			return false;
		}
		
		// Test if palindrome
		int i4 = i / 10 % 10;
		int i5 = i % 10;
		return (i1 == i5) && (i2 == i4);
	}
	else if (i < 1000000)
	{
		// The sum of six digit numbers must be even due to the palindrome requirements
		if (n % 2 == 1)
		{
			return false;
		}
		
		// Extract digits
		int i1 = i / 100000 % 10;
		int i2 = i / 10000 % 10;
		int i3 = i / 1000 % 10;
		
		// With palindrome requirements in mind, test for sum validity first
		if ((i1 + i2 + i3) * 2 != n)
		{
			return false;
		}
		
		// Test if palindrome
		int i4 = i / 100 % 10;
		int i5 = i / 10 % 10;
		int i6 = i % 10;
		return (i1 == i6) && (i2 == i5) && (i3 == i4);
	}
	
	// Impossible case by technicality
	return false;
	
    
	// General equation for testing if all digits added togethor matches n
	/*
	// Calculate the digit count first using log10
	int digitCount = (int)std::log10(i) + 1;
	int sum = 0;
	int div = 1;
	for (int j = 0; j < digitCount; j++)

	// Divide, truncate, then mod for the individual digit
	int digit = (i / div) % 10;
	sum += digit;
	div *= 10;
	}
	// Compare
	return sum == n;
	*/
	// ----------------------------------------------------------------------
}
