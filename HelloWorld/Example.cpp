
#include "engine/ConsoleEngine.h"
#include <chrono>

#include <iostream>

using namespace Engine;

int main1()
{

	/* ConsoleEngine::InitEngine(width, height, aspect, clearChar);
	* width and height are the dimensions of the text screen on the console
	* aspect is width/height stretch ratio and exists because text is naturally taller than wide so a normal cube drawn with 1:1 aspect would look very tall due to the text being taller
	* clearChar is the initial char to clear the screen with when calling Clear() (can be changed)
	*/
	ConsoleEngine::InitEngine(101, 51, 2, ' '); // It is important to call InitEngine() before GetInstance() otherwise the engine will be initiated with default parameters

	ConsoleEngine* engine = ConsoleEngine::GetInstance(); // Grabs the ConsoleEngine instance

	// Whether or not to print logs on screen when rendering
	// Note: this is very unstable due to the nature of rendering to the console
	engine->setPrintLogsEnabled(false);


	/*
	* Coordinate system:
	* 
	*             /\
	*              |
	*             (-y)
	*              |
	*              |
	*    <-(-x)----------(+x)->
	*              |
	*              |
	*             (+y)
	*              |
	*             \/
	* 
	* 
	* Left is negative x
	* Right is positive x
	* Up is negative y
	* Down is positive y
	* Forwards is negative z
	* Backwards is positive z
	*/


	// Auxiliary code that isn't part of the engine
	double fpsCap = 60;

	float rot = 0;


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

		rot += 1.0f * dt;

		// Engine logging code
		// Note that these are static functions
		ConsoleEngine::ClearLogs();
		ConsoleEngine::Log("This is a log");
		ConsoleEngine::Log("This is a log too");

		// These are bridge methods supplied by the ConsoleEngine to control the camera
		// You can also just use engine->c() to reference the camera directly
		engine->setPosition(clfe::Vector3f(0, 0, 40));
		//engine->setPosition(clfe::Vector3f(0, 0, std::sinf(rot * 1.5) * 20 + 20));
		engine->setRotation(clfe::Vector3f(0.3f * std::cosf(rot), 0.3f * std::sinf(rot), 0));

		// Common necessary step each drawing frame
		engine->clear();

		//engine->scheduleScreenRefresh();

		// Mainly updates the camera's transformation matrices so if your camera doesn't move then this step isn't absolutely necessary
		engine->beginRender();

		// Used to set the local transformation matrix of the object
		// engine->clearObjectMatrix() can be used to clear the matrix (to an identity matrix which applies no transformation)
		engine->setObjectMatrix(clfe::mrotateY(rot) * clfe::mrotateX(rot * 2.5f) * clfe::mrotateZ(rot * 0.3f));

		// Draw a 3d point
		engine->drawPoint(-5.0f, 5, -5, 'X');

		// Note: you can also used engine->r() to reference the rasterizer directly and call draw commands there

		// Draw a 3d line
		engine->drawLine(-10, 10, -10, 10, 10, -10, '#');
		engine->drawLine(10, 10, -10, 10, -10, -10, '#');
		engine->drawLine(10, -10, -10, -10, -10, -10, '#');
		engine->drawLine(-10, -10, -10, -10, 10, -10, '#');

		engine->drawLine(-10, 10, 10, 10, 10, 10, 'O');
		engine->drawLine(10, 10, 10, 10, -10, 10, 'O');
		engine->drawLine(10, -10, 10, -10, -10, 10, 'O');
		engine->drawLine(-10, -10, 10, -10, 10, 10, 'O');

		engine->drawLine(-10, -10, 10, -10, -10, -10, '*');
		engine->drawLine(10, -10, 10, 10, -10, -10, '*');
		engine->drawLine(10, 10, 10, 10, 10, -10, '*');
		engine->drawLine(-10, 10, 10, -10, 10, -10, '*');

		// Draw a 3d triangle
		// Note: there aren't "shaders" because it's unnecessary for my needs and I'm lazy
		engine->drawTriangle(-8, -8, -8, 8, -8, 8, 8, 8, 8, '.');

		// Note: you can check the CharRasterizer.cpp and ConsoleEngine.h for other more niche drawing methods (most need to be called from the rasterizer directly)

		// "Draws" the texture to the console, somewhat similar to double buffering
		engine->renderToScreen();
	}

	return 0;
}
