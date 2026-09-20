#include "ConsoleEngine.h"

#include <cstdint>
#include <cstdlib>
#include <string>
#include <iostream>
#include <malloc.h>

namespace Engine
{

	ConsoleEngine::ConsoleEngine(const uint32_t width = 100, const uint32_t height = 20, char clearChar = ' ') : width(width), height(height), clearChar(clearChar), screenRefresh(true)
	{
		framebuffer = new CharTexture(width, height);
		rasterizer = new CharRasterizer(framebuffer);
		clear();
	}

	ConsoleEngine::~ConsoleEngine()
	{
		free(framebuffer);
		free(rasterizer);
	}

	void ConsoleEngine::resize(const uint32_t width, const uint32_t height)
	{
		this->width = width;
		this->height = height;
		framebuffer = new CharTexture(width, height);
		rasterizer->changeTarget(framebuffer);
		clear();
		screenRefresh = true;
	}

	void ConsoleEngine::render()
	{
		std::string str;
		str.reserve(height * (width + 1));

		for (uint32_t y = 0; y < height; y++)
		{
			uint32_t i = y * width;
			for (uint32_t x = 0; x < width; x++)
			{
				char c = framebuffer->get(x, y);
				str.push_back(c == '\0' ? ' ' : c);
			}
			str.push_back('\n');
		}

		/* Older style for clearing the console
#ifdef _WIN32
		std::system("cls");
#elif
		std::system("clear");
#endif
		*/
		
		// "redraw"
		std::cout << (screenRefresh ?
			"\033[H\033[2J" : // Reset cursor position and clear screen
			"\033[H"          // Only reset cursor position to overwrite
			) << std::flush << str;

		screenRefresh = false;
	}

}