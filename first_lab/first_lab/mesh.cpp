#include "mesh.h"

Mesh::Mesh() {
	transform	= matrix();
	triangles		= std::vector<std::vector<vector>>(0);
}

Mesh::~Mesh() { }

Mesh::Mesh(std::vector<std::vector<vector>> p, int r_, int g_, int b_) {
	transform	= matrix();
	triangles		= p;

	r = r_;
	g = g_;
	b = b_;
}

Mesh::Mesh(const Mesh& other) {
	transform	= other.transform;
	triangles		= other.triangles;
}

void Mesh::operator=(const Mesh& other) {
	if (this == &other)
		return;

	transform	= other.transform;
	triangles		= other.triangles;
}

Mesh::Mesh(Mesh&& other) noexcept {
	transform	= std::move(other.transform);
	triangles		= std::move(other.triangles);
}

void Mesh::operator=(Mesh&& other) noexcept {
	if (this == &other)
		return;

	transform	= other.transform;
	triangles = other.triangles;
}

void Mesh::rotate(float angle) {
	matrix addRotation;
	float radians = angle * 3.14f / 180.0f;
	addRotation._matrix[0][0] = cosf(radians);
	addRotation._matrix[0][2] = sinf(radians);
	addRotation._matrix[2][0] = -sinf(radians);
	addRotation._matrix[2][2] = cosf(radians);

	transform *= addRotation;
}

void Mesh::draw(sf::RenderWindow& window, int width, int height) {
	std::vector<std::vector<vector>> clipSpaceTriangles;
	clipSpaceTriangles.resize(triangles.size());

	for (int i = 0; i < triangles.size(); i++) {
		clipSpaceTriangles[i].resize(triangles[i].size());

		for (int j = 0; j < triangles[i].size(); j++) {
			clipSpaceTriangles[i][j] = triangles[i][j];
			clipSpaceTriangles[i][j] = transform * clipSpaceTriangles[i][j];
			clipSpaceTriangles[i][j] = matrix::viewMatrix * clipSpaceTriangles[i][j];
			float w = clipSpaceTriangles[i][j].x * matrix::projMatrix._matrix[3][0] + clipSpaceTriangles[i][j].y * matrix::projMatrix._matrix[3][1] + clipSpaceTriangles[i][j].z * matrix::projMatrix._matrix[3][2] + matrix::projMatrix._matrix[3][3];
			clipSpaceTriangles[i][j] = matrix::projMatrix * clipSpaceTriangles[i][j];

			clipSpaceTriangles[i][j].x = clipSpaceTriangles[i][j].x / w;
			clipSpaceTriangles[i][j].y = clipSpaceTriangles[i][j].y / w;
			clipSpaceTriangles[i][j].z = clipSpaceTriangles[i][j].z / w;

			clipSpaceTriangles[i][j].x = width * 1.0f / 2  + clipSpaceTriangles[i][j].x * width / 2;
			clipSpaceTriangles[i][j].y = height * 1.0f / 2 + clipSpaceTriangles[i][j].y * height / 2;
		}
	}


	for (int i = 0; i < clipSpaceTriangles.size(); i++)
	{
		sf::Vertex line1[] =
		{
			sf::Vertex(sf::Vector2f(clipSpaceTriangles[i][0].x, clipSpaceTriangles[i][0].y), sf::Color(r, g, b, 255)),
			sf::Vertex(sf::Vector2f(clipSpaceTriangles[i][1].x, clipSpaceTriangles[i][1].y), sf::Color(r, g, b, 255))
		};

		sf::Vertex line2[] =
		{
			sf::Vertex(sf::Vector2f(clipSpaceTriangles[i][1].x, clipSpaceTriangles[i][1].y), sf::Color(r, g, b, 255)),
			sf::Vertex(sf::Vector2f(clipSpaceTriangles[i][2].x, clipSpaceTriangles[i][2].y), sf::Color(r, g, b, 255))
		};

		sf::Vertex line3[] =
		{
			sf::Vertex(sf::Vector2f(clipSpaceTriangles[i][2].x, clipSpaceTriangles[i][2].y), sf::Color(r, g, b, 255)),
			sf::Vertex(sf::Vector2f(clipSpaceTriangles[i][0].x, clipSpaceTriangles[i][0].y), sf::Color(r, g, b, 255))
		};

		window.draw(line1, 2, sf::Lines);
		window.draw(line2, 2, sf::Lines);
		window.draw(line3, 2, sf::Lines);
	}
}