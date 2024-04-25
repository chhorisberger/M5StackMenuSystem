#include "SoftKey.h"

#ifdef M5_UNIFIED
#include <M5Unified.h>
#else
#include <M5Stack.h>
#endif

SoftKey::SoftKey(SoftKeySlot slot_, Layout& layout_) : layout(layout_)
{
	slot = slot_;
	dirty = true;
	pressed = false;
}

void SoftKey::setPressed(bool pressed_)
{
	pressed = pressed_;
	dirty = true;
}

int SoftKey::getWidth()
{
	return layout.SCREEN_WIDTH / layout.BOTTOM_BAR_SOFTKEY_WIDTH_AS_FRACTION_OF_SCREEN;
}

int SoftKey::getHeight()
{
	return  M5.Lcd.fontHeight(layout.MENU_FONT) + (2 * layout.BOTTOM_BAR_SOFTKEY_V_PADDING);
}

void SoftKey::render(bool force)
{
	if (dirty || force)
	{
		int w = getWidth();
		int h = getHeight();
		int x = getXPosition();
		int y = layout.SCREEN_HEIGHT - (h + layout.BOTTOM_BAR_SOFTKEY_V_SPACING);

		renderInternal(x, y, w, h);

		dirty = false;
	}
}

void SoftKey::renderRow(int x, int y, int w, int h)
{
	if (pressed)
	{
		M5.Lcd.fillRoundRect(x, y, w, h, 3, layout.BOTTOM_BAR_SOFTKEY_COLOR);
	}
	else
	{
		M5.Lcd.fillRoundRect(x, y, w, h, 3, layout.BOTTOM_BAR_SOFTKEY_BACKGROUND_COLOR);
		M5.Lcd.drawRoundRect(x, y, w, h, 3, layout.BOTTOM_BAR_SOFTKEY_COLOR);
	}
}

int SoftKey::getXPosition()
{
	switch (slot)
	{
	case BtnASlot:
		return getWidth() / 2;
	case BtnBSlot:
		return (layout.SCREEN_WIDTH / 2) - (getWidth() / 2);
	case BtnCSlot:
		return layout.SCREEN_WIDTH - (getWidth() + (getWidth() / 2));
	}

	return -1;
}
