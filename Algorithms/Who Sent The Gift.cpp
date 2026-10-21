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
	
	std::cout << 'C';
	
	return 0;
}
