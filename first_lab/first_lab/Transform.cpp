#include "Transform.h"
#include "cmath"

vector::vector(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z)
{}

vector::vector(const vector& other) {
	x = other.x;
	y = other.y;
	z = other.z;
}

vector::vector(vector&& other) noexcept {
	x = other.x;
	y = other.y;
	z = other.z;
}

void vector::operator=(const vector& other) {
	if (this == &other)
		return;

	x = other.x;
	y = other.y;
	z = other.z;
}

void vector::operator=(vector&& other) noexcept {
	if (this == &other)
		return;

	x = other.x;
	y = other.y;
	z = other.z;
}

void vector::normalize() {
	float inv_len = 1.0f / this->length();
	(*this) *= inv_len;
}

float vector::length() const {
	return sqrtf(x * x + y * y + z * z);
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
	z += other.z;
}

void vector::operator-=(const vector& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
}

void vector::operator*=(float coef) {
	x *= coef;
	y *= coef;
	z *= coef;
}

////////////////////////////////////////////////////////////////////

matrix matrix::viewMatrix;
matrix matrix::projMatrix;

matrix::matrix() {
	_matrix = new float* [4];
	_matrix[0] = new float[4];
	_matrix[1] = new float[4];
	_matrix[2] = new float[4];
	_matrix[3] = new float[4];

	_matrix[0][0] = 1; _matrix[0][1] = 0; _matrix[0][2] = 0; _matrix[0][3] = 0;
	_matrix[1][0] = 0; _matrix[1][1] = 1; _matrix[1][2] = 0; _matrix[1][3] = 0;
	_matrix[2][0] = 0; _matrix[2][1] = 0; _matrix[2][2] = 1; _matrix[2][3] = 0;
	_matrix[3][0] = 0; _matrix[3][1] = 0; _matrix[3][2] = 0; _matrix[3][3] = 1;
}

matrix::~matrix() {
	delete[] _matrix[0];
	delete[] _matrix[1];
	delete[] _matrix[2];
	delete[] _matrix[3];
	delete[] _matrix;
}

matrix::matrix(const matrix& other) {
	_matrix = new float* [4];
	_matrix[0] = new float[4];
	_matrix[1] = new float[4];
	_matrix[2] = new float[4];
	_matrix[3] = new float[4];

	_matrix[0][0] = other._matrix[0][0]; _matrix[0][1] = other._matrix[0][1]; _matrix[0][2] = other._matrix[0][2]; _matrix[0][3] = other._matrix[0][3];
	_matrix[1][0] = other._matrix[1][0]; _matrix[1][1] = other._matrix[1][1]; _matrix[1][2] = other._matrix[1][2]; _matrix[1][3] = other._matrix[1][3];
	_matrix[2][0] = other._matrix[2][0]; _matrix[2][1] = other._matrix[2][1]; _matrix[2][2] = other._matrix[2][2]; _matrix[2][3] = other._matrix[2][3];
	_matrix[3][0] = other._matrix[3][0]; _matrix[3][1] = other._matrix[3][1]; _matrix[3][2] = other._matrix[3][2]; _matrix[3][3] = other._matrix[3][3];
}

matrix::matrix(matrix&& other) noexcept {
	_matrix = other._matrix;
	other._matrix = nullptr;
}

void matrix::operator=(const matrix& other) {
	if (this == &other)
		return;

	_matrix[0][0] = other._matrix[0][0]; _matrix[0][1] = other._matrix[0][1]; _matrix[0][2] = other._matrix[0][2]; _matrix[0][3] = other._matrix[0][3];
	_matrix[1][0] = other._matrix[1][0]; _matrix[1][1] = other._matrix[1][1]; _matrix[1][2] = other._matrix[1][2]; _matrix[1][3] = other._matrix[1][3];
	_matrix[2][0] = other._matrix[2][0]; _matrix[2][1] = other._matrix[2][1]; _matrix[2][2] = other._matrix[2][2]; _matrix[2][3] = other._matrix[2][3];
	_matrix[3][0] = other._matrix[3][0]; _matrix[3][1] = other._matrix[3][1]; _matrix[3][2] = other._matrix[3][2]; _matrix[3][3] = other._matrix[3][3];
}

void matrix::operator=(matrix&& other) noexcept {
	float** temp = _matrix;
	_matrix = other._matrix;
	other._matrix = temp;
}

void matrix::transpose() {
	matrix temp(*this);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
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
	new_mat *= other;

	return new_mat;
}

vector matrix::operator*(const vector& other) {
	vector ans;

	ans.x = _matrix[0][0] * other.x + _matrix[0][1] * other.y + _matrix[0][2] * other.z + _matrix[0][3];
	ans.y = _matrix[1][0] * other.x + _matrix[1][1] * other.y + _matrix[1][2] * other.z + _matrix[1][3];
	ans.z = _matrix[2][0] * other.x + _matrix[2][1] * other.y + _matrix[2][2] * other.z + _matrix[2][3];

	return ans;
}

matrix matrix::operator*(float coef) {
	matrix new_mat(*this);
	new_mat *= coef;

	return new_mat;
}

