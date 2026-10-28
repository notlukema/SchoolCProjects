/*
题目描述：
已知一个一元二次方程的系数为 a、b、c，且判别式大于零（即有两个不同的实根）。请编写一个程序，计算并输出这两个实根，结果保留 3 位小数。输出的两个根按 从小到大 的顺序排列，中间用空格分隔。

输入描述：
无输入，三个方程的三组a、b、c按顺序分别取以下值：
1.a = 1, b = -3, c = 2
2.a = 2, b = -5, c = 2
3.a = -3, b = 10, c = 2

输出描述：
三行，每行两个实数，按上述系数a、b、c顺序表示方程的两个不同实根，保留 3 位小数，按从小到大顺序输出，中间用空格分隔。

注释：
提示：
注意输出顺序。
可在使用cout输出前添加cout << fixed << setprecision(3)控制输出小数点后三位，示例代码如下：

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
cout << fixed << setprecision(3) << 65.4321234 << endl;
return 0;
}

代码输出：65.432
*/

#include <iostream>
#include <iomanip>
#include <cmath> // C++ version of math.h

// Since the instructions wants us to perform the same operation on different sets of variables, let us create a function to assist us:
void printQuadratic(int a, int b, int c)
{
	// Quadratic formula taken apart
	double sqrt_part = std::sqrt(b * b - 4 * a * c);
	double solution1 = ((-b) + sqrt_part) / (2 * a);
	double solution2 = ((-b) - sqrt_part) / (2 * a);
	
	// Print with setprecision() as recommended by the instructons
	std::cout << std::fixed << std::setprecision(3) << std::min(solution1, solution2) << " ";
	std::cout << std::fixed << std::setprecision(3) << std::max(solution1, solution2) << "\n"; // Note: I prefer "\n" over std::endl
}

int main()
{
	// The input is hard coded here
	printQuadratic(1, -3, 2);
	printQuadratic(2, -5, 2);
	printQuadratic(-3, 10, 2);
	
	return 0;
}
