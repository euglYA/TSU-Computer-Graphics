#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <windows.h>
#include "mesh.h"

int main() {
	int width = 800, height = 800;

	sf::RenderWindow window(sf::VideoMode(width, height), "help me", sf::Style::Default);
	window.setVerticalSyncEnabled(true); 
	window.setFramerateLimit(120);

	matrix::initViewMatrix();
	matrix::initProjMatrix(width * 1.0f / height, 60);

	std::vector<std::vector<vector>> triangles;

	std::vector<vector> points{ { 3,  1,  2},
								{ 3,  1, -2},
								{ 3, -1,  2}, 
								{ 3, -1, -2}, 
								{-3,  1,  2}, 
								{-3,  1, -2}, 
								{-3, -1,  2},
								{-3, -1, -2}};

	triangles.push_back({ points[0], points[1], points[3] });
	triangles.push_back({ points[0], points[2], points[3] });
	triangles.push_back({ points[0], points[5], points[1] });
	triangles.push_back({ points[0], points[5], points[4] });
	triangles.push_back({ points[1], points[3], points[7] });
	triangles.push_back({ points[1], points[5], points[7] });
	triangles.push_back({ points[5], points[4], points[6] });
	triangles.push_back({ points[5], points[7], points[6] });
	triangles.push_back({ points[2], points[3], points[6] });
	triangles.push_back({ points[3], points[7], points[6] });
	triangles.push_back({ points[0], points[2], points[6] });
	triangles.push_back({ points[0], points[4], points[6] });

	Mesh box(triangles, 255, 0, 0);

	float dA = 0.5;

	while (1) {
		sf::Event event;
		window.pollEvent(event);

		if (event.type == sf::Event::EventType::Closed)
		{
			window.close();
			break;
		}

		window.clear(sf::Color::White);

		box.rotate(dA);

		box.draw(window, width, height);

		window.display();
	}

    return 0;
}