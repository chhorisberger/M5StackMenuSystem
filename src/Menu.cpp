#include "Menu.h"

#include "SubMenuItem.h"
#include "MenuExitItem.h"

#include <M5Stack.h>

Menu::Menu(String title_) : menuTopSection(layout, title_), menuBottomSection(layout, this)
{
	enabled = true;
	dirty = true;
	firstItem = NULL;
	lastItem = NULL;
	highlightedItem = NULL;
	activeItem = NULL;
	firstItemInViewport = NULL;

	setDefaultLayout();
}

Menu::~Menu()
{
	MenuItem* item = firstItem;
	while (item != NULL)
	{
		MenuItem* next = item->getNext();
		delete item;
		item = next;
	}
}

void Menu::setDefaultLayout()
{
	// GENERAL
	layout.SCREEN_WIDTH = M5.Lcd.height();
	layout.SCREEN_HEIGHT = M5.Lcd.width();
	layout.MENU_FONT = 2;
	layout.MENU_FONT_SIZE = 2;

	// --- TOP ---
	layout.TOP_BAR_TITLE_COLOR = WHITE;
	layout.TOP_BAR_BACKGROUND_COLOR = RED;
	layout.TOP_BAR_V_PADDING = 4;

	// --- CENTER ---
	layout.MENU_ITEM_TEXT_COLOR = DARKGREY;
	layout.MENU_ITEM_BACKGROUND_COLOR = LIGHTGREY;
	layout.MENU_ITEM_HIGHLIGHTED_TEXT_COLOR = BLACK;
	layout.MENU_ITEM_HIGHLIGHTED_BACKGROUND_COLOR = WHITE;

	// --- BOTTOM ---
	layout.BOTTOM_BAR_BACKGROUND_COLOR = RED;
	layout.BOTTOM_BAR_SOFTKEY_V_SPACING = 4;
	layout.BOTTOM_BAR_SOFTKEY_V_PADDING = 0;
	layout.BOTTOM_BAR_SOFTKEY_WIDTH_AS_FRACTION_OF_SCREEN = 5;
	layout.BOTTOM_BAR_SOFTKEY_COLOR = WHITE;
	layout.BOTTOM_BAR_SOFTKEY_BACKGROUND_COLOR = RED;

	M5.Lcd.setTextFont(layout.MENU_FONT);
	M5.Lcd.setTextSize(layout.MENU_FONT_SIZE);
}

void Menu::enable()
{
	enabled = true;
}

void Menu::disable()
{
	enabled = false;
}

bool Menu::isEnabled()
{
	return enabled;
}

void Menu::reset()
{
	firstItemInViewport = firstItem;
	highlightedItem = firstItem;
	activeItem = NULL;
	dirty = true;
	setAllMenuItemsDirty();
}

void Menu::loop()
{
	if (enabled)
	{
		if (activeItem == NULL)
		{
			menuBottomSection.checkMenuButtons();
			render();
		}
		else
		{
			activeItem->loop();
		}
	}
}

void Menu::resetActiveMenuItem()
{
	activeItem = NULL;
	dirty = true;
}

void Menu::addMenuItem(String text, CallbackFunction callbackOneTimeFunction, CallbackFunction callbackLoopFunction)
{
	addItem(new CallbackMenuItem(layout, text, callbackOneTimeFunction, callbackLoopFunction));
}

void Menu::addSubMenu(String text, Menu* subMenu)
{
	addItem(new SubMenuItem(layout, text, subMenu));
}

void Menu::addExitItem(Menu* parentMenu)
{
	addItem(new MenuExitItem(layout, parentMenu));
}

void Menu::addItem(MenuItem* item)
{
	item->setMenu(this);
	item->setPosition((lastItem == NULL) ? 0 : lastItem->getPosition() + 1);

	if (firstItem == NULL)
	{
		item->setNext(item);

		firstItem = item;
		lastItem = item;

		highlightedItem = item;
		firstItemInViewport = item;
	}
	else
	{
		lastItem->setNext(item);

		item->setPrevious(lastItem);

		lastItem = item;
	}

	item->onAdded();
}


void Menu::upButtonPressed()
{
	if (highlightedItem != NULL)
	{
		MenuItem* previousItem = highlightedItem->getPrevious();
		if (previousItem != NULL)
		{
			highlightedItem->setDirty();
			previousItem->setDirty();

			highlightedItem = previousItem;

			if (isAboveViewPort(highlightedItem))
			{
				firstItemInViewport = firstItemInViewport->getPrevious();
				setAllMenuItemsDirty();
			}
		}
	}
}

void Menu::downButtonPressed()
{
	if (highlightedItem != NULL)
	{
		MenuItem* nextItem = highlightedItem->getNext();
		if (nextItem != NULL)
		{
			highlightedItem->setDirty();
			nextItem->setDirty();

			highlightedItem = nextItem;

			if (isBelowViewPort(highlightedItem))
			{
				firstItemInViewport = firstItemInViewport->getNext();
				setAllMenuItemsDirty();
			}
		}
	}
}

void Menu::okButtonPressed()
{
	activeItem = highlightedItem;
}

void Menu::render()
{
	if (dirty)
	{
		clearScreen();

		menuTopSection.render(true);
		renderCenterSection(true);
		menuBottomSection.render(true);

		dirty = false;
	}
	else
	{
		menuTopSection.render();
		renderCenterSection();
		menuBottomSection.render();
	}
}

void Menu::clearScreen()
{
	M5.Lcd.clear(layout.MENU_ITEM_BACKGROUND_COLOR);
}

void Menu::renderCenterSection(bool force)
{
	int fontHeight = M5.Lcd.fontHeight(layout.MENU_FONT);
	int titleHeight = fontHeight + (2 * layout.TOP_BAR_V_PADDING);

	int pos = 0;
	MenuItem* item = firstItemInViewport;
	while (item != NULL && !isBelowViewPort(item))
	{
		int x = 0;
		int y = titleHeight + (pos * fontHeight);
		item->render(x, y, item == highlightedItem, force);
		pos++;

		item = item->getNext();
	}
}

void Menu::setAllMenuItemsDirty()
{
	MenuItem* item = firstItem;
	while (item != NULL)
	{
		item->setDirty();
		item = item->getNext();
	}
}

bool Menu::isAboveViewPort(MenuItem* item)
{
	return item->getPosition() < firstItemInViewport->getPosition();
}

bool Menu::isBelowViewPort(MenuItem* item)
{
	int fontHeight = M5.Lcd.fontHeight(layout.MENU_FONT);
	int topSectionHeight = (2 * layout.TOP_BAR_V_PADDING) + fontHeight;
	int bottomSectionHeight = (2 * layout.BOTTOM_BAR_SOFTKEY_V_SPACING) + fontHeight;
	int maxItemsInViewport = (layout.SCREEN_HEIGHT - (topSectionHeight + topSectionHeight)) / fontHeight;
	return item->getPosition() >= firstItemInViewport->getPosition() + maxItemsInViewport;
}


