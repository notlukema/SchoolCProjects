#include "ConsoleEngine.h"

#include <cstdint>

namespace Engine
{

	ConsoleEngine* ConsoleEngine::engine = nullptr;

	ConsoleEngine* ConsoleEngine::InitEngine(uint32_t width = 100, uint32_t height = 20, char clearChar = ' ')
	{
		if (engine != nullptr)
		{
			return engine;
		}
		engine = new ConsoleEngine(width, height, clearChar);
		return engine;

	}

	ConsoleEngine* ConsoleEngine::GetInstance()
	{
		if (engine == nullptr)
		{
			InitEngine();
		}
		return engine;
	}

}