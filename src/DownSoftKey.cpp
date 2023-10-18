#include "DownSoftKey.h"

#include <M5Stack.h>


DownSoftKey::DownSoftKey(SoftKeySlot slot_) : SoftKey(slot_)
{
}

void DownSoftKey::renderInternal(int x, int y, int w, int h)
{
	renderRow(x, y, w, h);
	renderIcon(x, y, w, h);
}

void DownSoftKey::renderIcon(int x, int y, int w, int h)
{
	int iconX = x + (w/2);
	int iconY = y + (h/2);
	int x0 = iconX - 6;
	int y0 = iconY - 6;

	int x1 = iconX;
	int y1 = iconY + 6;

	int x2 = iconX + 6;
	int y2 = iconY - 6;

	M5.Lcd.fillTriangle(x0, y0, x1, y1, x2, y2, pressed ? BOTTOM_BAR_SOFTKEY_BACKGROUND_COLOR : BOTTOM_BAR_SOFTKEY_COLOR);
}