
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

	ConsoleEngine::InitEngine(100, 20, ' ');
	ConsoleEngine* engine = ConsoleEngine::GetInstance();

	double fpsCap = 120;

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

		rot += 5 * dt;

		engine->clear();
		engine->drawLine(-50, -50, 99, 19, 'O');
		engine->drawLine(10 + (int)rot, 0, 10, 50, '*');
		engine->render();
	}

	return 0;
}

