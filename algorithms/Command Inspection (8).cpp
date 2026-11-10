/*
题目描述:
以下是大作业的简单介绍（如果已经熟悉这一部分可以跳过）：
小明在学习了《程序设计基础》之后，构思了一款模拟机器人搬运积木的游戏。游戏背景是一间未来房间，房间内摆放着积木及两条传送带：
输入传送带 会传入一串积木；
输出传送带 将积木运走；
房间内还设有若干带编号的空地（编号从 0 开始），每个空地最多存放一块积木。
房间中有一个机器人。机器人执行一段由多条指令组成的程序来完成任务。每条指令有序号（从 1 开始），机器人默认从第 1 条开始顺序执行。机器人一次只能搬运一个积木，该积木称为 当前积木，初始状态下机器人手中没有积木。

机器人的完整指令集定义如下：
指令	操作数数量	功能说明
inbox	无	从输入传送带取一块积木作为当前积木
outbox	无	将当前积木放到输出传送带
add X	1	当前积木的数值 + 空地 X 中积木的数值
sub X	1	当前积木的数值 − 空地 X 中积木的数值
copyto X	1	当前积木复制到空地 X
copyfrom X	1	空地 X 的积木复制为当前积木
jump X	1	跳转到第 X 条指令继续执行
jumpifzero X	1	若当前积木为 0，则跳转到第 X 条指令

为了在后续大作业中模拟机器人执行过程，你需要首先判断机器人程序中是否存在静态错误。因此，本题要求对给定的一组指令做 静态语法检查，仅检查指令格式是否合法，不模拟运行过程。

简便起见，本题中只需要检查指令语法，不需要判断指令能否正常模拟运行。
即对于一条指令，若出现以下任意情况，则判定为出错：
使用了不在允许集合中的指令名称
指令需要操作数但缺少操作数
指令不需要操作数却多写了内容
操作数不是整数
对空地操作（add / sub / copyto / copyfrom）时，操作数不在 [0, 空地数量−1] 范围内
对跳转指令（jump / jumpifzero）时，目标行号不在 [1, 指令总数] 范围内
若没有出现上述错误，则通过语法检查。

注意：本题的输入输出均为文件输入输出！

输入描述:
本题的数据输入 从文件 input.txt 读取，格式如下：
第一行包含两个整数 N 和 M 。
N 表示空地数量，空地编号为 0 到 N−1
M 表示允许使用的指令名称个数
（保证 N ≥ 0，M ≥ 0）
第二行包含 M 个用空格分隔的字符串。
<指令名称1> <指令名称2> ... <指令名称M>
表示本次关卡允许使用的合法指令集合
指令名称区分大小写
第三行：包含一个整数 K 。
表示机器人程序包含的指令数量
每条指令按顺序从第 1 条到第 K 条编号
接下来 K 行，每行是一条需要检查的指令。
<指令1>
<指令2>
...
<指令K>
一条指令可能由一个或多个字符串组成

输出描述:
将检查结果输出到 文件 output.txt 中 。
输出顺序与输入指令顺序一致，共 K 行，每条指令对应一行输出。
对于每条指令，如果语法合法则输出OK，否则输出Error。

样例输入:
输入文件的内容如下：
5 6
inbox outbox add sub copyto copyfrom
6
inbox
add 2
sub -1
add 9
jump 3
copyto

样例输出:
输出文件的内容如下：
OK
OK
Error
Error
Error
Error

注释:
解释：
指令	原因
inbox	无操作数，合法
add 2	使用合法指令，空地 2 存在
sub -1	空地编号不能为负
add 9	空地编号越界（只有 0~4）
jump 3	jump 未出现在允许的指令集中
copyto	缺少操作数
*/

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

// Helper struct for storing format info
struct format
{
	std::string name;
	bool has_param, tile_bound, cmd_count_bound;
	
	// The booleans remind me of how bit operators can be used to combine boolean conditions
	// Of course, that would be way overkill for our use here
	
	format(std::string name, bool hp = false, bool tb = false, bool ccb = false) : name(name), has_param(hp), tile_bound(tb), cmd_count_bound(ccb)
	{}
};

