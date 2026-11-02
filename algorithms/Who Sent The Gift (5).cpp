/*
题目描述
徐老师有A，B，C，D四个得意门生，在中秋节他收到一份礼物，十分高兴，但不知道是谁送的。徐老师询问了四个学生，得到了如下答案： 
A：不是我送的礼物 
B：是我送的礼物 
C：不是B送的礼物 
D：是C送的礼物
已知四个学生中只有一个说了假话，那么到底是谁送的礼物呢？

输入描述:
无

输出描述:
送礼物的学生的代号。

样例输入:
无

样例输出:
A

注释:
输出样例仅表示输出格式，并非正确答案。
*/

#include <iostream>

int main()
{
	// No need to overthink
	
	// Student B and student C's statements conflict.
	// Since only one student is telling a lie, then it must be one of these two.
	// If student B was telling the lie, we can deduce that student C sent the gift due to student D's statement.
	// If student C was telling the lie, we would find that both student C and student B sent the gift, which would be impossible.
	// As a result, it is only possible if student B was telling the lie and that student C had sent the gift.
	
	// The answer
	//std::cout << 'C';
	
	
	// In code terms:
	
	// Because this is a relatively lightweight problem, we can test every possibility without much stress
	// Number equivalents:
	// A = 0
	// B = 1
	// C = 2
	// D = 3
	
	// Used for printing later
	char names[4] = { 'A', 'B', 'C', 'D' };
	
	// Here, i stands for the student that sent the gift
	for (int i = 0; i < 4; i++)
	{
		// We test each statement
		bool st_a = i != 0; // A didn't send the gift
		bool st_b = i == 1; // B sent the gift
		bool st_c = i != 1; // B didn't send the gift
		bool st_d = i == 2; // C sent the gift
		
		// Add togethor the number of true statements
		int st_true = st_a + st_b + st_c + st_d;
		
		// Based on the instructions, one student told a lie, so the number of true statements must be 3
		if (st_true == 3)
		{
			// Print
			// There should technically only be one correct combination here
			std::cout << names[i];
		}
	}
	
	return 0;
}
