#include <cmath>

#include "graphics.h"
#include "surface.h"
#include "app.h"

bool App::running_ = true;

// 6
Surface surface(-2, 2, -2, 2, [](float x, float z) { return x * z * (x + z) * (x - z); });

//Surface surface(-2 * pi, 2 * pi, -2 * pi, 2 * pi, [](float x, float z) { float a = sqrt(x * x + z * z); return cos(a) / (a + 1); });

void App::Run()
{

}

void App::Draw() {
	Graphics g;

	// surface
	surface.Draw(g);
}

void App::Update() {
	static float a = 0; // angle
	//static int32_t a = 0; // angle
	//static int32_t i = 1; // increment
	static float i = 0.5; // increment

	surface.SetAngles(10, a);

	a += i;

	if (a >= 40|| a <= 0)
	{
		i = -i;
	}

	Draw();
}

void App::Init() {
	Camera::LookAt(0, 0, -1);
	Camera::Ortho(Graphics::width / 2, Graphics::height / 2, 1);
}