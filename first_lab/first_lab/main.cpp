#include <iostream>
#include "Scene.h"

int main()
{

	Scene my_scene;

	std::vector<std::vector<vec>> shapes;
	std::vector<vec> points;
	points.push_back(vec(0, 0, 1));
	points.push_back(vec(-40, 25, 1));
	points.push_back(vec(40, 25, 1));
	shapes.push_back(points);
	points.clear();
	points.push_back(vec(40, 25, 1));
	points.push_back(vec(-40, 25, 1));
	points.push_back(vec(-40, 75, 1));
	points.push_back(vec(40, 75, 1));
	shapes.push_back(points);

	Object* obj = new Object(shapes, 0, 0, 0);
	my_scene.addObject(obj);

	float x, y;
	float angle = 90;
	float dA = -0.005;
	float r = 150;

	while (my_scene.isOpen()) {

		x = cosf(angle * 3.14 / 180) * r;
		y = sinf(angle * 3.14 / 180) * r;

		obj->setPosition(vec(x + 375, y + 400, 1));

		my_scene.render();

		angle += dA;

	}

    return 0;
}