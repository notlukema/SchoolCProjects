/*
题目描述：
给定一个圆环柱（即圆筒），其外半径为 R，内半径为 r，高度为 h。
请编写程序，按下列两个公式依次计算并输出：
侧面积  S = 2πh(R + r)
体积    V = πh(R² − r²)
π 取 3.141592653589793，结果均保留 5 位小数，且必须先输出侧面积，再输出体积，两行结果均不允许输出任何多余字符（如单位、文字说明）。

输入描述：
无输入，R、r、h按顺序分别取三组值：
R = 5.0, r = 2.0, h = 10.0
R = 3.5, r = 2.5, h = 5.5
R = 0.1, r = 0.001, h = 11.1

输出描述：
三行，每行两个实数，按上述系数顺序给出对应的圆筒的侧面积和体积，结果保留五位小数，侧面积和体积之间用空格隔开。

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

void printMetrics(double R, double r, double h)
{
	// PI as given by the instructions
	double pi = 3.141592653589793;
	
	// Follow the given formulas
	double area = 2 * pi * h * (R + r);
	double volume = pi * h * (R * R - r * r);
	
	// Print using setprecision() as recommended by the instructions
	std::cout << std::fixed << std::setprecision(5) << area << " ";
	std::cout << std::fixed << std::setprecision(5) << volume << "\n"; // "\n" over std::endl any day
}

int main()
{
	// No input, data is hardcoded
	printMetrics(5.0, 2.0, 10.0);
	printMetrics(3.5, 2.5, 5.5);
	printMetrics(0.1, 0.001, 11.1);
	
	return 0;
}
