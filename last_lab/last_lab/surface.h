#pragma once

#include "matrix.h"
#include "graphics.h"
#include "camera.h"

class Surface
{
public:
	Surface(float x_min, float x_max, float z_min, float z_max, float (*equation)(float x, float z));

	void SetAngles(float roll, float pitch);

	void Draw(Graphics& g);

private:
	const int32_t steps_ = 50;

	Matrix corners_;
	Matrix rotation_;

	Matrix vertices_;

	const Matrix Scale(const Matrix& vertices);
};