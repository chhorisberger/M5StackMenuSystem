#include "Display.h"


Display::Display() : display(), canvas(&display)
{	
}

void Display::init()
{
	display.begin();
	canvas.setColorDepth(8); // without this, creating full screen canvas fails
	canvas.createSprite(width(), height());
}

void Display::draw()
{
	canvas.pushSprite(&display, 0, 0);
}

int32_t Display::width()
{
	return display.width();
}

int32_t Display::height()
{
	return display.height();
}

int32_t Display::fontHeight(uint8_t font)
{
	return canvas.fontHeight(font);
}

void Display::setTextFont(int font)
{
	canvas.setTextFont(font);
}

void Display::setTextSize(float size)
{
	canvas.setTextSize(size);
}

void Display::setTextDatum(uint8_t datum)
{
	canvas.setTextDatum(datum);
}

void Display::setTextColor(int color)
{
	canvas.setTextColor(color);
}

void Display::drawString(const char *string, int32_t x, int32_t y)
{
	canvas.drawString(string, x, y);
}

void Display::fillRect(int32_t x, int32_t y, int32_t w, int32_t h, int color)
{
	canvas.fillRect(x, y, w, h, color);
}

void Display::drawRect(int32_t x, int32_t y, int32_t w, int32_t h, int color)
{
	canvas.drawRect(x, y, w, h, color);
}

void Display::fillRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, int color)
{
	display.fillRoundRect(x, y, w, h, r, color);
}

void Display::drawRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, int color)
{
	display.drawRoundRect(x, y, w, h, r, color);
}

void Display::fillTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int color)
{
	display.fillTriangle(x0, y0, x1, y1, x2, y2, color);
}

void Display::drawTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int color)
{
	display.drawTriangle(x0, y0, x1, y1, x2, y2, color);
}

