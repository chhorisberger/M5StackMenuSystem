#include "DownSoftKey.h"

#include <M5Unified.h>


DownSoftKey::DownSoftKey(SoftKeySlot slot_, Layout& layout_, Control& control_) : SoftKey(slot_, layout_, control_)
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
	int x0 = iconX - layout.BOTTOM_BAR_SOFTKEY_ICONS_SIZE;
	int y0 = iconY - layout.BOTTOM_BAR_SOFTKEY_ICONS_SIZE;

	int x1 = iconX;
	int y1 = iconY + layout.BOTTOM_BAR_SOFTKEY_ICONS_SIZE;

	int x2 = iconX + layout.BOTTOM_BAR_SOFTKEY_ICONS_SIZE;
	int y2 = iconY - layout.BOTTOM_BAR_SOFTKEY_ICONS_SIZE;

	M5.Lcd.fillTriangle(x0, y0, x1, y1, x2, y2, pressed ? layout.BOTTOM_BAR_SOFTKEY_BACKGROUND_COLOR : layout.BOTTOM_BAR_SOFTKEY_COLOR);
}
