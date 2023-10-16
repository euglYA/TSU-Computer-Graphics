#include <cmath>
#include <algorithm>

#include "graphics.h"

HWND Graphics::h_window_;

const HGDIOBJ Graphics::pen_null_ = GetStockObject(NULL_PEN);
const HGDIOBJ Graphics::pen_dc_ = GetStockObject(DC_PEN);
const HGDIOBJ Graphics::brush_dc_ = GetStockObject(DC_BRUSH);

BITMAPINFO Graphics::bitmap_info_ {
	.bmiHeader {
		.biSize = sizeof(BITMAPINFOHEADER),
		.biWidth = Graphics::width,
		.biHeight = -Graphics::height,
		.biPlanes = 1,
		.biBitCount = 32,
		.biCompression = BI_RGB,
	},
};
HBITMAP Graphics::h_bitmap_;
HDC Graphics::h_memory_dc_;

uint8_t* Graphics::bitmap_buffer_;

void Graphics::Init(HWND h_window) {
	h_window_ = h_window;

	//
	HDC desktop_dc = GetDC(HWND_DESKTOP);

	h_bitmap_ = CreateDIBSection(desktop_dc, &bitmap_info_, DIB_RGB_COLORS, (void**)&bitmap_buffer_, nullptr, 0);
	h_memory_dc_ = CreateCompatibleDC(desktop_dc);

	ReleaseDC(HWND_DESKTOP, desktop_dc);

	SelectObject(h_memory_dc_, h_bitmap_);
	SelectObject(h_memory_dc_, pen_dc_);
	SelectObject(h_memory_dc_, brush_dc_);
}

void Graphics::DeInit() {
	DeleteDC(h_memory_dc_);
	DeleteObject(h_bitmap_);
}

Graphics::Graphics()
	: h_window_dc_(GetDC(h_window_)) 
{
	memset(bitmap_buffer_, 0, bitmap_buffer_size_);
}

Graphics::~Graphics() {
	BitBlt(h_window_dc_, 0, 0, width, height, h_memory_dc_, 0, 0, SRCCOPY);

	ReleaseDC(h_window_, h_window_dc_);
}

void Graphics::SetPixel(int32_t x, int32_t y, COLORREF color) {
	bitmap_buffer_[(y * width + x) * 4] = GetBValue(color);
	bitmap_buffer_[(y * width + x) * 4 + 1] = GetGValue(color);
	bitmap_buffer_[(y * width + x) * 4 + 2] = GetRValue(color);
}

void Graphics::DrawLine(float x0, float y0, float x1, float y1, COLORREF color) {
	SetDCPenColor(h_memory_dc_, color);

	MoveToEx(h_memory_dc_, round(x0), round(y0), nullptr);
	LineTo(h_memory_dc_, round(x1), round(y1));
}

void Graphics::DrawPoly(std::vector<std::array<float, 2>> vertices, COLORREF color) {
	uint32_t points_size = vertices.size();

	POINT* points = new POINT[points_size];

	for (uint32_t i = 0; i < points_size; i++)
	{
		points[i].x = round(vertices[i][0]);
		points[i].y = round(vertices[i][1]);
	}

	SetDCBrushColor(h_memory_dc_, color);

	SelectObject(h_memory_dc_, pen_null_);

	Polygon(h_memory_dc_, points, points_size);

	SelectObject(h_memory_dc_, pen_dc_);
}

COLORREF Graphics::HSV(float h, float s, float v) {
	float r, g, b; // 0.0-1.0

	int hi = (int)(h / 60.0f) % 6;
	float f = (h / 60.0f) - hi;
	float p = v * (1.0f - s);
	float q = v * (1.0f - s * f);
	float t = v * (1.0f - s * (1.0f - f));

	switch (hi)
	{
	case 0:
		r = v, g = t, b = p;
		break;
	case 1:
		r = q, g = v, b = p;
		break;
	case 2:
		r = p, g = v, b = t;
		break;
	case 3:
		r = p, g = q, b = v;
		break;
	case 4:
		r = t, g = p, b = v;
		break;
	case 5:
		r = v, g = p, b = q;
		break;
	default:
		r = 0, g = 0, b = 0;
		break;
	}

	return RGB(r * 255, g * 255, b * 255);
}