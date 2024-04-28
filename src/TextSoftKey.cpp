#include "TextSoftKey.h"

#include <M5Unified.h>


TextSoftKey::TextSoftKey(SoftKeySlot slot_, Layout& layout_, String text_) : SoftKey(slot_, layout_)
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
		M5.Lcd.setTextColor(layout.BOTTOM_BAR_SOFTKEY_BACKGROUND_COLOR);
	}
	else
	{
		M5.Lcd.setTextColor(layout.BOTTOM_BAR_SOFTKEY_COLOR);
	}

	M5.Lcd.setTextDatum(MC_DATUM);
	M5.Lcd.drawString((text).c_str(), x + (w / 2), y + (h / 2));

}
