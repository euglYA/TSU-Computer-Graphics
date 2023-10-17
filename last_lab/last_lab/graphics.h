#pragma once

// WinGDI - graphics library

#define NOMINMAX

#include <stdint.h>
#include <Windows.h>
#include <array>
#include <vector>

class Graphics
{
public:
	static const int32_t width = 600;
	static const int32_t height = 600;

	static void Init(HWND h_window);
	static void DeInit();

	Graphics();
	~Graphics();

	void SetPixel(int32_t x, int32_t y, COLORREF color);
	void DrawLine(float x0, float y0, float x1, float y1, COLORREF color);
	void DrawPoly(std::vector<std::array<float, 2>> vertices, COLORREF color);

	static COLORREF HSV(float h, float s, float v);

private:
	static HWND h_window_;

	static const HGDIOBJ pen_null_;
	static const HGDIOBJ pen_dc_;
	static const HGDIOBJ brush_dc_;

	static BITMAPINFO bitmap_info_;
	static HBITMAP h_bitmap_;
	static HDC h_memory_dc_;

	static const int32_t bitmap_buffer_size_ = Graphics::width * Graphics::height * 4;
	static uint8_t* bitmap_buffer_; // array of RGBQUAD

	HDC h_window_dc_;
};