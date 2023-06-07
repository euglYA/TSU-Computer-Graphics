#include "Object.h"

Object::Object() {
	translation = matrix();
	rotation = matrix();
	scale = matrix();
	shapes = std::vector<std::vector<vec>>(0);
}

Object::~Object() { }

Object::Object(std::vector<std::vector<vec>> p, int r_, int g_, int b_) {
	translation = matrix();
	rotation	= matrix();
	scale		= matrix();
	shapes		= p;

	r = r_;
	g = g_;
	b = b_;
}

Object::Object(const Object& other) {
	translation = other.translation;
	rotation	= other.rotation;
	scale		= other.scale;
	shapes		= other.shapes;
}

void Object::operator=(const Object& other) {
	if (this == &other)
		return;

	translation = other.translation;
	rotation	= other.rotation;
	scale		= other.scale;
	shapes		= other.shapes;
}

Object::Object(Object&& other) noexcept {
	translation = std::move(other.translation);
	rotation	= std::move(other.rotation);
	scale		= std::move(other.scale);
	shapes		= std::move(other.shapes);
}

void Object::operator=(Object&& other) noexcept {
	if (this == &other)
		return;

	translation = other.translation;
	rotation	= other.rotation;
	scale		= other.scale;
	shapes		= other.shapes;
}

void Object::rotate(float angle) {
	matrix addition;
	float radians = angle * 3.14 / 180.0f;
	addition._matrix[0][0] = cosf(radians);
	addition._matrix[0][1] = sinf(radians);
	addition._matrix[1][0] = -sinf(radians);
	addition._matrix[1][1] = cosf(radians);

	rotation *= addition;
}

void Object::translate(vec translation) {
	matrix addition;
	addition._matrix[0][2] = translation.x;
	addition._matrix[1][2] = translation.y;

	this->translation *= addition;
}

void Object::scaling(float coef) {
	matrix addition;
	addition._matrix[0][0] = coef;
	addition._matrix[1][1] = coef;

	scale *= addition;
}

void Object::setPosition(vec position) {
	translation._matrix[0][2] = position.x;
	translation._matrix[1][2] = position.y;
}

void Object::render(sf::RenderWindow& window) {
	for (int i = 0; i < shapes.size(); i++) {
		sf::ConvexShape shape;
		shape.setPointCount(shapes[i].size());

		for (int j = 0; j < shapes[i].size(); j++) {
			vec new_point = shapes[i][j];
			new_point = scale		* new_point;
			new_point = rotation	* new_point;
			new_point = translation * new_point;

			shape.setPoint(j, sf::Vector2f(new_point.x, new_point.y));
		}

		shape.setFillColor(sf::Color(r, g, b));

		window.draw(shape);
	}
}
