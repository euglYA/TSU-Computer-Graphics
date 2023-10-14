#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <windows.h>
#include "mesh.h"

vector toClip(vector point, float width, float height)
{
	vector ans = point;

	ans = matrix::viewMatrix * ans;
	float w = ans.z * matrix::projMatrix._matrix[3][2];
	ans = matrix::projMatrix * ans;

	ans.x = ans.x / w;
	ans.y = ans.y / w;
	ans.z = ans.z / w;

	ans.x = width * 1.0f / 2 + ans.x * width / 2;
	ans.y = height * 1.0f / 2 +ans.y * height / 2;

	return ans;
}


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

	float start_angle = 0;
	float dA = 0.075;
	while (1) {
		sf::Event event;
		window.pollEvent(event);

		if (event.type == sf::Event::EventType::Closed)
		{
			window.close();
			break;
		}

		window.clear(sf::Color::White);

		if (start_angle <= 3000000) {
			box.rotate(dA);
			start_angle += dA;
		}

		box.draw(window, width, height);

		vector zero = { 0.0f, 0.0f, 0.0f };
		vector x = { 1.0f, 0.0f, 0.0f };
		vector y = { 0.0f, 1.0f, 0.0f };
		vector z = { 0.0f, 0.0f, 1.0f };
		vector minus_x = { -1.0f, 0.0f, 0.0f };
		vector minus_y = { 0.0f, -1.0f, 0.0f };
		vector minus_z = { 0.0f, 0.0f, -1.0f };

		zero = toClip(zero, width, height);
		x = toClip(x, width, height);
		y = toClip(y, width, height);
		z = toClip(z, width, height);
		minus_x = toClip(minus_x, width, height);
		minus_y = toClip(minus_y, width, height);
		minus_z = toClip(minus_z, width, height);


		sf::Vertex line1[] = {
			sf::Vertex(sf::Vector2f(zero.x, zero.y), sf::Color::Red),
			sf::Vertex(sf::Vector2f(x.x, x.y), sf::Color::Red)
		};

		sf::Vertex line2[] = {
			sf::Vertex(sf::Vector2f(zero.x, zero.y), sf::Color::Green),
			sf::Vertex(sf::Vector2f(y.x, y.y), sf::Color::Green)
		};

		sf::Vertex line3[] = {
			sf::Vertex(sf::Vector2f(zero.x, zero.y), sf::Color::Blue),
			sf::Vertex(sf::Vector2f(z.x, z.y), sf::Color::Blue)
		};
		sf::Vertex minus_line1[] = {
			sf::Vertex(sf::Vector2f(zero.x, zero.y), sf::Color::Black),
			sf::Vertex(sf::Vector2f(minus_x.x, minus_x.y), sf::Color::Black)
		};

		sf::Vertex minus_line2[] = {
			sf::Vertex(sf::Vector2f(zero.x, zero.y), sf::Color::Black),
			sf::Vertex(sf::Vector2f(minus_y.x, minus_y.y), sf::Color::Black)
		};

		sf::Vertex minus_line3[] = {
			sf::Vertex(sf::Vector2f(zero.x, zero.y), sf::Color::Black),
			sf::Vertex(sf::Vector2f(minus_z.x, minus_z.y), sf::Color::Black)
		};


		window.draw(line1, 2, sf::Lines);
		window.draw(line2, 2, sf::Lines);
		window.draw(line3, 2, sf::Lines);
		//window.draw(minus_line1, 2, sf::Lines);
		//window.draw(minus_line2, 2, sf::Lines);
		window.draw(minus_line3, 2, sf::Lines);

		window.display();
	}

    return 0;
}