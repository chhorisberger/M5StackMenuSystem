#include "TextSoftKey.h"

#include <M5Unified.h>


TextSoftKey::TextSoftKey(SoftKeySlot slot_, Layout& layout_, Control& control_, String text_) : SoftKey(slot_, layout_, control_)
{
	text = text_;
}

void TextSoftKey::renderInternal(int x, int y, int w, int h)
{
	renderRow(x, y, w, h);
	renderText(x, y, w, h);
}

void TextSoftKey::renderText(int x, int y, int w, int h)
{
	if (pressed)
	{
		Display::getInstance()->setTextColor(layout.BOTTOM_BAR_SOFTKEY_BACKGROUND_COLOR);
	}
	else
	{
		Display::getInstance()->setTextColor(layout.BOTTOM_BAR_SOFTKEY_COLOR);
	}

	Display::getInstance()->setTextDatum(MC_DATUM);
	Display::getInstance()->drawString((text).c_str(), x + (w / 2), y + (h / 2));

}
