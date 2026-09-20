#include "ConsoleEngine.h"

#include <cstdint>
#include <malloc.h>

namespace Engine
{

	CharTexture::CharTexture(const uint32_t width, const uint32_t height) : width(width), height(height), size(width * height)
	{
		buffer = (char*)calloc(size, sizeof(char));
	}

	CharTexture::~CharTexture()
	{
		free(buffer);
	}

	void CharTexture::clear(char c)
	{
		for (uint32_t i = 0; i < size; i++)
		{
			buffer[i] = c;
		}
	}

	char CharTexture::get(const uint32_t x, const uint32_t y) const
	{
		if (!inBounds(x, y))
		{
			return '\0';
		}
		return getr(x, y);
	}

	void CharTexture::put(const uint32_t x, const uint32_t y, char c)
	{
		if (!inBounds(x, y))
		{
			return;
		}
		putr(x, y, c);
	}

}