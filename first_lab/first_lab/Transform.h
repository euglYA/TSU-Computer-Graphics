#pragma once
#include <cmath>
#include <utility>

struct vector {
	float x;
	float y;

	vector(float _x = 0, float _y = 0);
	vector(const vector& other);
	vector(vector&& other) noexcept;

	void	operator=(const vector& other);
	void	operator=(vector&& other) noexcept;
	void	normalize();
	float	length() const;

	vector		operator+(const vector& other);
	vector		operator-(const vector& other);
	vector		operator*(float coef);

	void	operator+=(const vector& other);
	void	operator-=(const vector& other);
	void	operator*=(float coef);
};

struct matrix {
	float** _matrix = nullptr;

	matrix();
	~matrix();
	matrix(const matrix& other);
	matrix(matrix&& other) noexcept;

	void	operator=(const matrix& other);
	void	operator=(matrix&& other) noexcept;
	void	transpose();

	matrix	operator+(const matrix& other);
	matrix	operator-(const matrix& other);
	matrix	operator*(const matrix& other);
	matrix	operator*(float coef);
	vector	operator*(const vector& other);

	void	operator+=(const matrix& other);
	void	operator-=(const matrix& other);
	void	operator*=(const matrix& other);
	void	operator*=(float coef);
};
