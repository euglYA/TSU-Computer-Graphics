#pragma once
#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Transform.h"



class Figure {
public:
	Figure();
	~Figure();

	Figure(std::vector<std::vector<vector>> p, int _r, int _g, int _b);
	Figure(const Figure& other);
	Figure(Figure&& other) noexcept;
	void operator=(const Figure& other);
	void operator=(Figure&& other) noexcept;

	void translate(vector translation);
	void rotate(float angle);
	void setPosition(vector position);
	vector getPosition() const;
	void draw(sf::RenderWindow& window);


private:
	int r;
	int g;
	int b;
	matrix transform;

	std::vector<std::vector<vector>> parts;
};

