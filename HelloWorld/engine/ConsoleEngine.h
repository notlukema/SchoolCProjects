//#pragma once
#ifndef CONSOLE_ENGINE_H
#define CONSOLE_ENGINE_H

#include <cstdint>
#include <functional>

// The engine is quite simple so all headers are combined into one single header here

namespace Engine
{
	
	// Acts as a framebuffer too since the engine is quite simple
	class CharTexture
	{
	private:
		const uint32_t width, height, size;
		char* buffer;

		/*
		
		0,0 --------- 1, 0
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

	};

	class CharRasterizer
	{
	private:
		friend class ConsoleEngine;

		CharTexture* target;
		
		using depth_t = float;

		depth_t* depthBuffer;
		uint32_t size;

		CharRasterizer(CharTexture* target);
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

		void drawLine(int x1, int y1, int x2, int y2, char c);

	};

	class ConsoleEngine
	{
	public:
		static ConsoleEngine* engine;
		static ConsoleEngine* InitEngine(uint32_t width, uint32_t height, char clearChar);
		static ConsoleEngine* GetInstance();

	private:
		uint32_t width, height;
		// No need for extra buffers (it's literally a console based rendering engine bro)
		CharTexture* framebuffer;
		char clearChar;

		CharRasterizer* rasterizer;

		bool screenRefresh;

	public: // Bridged drawing methods
		inline CharRasterizer* r()
		{
			return rasterizer;
		}

		inline void drawLine(int x1, int y1, int x2, int y2, char c)
		{
			rasterizer->drawLine(x1, y1, x2, y2, c);
		}

	public:
		ConsoleEngine(uint32_t width, uint32_t height, char clearChar);
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

		void render();

		inline void scheduleScreenRefresh()
		{
			screenRefresh = true;
		}

		// Getters and setters

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