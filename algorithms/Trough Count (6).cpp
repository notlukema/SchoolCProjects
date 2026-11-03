/*
题目描述:
如果在长为n的数组a中对某个下标 i (0 < i < n)满足 a[i-1] > a[i] 并且 a[i+1] > a[i]，则a[i]为数组a中的一个波谷。
补全代码：函数 count_valley 统计整数数组中的波谷的个数并返回。   

#include <iostream>
using namespace std;

int count_valley(const int a[], int n)
{
// 填空1：统计波谷个数
}

int main()
{
int n;
cin >> n;
int *a = new int[n];
for(int i = 0; i < n; i ++) cin >> a[i];

// 调用函数返回波谷个数
cout << count_valley(a, n) << endl;

delete[] a;
return 0;
}

输入描述:
第一行一个正整数 n（3 ≤ n ≤ 10^6）。
第二行 n 个整数，表示序列 a[i]（−10^9 ≤ a[i] ≤ 10^9），相邻两数用空格分隔。

输出描述:
输出一个整数，表示序列中波谷的个数。

样例输入:
10
5 2 7 1 3 8 4 6 0 9

样例输出:
4
*/

// Given code
#include <iostream>
using namespace std;

int count_valley(const int a[], int n)
{
	// New code
	
	// We need at least 3 values to have the possibility of forming a trough
	if (n < 3)
	{
		return 0;
	}
	
	int count = 0;
	
	// Don't test the first and last values
	for (int i = 1; i < n - 1; i++)
	{
		// Literally the formula provided in the instructions
		if (a[i - 1] > a[i] && a[i + 1] > a[i])
		{
			count++;
		}
	}
	
	return count;
}

// Given code
int main()
{
	int n;
	cin >> n;
	int *a = new int[n];
	for(int i = 0; i < n; i ++) cin >> a[i];
	
	// 调用函数返回波谷个数
	cout << count_valley(a, n) << endl;
	
	delete[] a;
	return 0;
}
