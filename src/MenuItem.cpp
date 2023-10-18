#include "MenuItem.h"

#include "Menu.h"

#include <M5Stack.h>


MenuItem::MenuItem(String text_)
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
		int fontHeight = MENU_FONT_HEIGHT;

		int w = SCREEN_WIDTH;
		int h = fontHeight;
		M5.Lcd.fillRect(x,y,w,h, isHighlighted ? MENU_ITEM_HIGHLIGHTED_BACKGROUND_COLOR : MENU_ITEM_BACKGROUND_COLOR);

		if (isHighlighted)
		{
			int iconX = 16;
			int iconY = y + (fontHeight / 2);
			int x0 = iconX - 6;
			int y0 = iconY - 6;
			int x1 = iconX - 6;
			int y1 = iconY + 6; 
			int x2 = iconX + 6;
			int y2 = iconY;
			M5.Lcd.fillTriangle(x0, y0, x1, y1, x2, y2, MENU_ITEM_HIGHLIGHTED_TEXT_COLOR);
		}

		int textX = 34;	// TODO
		M5.Lcd.setTextColor(isHighlighted ? MENU_ITEM_HIGHLIGHTED_TEXT_COLOR : MENU_ITEM_TEXT_COLOR);
		M5.Lcd.setTextDatum(TL_DATUM);
		M5.Lcd.drawString((text).c_str(), textX, y);

		dirty = false;
	}
}

