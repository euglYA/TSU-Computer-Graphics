#include "Transform.h"

vector::vector(float _x, float _y)
	: x(_x), y(_y)
{}

vector::vector(const vector& other) {
	x = other.x;
	y = other.y;
}

vector::vector(vector&& other) noexcept {
	x = other.x;
	y = other.y;
}

void vector::operator=(const vector& other) {
	if (this == &other)
		return;

	x = other.x;
	y = other.y;
}

void vector::operator=(vector&& other) noexcept {
	if (this == &other)
		return;

	x = other.x;
	y = other.y;
}

void vector::normalize() {
	float inv_len = 1.0f / this->length();
	(*this) *= inv_len;
}

float vector::length() const {
	return sqrtf(x * x + y * y);
}

vector vector::operator+(const vector& other) {
	vector vec(*this);
	vec += other;

	return vec;
}

vector vector::operator-(const vector& other) {
	vector vec(*this);
	vec -= other;

	return vec;
}

vector vector::operator*(float coef) {
	vector vec(*this);
	vec *= coef;

	return vec;
}

void vector::operator+=(const vector& other) {
	x += other.x;
	y += other.y;
}

void vector::operator-=(const vector& other) {
	x -= other.x;
	y -= other.y;
}

void vector::operator*=(float coef) {
	x *= coef;
	y *= coef;
}

////////////////////////////////////////////////////////////////////

matrix::matrix() {
	_matrix = new float* [3];
	_matrix[0] = new float[3];
	_matrix[1] = new float[3];
	_matrix[2] = new float[3];

	_matrix[0][0] = 1; _matrix[0][1] = 0; _matrix[0][2] = 0;
	_matrix[1][0] = 0; _matrix[1][1] = 1; _matrix[1][2] = 0;
	_matrix[2][0] = 0; _matrix[2][1] = 0; _matrix[2][2] = 1;
}

matrix::~matrix() {
	delete[] _matrix[0];
	delete[] _matrix[1];
	delete[] _matrix[2];
	delete[] _matrix;
}

matrix::matrix(const matrix& other) {
	_matrix = new float* [3];
	_matrix[0] = new float[3];
	_matrix[1] = new float[3];
	_matrix[2] = new float[3];

	_matrix[0][0] = other._matrix[0][0]; _matrix[0][1] = other._matrix[0][1]; _matrix[0][2] = other._matrix[0][2];
	_matrix[1][0] = other._matrix[1][0]; _matrix[1][1] = other._matrix[1][1]; _matrix[1][2] = other._matrix[1][2];
	_matrix[2][0] = other._matrix[2][0]; _matrix[2][1] = other._matrix[2][1]; _matrix[2][2] = other._matrix[2][2];
}

matrix::matrix(matrix&& other) noexcept {
	_matrix = other._matrix;
	other._matrix = nullptr;
}

void matrix::operator=(const matrix& other) {
	if (this == &other)
		return;

	_matrix[0][0] = other._matrix[0][0]; _matrix[0][1] = other._matrix[0][1]; _matrix[0][2] = other._matrix[0][2];
	_matrix[1][0] = other._matrix[1][0]; _matrix[1][1] = other._matrix[1][1]; _matrix[1][2] = other._matrix[1][2];
	_matrix[2][0] = other._matrix[2][0]; _matrix[2][1] = other._matrix[2][1]; _matrix[2][2] = other._matrix[2][2];
}

void matrix::operator=(matrix&& other) noexcept {
	float** temp = _matrix;
	_matrix = other._matrix;
	other._matrix = temp;
}

void matrix::transpose() {
	matrix temp(*this);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			_matrix[i][j] = temp._matrix[j][i];
}

matrix matrix::operator+(const matrix& other) {
	matrix new_mat(*this);
	new_mat += other;

	return new_mat;
}

matrix matrix::operator-(const matrix& other) {
	matrix new_mat(*this);
	new_mat -= other;

	return new_mat;
}

matrix matrix::operator*(const matrix& other) {
	matrix new_mat(*this);
	new_mat += other;

	return new_mat;
}

vector matrix::operator*(const vector& other) {
	vector ans;

	ans.x = _matrix[0][0] * other.x + _matrix[0][1] * other.y + _matrix[0][2];
	ans.y = _matrix[1][0] * other.x + _matrix[1][1] * other.y + _matrix[1][2];

	return ans;
}

matrix matrix::operator*(float coef) {
	matrix new_mat(*this);
	new_mat *= coef;

	return new_mat;
}

void matrix::operator+=(const matrix& other) {
	_matrix[0][0] += other._matrix[0][0]; _matrix[0][1] += other._matrix[0][1]; _matrix[0][2] += other._matrix[0][2];
	_matrix[1][0] += other._matrix[1][0]; _matrix[1][1] += other._matrix[1][1]; _matrix[1][2] += other._matrix[1][2];
	_matrix[2][0] += other._matrix[2][0]; _matrix[2][1] += other._matrix[2][1]; _matrix[2][2] += other._matrix[2][2];
}

void matrix::operator-=(const matrix& other) {
	_matrix[0][0] -= other._matrix[0][0]; _matrix[0][1] -= other._matrix[0][1]; _matrix[0][2] -= other._matrix[0][2];
	_matrix[1][0] -= other._matrix[1][0]; _matrix[1][1] -= other._matrix[1][1]; _matrix[1][2] -= other._matrix[1][2];
	_matrix[2][0] -= other._matrix[2][0]; _matrix[2][1] -= other._matrix[2][1]; _matrix[2][2] -= other._matrix[2][2];
}

void matrix::operator*=(const matrix& other) {
	matrix new_mat(*this);

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			new_mat._matrix[i][j] = 0;
			for (int k = 0; k < 3; k++)
				new_mat._matrix[i][j] += _matrix[i][k] * other._matrix[k][j];
		}

	(*this) = std::move(new_mat);
}

void matrix::operator*=(float coef) {
	_matrix[0][0] *= coef; _matrix[0][1] *= coef; _matrix[0][2] *= coef;
	_matrix[1][0] *= coef; _matrix[1][1] *= coef; _matrix[1][2] *= coef;
	_matrix[2][0] *= coef; _matrix[2][1] *= coef; _matrix[2][2] *= coef;
}