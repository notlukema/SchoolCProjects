#include "ConsoleEngine.h"

#include <cstdint>
#include <cstdlib>
#include <string>
#include <iostream>
#include <malloc.h>

namespace Engine
{

	ConsoleEngine::ConsoleEngine(const uint32_t width, const uint32_t height, float aspect, char clearChar) : width(width), height(height), clearChar(clearChar), screenRefresh(true), printLogs(false)
	{
		framebuffer = new CharTexture(width, height);
		camera = new CharCamera();
		rasterizer = new CharRasterizer(framebuffer, camera, aspect);
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

	void ConsoleEngine::beginRender()
	{
		rasterizer->catchCamera();
	}

	void ConsoleEngine::renderToScreen()
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

		if (screenRefresh)
		{
#ifdef _WIN32
			std::system("cls");
#elif
			std::system("clear");
#endif
		}

		// Weird inconsistencies in screen refreshes...

		std::cout << (screenRefresh ?
			"\033[H\033[2J" : // Reset cursor position and clear screen
			"\033[H"          // Only reset cursor position to overwrite
			//"\033[2J\033[1;1H" :
			//"\033[1;1H"
			) << std::flush << str;

		screenRefresh = false;

		// Print logs if enabled
		if (printLogs)
		{
			std::cout << std::endl;
			for (const std::string& log : logs)
			{
				std::cout << log << std::endl;
			}
		}
	}

}