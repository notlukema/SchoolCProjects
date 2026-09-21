//#pragma once
#ifndef CONSOLE_ENGINE_H
#define CONSOLE_ENGINE_H

#include <cstdint>
#include <functional>
#include <vector>
#include <string>

// Simple vector and matrix math library I wrote for another project
#include "../clm/Vector.h"
#include "../clm/Matrix.h"

// The engine is quite simple so all  headers are combined into one single header here

namespace Engine
{
	
	// Acts as a framebuffer too since the engine is quite simple
	class CharTexture
	{
	private:
		const uint32_t width, height, size;
		char* buffer;

		/*
		
		0, 0 -------- 1, 0
		|                |
		|                |
		|                |
		|                |
		0, 1 -------- 1, 1
		
		*/

	public:
		CharTexture(const uint32_t width, const uint32_t height);
		~CharTexture();

		inline uint32_t getWidth() const
		{
			return width;
		}

		inline uint32_t getHeight() const
		{
			return height;
		}

		inline uint32_t geti(const uint32_t x, const uint32_t y) const
		{
			return y * width + x;
		}

		inline bool inBounds(const uint32_t x, const uint32_t y) const
		{
			return x < width && y < height;
		}

		inline bool inBounds(int x, int y) const
		{
			return x >= 0 && y >= 0 && x < static_cast<int>(width) && y < static_cast<int>(height);
		}

		void clear(char c);
		char get(const uint32_t x, const uint32_t y) const;
		void put(const uint32_t x, const uint32_t y, char c);

		inline char getr(const uint32_t x, const uint32_t y) const
		{
			return buffer[geti(x, y)];
		}

		inline void putr(const uint32_t x, const uint32_t y, char c)
		{
			buffer[geti(x, y)] = c;
		}

		inline void putr(const uint32_t i, char c)
		{
			buffer[i] = c;
		}

	};

	class CharCamera
	{
	private:
		friend class ConsoleEngine;
		clfe::Vector3f position;
		clfe::Vector3f rotation; // Euler angles

		float fov;
		float near, far;

		CharCamera(const clfe::Vector3f& position = clfe::Vector3f(0.0f, 0.0f, 0.0f), const clfe::Vector3f& rotation = clfe::Vector3f(0.0f, 0.0f, 0.0f), float fov = 90.0f);

	public:
		inline float getFOV() const
		{
			return fov;
		}

		inline void setFOV(float fov)
		{
			this->fov = fov;
		}

		inline float getNear() const
		{
			return near;
		}

		inline void setNear(float near)
		{
			this->near = near;
		}

		inline float getFar() const
		{
			return far;
		}

		inline void setFar(float far)
		{
			this->far = far;
		}

		//

		clfe::Matrix4x4f getCameraMatrix(float width, float height) const;
		clfe::Matrix4x4f getFrustumMatrix(float width, float height) const;
		clfe::Matrix4x4f getViewMatrix() const;

		inline clfe::Vector3f getPosition() const
		{
			return position;
		}

		inline void setPosition(const clfe::Vector3f& position)
		{
			this->position = position;
		}

		inline void move(const clfe::Vector3f& delta)
		{
			position += delta;
		}

		inline clfe::Vector3f getRotation() const
		{
			return rotation;
		}

		inline void setRotation(const clfe::Vector3f& rotation)
		{
			this->rotation = rotation;
		}

		inline void rotate(const clfe::Vector3f& delta)
		{
			rotation += delta;
		}

	};

	class CharRasterizer
	{
	private:
		friend class ConsoleEngine;

		CharTexture* target;
		CharCamera* camera;
		clfe::Matrix4x4f cameraMatrix;
		float aspect;
		
		using depth_t = float;

		depth_t* depthBuffer;
		uint32_t size;

		CharRasterizer(CharTexture* target, CharCamera* camera, float aspect);
		~CharRasterizer();

	public:
		inline CharTexture* getTarget() const
		{
			return target;
		}

		inline void changeTarget(CharTexture* newTarget)
		{
			target = newTarget;
		}

		inline void catchCamera()
		{
			cameraMatrix = camera->getCameraMatrix(static_cast<float>(target->getWidth()), static_cast<float>(target->getHeight()) * aspect);
		}

		inline float getAspect() const
		{
			return aspect;
		}

		inline void setAspect(float aspect)
		{
			this->aspect = aspect;
		}

		inline clfe::Vector3f screenScale(const clfe::Vector3f& point) const
		{
			return clfe::Vector3f((point.x() + 1.0f) * (target->getWidth() - 1) * 0.5f, (point.y() + 1.0f) * (target->getHeight() - 1) * 0.5f, point.z());
		}

		inline void screenScaleR(clfe::Vector3f& point) const
		{
			point.x((point.x() + 1.0f) * (target->getWidth() - 1) * 0.5f);
			point.y((point.y() + 1.0f) * (target->getHeight() - 1) * 0.5f);
		}

		inline clfe::Vector3i screenScaleInt(const clfe::Vector3f& point) const
		{
			return clfe::Vector3i(std::round((point.x() + 1.0f) * (target->getWidth() - 1) * 0.5f), std::round((point.y() + 1.0f) * (target->getHeight() - 1) * 0.5f), std::round(point.z()));
		}

		// Rendering

		inline void clearColor(char c)
		{
			target->clear(c);
		}

		void clearDepth();

		inline void clear(char c)
		{
			clearColor(c);
			clearDepth();
		}

		inline void drawPoint(uint32_t x, uint32_t y, char c)
		{
			target->put(x, y, c);
		}

