#pragma once
#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Transform.h"



class Object {
public:
	Object();
	~Object();

	Object(std::vector<std::vector<vec>> p, int _r, int _g, int _b);
	Object(const Object& other);
	Object(Object&& other) noexcept;
	void operator=(const Object& other);
	void operator=(Object&& other) noexcept;

	void translate(vec translation);
	void setPosition(vec position);
	void render(sf::RenderWindow& window);


private:
	int r;
	int g;
	int b;
	matrix translation;
	matrix rotation;

	std::vector<std::vector<vec>> shapes;
};

