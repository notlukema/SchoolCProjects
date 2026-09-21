#include "ConsoleEngine.h"

#include <cstdint>
#include <vector>
#include <string>

namespace Engine
{

	ConsoleEngine* ConsoleEngine::engine = nullptr;

	ConsoleEngine* ConsoleEngine::InitEngine(uint32_t width, uint32_t height, float aspect, char clearChar)
	{
		if (engine != nullptr)
		{
			return engine;
		}
		engine = new ConsoleEngine(width, height, aspect, clearChar);
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

	// Logging

	std::vector<std::string> ConsoleEngine::logs = std::vector<std::string>();

	void ConsoleEngine::Log(const std::string& message)
	{
		logs.push_back(message);
	}

	void ConsoleEngine::ClearLogs()
	{
		logs.clear();
	}



}