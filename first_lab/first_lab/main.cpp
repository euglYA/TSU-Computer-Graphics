#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <windows.h>
#include "Figure.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 800), "help me", sf::Style::Default);

	std::vector<std::vector<vector>> figureParts;
	std::vector<vector> points;

	points.push_back(vector(0, 0));
	points.push_back(vector(-40, 25));
	points.push_back(vector(40, 25));
	figureParts.push_back(points);
	points.clear();
	points.push_back(vector(40, 25));
	points.push_back(vector(-40, 25));
	points.push_back(vector(-40, 75));
	points.push_back(vector(40, 75));
	figureParts.push_back(points);
	points.clear();

	Figure box(figureParts, 0, 0, 0);
	points.clear();
	figureParts.clear();
	points.push_back(vector(2, 153));
	points.push_back(vector(-2, 153));
	points.push_back(vector(-2, 0));
	points.push_back(vector(2, 0));
	figureParts.push_back(points);

	Figure stick(figureParts, 0, 0, 0);
	
	box.setPosition(vector(375, 500));
	stick.setPosition(vector(375, 400));

	float x, y;
	float angle = 90;
	float dA = -0.005;
	float r = 150;

	while (1) {
		window.clear(sf::Color::White);

		x = cosf(angle * 3.14 / 180) * r + 375;
		y = sinf(angle * 3.14 / 180) * r + 400;

		vector offset = vector(x, y) - box.getPosition();

		std::cout << offset.x << " " << offset.y << std::endl;

		box.translate(offset);

		//box.setPosition(vector(x + 375, y + 400));
		box.rotate(-dA);
		stick.rotate(-dA);

		angle += dA;

		box.draw(window);
		stick.draw(window);
		window.display();
		//Sleep(500);
	}

    return 0;
}