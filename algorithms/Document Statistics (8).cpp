/*
题目描述:
学校期末考试的成绩被保存为一个 CSV（逗号分隔值）格式文件，命名为input.csv，每一行代表一名学生的成绩，每一列代表一门课程的分数。
请你编写一个 C++ 程序，读取该 CSV 文件，统计每门课程的以下数据指标：
平均值（Mean）
中位数（Median）
最大值（Max）
最小值（Min）
方差（Variance）
并将结果输出到output.csv。

输入描述:
输入文件input.csv内为若干行，每行包含若干个用英文逗号分隔的数值（行尾没有逗号，文件尾没有换行）。
每一行表示一名学生的多门课程成绩。
每一列表示所有学生在该课程下的分数。
数据量不固定，但保证每行列数相同。
文件中 不包含表头行、列（即第一行、列就是成绩数据）。
所有分数均为100以内（≤100）非负整数。

输出描述:
输出文件output.csv内为若干行
每行对应原文件中一列的平均值、中位数、最大值、最小值、方差这五个统计量，用英文逗号隔开（行尾没有逗号）
数据四舍五入到小数点后2位
文件结尾不要添加额外回车（最后一行数字之后没有换行符）

样例输入:
输入文件存放于同文件夹下的input.csv，可通过文本格式读取，内容示例如下：
10,20,30
50,40,60
10,30,50

样例输出:
输出文件存放于同文件夹下的output.csv，可通过文本格式读取，内容示例如下：
23.33,10.00,50.00,10.00,355.56
30.00,30.00,40.00,20.00,66.67
46.67,50.00,60.00,30.00,155.56
*/

#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
	// Open input file
	std::ifstream input("input.csv");
	
	if (!input) // No file?
	{
		return 0;
	}
	
	// Recieve every line into a vector
	std::vector<std::string> lines;
	std::string line;
	while (getline(input, line))
	{
		lines.push_back(line);
	}
	
	// Close input file
	input.close();
	
	// Open output file
	std::ofstream output("output.csv");
	
	// Calculate column count based on the comma count in the first line
	int cols = 1 + std::count(lines[0].begin(), lines[0].end(), ',');
	for (int i = 0; i < cols; i++) // Loop every line (row)
	{
		// Start by finding the next column
		// We do this by snipping the next number off every line
		std::vector<int> col;
		int sum = 0; // The sum of all numbers in the column
		int sumsq = 0; // The square of the sum (used for calculating variance)
		for (std::string& row : lines)
		{
			if (row.empty()) // Skip column if there is nothing left (shouldn't happen)
			{
				continue;
			}
			
			// Find next comma or the end of the line if no comma
			int t = row.find(',');
			if (t < 0)
			{
				t = row.size();
			}
			
			// Grab next number
			int num = std::stoi(row.substr(0, t));
			
			// Add to sums
			sum += num;
			sumsq += num * num;
			
			// Add to vector and snip off the number from the line
			col.push_back(num);
			row.erase(0, t + 1);
		}
		
		// Sort the vector array
		// This allows us to easily grab the minimum and maximum
		std::sort(col.begin(), col.end());
		
		// Used for calculations
		int n = col.size();
		
		// Calculate mean
		double mean = ((double)sum / n);
		output << std::fixed << std::setprecision(2) << mean << ",";
		
		// Calculate median (with ternary operator for even and odd count cases)
		double median = (col.size() % 2 == 1) ? col[n / 2] : (double)(col[n / 2 - 1] + col[n / 2]) / 2;
		output << std::fixed << std::setprecision(2) << median << ",";
		
		output << std::fixed << std::setprecision(2) << (double)col.back() << ","; // Maximum
		output << std::fixed << std::setprecision(2) << (double)col.front() << ","; // Minimum
		output << std::fixed << std::setprecision(2) << (double)(n * sumsq - sum * sum) / (n * n); // Variance
		
		// New line if not final line
		if (i < cols - 1)
		{
			output << "\n";
		}
	}
	
	// Close output file
	output.close();
	
	return 0;
}
