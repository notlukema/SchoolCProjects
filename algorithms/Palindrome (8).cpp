/*
题目描述:
回文串是一个正读和反读都一样的字符串。比如“level”、“noon”、“aba”、“c”都是回文串，但“abc”、“good”、“abab“都不是回文串。
现在输入一行字符串，现只考虑其中字母和数字，并忽略大小写，判断其是否为回文串。

说明:本题中,我们将空字符串定义为有效的回文串。

输入描述:
一行字符串，字符个数不超过100。（可能包含大小写字母、数字、标点符号、空格等）

输出描述:
如果回文串，输出1，否则输出0。

样例输入:
A man, a plan, a canal: Panama

样例输出:
1
*/

#include <iostream>
#include <string>

// What's interesting is how we disregard non-letter and non-number characters
// So we format the string first for ease of checking later
void formatStr(std::string& str)
{
	// Loop string
	unsigned int i = 0; // Unsigned is used because str.length() is unsigned and we don't want to compare differently signed integers
	while (i < str.length())
	{
		// Grab reference so we can manipulate easily
		char& c = str.at(i);
		if (c >= 'A' && c <= 'Z') // Make uppercase lowercase
		{
			c += 'a' - 'A';
			i++;
			continue; // Step i and skip validity check because it is already a valid character
		}
		if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) // Validity check
		{
			// A valid character so step and continue
			i++;
		}
		else
		{
			// Invalid character so remove (don't step i)
			str.erase(i, 1);
		}
	}
}

// Function to check if palindrome
bool palindrome(const std::string str)
{
	// Here, we start from both ends and move torwards the middle until i and j either overlap or cross each other
	int i = 0;
	int j = str.length() - 1;
	while (i < j)
	{
		if (str.at(i) != str.at(j)) // Character mismatch: not a palindrome
		{
			return false;
		}
		i++;
		j--;
	}
	// No character mismatch: it is a palindrome
	return true;
}

int main()
{
	// Recieve input
	std::string str;
	std::getline(std::cin, str);
	
	// Format string
	formatStr(str);
	
	// Test and print
	std::cout << palindrome(str);
}
