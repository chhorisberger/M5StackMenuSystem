#include "BufferedDisplay.h"


BufferedDisplay::BufferedDisplay() : canvas()
{	
}

void BufferedDisplay::init()
{
	canvas.setColorDepth(8); // TODO: without this, a full screen size canvas fails to draw... maybe related to chosen board in arduino ide?
	canvas.createSprite(width(), height());
}

void BufferedDisplay::drawStart()
{
	canvas.clear();
}

void BufferedDisplay::drawEnd()
{
	canvas.pushSprite(&M5.Display, 0,0);
}

int32_t BufferedDisplay::width()
{
	return M5.Display.width();
}

int32_t BufferedDisplay::height()
{
	return M5.Display.height();
}

int32_t BufferedDisplay::fontHeight(uint8_t font)
{
	return canvas.fontHeight(font);
}

void BufferedDisplay::setTextFont(int font)
{
	canvas.setTextFont(font);
}

void BufferedDisplay::setTextSize(float size)
{
	canvas.setTextSize(size);
}

void BufferedDisplay::setTextDatum(uint8_t datum)
{
	canvas.setTextDatum(datum);
}

void BufferedDisplay::setTextColor(int color)
{
	canvas.setTextColor(color);
}

void BufferedDisplay::drawString(const char *string, int32_t x, int32_t y)
{
	canvas.drawString(string, x, y);
}

void BufferedDisplay::fillRect(int32_t x, int32_t y, int32_t w, int32_t h, int color)
{
	canvas.fillRect(x, y, w, h, color);
}

void BufferedDisplay::drawRect(int32_t x, int32_t y, int32_t w, int32_t h, int color)
{
	canvas.drawRect(x, y, w, h, color);
}

void BufferedDisplay::fillRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, int color)
{
	canvas.fillRoundRect(x, y, w, h, r, color);
}

void BufferedDisplay::drawRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, int color)
{
	canvas.drawRoundRect(x, y, w, h, r, color);
}

void BufferedDisplay::fillTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int color)
{
	canvas.fillTriangle(x0, y0, x1, y1, x2, y2, color);
}

void BufferedDisplay::drawTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int color)
{
	canvas.drawTriangle(x0, y0, x1, y1, x2, y2, color);
}

