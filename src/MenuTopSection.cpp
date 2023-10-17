#include "MenuTopSection.h"

#include <M5Stack.h>

MenuTopSection::MenuTopSection(String title_)
{
	title = title_;
	dirty = true;
}

void MenuTopSection::render(bool force)
{
	if (dirty || force)
	{
		int barW = M5.Lcd.width();
		int barH = M5.Lcd.fontHeight(MY_FONT) + (2 * V_PADDING_TOP_SECTION);
		M5.Lcd.fillRect(0, 0, barW, barH, TOP_BAR_BACKGROUND_COLOR);

		M5.Lcd.setTextColor(TOP_BAR_TITLE_COLOR);
		M5.Lcd.setTextDatum(TC_DATUM);
		M5.Lcd.drawString((title).c_str(), M5.Lcd.width() / 2, V_PADDING_TOP_SECTION);

		dirty = false;
	}
}

void MenuTopSection::setTitle(String title_)
{
	title = title_;
	dirty = true;
}