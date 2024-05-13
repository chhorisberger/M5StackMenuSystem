#include "MenuItem.h"

#include "Menu.h"

#include <M5Unified.h>


MenuItem::MenuItem(Layout& layout_, Display& display_, String text_) : layout(layout_), display(display_)
{
	text = text_;
	previousItem = NULL;
	nextItem = NULL;
	menu = NULL;
	dirty = true;
	position = -1;
}

void MenuItem::onAdded()
{
}

MenuItem* MenuItem::getPrevious()
{
	return previousItem;
}

void MenuItem::setPrevious(MenuItem* item)
{
	previousItem = item;
}

MenuItem* MenuItem::getNext()
{
	return nextItem;
}

void MenuItem::setNext(MenuItem* item)
{
	nextItem = item;
}

void MenuItem::setDirty()
{
	dirty = true;
}

String MenuItem::getText()
{
	return text;
}

void MenuItem::setMenu(Menu* menu_)
{
	menu = menu_;
}

Menu* MenuItem::getMenu()
{
	return menu;
}

void MenuItem::setPosition(int position_)
{
	position = position_;
}

int MenuItem::getPosition()
{
	return position;
}

void MenuItem::render(int x, int y, bool isHighlighted, bool force)
{
	if (dirty || force)
	{
		int fontHeight = display.fontHeight(layout.MENU_FONT);

		int w = layout.SCREEN_WIDTH;
		int h = fontHeight;
		display.fillRect(x,y,w,h, isHighlighted ? layout.MENU_ITEM_HIGHLIGHTED_BACKGROUND_COLOR : layout.MENU_ITEM_BACKGROUND_COLOR);

		if (isHighlighted)
		{
			int iconX = 16;
			int iconY = y + (fontHeight / 2);
			int x0 = iconX - layout.MENU_ITEM_HIGHLIGHTED_ICON_SIZE;
			int y0 = iconY - layout.MENU_ITEM_HIGHLIGHTED_ICON_SIZE;
			int x1 = iconX - layout.MENU_ITEM_HIGHLIGHTED_ICON_SIZE;
			int y1 = iconY + layout.MENU_ITEM_HIGHLIGHTED_ICON_SIZE;
			int x2 = iconX + layout.MENU_ITEM_HIGHLIGHTED_ICON_SIZE;
			int y2 = iconY;
			display.fillTriangle(x0, y0, x1, y1, x2, y2, layout.MENU_ITEM_HIGHLIGHTED_TEXT_COLOR);
		}

		int textX = 34;	// TODO
		display.setTextColor(isHighlighted ? layout.MENU_ITEM_HIGHLIGHTED_TEXT_COLOR : layout.MENU_ITEM_TEXT_COLOR);
		display.setTextDatum(TL_DATUM);
		display.drawString((text).c_str(), textX, y);

		dirty = false;
	}
}

