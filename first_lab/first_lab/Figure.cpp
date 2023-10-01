#include "Figure.h"

Figure::Figure() {
	transform	= matrix();
	parts		= std::vector<std::vector<vector>>(0);
}

Figure::~Figure() { }

Figure::Figure(std::vector<std::vector<vector>> p, int r_, int g_, int b_) {
	transform	= matrix();
	parts		= p;

	r = r_;
	g = g_;
	b = b_;
}

Figure::Figure(const Figure& other) {
	transform	= other.transform;
	parts		= other.parts;
}

void Figure::operator=(const Figure& other) {
	if (this == &other)
		return;

	transform	= other.transform;
	parts		= other.parts;
}

Figure::Figure(Figure&& other) noexcept {
	transform	= std::move(other.transform);
	parts		= std::move(other.parts);
}

void Figure::operator=(Figure&& other) noexcept {
	if (this == &other)
		return;

	transform	= other.transform;
	parts		= other.parts;
}

void Figure::translate(vector translation) {
	matrix addTranslation;
	transform._matrix[0][2] += translation.x;
	transform._matrix[1][2] += translation.y;
}

void Figure::rotate(float angle) {
	matrix addRotation;
	float radians = angle * 3.14f / 180.0f;
	addRotation._matrix[0][0] = cosf(radians);
	addRotation._matrix[0][1] = sinf(radians);
	addRotation._matrix[1][0] = -sinf(radians);
	addRotation._matrix[1][1] = cosf(radians);

	transform *= addRotation;
}

void Figure::setPosition(vector position) {
	transform._matrix[0][2] = position.x;
	transform._matrix[1][2] = position.y;
}

vector Figure::getPosition() const
{
	return vector(transform._matrix[0][2], transform._matrix[1][2]);
}

void Figure::draw(sf::RenderWindow& window) {
	for (int i = 0; i < parts.size(); i++) {
		sf::ConvexShape shape;
		shape.setPointCount(parts[i].size());

		for (int j = 0; j < parts[i].size(); j++) {
			vector gPoint = parts[i][j];
			gPoint = transform * gPoint;

			shape.setPoint(j, sf::Vector2f(gPoint.x, gPoint.y));
		}

		shape.setFillColor(sf::Color(r, g, b));

		window.draw(shape);
	}
}