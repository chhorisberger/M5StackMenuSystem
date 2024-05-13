#include "TextSoftKey.h"

#include <M5Unified.h>


TextSoftKey::TextSoftKey(SoftKeySlot slot_, Layout& layout_, Control& control_, Display& display_, String text_) : SoftKey(slot_, layout_, control_, display_)
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
		display.setTextColor(layout.BOTTOM_BAR_SOFTKEY_BACKGROUND_COLOR);
	}
	else
	{
		display.setTextColor(layout.BOTTOM_BAR_SOFTKEY_COLOR);
	}

	display.setTextDatum(MC_DATUM);
	display.drawString((text).c_str(), x + (w / 2), y + (h / 2));

}
