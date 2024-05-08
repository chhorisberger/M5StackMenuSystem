#include "MenuCenterSection.h"

#include "Menu.h"

#include <M5Unified.h>

MenuCenterSection::MenuCenterSection(Layout& layout_, Control& control_, Menu* menu_) : layout(layout_), control(control_)
{
	menu = menu_;
	dirty = true;

	firstItem = NULL;
	lastItem = NULL;
	highlightedItem = NULL;
	activeItem = NULL;
	firstItemInViewport = NULL;
}

MenuCenterSection::~MenuCenterSection()
{
	MenuItem* item = firstItem;
	while (item != NULL)
	{
		MenuItem* next = item->getNext();
		delete item;
		item = next;
	}
}

void MenuCenterSection::reset()
{
	firstItemInViewport = firstItem;
	highlightedItem = firstItem;
	resetActiveMenuItem();
	setAllMenuItemsDirty();
}

void MenuCenterSection::addItem(MenuItem* item)
{
	item->setMenu(menu);
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

void MenuCenterSection::upButtonPressed()
{
	dirty = true;

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

void MenuCenterSection::downButtonPressed()
{
	dirty = true;

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

void MenuCenterSection::okButtonPressed()
{
	activeItem = highlightedItem;
}

void MenuCenterSection::render(bool force)
{
	if (dirty || force)
	{
		renderMenuItems(force);
		dirty = false;
	}
}

void MenuCenterSection::renderMenuItems(bool force)
{
	int menuItemHeight = M5.Lcd.fontHeight(layout.MENU_FONT);
	int menuItemsStartY = getMenuItemsStartY();

	// TODO: instead use viewportYOffset and compare to 
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

void MenuCenterSection::setAllMenuItemsDirty()
{
	MenuItem* item = firstItem;
	while (item != NULL)
	{
		item->setDirty();
		item = item->getNext();
	}
}

MenuItem* MenuCenterSection::getActiveMenuItem()
{
	return activeItem;
}

void MenuCenterSection::resetActiveMenuItem()
{
	activeItem = NULL;
	dirty = true;
}

bool MenuCenterSection::isAboveViewPort(MenuItem* item)
{
	return item->getPosition() < firstItemInViewport->getPosition();
}

bool MenuCenterSection::isBelowViewPort(MenuItem* item)
{
	int maxItemsInViewport = getMaxMenuItemsInViewport();
	return item->getPosition() >= firstItemInViewport->getPosition() + maxItemsInViewport;
}

int MenuCenterSection::getCenterSectionHeight()
{
	int topSectionHeight = menu->menuTopSection.getHeight();
	int bottomSectionHeight = menu->menuBottomSection.getHeight();
	int centerSectionHeight = layout.SCREEN_HEIGHT - (topSectionHeight + bottomSectionHeight);
	return centerSectionHeight;
}

int MenuCenterSection::getMenuItemsStartY()
{
	int centerSectionHeight = getCenterSectionHeight();
	int maxItemsInViewport = getMaxMenuItemsInViewport();
	int menuItemHeight = M5.Lcd.fontHeight(layout.MENU_FONT);
	int remainingPixels = centerSectionHeight - (maxItemsInViewport * menuItemHeight);
	return menu->menuTopSection.getHeight() + (remainingPixels / 2);
}

int MenuCenterSection::getMaxMenuItemsInViewport()
{
	int menuItemHeight = M5.Lcd.fontHeight(layout.MENU_FONT);
	int maxItemsInViewport = getCenterSectionHeight() / menuItemHeight;
	return maxItemsInViewport;
}
