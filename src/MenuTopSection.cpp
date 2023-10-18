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
		int barW = SCREEN_WIDTH;
		int barH = MENU_FONT_HEIGHT + (2 * V_PADDING_TOP_SECTION);
		M5.Lcd.fillRect(0, 0, barW, barH, TOP_BAR_BACKGROUND_COLOR);

		M5.Lcd.setTextColor(TOP_BAR_TITLE_COLOR);
		M5.Lcd.setTextDatum(TC_DATUM);
		M5.Lcd.drawString((title).c_str(), SCREEN_WIDTH / 2, V_PADDING_TOP_SECTION);

		dirty = false;
	}
}

void MenuTopSection::setTitle(String title_)
{
	title = title_;
	dirty = true;
}