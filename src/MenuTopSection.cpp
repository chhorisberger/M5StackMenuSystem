#include "MenuTopSection.h"

#include <M5Unified.h>

MenuTopSection::MenuTopSection(Layout& layout_, Display& display_, String title_) : layout(layout_), display(display_)
{
	title = title_;
	dirty = true;
}

void MenuTopSection::render(bool force)
{
	if (dirty || force)
	{
		int barW = layout.SCREEN_WIDTH;
		int barH = getHeight();
		display.fillRect(0, 0, barW, barH, layout.TOP_BAR_BACKGROUND_COLOR);

		display.setTextColor(layout.TOP_BAR_TITLE_COLOR);
		display.setTextDatum(TC_DATUM);
		display.drawString((title).c_str(), layout.SCREEN_WIDTH / 2, layout.TOP_BAR_V_PADDING);

		dirty = false;
	}
}

void MenuTopSection::setTitle(String title_)
{
	title = title_;
	dirty = true;
}

int MenuTopSection::getHeight()
{
	return display.fontHeight(layout.MENU_FONT) + (2 * layout.TOP_BAR_V_PADDING);
}

void MenuTopSection::setDirty()
{
	dirty = true;
}
