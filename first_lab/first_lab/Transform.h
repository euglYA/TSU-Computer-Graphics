#pragma once
#include <cmath>
#include <utility>

struct vec {
	float x;
	float y;
	float z;

	vec(float _x = 0, float _y = 0, float _z = 0);
	vec(const vec& other);
	vec(vec&& other) noexcept;
	void operator=(const vec& other);
	void operator=(vec&& other) noexcept;

	void normalize();

	float length() const;

	vec operator+(const vec& other);
	vec operator-(const vec& other);
	vec operator*(float coef);

	void operator+=(const vec& other);
	void operator-=(const vec& other);
	void operator*=(float coef);

};

struct matrix {
	float** _matrix = nullptr;

	matrix();
	~matrix();
	matrix(const matrix& other);
	matrix(matrix&& other) noexcept;
	void operator=(const matrix& other);
	void operator=(matrix&& other) noexcept;

	void transpose();

	matrix operator+(const matrix& other);
	matrix operator-(const matrix& other);
	matrix operator*(const matrix& other);
	vec operator*(const vec& other);
	matrix operator*(float coef);

	void operator+=(const matrix& other);
	void operator-=(const matrix& other);
	void operator*=(const matrix& other);
	void operator*=(float coef);
};