// Define instructions and their valid formats
const int total_ins_count = 8;
const format ins_set[total_ins_count] = {
	format("inbox"),
	format("outbox"),
	format("add", true, true),
	format("sub", true, true),
	format("copyto", true, true),
	format("copyfrom", true, true),
	format("jump", true, false, true),
	format("jumpifzero", true, false, true)
};

// Find the corresponding index of an instruction in the instructions set
int find_match(std::string name)
{
	// Loop through every existing instruction
	for (int i = 0; i < total_ins_count; i++)
	{
		if (name == ins_set[i].name)
		{
			return i;
		}
	}
	return -1;
}

// Check if string is integer
bool is_int(std::string str)
{
	// Loop
	for (char c : str)
	{
		if (c < '0' || c > '9') // Not a number?
		{
			return false;
		}
	}
	return true;
}

int main()
{
	// Open input file
	std::ifstream input("input.txt");
	
	if (!input.is_open()) // Boo hoo (no file)
	{
		return 0;
	}
	
	// Read and store all the lines first
	std::vector<std::string> lines;
	std::string line;
	while (getline(input, line))
	{
		lines.push_back(line);
	}
	
	// Close input file since we read all the data already
	input.close();
	
	// Open output file (blank file)
	std::ofstream output("output.txt");
	
	// 3 lines or less means there aren't enough lines for even basic info
	if (lines.size() < 4)
	{
		return 0;
	}
	
	// Extract info from first two lines
	std::string l1 = lines[0];
	std::string l2 = lines[1];
	std::string l3 = lines[2];
	
	// We assume the basic info always conforms
	int t = l1.find(' ');
	int tiles = std::stoi(l1.substr(0, t)); // How many available tiles there are
	int instructions = std::stoi(l1.substr(t, l1.size())); // How many allowed instructions there are
	
	// Create list of allowed instructions
	bool allowed[total_ins_count] = { false };
	for (int i = 0; i < instructions; i++)
	{
		// Skip if line is empty (shouldn't be possible)
		if (l2.empty())
		{
			continue;
		}
		
		// Find index of next space or end of line if no space
		t = l2.find(' ');
		if (t < 0)
		{
			t = l2.size();
		}
		
		// Name of instruction
		std::string instruction = l2.substr(0, t);
		l2.erase(0, t + 1); // Snip off this part
		
		// Find matching instruction and mark as allowed
		int idx = find_match(instruction);
		if (idx >= 0)
		{
			allowed[idx] = true;
		}
	}
	
	// Extract the amount of commands
	int ins_count = std::stoi(l3);
	
	// Loop instructions
	for (int i = 0; i < ins_count; i++)
	{
		// Grab line starting from the 4th line
		std::string l = lines[i + 3];
		
		// Get name first
		t = l.find(' '); // Same technique used earlier
		if (t < 0)
		{
			t = l.size();
		}
		std::string name = l.substr(0, t);
		
		l.erase(0, t + 1); // Snip
		
		int idx = find_match(name);
		if (idx < 0) // Instruction doesn't exist
		{
			output << "Error\n";
			continue;
		}
		
		if (!allowed[idx]) // Instruction not allowed
		{
			output << "Error\n";
			continue;
		}
		
		// Get corresponding format
		format f = ins_set[idx];
		
		if (f.has_param == l.empty()) // Requires parameter?
		{
			output << "Error\n";
			continue;
		}
		
		if (!f.has_param) // The rest of the checks are based on the fact that the instruction has a parameter
		{
			output << "OK\n";
			continue;
		}
		
		if (!is_int(l)) // Not integer
		{
			output << "Error\n";
			continue;
		}
		
		// Get parameter value
		int param = std::stoi(l);
		
		if (f.tile_bound) // Check if within tile bounds
		{
			if (param < 0 || param >= tiles)
			{
				output << "Error\n";
				continue;
			}
		}
		
		if (f.cmd_count_bound) // Check if within instruction count bounds
		{
			if (param < 1 || param > ins_count)
			{
				output << "Error\n";
				continue;
			}
		}
		
		// Passed all checks
		output << "OK\n";
	}
	
	// Close output file
	output.close();
	
	return 0;
}
