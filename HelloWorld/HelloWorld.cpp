// v1.0

#include "engine/ConsoleEngine.h"
#include <chrono>
#include <cstdint>

#include <iostream>

using namespace Engine;

struct Letter
{

	uint16_t lines;
	float x, y;
	float* dx;
	float* dy;

	Letter(uint16_t lines, float x, float y, float* dx, float* dy) : lines(lines), x(x), y(y), dx(dx), dy(dy)
	{}

	~Letter()
	{
		free(dx);
		free(dy);
	}

	void draw(ConsoleEngine* engine, float scalex, float scaley, char c)
	{
		for (uint16_t i = 0; i < lines; i++)
		{
			uint16_t i1 = i * 2;
			uint16_t i2 = i1 + 1;
			engine->drawLine((x + dx[i1]) * scalex, (y - dy[i1]) * scaley, 0, (x + dx[i2]) * scalex, (y - dy[i2]) * scaley, 0, c);
		}
	}

	void applyTransformation(float fx, float fy)
	{
		x *= fx;
		y *= fy;
		for (uint16_t i = 0; i < lines; i++)
		{
			uint16_t i1 = i * 2;
			uint16_t i2 = i1 + 1;
			dx[i1] *= fx;
			dy[i1] *= fy;
			dx[i2] *= fx;
			dy[i2] *= fy;
		}
	}

};

uint8_t rollType(uint8_t old)
{
	uint8_t r;
	do
	{
		r = std::rand() % 3;
	} while (r == old);

	return r;
}

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

	uint16_t letterCount = 10;
	Letter** letters = new Letter*[]{
		new Letter(3, -31.0f, 0, new float[] {-2, -2, -2, 2, 2, 2}, new float[] {2, -2, 0, 0, 2, -2}),
		new Letter(4, -25.0f, 0, new float[] {-2, 2, -2, 2, -2, 2, -2, -2}, new float[] {2, 2, 0, 0, -2, -2, 2, -2}),
		new Letter(2, -19.0f, 0, new float[] {-2, -2, -2, 2}, new float[] {2, -2, -2, -2}),
		new Letter(2, -13.0f, 0, new float[] {-2, -2, -2, 2}, new float[] {2, -2, -2, -2}),
		new Letter(4, -7.0f, 0, new float[] {-2, 2, -2, 2, -2, -2, 2, 2}, new float[] {2, 2, -2, -2, 2, -2, 2, -2}),
		new Letter(7, 4.0f, 0, new float[] {-4, -4, 0, 0, 4, 4, -4, -2, -2, 0, 0, 2, 2, 4}, new float[] {2, 0, 2, 0, 2, 0, 0, -2, -2, 0, 0, -2, -2, 0}),
		new Letter(4, 12.0f, 0, new float[] {-2, 2, -2, 2, -2, -2, 2, 2}, new float[] {2, 2, -2, -2, 2, -2, 2, -2}),
		new Letter(5, 18.0f, 0, new float[] {-2, 2, -2, 2, -2, -2, 2, 2, -2, 2}, new float[] {2, 2, 0, 0, 2, -2, 2, 0, 0, -2}),
		new Letter(2, 24.0f, 0, new float[] {-2, -2, -2, 2}, new float[] {2, -2, -2, -2}),
		new Letter(5, 30.0f, 0, new float[] {-2, -2, -2, 1, -2, 1, 1, 3, 1, 3}, new float[] {2, -2, 2, 2, -2, -2, 2, 0, -2, 0}),
	};

	uint32_t helloWorldWidth = 67;
	uint32_t helloWorldHeight = 5;

	ConsoleEngine::InitEngine(helloWorldWidth + 16, helloWorldHeight + 8, 2, ' ');
	ConsoleEngine* engine = ConsoleEngine::GetInstance();

	float jump = 0.0f;
	float jumpCD = 1.0f;
	float jcd = 3.0f;
	float* rotations = new float[letterCount];
	for (uint16_t i = 0; i < letterCount; i++)
	{
		rotations[i] = (std::rand() % 2 - 0.5f) * 2.0f;
	}
	uint8_t type = rollType(2);


	double fpsCap = 60;

	double timeCap = 1.0 / fpsCap;
	auto now = std::chrono::system_clock::now();
	auto point = now;
	float dt = 0;

	while (true)
	{
		// fps related stuff (auxiliary non-engine related code)
		while (now - point < std::chrono::duration<double>(timeCap))
		{
			now = std::chrono::system_clock::now();
		}
		dt = std::chrono::duration<float>(now - point).count();
		point = now;

		if (jcd > 0)
		{
			jcd -= dt;
		}
		else
		{
			jump += dt * 60.0f;
			if (jump >= 180)
			{
				// Permanently apply transformations
				float fx = (type == 2 ? 1.0f : -1.0f);
				float fy = (type == 1 ? 1.0f : -1.0f);
				for (uint16_t i = 0; i < letterCount; i++)
				{
					letters[i]->applyTransformation(fx, fy);
				}
				// Reset
				jump = 0.0f;
				jcd = jumpCD;
				type = rollType(type);
				for (uint16_t i = 0; i < letterCount; i++)
				{
					rotations[i] = (std::rand() % 2 - 0.5f) * 2.0f;
				}
			}
		}

		engine->setPosition(clfe::Vector3f(0, 0, 65));

		engine->clear();
		engine->beginRender();

		for (uint16_t i = 0; i < letterCount; i++)
		{
			float r = jump / 180.0f * 3.141592f;
			if (type == 0)
			{
				engine->setObjectMatrix(clfe::mrotateZ(r * rotations[i]));
			}
			else if (type == 1)
			{
				engine->setObjectMatrix(clfe::mrotateY(r * rotations[i]));
			}
			else
			{
				engine->setObjectMatrix(clfe::mrotateX(r * rotations[i]));
			}
			letters[i]->draw(engine, 5, 10, '*');
		}

		engine->renderToScreen();
	}

	return 0;
}