		void drawPoint(uint32_t x, uint32_t y, depth_t z, char c);
		void drawPointR(const clfe::Vector3f& point, char c);

		void drawLine(int x1, int y1, int x2, int y2, char c);

		inline void drawLine(const clfe::Vector2i& p1, const clfe::Vector2i& p2, char c)
		{
			drawLine(p1.x(), p1.y(), p2.x(), p2.y(), c);
		}

		// 3d (too lazy to do textures plus they probably don't look good anyways)

		clfe::Vector3f transformPoint(const clfe::Vector3f& point) const;

		void drawPoint(const clfe::Vector3f& point, char c);

		inline void drawPoint(float x, float y, float z, char c)
		{
			drawPoint(clfe::Vector3f(x, y, z), c);
		}

		void drawLine(const clfe::Vector3f& p1, const clfe::Vector3f& p2, char c);

		inline void drawLine(float x1, float y1, float z1, float x2, float y2, float z2, char c)
		{
			drawLine(clfe::Vector3f(x1, y1, z1), clfe::Vector3f(x2, y2, z2), c);
		}

	};

	class ConsoleEngine
	{
	public:
		static ConsoleEngine* engine;
		static ConsoleEngine* InitEngine(uint32_t width = 101, uint32_t height = 51, float aspect = 2.0f, char clearChar = ' ');
		static ConsoleEngine* GetInstance();

		static std::vector<std::string> logs;
		static void Log(const std::string& message);
		static void ClearLogs();

	private:
		uint32_t width, height;
		// No need for extra buffers (it's literally a console based rendering engine bro)
		CharTexture* framebuffer;
		char clearChar;

		CharCamera* camera;
		CharRasterizer* rasterizer;

		bool screenRefresh;

		bool printLogs;

	public: // Bridged camera methods
		inline CharCamera* c()
		{
			return camera;
		}

		inline float getFOV() const
		{
			return camera->getFOV();
		}

		inline void setFOV(float fov)
		{
			camera->setFOV(fov);
		}

		inline clfe::Vector3f getPosition() const
		{
			return camera->getPosition();
		}

		inline void setPosition(const clfe::Vector3f& position)
		{
			camera->setPosition(position);
		}

		inline void move(const clfe::Vector3f& delta)
		{
			camera->move(delta);
		}

		inline clfe::Vector3f getRotation() const
		{
			return camera->getRotation();
		}

		inline void setRotation(const clfe::Vector3f& rotation)
		{
			camera->setRotation(rotation);
		}

		inline void rotate(const clfe::Vector3f& delta)
		{
			camera->rotate(delta);
		}

	public: // Bridged drawing methods
		inline CharRasterizer* r()
		{
			return rasterizer;
		}

		inline void drawPoint(uint32_t x, uint32_t y, char c)
		{
			rasterizer->drawPoint(x, y, c);
		}

		inline void drawPoint(uint32_t x, uint32_t y, float z, char c)
		{
			rasterizer->drawPoint(x, y, z, c);
		}

		inline void drawPointR(const clfe::Vector3f& point, char c)
		{
			rasterizer->drawPointR(point, c);
		}

		inline void drawLine(int x1, int y1, int x2, int y2, char c)
		{
			rasterizer->drawLine(x1, y1, x2, y2, c);
		}

		inline void drawLine(const clfe::Vector2i& p1, const clfe::Vector2i& p2, char c)
		{
			rasterizer->drawLine(p1, p2, c);
		}

		// 3d

		inline void drawPoint(const clfe::Vector3f& point, char c)
		{
			rasterizer->drawPoint(point, c);
		}

		inline void drawPoint(float x, float y, float z, char c)
		{
			rasterizer->drawPoint(x, y, z, c);
		}

		inline void drawLine(const clfe::Vector3f& p1, const clfe::Vector3f& p2, char c)
		{
			rasterizer->drawLine(p1, p2, c);
		}

		inline void drawLine(float x1, float y1, float z1, float x2, float y2, float z2, char c)
		{
			rasterizer->drawLine(x1, y1, z1, x2, y2, z2, c);
		}

	public:
		ConsoleEngine(uint32_t width, uint32_t height, float aspect, char clearChar);
		~ConsoleEngine();

		inline uint32_t getWidth() const
		{
			return width;
		}

		inline uint32_t getHeight() const
		{
			return height;
		}

		void resize(uint32_t width, uint32_t height);

		inline void clear()
		{
			rasterizer->clear(clearChar);
		}

		inline void clearColor()
		{
			rasterizer->clearColor(clearChar);
		}

		inline void clearDepth()
		{
			rasterizer->clearDepth();
		}

		void beginRender();
		void renderToScreen();

		inline void scheduleScreenRefresh()
		{
			screenRefresh = true;
		}

		// Getters and setters

		inline bool printLogsEnabled() const
		{
			return printLogs;
		}

		inline void setPrintLogsEnabled(bool enabled)
		{
			printLogs = enabled;
			screenRefresh = true;
		}

		inline CharTexture* getFramebuffer() const
		{
			return framebuffer;
		}

		inline CharRasterizer* getRasterizer() const
		{
			return rasterizer;
		}

		inline char getClearChar() const
		{
			return clearChar;
		}

		inline void setClearChar(char clearChar)
		{
			this->clearChar = clearChar;
		}

	};

	//

	inline ConsoleEngine* GetConsoleEngine()
	{
		return ConsoleEngine::GetInstance();
	}

}

#endif