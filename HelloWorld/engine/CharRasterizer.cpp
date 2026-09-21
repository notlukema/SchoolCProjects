#include "ConsoleEngine.h"

#include <cstdint>
#include <cmath>
#include <malloc.h>
#include <limits>

namespace Engine
{

	CharRasterizer::CharRasterizer(CharTexture* target, CharCamera* camera, float aspect) : target(target), camera(camera), aspect(aspect), cameraMatrix(clfe::Matrix4x4f())
	{
		size = target->getWidth() * target->getHeight();
		depthBuffer = (depth_t*)malloc(size * sizeof(depth_t));
	}

	CharRasterizer::~CharRasterizer()
	{
		free(depthBuffer);
		// Don't free camera since it is given and doesn't belong to this class
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
		if (z < -1 || z > 1)
		{
			return;
		}
		if (!target->inBounds(x, y))
		{
			return;
		}
		uint32_t i = target->geti(x, y);
		depth_t currentDepth = depthBuffer[i];
		if (z < currentDepth)
		{
			depthBuffer[i] = z;
			target->putr(i, c);
		}
	}

	void CharRasterizer::drawPointR(const clfe::Vector3f& point, char c)
	{
		depth_t z = static_cast<depth_t>(point.z());
		if (z < -1 || z > 1)
		{
			return;
		}
		int x1 = static_cast<int>(std::round(point.x()));
		int y1 = static_cast<int>(std::round(point.y()));
		if (x1 < 0 || y1 < 0)
		{
			return;
		}
		uint32_t x = static_cast<uint32_t>(x1);
		uint32_t y = static_cast<uint32_t>(y1);
		if (x >= target->getWidth() || y >= target->getHeight())
		{
			return;
		}

		uint32_t i = target->geti(x, y);
		depth_t currentDepth = depthBuffer[i];
		if (z < currentDepth)
		{
			depthBuffer[i] = z;
			target->putr(i, c);
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

	// 3d

	clfe::Vector3f CharRasterizer::transformPoint(const clfe::Vector3f& point) const
	{
		clfe::Vector4f tp4 = clfe::Vector4f(point.x(), point.y(), point.z(), 1.0f) * cameraMatrix;
		if (tp4.w() == 0.0f)
		{
			return clfe::Vector3f(0.0f, 0.0f, 0.0f);
		}
		clfe::Vector3f tp3 = clfe::Vector3f(tp4.x() / tp4.w(), tp4.y() / tp4.w(), tp4.z() / tp4.w());
		return tp3;
	}

	void CharRasterizer::drawPoint(const clfe::Vector3f& point, char c)
	{
		clfe::Vector3f tp3 = transformPoint(point);
		screenScaleR(tp3);
		drawPointR(tp3, c);

		//ConsoleEngine::Log("Drawing point: " + std::to_string(tp3.x()) + ", " + std::to_string(tp3.y()) + ", " + std::to_string(tp3.z()));
	}

	void CharRasterizer::drawLine(const clfe::Vector3f& p1, const clfe::Vector3f& p2, char c)
	{
		clfe::Vector3f tp1 = transformPoint(p1);
		clfe::Vector3f tp2 = transformPoint(p2);
		if (tp1.z() < -1 && tp2.z() < -1)
		{
			return;
		}
		if (tp1.z() > 1 && tp2.z() > 1)
		{
			return;
		}
		screenScaleR(tp1);
		screenScaleR(tp2);
		if (tp1.x() < 0 && tp2.x() < 0)
		{
			return;
		}
		if (tp1.x() >= target->getWidth() && tp2.x() >= target->getWidth())
		{
			return;
		}
		if (tp1.y() < 0 && tp2.y() < 0)
		{
			return;
		}
		if (tp1.y() >= target->getHeight() && tp2.y() >= target->getHeight())
		{
			return;
		}

		//ConsoleEngine::Log("Drawing line: " + std::to_string(tp1.x()) + ", " + std::to_string(tp1.y()) + ", " + std::to_string(tp1.z()) + " to " + std::to_string(tp2.x()) + ", " + std::to_string(tp2.y()) + ", " + std::to_string(tp2.z()));

		int x1 = static_cast<int>(std::round(tp1.x()));
		int y1 = static_cast<int>(std::round(tp1.y()));
		int x2 = static_cast<int>(std::round(tp2.x()));
		int y2 = static_cast<int>(std::round(tp2.y()));

		int x = x1;
		int y = y1;
		int dx = abs(x2 - x1);
		int dy = abs(y2 - y1);
		int sx = (x1 < x2) ? 1 : -1;
		int sy = (y1 < y2) ? 1 : -1;
		int err = dx - dy;
		int width = static_cast<int>(target->getWidth());
		int height = static_cast<int>(target->getHeight());
		while (true)
		{
			if (x >= 0 && y >= 0)
			{
				target->put(static_cast<uint32_t>(x), static_cast<uint32_t>(y), c);
			}
			if (x == x2 && y == y2)
			{
				break;
			}
			int e2 = err * 2;
			if (e2 > -dy)
			{
				err -= dy;
				x += sx;

			}
			if (e2 < dx)
			{
				err += dx;
				y += sy;
			}

			// Clip extras in case
			if (x < 0 && sx < 0)
			{
				break;
			}
			if (y < 0 && sy < 0)
			{
				break;
			}
			if (x >= width && sx > 0)
			{
				break;
			}
			if (y >= height && sy > 0)
			{
				break;
			}
		}

	}

}