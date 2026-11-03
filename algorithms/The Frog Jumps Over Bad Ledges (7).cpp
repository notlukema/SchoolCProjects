/*
题目描述:
一只青蛙要从第 0 级台阶跳到第 N 级。它每次可以跳 1 级或 2 级。但有一些台阶是坏的，不能落脚，最终落在第 N 级台阶时也不能是坏台阶。请计算它有多少种不同的跳法。

输入描述:
第一行两个整数 N 和 M ，分别表示台阶级数和坏台阶数量。
下面 M 行输入，每行一个整数表示坏台阶级数。

输出描述:
输出一个整数，表示不同的跳法数。保证答案不超过 long long 范围。

样例输入:
5 1
3

样例输出:
2

注释:
样例解释：可行跳法为 0→1→2→4→5 以及 0→2→4→5。
数据范围：0 ≤ M ≤ N，1 ≤ N ≤ 100 。坏台阶级数保证在 [1, N] 整数范围内。
建议参考练习题四中第3题的提示，先想出递推关系，再写代码。
*/

#include <iostream>

// Calculate the (n+1)th member of the Fibonacci sequence
int fibonacci(int n)
{
	// We assume that n cannot exceed 100 so our sequence will be no longer than 101
	static int fib_seq[101] = {1, 1}; // Start with two numbers
	static int fib_i = 2; // The next index of the fibonacci sequence to be calculated
	if (n < fib_i) // Fibonacci member already calculated?
	{
		return fib_seq[n];
	}
	// Calculate until the (n+1)th number is reached
	while (fib_i <= n)
	{
		fib_seq[fib_i] = fib_seq[fib_i - 1] + fib_seq[fib_i - 2];
		fib_i++;
	}
	return fib_seq[n];
}

int main()
{
	// Recieve input
	int n, m;
	std::cin >> n >> m;
	
	// true = bad step
	bool* steps = new bool[n] {false};
	
	// Recieve bad steps
	for (int i = 0; i < m; i++)
	{
		int step;
		std::cin >> step;
		steps[step - 1] = true; // One index down since we don't store the first step in the data
	}
	
	// Test for if the final step is broken: if it is, the frog can never reach it so there are no possible paths to it
	if (steps[n - 1])
	{
		std::cout << "0";
		return 0;
	}
	
	// Since the frog only has a single choice of double jumping when it reaches a bad step, each bad step can be considered a reset for the accumulating possibilities
	// Basically, we only need to multiply the pathway possibilities of all the consecutive good step combinations all the way to step n
	
	// And after some testing and confirmation, the possibility accumulation is directly correlated to the Fibonacci sequence
	// More specifically, the possibilties for n consecutive good steps (disregarding the starting step) is the (n+1) member of the Fibonacci sequence
	
	// Start with one possible pathway
	long long combos = 1; // long long is used because there are chances for numbers higher than what an integer can store here (and the instructions calls for it)
	// (unsigned is an option too)
	
	int consecutive_steps = 0;
	for (int i = 0; i < n; i++)
	{
		// We assume that the first and last steps cannot be bad steps so we can ignore those cases
		// We also assume bad steps cannot come in doubles (it would make reaching the top impossible)
		if (steps[i])
		{
			combos *= fibonacci(consecutive_steps);
			consecutive_steps = 0;
			i++; // Skip the next step because the frog starts on it so it doesn't need to be counted
		}
		else
		{
			consecutive_steps++;
		}
	}
	
	// One final multiply by the final consecutive steps to n
	combos *= fibonacci(consecutive_steps);
	
	// Print combos (possible pathway count)
	std::cout << combos;
	
	// Cleanup
	delete[] steps;
	
	return 0;
}
