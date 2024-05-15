#ifndef BUFFERED_DISPLAY_H
#define BUFFERED_DISPLAY_H

#include <stdint.h>
#include <M5Unified.h> 

#include "Display.h"

class BufferedDisplay : virtual public Display
{
	public:
		BufferedDisplay();

		virtual void init();
		virtual void drawStart();
		virtual void drawEnd();

		virtual int32_t width();
		virtual int32_t height();
		virtual int32_t fontHeight(uint8_t font);

		virtual void setTextFont(int font);
		virtual void setTextSize(float size);
		virtual void setTextDatum(uint8_t datum);
		virtual void setTextColor(int color);

		virtual void drawString(const char *string, int32_t x, int32_t y);

		virtual void fillRect(int32_t x, int32_t y, int32_t w, int32_t h, int color);
		virtual void drawRect(int32_t x, int32_t y, int32_t w, int32_t h, int color);

		virtual void fillRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, int color);
		virtual void drawRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, int color);

		virtual void fillTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int color);
		virtual void drawTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int color);

	private:
		M5Canvas canvas;

};

#endif 