void matrix::operator+=(const matrix& other) {
	_matrix[0][0] += other._matrix[0][0]; _matrix[0][1] += other._matrix[0][1]; _matrix[0][2] += other._matrix[0][2]; _matrix[0][3] += other._matrix[0][3];
	_matrix[1][0] += other._matrix[1][0]; _matrix[1][1] += other._matrix[1][1]; _matrix[1][2] += other._matrix[1][2]; _matrix[1][3] += other._matrix[1][3];
	_matrix[2][0] += other._matrix[2][0]; _matrix[2][1] += other._matrix[2][1]; _matrix[2][2] += other._matrix[2][2]; _matrix[2][3] += other._matrix[2][3];
	_matrix[3][0] += other._matrix[3][0]; _matrix[3][1] += other._matrix[3][1]; _matrix[3][2] += other._matrix[3][2]; _matrix[3][3] += other._matrix[3][3];
}

void matrix::operator-=(const matrix& other) {
	_matrix[0][0] -= other._matrix[0][0]; _matrix[0][1] -= other._matrix[0][1]; _matrix[0][2] -= other._matrix[0][2]; _matrix[0][3] -= other._matrix[0][3];
	_matrix[1][0] -= other._matrix[1][0]; _matrix[1][1] -= other._matrix[1][1]; _matrix[1][2] -= other._matrix[1][2]; _matrix[1][3] -= other._matrix[1][3];
	_matrix[2][0] -= other._matrix[2][0]; _matrix[2][1] -= other._matrix[2][1]; _matrix[2][2] -= other._matrix[2][2]; _matrix[2][3] -= other._matrix[2][3];
	_matrix[3][0] -= other._matrix[3][0]; _matrix[3][1] -= other._matrix[3][1]; _matrix[3][2] -= other._matrix[3][2]; _matrix[3][3] -= other._matrix[3][3];
}

void matrix::operator*=(const matrix& other) {
	matrix new_mat(*this);

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			new_mat._matrix[i][j] = 0;
			for (int k = 0; k < 4; k++)
				new_mat._matrix[i][j] += _matrix[i][k] * other._matrix[k][j];
		}

	(*this) = std::move(new_mat);
}

void matrix::operator*=(float coef) {
	_matrix[0][0] *= coef; _matrix[0][1] *= coef; _matrix[0][2] *= coef; _matrix[0][3] *= coef;
	_matrix[1][0] *= coef; _matrix[1][1] *= coef; _matrix[1][2] *= coef; _matrix[1][3] *= coef;
	_matrix[2][0] *= coef; _matrix[2][1] *= coef; _matrix[2][2] *= coef; _matrix[2][3] *= coef;
	_matrix[3][0] *= coef; _matrix[3][1] *= coef; _matrix[3][2] *= coef; _matrix[3][3] *= coef;
}

void matrix::initViewMatrix() {
	viewMatrix._matrix[0][0] = 0.707;	viewMatrix._matrix[0][1] = 0;	viewMatrix._matrix[0][2] = -0.707;		viewMatrix._matrix[0][3] = 0;
	viewMatrix._matrix[1][0] = 0;		viewMatrix._matrix[1][1] = 1;	viewMatrix._matrix[1][2] = 0;			viewMatrix._matrix[1][3] = 0;
	viewMatrix._matrix[2][0] = 0.707;	viewMatrix._matrix[2][1] = 0;	viewMatrix._matrix[2][2] = 0.707;		viewMatrix._matrix[2][3] = 10;
	viewMatrix._matrix[3][0] = 0;		viewMatrix._matrix[3][1] = 0;	viewMatrix._matrix[3][2] = 0;			viewMatrix._matrix[3][3] = 1;
}

void matrix::initProjMatrix(float aspect, float FOV) {
	float near = 0.01;
	float far = 1000;
	projMatrix._matrix[0][0] = 1.0f / (aspect * tan(FOV/2 * PI / 180)); projMatrix._matrix[0][1] = 0;								projMatrix._matrix[0][2] = 0;							projMatrix._matrix[0][3] = 0;
	projMatrix._matrix[1][0] = 0;										projMatrix._matrix[1][1] = 1.0f / (tan(FOV/2 * PI / 180));	projMatrix._matrix[1][2] = 0;							projMatrix._matrix[1][3] = 0;
	projMatrix._matrix[2][0] = 0;										projMatrix._matrix[2][1] = 0;								projMatrix._matrix[2][2] = -(far + near)/(far - near);	projMatrix._matrix[2][3] = -2*(far * near)/(far - near);
	projMatrix._matrix[3][0] = 0;										projMatrix._matrix[3][1] = 0;								projMatrix._matrix[3][2] = -1;							projMatrix._matrix[3][3] = 0;
}


matrix matrix::getPerspective(float aspect, float FOV, float near, float far) {
	matrix ans;

	float radians = FOV * 3.14f / 180.0f;

	ans._matrix[0][0] = 1.0f / (aspect * tanf(radians / 2.0f));
	ans._matrix[1][1] = 1.0f / tanf(radians / 2.0f);
	ans._matrix[2][2] = -(far + near) / (far - near);
	ans._matrix[2][3] = -2.0f * far * near / (far - near);
	ans._matrix[3][2] = -1.0f;
	ans._matrix[3][3] = 0.0f;

	return ans;
}

matrix matrix::getOrtographic(float aspect, float width, float height, float near, float far) {
	matrix ans;

	ans._matrix[0][0] = 1.0f / (aspect * width);
	ans._matrix[1][1] = 1.0f / height;
	ans._matrix[2][2] = -2.0f / (far - near);
	ans._matrix[2][3] = -(far + near) / (far - near);
	ans._matrix[3][3] = 1.0f;

	return ans;
}