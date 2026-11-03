/*
题目描述:
若一个数能被某个大于 1 的整数的平方整除，则称该数为“平方因子数”（squareful number）。
例如：
4 = 2² × 1 → 含平方因子 2²
8 = 2² × 2 → 含平方因子 2²
18 = 3² × 2 → 含平方因子 3²
因此4，8，18都是平方因子数。
给定一个整数n，请你计算在区间[1, n]内有多少个整数是非平方因子数。

输入描述:
一个整数 n (1 ≤ n ≤ 10^7）

输出描述:
一个整数，表示区间[1, n]内非平方因子数的数量。

样例输入:
20

样例输出:
13

注释:
1 到 20 中的平方因子数为：
4, 8, 9, 12, 16, 18, 20 → 共 7 个。
故余下13个为非平方因子数。

提示：
可运用筛法思想，不要依次对每个数进行因数分解
对于不同n可开一个大数组（如int a[10 000 000]）使范围内数据能全部放入，每次只用前n位
由于数组长度较大，可将其定义为全局变量（在main函数外定义）
*/

#include <iostream>

// Array for marking multiples
const int MAX = 10000000;
unsigned char mark[MAX]; // Unsigned char is equal to uint8_t except without needing the header cstdint

int main()
{
	// Recieve input
	int n;
	std::cin >> n;
	
	int sqr;
	// Repeat until the square is bigger than n
	for (int i = 2; (sqr = i * i) <= n; i++)
	{
		// If already marked, it means any multiple of it will also already be marked, so skip
		if (mark[i - 1])
		{
			continue;
		}
		// Mark all multiples
		for (int j = sqr; j <= n; j += sqr)
		{
			mark[j - 1] = 1;
		}
	}
	
	// Count all not marked
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (!mark[i])
		{
			count++;
		}
	}
	
	// Print
	std::cout << count;
	
	return 0;
}


/* I tried to make an optimized version but the overlapping mutliples that overlap again and again defeated me :(
// Also, I miscounted 10^7 as 10^6

// Prime numbers up to the theoretical highest number (since the sqrt of n has a maximum of 1000)
const int prime_numbers[169] = {
	  2,   3,   5,   7,  11,  13,  17,  19,  23,  29,
	 31,  37,  41,  43,  47,  53,  59,  61,  67,  71,
	 73,  79,  83,  89,  97, 101, 103, 107, 109, 113,
	127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
	179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
	233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
	283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
	353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
	419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
	467, 479, 487, 491, 499, 503, 509, 521, 523, 541,
	547, 557, 563, 569, 571, 577, 587, 593, 599, 601,
	607, 613, 617, 619, 631, 641, 643, 647, 653, 659,
	661, 673, 677, 683, 691, 701, 709, 719, 727, 733,
	739, 743, 751, 757, 761, 769, 773, 787, 797, 809,
	811, 821, 823, 827, 829, 839, 853, 857, 859, 863,
	877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
	947, 953, 967, 971, 977, 983, 991, 997, 0
};

const int MAX_PRIMES = 168;

int main()
{
	// Collect input
	int n;
	std::cin >> n;

    // We start from 2^2 so we need at least 4
    if (n < 4)
    {
        std::cout << n;
        return 0;
    }
	
	// Highest number possible (10^7 as guaranteed by the instructions)
	if (n > 1000 * 1000)
	{
		std::cout << "Number bigger than guaranteed in instructions";
		return 0;
	}
	
	long long prime_squares[MAX_PRIMES];
	
	int mcount = 0;
	
	int i = 0;
	int num;
	while (i < MAX_PRIMES && (num = prime_squares[i] = (long long)prime_numbers[i] * prime_numbers[i]) < n)
	{
		int add = (n / prime_squares[i]);
		//int mlast = mcount;
		mcount += add;
		//std::cout << (num) << ", " << add << ": ";
		//std::cout << num << ", ";
		for (int j = 0; j < i; j++)
		{
			int sub = add / prime_squares[j];
			if (sub == 0)
			{
				break;
			}
			mcount -= sub;
			//std::cout << sub << ", ";
		}
		//std::cout << (mcount - mlast) << "\n";
		i++;
	}
	
	std::cout << n - mcount;
	
}

*/
