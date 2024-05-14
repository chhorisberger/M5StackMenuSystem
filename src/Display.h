#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <M5Unified.h> 

class Display
{
	public:
		Display();

		void init();
		void draw();

		int32_t width();
		int32_t height();
		int32_t fontHeight(uint8_t font);

		void setTextFont(int font);
		void setTextSize(float size);
		void setTextDatum(uint8_t datum);
		void setTextColor(int color);

		void drawString(const char *string, int32_t x, int32_t y);

		void fillRect(int32_t x, int32_t y, int32_t w, int32_t h, int color);
		void drawRect(int32_t x, int32_t y, int32_t w, int32_t h, int color);

		void fillRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, int color);
		void drawRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, int color);

		void fillTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int color);
		void drawTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int color);

	private:
		M5GFX display;
		M5Canvas canvas;

};

#endif 

