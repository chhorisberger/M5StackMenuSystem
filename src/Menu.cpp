#include "Menu.h"

#include "SubMenuItem.h"
#include "MenuExitItem.h"

#include <M5Unified.h>

Menu::Menu(String title_) : control(), menuTopSection(layout, title_), menuBottomSection(layout, control, this)
{
	enabled = true;
	dirty = true;
	firstItem = NULL;
	lastItem = NULL;
	highlightedItem = NULL;
	activeItem = NULL;
	firstItemInViewport = NULL;
	parentMenu = NULL;
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

void Menu::init()
{
	control.init();
	layout.SCREEN_WIDTH = M5.Display.width();
	layout.SCREEN_HEIGHT = M5.Display.height();
	initialized = true;
}


void Menu::enable()
{
	enabled = true;
	dirty = true;
}

void Menu::disable()
{
	enabled = false;

	if (parentMenu != NULL)
	{
		parentMenu->reset();
	}
}

bool Menu::isEnabled()
{
	return enabled;
}

bool Menu::isDirty()
{
	return dirty;
}

void Menu::reset()
{
	firstItemInViewport = firstItem;
	highlightedItem = firstItem;
	resetActiveMenuItem();
	setAllMenuItemsDirty();
}

void Menu::loop()
{
	if (!initialized)
	{
		init();
	}

	if (enabled)
	{
		control.loop();

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

void Menu::setParentMenu(Menu* menu)
{
	parentMenu = menu;
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
	subMenu->setParentMenu(this);
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

Layout& Menu::getLayout()
{
	return layout;
}

void Menu::displaySoftKey(SoftKeySlot slot, String text)
{
	TextSoftKey escapeSoftKey(slot, layout, text);
	escapeSoftKey.render();
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
	M5.Lcd.setTextFont(layout.MENU_FONT);
	M5.Lcd.setTextSize(layout.MENU_FONT_SIZE);
}

void Menu::renderCenterSection(bool force)
{
	int menuItemHeight = M5.Lcd.fontHeight(layout.MENU_FONT);
	int menuItemsStartY = getMenuItemsStartY();

	int pos = 0;
	MenuItem* item = firstItemInViewport;
	while (item != NULL && !isBelowViewPort(item))
	{
		int x = 0;
		int y = menuItemsStartY + (pos * menuItemHeight);
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
	int maxItemsInViewport = getMaxMenuItemsInViewport();
	return item->getPosition() >= firstItemInViewport->getPosition() + maxItemsInViewport;
}

int Menu::getCenterSectionHeight()
{
	int menuItemHeight = M5.Lcd.fontHeight(layout.MENU_FONT);
	int topSectionHeight = menuTopSection.getHeight();
	int bottomSectionHeight = menuBottomSection.getHeight();
	int centerSectionHeight = layout.SCREEN_HEIGHT - (topSectionHeight + bottomSectionHeight);
	return centerSectionHeight;
}

int Menu::getMaxMenuItemsInViewport()
{
	int menuItemHeight = M5.Lcd.fontHeight(layout.MENU_FONT);
	int maxItemsInViewport = getCenterSectionHeight() / menuItemHeight;
	return maxItemsInViewport;
}

int Menu::getMenuItemsStartY()
{
	int centerSectionHeight = getCenterSectionHeight();
	int maxItemsInViewport = getMaxMenuItemsInViewport();
	int menuItemHeight = M5.Lcd.fontHeight(layout.MENU_FONT);
	int remainingPixels = centerSectionHeight - (maxItemsInViewport * menuItemHeight);
	return menuTopSection.getHeight() + (remainingPixels / 2);
}


