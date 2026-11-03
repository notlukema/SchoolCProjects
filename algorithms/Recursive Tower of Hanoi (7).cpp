/*
题目描述：
有三根柱子 A、B、C。起初有 n 个大小各不相同的圆盘，从小到大（小在上、大在下）依次叠在柱子 A 上。一次移动被定义为：从某一根柱子上取下该柱子最上方的一个圆盘，并将其放到另一根柱子的最上方。在任何时刻，不得将较大的圆盘放在较小的圆盘上。请计算将整叠圆盘从柱子 A 移到柱子 C 所需的最少移动次数。

输入描述：
一行一个整数 n ，表示圆盘数量。

输出描述：
输出一行，一个整数表示最少移动次数。保证答案不超过64位无符号整数范围。

样例输入：
3

样例输出：
7

注释：
数据范围： 1 ≤ N ≤ 64 。
使用递推求解。提示：要将移动 N+1 个圆盘从 A 移动到 C，可以先移动前 N 个圆盘到 B ，然后移动最后一个圆盘到 C ，最后再将前 N 个圆盘移动到 C 。
*/

#include <iostream>

// Function declaration
unsigned long long moves_to_solve(int n);

int main()
{
	// Recieve Input
	int n;
	std::cin >> n;
	
	// A Tower of Hanoi of n rings can be solved in 2^n - 1 moves, but we will be considering it from a recursive standpoint
	// (The assignment title suggests recursion as the solution)
	
	std::cout << moves_to_solve(n);
	
	// Do note that this recursion will likely result in a timeout for higher values of n so just use the 2^n - 1 equation when submitting
	// (Check the other file of the same name)
	
	// Exit program
	return 0;
}

// Real solver function
// The Tower of Hanoi puzzle can be boiled down to three recursive steps:
// 1. Move all rings on the source peg above the target ring to the spare peg
// 2. Move the target ring to the target peg
// 3. Move all rings on the spare peg back onto the target peg
// Note that you cannot simply move all the rings above the target ring one-by-one onto the spare peg in steps 1 and 3 unless there is only one ring above the target ring
// Rather, you have to use a recursion of steps 1-3 again except with a target ring one higher than the last
// And by redefining the spare, target, and source pegs during recursion, moving the higher rings from the source to the spare and from the spare to the target peg is essentially the same sequence of operations
// Paired with how the last recursion left the larger rings at the bottom, we can confidently pretend that those larger rings do not exist and call the same recursion again
// We can continue this recursion until there is only one ring higher than the target ring, at which it only requires a total of 3 moves to move both rings from the source peg to the target peg

// Because we only want the move count, there is no need to implement any actual ring and peg representations
unsigned long long moves(int n)
{
	// Rare case: if there are no rings above, it only needs 1 move (this case is only true if we start with only one ring in the entire tower)
	if (n <= 0)
	{
		return 1;
	}
	
	// Only 3 moves are required to move a stack of two rings
	if (n == 1)
	{
		return 3;
	}
	
	// Total moves = the moves required to move the stack above the target ring to the spare peg
	// + 1 move to move the target ring to the target peg
	// + the moves required to move the stack on the spare peg onto the target peg
	return moves(n - 1) + 1 + moves(n - 1);
}

unsigned long long moves_to_solve(int n)
{
	// Start the recursion from n - 1 since it starts with one bottom ring
	return moves(n - 1);
}
