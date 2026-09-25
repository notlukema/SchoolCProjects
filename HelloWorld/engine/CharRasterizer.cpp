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

	void CharRasterizer::drawTriangle(const clfe::Vector3f& p1, const clfe::Vector3f& p2, const clfe::Vector3f& p3, char c)
	{
		clfe::Vector4f tp1 = transformPoint(p1);
		clfe::Vector4f tp2 = transformPoint(p2);
		clfe::Vector4f tp3 = transformPoint(p3);
		if (tp1.z() < tp2.z())
		{
			if (tp2.z() < tp3.z())
			{
				drawTri(tp3, tp2, tp1, c);
				return;
			}
			if (tp1.z() < tp3.z())
			{
				drawTri(tp2, tp3, tp1, c);
				return;
			}
			drawTri(tp2, tp1, tp3, c);
			return;
		}
		// tp2.z() < tp1.z()
		if (tp1.z() < tp3.z())
		{
			drawTri(tp3, tp1, tp2, c);
			return;
		}
		if (tp2.z() < tp3.z())
		{
			drawTri(tp1, tp3, tp2, c);
			return;
		}
		drawTri(tp1, tp2, tp3, c);
	}

	clfe::Vector4f CharRasterizer::clipLineZ(const clfe::Vector4f& point, const clfe::Vector4f& clip, float z)
	{
		float p = (z - point.z()) / (clip.z() - point.z());
		return clfe::Vector4f(point.x() + p * (clip.x() - point.x()), point.y() + p * (clip.y() - point.y()), z, clip.w());
	}

	// Points go in z order from highest to lowest (smallest negative to biggest negative)
	void CharRasterizer::drawTri(clfe::Vector4f p1, clfe::Vector4f p2, clfe::Vector4f p3, char c)
	{
		float near = -camera->getNear();
		float far = -camera->getFar();
		if (p3.z() > near)
		{
			return;
		}
		if (p1.z() < far)
		{
			return;
		}
		if (p2.z() > near)
		{
			p1 = clipLineZ(p3, p1, near);
			p2 = clipLineZ(p3, p2, near);
		}
		else if (p1.z() > near)
		{
			clfe::Vector4f p12 = clipLineZ(p2, p1, near);
			clfe::Vector4f p13 = clipLineZ(p3, p1, near);
			drawTri(p12, p13, p2, c);
			drawTri(p13, p2, p3, c);
			return;
		}
		if (p2.z() < far)
		{
			p2 = clipLineZ(p1, p2, far);
			p3 = clipLineZ(p1, p3, far);
		}
		else if (p3.z() < far)
		{
			clfe::Vector4f p31 = clipLineZ(p1, p3, far);
			clfe::Vector4f p32 = clipLineZ(p2, p3, far);
			drawTri(p1, p31, p32, c);
			drawTri(p1, p2, p32, c);
			return;
		}

		clfe::Vector3f sp1 = screenScale(toScreen(p1));
		clfe::Vector3f sp2 = screenScale(toScreen(p2));
		clfe::Vector3f sp3 = screenScale(toScreen(p3));

		// Sort from top to bottom for easy rendering
		if (sp1.y() < sp2.y())
		{
			if (sp2.y() < sp3.y())
			{
				drawTriR(sp3, sp2, sp1, c);
				return;
			}
			if (sp1.y() < sp3.y())
			{
				drawTriR(sp2, sp3, sp1, c);
				return;
			}
			drawTriR(sp2, sp1, sp3, c);
			return;
		}
		// sp2.y() < sp1.y()
		if (sp1.y() < sp3.y())
		{
			drawTriR(sp3, sp1, sp2, c);
			return;
		}
		if (sp2.y() < sp3.y())
		{
			drawTriR(sp1, sp3, sp2, c);
			return;
		}
		drawTriR(sp1, sp2, sp3, c);
	}

	// Points go in y order from highest to lowest
	void CharRasterizer::drawTriR(const clfe::Vector3f& p1, const clfe::Vector3f& p2, const clfe::Vector3f& p3, char c)
	{
		int width = static_cast<int>(target->getWidth());
		int height = static_cast<int>(target->getHeight());

		int x1 = static_cast<int>(std::round(p1.x()));
		int y1 = static_cast<int>(std::round(p1.y()));
		int x2 = static_cast<int>(std::round(p2.x()));
		int y2 = static_cast<int>(std::round(p2.y()));
		int x3 = static_cast<int>(std::round(p3.x()));
		int y3 = static_cast<int>(std::round(p3.y()));

		if (x1 < 0 && x2 < 0 && x3 < 0)
		{
			return;
		}
		if (x1 >= width && x2 >= width && x3 >= width)
		{
			return;
		}
		if (y1 < 0 && y2 < 0 && y3 < 0)
		{
			return;
		}
		if (y1 >= height && y2 >= height && y3 >= height)
		{
			return;
		}

		int y = y1;
		if (y >= height)
		{
			y = height - 1;
		}
		int cy = y3;
		if (cy < 0)
		{
			cy = 0;
		}
		while (y >= cy)
		{
			float pc1 = (float)(y - y3) / (y1 - y3);
			float lx1 = x3 + pc1 * (x1 - x3);
			float lz1 = p3.z() + pc1 * (p1.z() - p3.z());
			float pc2;
			float lx2;
			float lz2;
			if (y > y2)
			{
				pc2 = (float)(y - y2) / (y1 - y2);
				lx2 = x2 + pc2 * (x1 - x2);
				lz2 = p2.z() + pc2 * (p1.z() - p2.z());
			}
			else
			{
				pc2 = (float)(y - y3) / (y2 - y3);
				lx2 = x3 + pc2 * (x2 - x3);
				lz2 = p3.z() + pc2 * (p2.z() - p3.z());
			}
			int x = lx1 < lx2 ? static_cast<int>(std::round(lx1)) : static_cast<int>(std::round(lx2));
			int cx = lx1 < lx2 ? static_cast<int>(std::round(lx2)) : static_cast<int>(std::round(lx1));
			
			if (x >= width || cx < 0)
			{
				y--;
				continue;
			}

			if (x < 0)
			{
				x = 0;
			}
			if (cx >= width)
			{
				cx = width - 1;
			}

			uint32_t i = target->geti(x, y);

			while (x <= cx)
			{
				float pc3 = (x - lx1) / (lx2 - lx1);
				float z = lz1 + pc3 * (lz2 - lz1);
				if (z < depthBuffer[i])
				{
					depthBuffer[i] = z;
					target->putr(i, c);
				}
				i++;
				x++;
			}

			y--;
		}
	}

}