#include "DirectDisplay.h"


DirectDisplay::DirectDisplay()
{	
}

void DirectDisplay::init()
{
	M5.Display.begin();
}

void DirectDisplay::drawStart()
{
	M5.Display.startWrite();
}

void DirectDisplay::drawEnd()
{
	M5.Display.endWrite();
}

int32_t DirectDisplay::width()
{
	return M5.Display.width();
}

int32_t DirectDisplay::height()
{
	return M5.Display.height();
}

int32_t DirectDisplay::fontHeight(uint8_t font)
{
	return M5.Display.fontHeight(font);
}

void DirectDisplay::setTextFont(int font)
{
	M5.Display.setTextFont(font);
}

void DirectDisplay::setTextSize(float size)
{
	M5.Display.setTextSize(size);
}

void DirectDisplay::setTextDatum(uint8_t datum)
{
	M5.Display.setTextDatum(datum);
}

void DirectDisplay::setTextColor(int color)
{
	M5.Display.setTextColor(color);
}

void DirectDisplay::drawString(const char *string, int32_t x, int32_t y)
{
	M5.Display.drawString(string, x, y);
}

void DirectDisplay::fillRect(int32_t x, int32_t y, int32_t w, int32_t h, int color)
{
	M5.Display.fillRect(x, y, w, h, color);
}

void DirectDisplay::drawRect(int32_t x, int32_t y, int32_t w, int32_t h, int color)
{
	M5.Display.drawRect(x, y, w, h, color);
}

void DirectDisplay::fillRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, int color)
{
	M5.Display.fillRoundRect(x, y, w, h, r, color);
}

void DirectDisplay::drawRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, int color)
{
	M5.Display.drawRoundRect(x, y, w, h, r, color);
}

void DirectDisplay::fillTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int color)
{
	M5.Display.fillTriangle(x0, y0, x1, y1, x2, y2, color);
}

void DirectDisplay::drawTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int color)
{
	M5.Display.drawTriangle(x0, y0, x1, y1, x2, y2, color);
}

