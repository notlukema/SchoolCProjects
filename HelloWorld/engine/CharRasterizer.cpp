#include "ConsoleEngine.h"

#include <cstdint>
#include <cmath>
#include <malloc.h>
#include <limits>

namespace Engine
{

	CharRasterizer::CharRasterizer(CharTexture* target, CharCamera* camera, float aspect) : target(target), camera(camera), aspect(aspect),
		worldMatrix(clfe::Matrix4x4f()), objectMatrix(clfe::Matrix4x4f()), transformMatrix(clfe::Matrix4x4f()), viewMatrix(clfe::Matrix4x4f())
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
		if (z < depthBuffer[i])
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

	clfe::Vector4f CharRasterizer::transformPoint(const clfe::Vector3f& point) const
	{
		return clfe::Vector4f(point.x(), point.y(), point.z(), 1.0f) * transformMatrix;
	}

	clfe::Vector3f CharRasterizer::toScreen(const clfe::Vector4f& point) const
	{
		clfe::Vector4f tp4 = point * viewMatrix;
		if (tp4.w() == 0.0f)
		{
			return clfe::Vector3f(0.0f, 0.0f, 0.0f);
		}
		return clfe::Vector3f(tp4.x() / tp4.w(), tp4.y() / tp4.w(), tp4.z() / tp4.w());
	}

	void CharRasterizer::drawPoint(const clfe::Vector3f& point, char c)
	{
		clfe::Vector3f tp3 = toScreen(transformPoint(point));
		screenScaleR(tp3);
		drawPointR(tp3, c);

		//ConsoleEngine::Log("Drawing point: " + std::to_string(tp3.x()) + ", " + std::to_string(tp3.y()) + ", " + std::to_string(tp3.z()));
	}

	void CharRasterizer::drawLine(const clfe::Vector3f& p1, const clfe::Vector3f& p2, char c)
	{
		clfe::Vector4f tp1 = transformPoint(p1);
		clfe::Vector4f tp2 = transformPoint(p2);

		float near = -camera->getNear();
		float far = -camera->getFar();

		if (tp1.z() > near && tp2.z() > near)
		{
			return;
		}
		if (tp1.z() < far && tp2.z() < far)
		{
			return;
		}

		if (tp1.z() > near)
		{
			float p = (near - tp2.z()) / (tp1.z() - tp2.z());
			tp1.z(-1);
			tp1.x(tp2.x() + (tp1.x() - tp2.x()) * p);
			tp1.y(tp2.y() + (tp1.y() - tp2.y()) * p);
		}
		if (tp1.z() < far)
		{
			float p = (far - tp2.z()) / (tp1.z() - tp2.z());
			tp1.z(1);
			tp1.x(tp2.x() + (tp1.x() - tp2.x()) * p);
			tp1.y(tp2.y() + (tp1.y() - tp2.y()) * p);
		}
		if (tp2.z() > near)
		{
			float p = (near - tp1.z()) / (tp2.z() - tp1.z());
			tp2.z(-1);
			tp2.x(tp1.x() + (tp2.x() - tp1.x()) * p);
			tp2.y(tp1.y() + (tp2.y() - tp1.y()) * p);
		}
		if (tp2.z() < far)
		{
			float p = (far - tp1.z()) / (tp2.z() - tp1.z());
			tp2.z(1);
			tp2.x(tp1.x() + (tp2.x() - tp1.x()) * p);
			tp2.y(tp1.y() + (tp2.y() - tp1.y()) * p);
		}

		//ConsoleEngine::Log("Drawing line: " + std::to_string(tp1.x()) + ", " + std::to_string(tp1.y()) + ", " + std::to_string(tp1.z()) + " to " + std::to_string(tp2.x()) + ", " + std::to_string(tp2.y()) + ", " + std::to_string(tp2.z()));

		clfe::Vector3f sp1 = screenScale(toScreen(tp1));
		clfe::Vector3f sp2 = screenScale(toScreen(tp2));

		if (sp1.x() < 0 && sp2.x() < 0)
		{
			return;
		}
		if (sp1.x() >= target->getWidth() && sp2.x() >= target->getWidth())
		{
			return;
		}
		if (sp1.y() < 0 && sp2.y() < 0)
		{
			return;
		}
		if (sp1.y() >= target->getHeight() && sp2.y() >= target->getHeight())
		{
			return;
		}

		int x1 = static_cast<int>(std::round(sp1.x()));
		int y1 = static_cast<int>(std::round(sp1.y()));
		int x2 = static_cast<int>(std::round(sp2.x()));
		int y2 = static_cast<int>(std::round(sp2.y()));
		float z1 = sp1.z();
		float z2 = sp2.z();
		
		//ConsoleEngine::Log("Zs: " + std::to_string(z1) + ", " + std::to_string(z2));
		
		int x = x1;
		int y = y1;
		float z = z1;
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
				depth_t uz = static_cast<depth_t>(z);
				if (uz >= -1 && uz <= 1)
				{
					uint32_t ux = static_cast<uint32_t>(x);
					uint32_t uy = static_cast<uint32_t>(y);

					if (target->inBounds(ux, uy))
					{
						uint32_t i = target->geti(ux, uy);
						if (uz < depthBuffer[i])
						{
							depthBuffer[i] = uz;
							target->putr(i, c);
						}
					}
				}
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
				z = (float)(x - x1) / (x2 - x1) * (z2 - z1) + z1;
			}
			if (e2 < dx)
			{
				err += dx;
				y += sy;
				z = (float)(y - y1) / (y2 - y1) * (z2 - z1) + z1;
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