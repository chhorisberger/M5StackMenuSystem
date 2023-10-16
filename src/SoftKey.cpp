#include "SoftKey.h"

#include <M5Stack.h>


SoftKey::SoftKey(SoftKeySlot slot_)
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
	return M5.Lcd.width() / 5;
}

int SoftKey::getHeight()
{
	return M5.Lcd.fontHeight(MY_FONT);
}

void SoftKey::render(bool force)
{
	if (dirty || force)
	{
		int w = getWidth();
		int h = getHeight();
		int x = getXPosition();
		int y = M5.Lcd.height() - (h + V_PADDING_BOTTOM_SECTION);

		renderInternal(x, y, w, h);

		dirty = false;
	}
}

void SoftKey::renderRow(int x, int y, int w, int h)
{
	if (pressed)
	{
		M5.Lcd.fillRoundRect(x, y, w, h, 3, SOFTKEY_COLOR);
	}
	else
	{
		M5.Lcd.fillRoundRect(x, y, w, h, 3, SOFTKEY_BACKGROUND_COLOR);
		M5.Lcd.drawRoundRect(x, y, w, h, 3, SOFTKEY_COLOR);
	}
}

int SoftKey::getXPosition()
{
	switch (slot)
	{
	case BtnASlot:
		return getWidth() / 2;
	case BtnBSlot:
		return (M5.Lcd.width() / 2) - (getWidth() / 2);
	case BtnCSlot:
		return M5.Lcd.width() - (getWidth() + (getWidth() / 2));
	}

	return -1;
}