#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

class Display
{
	public:
		Display();

		virtual void init();
		virtual void drawStart();
		virtual void drawEnd();

		virtual int32_t width() = 0;
		virtual int32_t height() = 0;
		virtual int32_t fontHeight(uint8_t font) = 0;

		virtual void setTextFont(int font) = 0;
		virtual void setTextSize(float size) = 0;
		virtual void setTextDatum(uint8_t datum) = 0;
		virtual void setTextColor(int color) = 0;

		virtual void drawString(const char *string, int32_t x, int32_t y) = 0;

		virtual void fillRect(int32_t x, int32_t y, int32_t w, int32_t h, int color) = 0;
		virtual void drawRect(int32_t x, int32_t y, int32_t w, int32_t h, int color) = 0;

		virtual void fillRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, int color) = 0;
		virtual void drawRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, int color) = 0;

		virtual void fillTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int color) = 0;
		virtual void drawTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int color) = 0;


};

#endif 

