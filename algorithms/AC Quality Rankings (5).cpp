/*
题目描述:
夏日炎炎，空调机走俏。5家空调机厂的产品在一次质量评比活动中分获前5名。评前大家就已知道E厂的产品肯定不是第2名和第3名。
A厂的代表猜：E厂的产品稳获第1名。
B厂的代表猜：我厂可能获第2名。
C厂的代表猜：A厂的质量最差。
D厂的代表猜：C厂的产品不是最好的。
E厂的代表猜：D厂会获第1名。
评比结果公布后发现，只有获第1名和第2名的两个厂的代表猜对了。请编程给出A、B、C、D、E各是第几名？

输入描述:
无

输出描述:
1-5的一种排列，用空格隔开

样例输入:
无

样例输出:
3 1 2 4 5
*/

#include <iostream>

int main()
{
	// I tried and turns out the 样例输出 was not the answer :(
	//std::cout << "3 1 2 4 5";
	
	
	// First we know that D cannot possibly be #1 due to E's guess. This is because E is either #1 and takes up the space or its guess is wrong.
	// From this, we also know that E is not #1 due to the spot conflict with D, and can't be #2 or #3 either from the information prior to the reveal.
	// This leads to A being unable to occupy #1 or #2 since its guess is that E would be #1, which is impossible based on previous deductions.
	// Also, from B's standalone guess, we know that B is either #2 or neither #1 nor #2.
	
	// At this point, we know that E is lower than #3, A are lower than #2, D is either #2 or lower, and B is either #2 or lower.
	
	// Next, knowing that D can only possibly have a successful guess at #2, we can quickly dispatch of this special statement.
	// If D was #2, then we know that C cannot be #1, which means all spots below #1 are filled and B must be #1.
	// However, this is impossible since B cannot be #1, so D must not be #2 either.
	
	// If D was not #2, then we know that C must be #1 due to D's wrong guess.
	// Then with C's guess, we can confidently put A into fifth place.
	// And since D and E are also lower than #2, B has no choice but to be #2.
	
	// At this point, we know that C is #1, B is #2, and A is #5.
	// And since E cannot be #3, E must occupy #4, leaving D to be #3.
	
	// Final rankings from #1 to #5: C, B, D, E, A
	// Print as: 5 2 1 3 4
	
	std::cout << "5 2 1 3 4";
	
	return 0;
}
