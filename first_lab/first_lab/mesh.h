#pragma once
#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Transform.h"



class Mesh {
public:
	Mesh();
	~Mesh();

	Mesh(std::vector<std::vector<vector>> p, int _r, int _g, int _b);
	Mesh(const Mesh& other);
	Mesh(Mesh&& other) noexcept;
	void operator=(const Mesh& other);
	void operator=(Mesh&& other) noexcept;

	void rotate(float angle);
	void draw(sf::RenderWindow& window, int width, int height);
	void getW(std::vector<std::vector<vector>> triangles);
	void getW_sec(std::vector<std::vector<vector>> triangles);

private:
	int r; int g; int b;
	matrix transform;
	std::vector<std::vector<vector>> triangles;
	float** W;
	vector weightCenter;
	vector viewPoint;
};