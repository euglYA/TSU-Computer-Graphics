#include <iostream>
#include "Scene.h"

int main()
{

	Scene my_scene;

	std::vector<std::vector<vec>> shapes;
	std::vector<vec> points;
	points.push_back(vec(-5, 0, 1));
	points.push_back(vec(-5, 200, 1));
	points.push_back(vec(5, 200, 1));
	points.push_back(vec(5, 0, 1));
	shapes.push_back(points);
	points.clear();
	points.push_back(vec(0, 175, 1));
	points.push_back(vec(-25, 200, 1));
	points.push_back(vec(0, 225, 1));
	points.push_back(vec(25, 200, 1));
	shapes.push_back(points);

	Object* obj = new Object(shapes, 150, 75, 0);
	my_scene.addObject(obj);

	obj->translate(vec(400, 200, 1));

	float start_angle = 55.0f;
	float start_delta = 0.05;
	float damping = 5.0f;
	float max_angle = start_angle;
	float angle = -start_angle;
	float delta = start_delta;
	int dir = 1;
	obj->rotate(angle);

	while (my_scene.isOpen())
	{
		bool isHit = false;
		my_scene.pollEvents(isHit);

		if (isHit)
		{
			delta = start_delta;
			max_angle = start_angle;
			obj->rotate(-angle);
			angle = -start_angle;
			obj->rotate(angle);
			dir = 1;
		}

		if (max_angle >= 0)
		{
			obj->rotate(delta * dir);
			angle += delta * dir;
			if ((angle >= max_angle && dir > 0) || (angle <= -max_angle && dir < 0))
			{
				dir *= -1;
				max_angle -= damping;
				if (max_angle > 0)
					delta = start_delta * (max_angle / start_angle);
			}
		}

		my_scene.render();
	}

    /*sf::RenderWindow window(sf::VideoMode(400, 400), L"Новый проект", sf::Style::Default);

    window.setVerticalSyncEnabled(true);

	sf::CircleShape shape(100.f, 3);
    shape.setPosition(100, 100);
    shape.setFillColor(sf::Color::Magenta);

    while (window.isOpen())
    {
		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Blue);
        window.draw(shape);
        window.display();
    }*/

    return 0;
}