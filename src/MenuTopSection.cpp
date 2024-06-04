#include "MenuTopSection.h"
#include "Display.h"

#include <M5Unified.h>

MenuTopSection::MenuTopSection(Layout& layout_,  String title_) : layout(layout_)
{
	title = title_;
}

void MenuTopSection::render()
{
	int barW = layout.SCREEN_WIDTH;
	int barH = getHeight();
	Display::getInstance()->fillRect(0, 0, barW, barH, layout.TOP_BAR_BACKGROUND_COLOR);

	Display::getInstance()->setTextColor(layout.TOP_BAR_TITLE_COLOR);
	Display::getInstance()->setTextDatum(TC_DATUM);
	Display::getInstance()->drawString((title).c_str(), layout.SCREEN_WIDTH / 2, layout.TOP_BAR_V_PADDING);
}

void MenuTopSection::setTitle(String title_)
{
	title = title_;
}

int MenuTopSection::getHeight()
{
	return Display::getInstance()->fontHeight(layout.MENU_FONT) + (2 * layout.TOP_BAR_V_PADDING);
}

