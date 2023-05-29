#include "Transform.h"

vec::vec(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z)
{}

vec::vec(const vec& other) {
	x = other.x;
	y = other.y;
	z = other.z;
}

vec::vec(vec&& other) noexcept {
	x = other.x;
	y = other.y;
	z = other.z;
}

void vec::operator=(const vec& other) {
	if (this == &other)
		return;

	x = other.x;
	y = other.y;
	z = other.z;
}

void vec::operator=(vec&& other) noexcept {
	if (this == &other)
		return;

	x = other.x;
	y = other.y;
	z = other.z;
}

void vec::normalize() {
	float inv_len = 1.0f / this->length();
	(*this) *= inv_len;
}

float vec::length() const {
	return sqrtf(x * x + y * y + z * z);
}

vec vec::operator+(const vec& other) {
	vec vec(*this);
	vec += other;

	return vec;
}

vec vec::operator-(const vec& other) {
	vec vec(*this);
	vec -= other;

	return vec;
}

vec vec::operator*(float coef) {
	vec vec(*this);
	vec *= coef;

	return vec;
}

void vec::operator+=(const vec& other) {
	x += other.x;
	y += other.y;
	z += other.z;
}

void vec::operator-=(const vec& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
}

void vec::operator*=(float coef) {
	x *= coef;
	y *= coef;
	z *= coef;
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

vec matrix::operator*(const vec& other) {
	vec ans;

	ans.x = _matrix[0][0] * other.x + _matrix[0][1] * other.y + _matrix[0][2] * other.z;
	ans.y = _matrix[1][0] * other.x + _matrix[1][1] * other.y + _matrix[1][2] * other.z;
	ans.z = _matrix[2][0] * other.x + _matrix[2][1] * other.y + _matrix[2][2] * other.z;

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