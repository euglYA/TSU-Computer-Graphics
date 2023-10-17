#include <cmath>

#include "graphics.h"
#include "surface.h"
#include "app.h"

bool App::running_ = true;

Surface surface(-2, 2, -2, 2, []
	(float x, float z) { 
		return x * z * (x + z) * (x - z); 
	});

void App::Run() { }

void App::Draw() {
	Graphics g;
	surface.draw(g);
}

void App::Update() {
	static float a = 0;
	static float i = 0.5;

	surface.SetAngles(10, a);

	a += i;

	if (a >= 40|| a <= 0)
		i = -i;

	Draw();
}

void App::Init() {
	Camera::LookAt(0, 0, -1);
	Camera::Ortho(Graphics::width / 2, Graphics::height / 2, 1);
}