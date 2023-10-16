#pragma once

#include <array>

#include "graphics.h"
#include "matrix.h"

class Camera {
public:
	Camera() = delete;

	static const float x() { return x_; }
	static const float y() { return y_; }
	static const float z() { return z_; }

	static const Matrix& view() { return view_; }
	static const Matrix& projection() { return projection_; }

	static void LookAt(float x, float y, float z);
	static void Ortho(float offset_x, float offset_y, float zoom);

	static void DrawLine(Graphics& g, float x0, float y0, float z0, float x1, float y1, float z1, COLORREF color);

private:
	static float x_;
	static float y_;
	static float z_;

	static Matrix view_;
	static Matrix projection_;
};