/*
题目描述:
A、B、C是小学老师，各教2门课，互不重复。共有如下6门课：语文、算术、政治、地理、音乐和美术。已知：
（1）政治老师和算术老师是邻居。
（2）地理老师比语文老师年龄大。
（3）B 最年轻。
（4）A 经常对地理老师和算术老师这两个人讲他看过的文学作品。
（5）B 经常和音乐老师、语文老师这两个人一起游泳。
请编程输出 A、B、C各教哪两门课。

输入描述:
无。

输出描述:
输出三行，分别为A、B、C三位老师所教授的课程，每行内的答案按照汉字拼音的首字母排序（如语文、音乐的拼音首字母分别是YW、YY），中间用空格分开。

样例输入:
无。

样例输出:
算术 语文
地理 政治
美术 音乐

注释:
输出必须是语文、算术、政治、地理、音乐和美术的某种排列。
*/

#include <iostream>

int main()
{
	// From statements (1), (2), (4), and (5), we know that:
	// 1. 政治 and 算术 do not belong to the same teacher
	// 2. 地理 and 语文 do not belong to the same teacher
	// 3. 地理 and 算术 do not belong to the same teacher and do not belong to teacher A
	// 4. 音乐 and 语文 do not belong to the same teacher and do not belong to teacher B
	
	// From these, we can first make these assumptions:
	// A does not teach 地理 or 算术
	// B does not teach 音乐 or 语文
	
	// And from statments (2) and (3) we know that B does not teach 地理.
	// (Based on the statement, B is the youngest and the teacher of 地理 is older than someone)
	// Therefore, A and B do not teach 地理, meaning C teaches 地理 and we can start from there.
	// And since 算术 does not belong to C nor A, then B must teach 算术.
	// Next, we also know that 语文 does not belong to C nor B, meaning A must teach it.
	
	// So far, we know that:
	// A teaches 语文
	// B teaches 算术
	// C teaches 地理
	
	// Next, going back to the last statment, 音乐 must be taught by C since it can't be taught by A or B.
	// Finally, since C is full and 政治 doesn't belong to B, it must be taught by A.
	// And as for the one that was never mentioned, 美术 can only fit into B's teaching arrangements.
	
	// A teaches 语文, 政治
	// B teaches 算术, 美术
	// C teaches 地理, 音乐
	
	// Rearrange based on pinyin alphabetical order:
	// A: 语文, 政治
	// B: 美术, 算术
	// C: 地理, 音乐
	
	// Print
	// Note: this may not work depending on the environment, version, encoding, etc
	// (It usually just prints a bunch of random glyphs)
	// (At least the assignment's compiler accepts it)
	std::cout << "语文 政治\n美术 算术\n地理 音乐";
	
	return 0;
}
