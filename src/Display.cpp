#include "Display.h"

#include <M5Unified.h> 

Display::Display()
{	
}

void Display::init()
{
}

void Display::draw()
{
}

int32_t Display::width()
{
	return M5.Display.width();
}

int32_t Display::height()
{
	return M5.Display.height();
}

int32_t Display::fontHeight(uint8_t font)
{
	return M5.Display.fontHeight(font);
}

void Display::setTextFont(int font)
{
	M5.Display.setTextFont(font);
}

void Display::setTextSize(float size)
{
	M5.Display.setTextSize(size);
}

void Display::setTextDatum(uint8_t datum)
{
	M5.Display.setTextDatum(datum);
}

void Display::setTextColor(int color)
{
	M5.Display.setTextColor(color);
}

void Display::drawString(const char *string, int32_t x, int32_t y)
{
	M5.Display.drawString(string, x, y);
}

void Display::fillRect(int32_t x, int32_t y, int32_t w, int32_t h, int color)
{
	M5.Display.fillRect(x, y, w, h, color);
}

void Display::drawRect(int32_t x, int32_t y, int32_t w, int32_t h, int color)
{
	M5.Display.drawRect(x, y, w, h, color);
}

void Display::fillRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, int color)
{
	M5.Display.fillRoundRect(x, y, w, h, r, color);
}

void Display::drawRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, int color)
{
	M5.Display.drawRoundRect(x, y, w, h, r, color);
}

void Display::fillTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int color)
{
	M5.Display.fillTriangle(x0, y0, x1, y1, x2, y2, color);
}

void Display::drawTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int color)
{
	M5.Display.drawTriangle(x0, y0, x1, y1, x2, y2, color);
}

