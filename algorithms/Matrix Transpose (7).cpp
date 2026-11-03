/*
题目描述:
请完成以下C++代码的填空部分。代码的功能是对一个矩阵进行转置，输出转置后的结果。

#include <iostream>
using namespace std;

/// 实现transposeMatrix函数

int main() {
int M, N;
cin >> M >> N;

///声明指针original、transposed

///动态分配原始矩阵original


// 输入原始矩阵
for (int i = 0; i < M; i++) {
for (int j = 0; j < N; j++) {
cin >> original[i][j];
}
}

/// transposeMatrix 对传入矩阵做转置操作并返回结果
transposed = transposeMatrix(original, M, N);

// 输出转置矩阵
for (int i = 0; i < N; i++) {
for (int j = 0; j < M; j++) {
cout << transposed[i][j] << " ";
}
cout << endl;
}

// 释放动态分配的原始矩阵
for (int i = 0; i < M; i++) {
delete[] original[i];
}
delete[] original;

// 释放动态分配的转置矩阵
for (int i = 0; i < N; i++) {
delete[] transposed[i];
}
delete[] transposed;

return 0;
}


填补代码要求：
指针original、transposed：
请正确声明指针original、transposed。
使用original申请二维动态数组用于存放原始输入矩阵。
2.transposeMatrix函数：
请实现transposeMatrix函数，该函数对传入矩阵做转置操作并返回结果。


输入描述:
输入共 M+1 行：
第一行包含两个整数 M 和 N (1 ≤ M,N ≤ 1000)，分别表示矩阵的行数和列数。
接下来的 M 行，每行包含 N 个整数，表示矩阵的每一行的元素。

输出描述:
输出 N 行，每行 M 个整数，表示转置后的矩阵

样例输入:
3 2
1 2
3 4
5 6

样例输出:
1 3 5
2 4 6
*/

// Given code
#include <iostream>
using namespace std;

// ------------------------------ New Code ------------------------------
int** transposeMatrix(int** arr, int m, int n)
{
	// Generate a new 2d array of flipped dimensions and at the same time input values
	int** arr2 = new int*[n];
	for (int i = 0; i < n; i++)
	{
		arr2[i] = new int[m];
		for (int j = 0; j < m; j++)
		{
			// Mapping values over
			arr2[i][j] = arr[j][i];
		}
	}
	
	// Return new array
	return arr2;
}
// ----------------------------------------------------------------------

int main() {
	int M, N;
	cin >> M >> N;
	
	// ------------------------------ New Code ------------------------------
	// Declare the 2d arrays (no need to define the second one yet since the function will do that for us)
	int** original = new int*[M];
	int** transposed;
	// ----------------------------------------------------------------------
	
	// ------------------------------ New Code ------------------------------
	// Define the inner-arrays of the 2d array
	for (int i = 0; i < M; i++)
	{
		original[i] = new int[N];
	}
	// ----------------------------------------------------------------------
	
	
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			cin >> original[i][j];
		}
	}
	
	transposed = transposeMatrix(original, M, N);
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << transposed[i][j] << " ";
		}
		cout << endl;
	}
	
	for (int i = 0; i < M; i++) {
		delete[] original[i];
	}
	delete[] original;
	
	for (int i = 0; i < N; i++) {
		delete[] transposed[i];
	}
	delete[] transposed;
	
	return 0;
}
