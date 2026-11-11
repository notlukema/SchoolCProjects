/*
题目描述:
读入BMP图片文件，根据BMP文件头和信息头的格式说明，输出图片的几个重要信息。
判断文件 image.bmp 是否是标准BMP文件（即 BMP文件头中 signature 是否等于 0x4D42），若是，则输出其【图像尺寸（宽度×高度），数据大小（字节数），文件大小（字节数）】信息到文件 image_info.txt。

BMP文件的数据按照从文件头开始的先后顺序分为四个部分：
BMP文件头（BMP file header）：提供文件的格式、大小等信息
BMP信息头（BMP information header）：提供图像数据的尺寸、位平面数、压缩方式、颜色索引等信息
调色板（color palette）：可选，如使用索引来表示图像，调色板就是索引与其对应的颜色的映射表
位图数据（BMP data）：图像数据
本题要求输出的信息均在 BMP文件头 和 BMP信息头 中，二者结构体在下方注释中有声明。

输入描述:
一个BMP图片文件 image.bmp（示例BMP图片，请点击下载）

输出描述:
一个文本文件 image_info.txt，其中包括BMP图片的【图像尺寸（宽度×高度），数据大小（字节数），文件大小（字节数）】

样例输入:
一个BMP图片文件（image.bmp）

样例输出:
一个文本文件（image_info.txt），内容为：
image size 195 * 195 pixels
data size 114660 bytes
file size 114798 bytes

注释:
为提供更多测试用例，示例图片的云盘链接还有 2.bmp 和 3.bmp，它们的输出信息分别为：
输入：2.bmp
输出：image_info.txt
image size 112 * 112 pixels
data size 37632 bytes
file size 37770 bytes

输入：3.bmp
输出：image_info.txt
image size 650 * 489 pixels
data size 954528 bytes
file size 954666 bytes

（注意提交代码中的输入文件名为 "image.bmp"，输出文件名为 "image_info.txt"）

BMP图片的文件头和信息头结构体：

#include <cstdint>  // int32_t, uint32_t, uint16_t

#pragma pack(push, 1)
typedef struct {
uint16_t signature;      // "BM" (0x4D42)
uint32_t file_size;      // 文件总大小
uint16_t reserved1;      // 保留
uint16_t reserved2;      // 保留
uint32_t data_offset;    // 图像数据起始偏移
} BMPFileHeader;
#pragma pack(pop)

typedef struct {
uint32_t biSize;         // 本结构大小(40字节)
int32_t biWidth;         // 图像宽度（像素）
int32_t biHeight;        // 图像高度（像素，正数表示倒序）
uint16_t biPlanes;       // 颜色平面数（必须为1）
uint16_t biBitCount;     // 每像素位数
uint32_t biCompression;  // 压缩类型
uint32_t biSizeImage;    // 图像数据大小（字节）
int32_t biXPelsPerMeter; // 水平分辨率（像素/米）
int32_t biYPelsPerMeter; // 垂直分辨率（像素/米）
uint32_t biClrUsed;      // 实际使用的颜色数
uint32_t biClrImportant; // 重要颜色数
} BMPInfoHeader;
*/

#include <fstream>
#include <cstdint> // uint64_t is equivalent to unsigned long long

// Hmmm the given code isn't mandatory plus it's format isn't the best for this case

using byte_t = uint8_t; // Rename for convenience

// We could create a struct to hold header and info data but there isn't much usage for that here

// However, I do like code that can do more than required
// So here is a complete file bit reading system

struct bit_pointer // Compress two numbers into one
{
	byte_t last_byte;
	uint8_t bit;
	bool read_all;
	
	bit_pointer() : last_byte(0), bit(0), read_all(false)
	{}
};

static uint8_t bit_mask[8] = // Pre-calculate the masks needed for how many bits
{
	1,
	3,
	7,
	15,
	31,
	63,
	127,
	255
};

// I like being able to read individual bits instead of always bytes
template<typename T>
T read_bits(std::ifstream& input, bit_pointer& p, uint64_t count)
{
	if (count > sizeof(T) * 8) // Reading more than can be stored?
	{
		throw std::out_of_range("Attempting to read more bits than type can hold!");
	}
	
	if (p.read_all) // No bits/bytes to read
	{
		return 0;
	}
	
	T out = 0;
	uint64_t base = count;
	
	// Read until we reach "0 bits left to read"
	while (count > 0)
	{
		uint8_t starting_bit = p.bit;
		if (starting_bit == 0) // Read next byte in file if we are starting a new byte
		{
			if (!input.read(reinterpret_cast<char*>(&p.last_byte), 1)) // We read all bytes in the file?
			{
				p.read_all = true;
				break;
			}
		}
		
		// How many bits to read (don't read past 8 bits per byte)
		uint8_t read_count = 8 - starting_bit;
		if (read_count > count) // Skip using std::min from cmath (or algorithm)
		{
			read_count = count;
		}
		
		// Technically |= and += have the same effect since the overlapping areas are all zeros
		out |= (p.last_byte & bit_mask[read_count - 1]) << (base - count);
		
		// Flipped bit adding
		//out <<= read_count;
		//out |= p.last_byte & bit_mask[read_count - 1];
		
		// Increment and decrement
		count -= read_count;
		p.bit += read_count;
		
		if (p.bit == 8) // Starting new byte?
		{
			p.bit = 0;
		}
		else
		{
			// Snip current byte by bits read
			p.last_byte >>= read_count;
		}
	}
	
	return out;
}

// Bit more complicated than just increasing the pointer numbers
// We also need to make sure we are incrementing the file reading progress
void skip_bits(std::ifstream& input, bit_pointer& p, uint64_t count)
{
	// Loop until no bits to skip
	while (count > 0)
	{
		if (p.bit == 0) // Read bytes to progress file
		{
			if (!input.read(reinterpret_cast<char*>(&p.last_byte), 1)) // Read all bytes?
			{
				p.read_all = true;
				break;
			}
		}
		uint8_t bits_left = 8 - p.bit; // How many bits to read to advance to next byte
		if (count < bits_left) // We do not need to read the next byte
		{
			p.bit += count;
			break; // Same as count = 0
		}
		
		// Decrement and advance
		count -= bits_left;
		p.bit = 0;
	}
}

// Usually we output to the previously mentioned theoretical struct but this time we just print to a file
void read_bmp_data(std::ifstream& input)
{
	// Initialization
	std::ofstream output("image_info.txt");
	bit_pointer p;
	
	// Get and check signature
	uint16_t signature = read_bits<uint16_t>(input, p, 16);
	if (signature != 0x4D42)
	{
		output << "Signature is not \'BM\'!";
		output.close();
		return;
	}
	
	uint32_t file_size = read_bits<uint32_t>(input, p, 32); // Get file size
	skip_bits(input, p, 32); // Skip reserved 1 and 2
	uint32_t data_offset = read_bits<uint32_t>(input, p, 32); // Get data offset
	
	skip_bits(input, p, 32); // Skip DIB header size
	int32_t bi_width = read_bits<int32_t>(input, p, 32); // Get width
	int32_t bi_height = read_bits<int32_t>(input, p, 32); // Get height
	
	// Skip getting the rest of the data
	
	// Print metrics
	output << "image size " << bi_width << " * " << bi_height << " pixels\n";
	output << "data size " << (file_size - data_offset) << " bytes\n";
	output << "file size " << file_size << " bytes";
	
	// Close output
	output.close();
}

int main()
{
	// Recieve input
	std::ifstream input("image.bmp");
	
	// Read
	read_bmp_data(input);
	
	// Close file
	input.close();
	
	return 0;
}
