
#include "engine/ConsoleEngine.h"
#include <chrono>

#include <iostream>

using namespace Engine;

int main()
{
	/*
	std::cout << "*   * ***** *     *     *****    *   *   * ***** ***** *     ****  " << std::endl;
	std::cout << "*   * *     *     *     *   *    *   *   * *   * *   * *     *   * " << std::endl;
	std::cout << "***** ***** *     *     *   *    *   *   * *   * ***** *     *    *" << std::endl;
	std::cout << "*   * *     *     *     *   *     * * * *  *   * * *   *     *   * " << std::endl;
	std::cout << "*   * ***** ***** ***** *****      *   *   ***** *   * ***** ****  " << std::endl;

    std::cout << "Hello World!\n";
	*/

	ConsoleEngine::InitEngine(51, 26, 2, ' ');
	ConsoleEngine* engine = ConsoleEngine::GetInstance();
	engine->setPrintLogsEnabled(true);

	double fpsCap = 60;

	double rot = 0;


	double timeCap = 1.0 / fpsCap;
	auto now = std::chrono::system_clock::now();
	auto point = now;
	double dt = 0;

	while (true)
	{
		// fps related stuff
		while (now - point < std::chrono::duration<double>(timeCap))
		{
			now = std::chrono::system_clock::now();
		}
		dt = std::chrono::duration<double>(now - point).count();
		point = now;

		rot += 5.0f * dt;

		ConsoleEngine::ClearLogs();

		engine->setRotation(clfe::Vector3f(0, 0, (float)rot));

		engine->clear();
		engine->beginRender();

		engine->drawPoint(clfe::Vector3f(0, 0, -50), 'X');

		engine->drawLine(-10, 10, -30, 10, 10, -30, '#');
		engine->drawLine(10, 10, -30, 10, -10, -30, '#');
		engine->drawLine(10, -10, -30, -10, -10, -30, '#');
		engine->drawLine(-10, -10, -30, -10, 10, -30, '#');

		engine->renderToScreen();
	}

	return 0;
}

