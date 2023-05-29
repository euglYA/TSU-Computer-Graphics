#pragma once
#include <iostream>
#include <vector>



class Object {
public:
	Object();
	~Object();

	Object(std::vector<std::vector<vec>> p, int _r, int _g, int _b);
	Object(const Object& other);
	Object(Object&& other) noexcept;
	void operator=(const Object& other);
	void operator=(Object&& other) noexcept;

	void rotate(float angle);
	void translate(vec translation);
	void scaling(float coef);

	void render(sf::RenderWindow& window);


private:
	int r;
	int g;
	int b;
	matrix translation;
	matrix rotation;
	matrix scale;
	std::vector<std::vector<vec>> shapes;
};

