/*
题目描述：
平面上有两条相互平行的直线 y = 1 和 y = 0。给定一个正整数 m，两条直线上分别有以下这些点：
在直线 y = 1 上有 p 个点，其坐标依次为 (a0, 1), (a1, 1), ..., (ap-1, 1)。
在直线 y = 0 上有 q 个点，其坐标依次为 (b0, 0), (b1, 0), ..., (bq-1, 0)。
所有点的横坐标均为非负整数，且输入中每条直线上的点已按横坐标严格递增的顺序给出，即 0≤a0<a1< ...<ap-1≤m，0≤b0<b1< ...<bq-1≤m。
两条不同直线上的点可以具有相同的横坐标。
你的任务是，从两条直线上各选取一个点，使这两个点之间的欧几里得距离最短，并输出这个最短距离。
其中，点 (ai, 1) 和点 (bj, 0) 之间的距离为 
$$
\sqrt{(a_i - b_j)^2 + 1}.
$$

输入描述：
输入数据共三行。
第一行三个整数 m, p, q，分别表示横坐标的上界，以及直线 y = 1 和直线 y = 0 上的点数。
第二行 p 个整数 a0, a1, ..., ap-1，依次表示直线 y = 1 上各点的横坐标。
第三行 q 个整数 b0, b1, ..., bq-1，依次表示直线 y = 0 上各点的横坐标。
同一行中的相邻整数之间用一个空格分隔。

输出描述：
输出数据共一行，一个实数，表示所求的最短距离。按照四舍五入的规则，保留小数点后两位。

样例输入：
8 2 2
1 4
4 7

样例输出：
1.00

注释：
样例输入 2：
50 4 3
0 14 28 43
9 26 38

样例输出 2：
2.24

样例输入 3：
400 10 9
0 4 8 12 16 20 24 28 75 140
60 78 150 180 220 260 300 340 380

样例输出 3：
3.16

说明/提示：
对于 30% 的数据，满足 1≤p, q≤100。
对于 60% 的数据，满足 1≤p, q≤104。
对于 100% 的数据，满足 1≤m≤109，1≤p, q≤106，0≤ai, bj≤m。
所有输入数值均为整数，且序列 a 和 b 分别严格递增。

输入 #1 解释：
选取点 (4, 1) 和点 (4, 0) 时，两点之间的距离为 1，恰好等于两条直线之间的距离，因此输出 1.00。

输入 #2 解释：
选取点 (28, 1) 和点 (26, 0) 时，两点之间的距离最短，为 $\sqrt{(28 - 26)^2 + 1} = \sqrt{5}$。保留小数点后两位，得到 2.24。

输入 #3 解释：
选取点 (75, 1) 和点 (78, 0) 时，两点之间的距离最短，为 $\sqrt{(75 - 78)^2 + 1} = \sqrt{10}$。保留小数点后两位，得到 3.16。
*/

#include <iostream>
#include <iomanip>
#include <cmath> // C++ version of math.h

// The instructions provides us with a formula for distance, so let's get that over with first
double distance(double x1, double x2)
{
	// Which point is on y=1 and the other on y=0 is not important, since the distance will be the same regardless
	return std::sqrt((x2 - x1) * (x2 - x1) + 1.0);
}

int main()
{
	// Recieve input first
	int m, p, q;
	std::cin >> m >> p >> q;
	
	// In reality, m has no play in our algorithm here because the inputs already conform to it as a maximum value
	
	// Create arrays (no need to use vectors and stuff here)
	int* parr = new int[p];
	int* qarr = new int[q];
	
	// Receive array input
	for (int i = 0; i < p; i++)
	{
		std::cin >> parr[i];
	}
	for (int i = 0; i < q; i++)
	{
		std::cin >> qarr[i];
	}
	
	// Since we will be dealing with a massive amount of points, we cannot test each point individually with every other point
	// (Speed is critical here)
	// Instead, we will rely on the fact that y is constant, meaning we only need to test the distance between x coordinates
	
	// In practice, only the two points to the immediate left and right are the closest to any single point
	// Which means we only need to test these distances to find our overall smallest distance
	// Which also means that we are able to encompass all possibilities of having the smallest distance by progressively stepping through the nearest points to each other
	// (Note that the points are inputted in a constantly increasing manner)
	int pi = 0;
	int qi = 0;
	int mindx = -1; // Negative means empty
	int minp = 0;
	int minq = 0;
	
	// Since we step the point with a smaller x, if any point reaches the end, it means there are no more points that are closer
	while (pi < p && qi < q)
	{
		// Find x distance
		int x1 = parr[pi];
		int x2 = qarr[qi];
		int dx = std::abs(x1 - x2);
		
		// Record if the x distance is smaller
		if (dx < mindx || mindx < 0)
		{
			mindx = dx;
			minp = pi;
			minq = qi;
		}
		
		// Step the point with a smaller x
		if (x1 < x2)
		{
			pi++;
		}
		else
		{
			qi++;
		}
	}
	
	// Due to the nature of the input, we can safely assume there is always a result (mindx does not equal -1)
	// In that case, calculate the true distance and print with two decimals
	double dis = distance(parr[minp], qarr[minq]);
	std::cout << std::fixed << std::setprecision(2) << dis;
	
	// Cleanup despite the program ending
	delete[] parr;
	delete[] qarr;
	
	return 0;
}
