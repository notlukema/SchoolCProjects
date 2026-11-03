/*
题目描述:
输入一行空格分隔的英语单词串（只含空格与字母），不超过100个字符。
要求编写函数，对输入的一行单词序列（单词中间以空格分隔），要求删除行首和行尾的空格，去掉单词中多余的空格（单词间只保留一个空格），每个单词的首字母大写，其余字母小写。
函数返回值类型为字符指针，指向在函数中的动态分配内存（保存处理后的字符串）。

#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

// 补充函数 format_line

int main()
{
char input_line[100];
cin.getline(input_line, 100);

char* result_str = format_line(input_line);
cout << result_str << endl;

delete[] result_str;
return 0;
}


输入描述:
输入一行空格分隔的英语单词串（只含空格与字母），不超过100个字符。

输出描述:
输出处理后的英语单词串。

样例输入:
fundamentals   of  programming 

样例输出:
Fundamentals Of Programming

注释:
根据main函数中的调用方式补充函数头和函数体。
*/

// Given code
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

// ------------------------------ New Code ------------------------------
char* format_line(const char* str)
{
	// Note: no standard library shenanigans here, just plain old C++
	
	// There is no need for us to create a new char with a length that strictly conforms to the formatted string (we can spare some space)
	// And because the formatting does not increase string length, we can use the original length as a safe highest possibility plus one for the null terminator
	int len = strlen(str);
	char* str2 = new char[len + 1];
	
	// Loop through every character in the original string
	bool last_char_was_space = true;
	int i = 0;
	int j = 0; // This one's for recording the progress in making the new string
	while (i < len)
	{
		char c = str[i];
		if (c == ' ') // Char is space?
		{
			// Skip repeating spaces
			if (last_char_was_space)
			{
				i++; // Don't forget we have to manually step i here
				continue;
			}
			
			last_char_was_space = true;
			
			// Input space into new string
			str2[j] = ' ';
			j++;
		}
		else
		{
			// Determine whether or not we have to change capitalization
			if (last_char_was_space)
			{
				if (c >= 'a' && c <= 'z')
				{
					// Shift by the distance between the upper and lowercase letters
					c += ('A' - 'a');
				}
			}
			else
			{
				if (c >= 'A' && c <= 'Z')
				{
					// Shift by the distance between the lower and uppercase letters
					c += ('a' - 'A');
				}
			}
			
			last_char_was_space = false;
			
			// Input character into new string
			str2[j] = c;
			j++;
		}
		
		i++;
	}
	
	// Finally, add the null terminator to the new string
	str2[j] = '\0';
	
	return str2;
}
// ----------------------------------------------------------------------

int main()
{
	char input_line[100];
	cin.getline(input_line, 100);
	
	char* result_str = format_line(input_line);
	cout << result_str << endl;
	
	delete[] result_str;
	return 0;
}
