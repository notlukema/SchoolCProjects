#include "ConsoleEngine.h"

#include <cstdint>
#include <cmath>
#include <malloc.h>
#include <limits>

namespace Engine
{

	CharRasterizer::CharRasterizer(CharTexture* target) : target(target)
	{
		size = target->getWidth() * target->getHeight();
		depthBuffer = (depth_t*)malloc(size * sizeof(depth_t));
	}

	CharRasterizer::~CharRasterizer()
	{
		free(depthBuffer);
	}

	void CharRasterizer::clearDepth()
	{
		auto limits = std::numeric_limits<depth_t>();
		depth_t val = limits.has_infinity ? limits.infinity() : limits.max();
		for (uint32_t i = 0; i < size; i++)
		{
			depthBuffer[i] = val;
		}
	}

	void CharRasterizer::drawPoint(uint32_t x, uint32_t y, depth_t z, char c)
	{
		if (!target->inBounds(x, y))
		{
			return;
		}
		uint32_t i = target->geti(x, y);
		depth_t currentDepth = depthBuffer[i];
		if (z < currentDepth)
		{
			depthBuffer[i] = z;
			target->putr(x, y, c);
		}
	}

	void CharRasterizer::drawLine(int x1, int y1, int x2, int y2, char c)
	{
		int dx = abs(x2 - x1);
		int dy = abs(y2 - y1);
		int sx = (x1 < x2) ? 1 : -1;
		int sy = (y1 < y2) ? 1 : -1;
		int err = dx - dy;
		int width = static_cast<int>(target->getWidth());
		int height = static_cast<int>(target->getHeight());
		while (true)
		{
			if (x1 >= 0 && y1 >= 0)
			{
				target->put(static_cast<uint32_t>(x1), static_cast<uint32_t>(y1), c);
			}
			if (x1 == x2 && y1 == y2)
			{
				break;
			}
			int e2 = err * 2;
			if (e2 > -dy)
			{
				err -= dy;
				x1 += sx;
			}
			if (e2 < dx)
			{
				err += dx;
				y1 += sy;
			}

			// Clip extras in case
			if (x1 < 0 && sx < 0)
			{
				break;
			}
			if (y1 < 0 && sy < 0)
			{
				break;
			}
			if (x1 >= width && sx > 0)
			{
				break;
			}
			if (y1 >= height && sy > 0)
			{
				break;
			}
		}
	}

}