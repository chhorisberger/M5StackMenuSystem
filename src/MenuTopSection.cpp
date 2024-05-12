#include "MenuTopSection.h"

#include <M5Unified.h>

MenuTopSection::MenuTopSection(Layout& layout_, String title_) : layout(layout_)
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
		M5.Display.fillRect(0, 0, barW, barH, layout.TOP_BAR_BACKGROUND_COLOR);

		M5.Display.setTextColor(layout.TOP_BAR_TITLE_COLOR);
		M5.Display.setTextDatum(TC_DATUM);
		M5.Display.drawString((title).c_str(), layout.SCREEN_WIDTH / 2, layout.TOP_BAR_V_PADDING);

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
	return M5.Display.fontHeight(layout.MENU_FONT) + (2 * layout.TOP_BAR_V_PADDING);
}

void MenuTopSection::setDirty()
{
	dirty = true;
}
