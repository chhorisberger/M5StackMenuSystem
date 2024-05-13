#include "MenuCenterSection.h"

#include "Menu.h"

#include <M5Unified.h>

MenuCenterSection::MenuCenterSection(Layout& layout_, Control& control_, Menu* menu_) : layout(layout_), control(control_)
{
	menu = menu_;
	setDirty();

	firstItem = NULL;
	lastItem = NULL;
	highlightedItem = NULL;
	activeItem = NULL;
	viewportY = 0;
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
	viewportY = 0;
	highlightedItem = firstItem;
	resetActiveMenuItem();
	setDirty();
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
				viewportY -= getMenuItemHeight();
				menu->setDirty();
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
				viewportY += getMenuItemHeight();
				menu->setDirty();
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
		if(force)
		{
			clear();
		}
		
		renderMenuItems(force);
		dirty = false;
	}
}

void MenuCenterSection::renderMenuItems(bool force)
{
	int menuItemHeight = M5.Display.fontHeight(layout.MENU_FONT);
	int menuItemsStartY = getMenuItemsStartY();

	MenuItem* item = firstItem;
	while (item != NULL)
	{
		if (isBelowViewPort(item))
		{
			break;
		}
		
		if (!isAboveViewPort(item))
		{
			int x = 0;
			int y = getMenuItemY(item);
			item->render(x, y, item == highlightedItem, force);


		item = item->getNext();
	}

}

void MenuCenterSection::setDirty()
{
	MenuItem* item = firstItem;
	while (item != NULL)
	{
		item->setDirty();
		item = item->getNext();
	}
}

void MenuCenterSection::loop()
{
	checkTouch();
}

void MenuCenterSection::checkTouch()
{
	int nrTouchEvents = control.getNrTouchEvents();
	TouchEvent* touchEvents = control.getTouchEvents();
	for (std::size_t i = 0; i < nrTouchEvents; i++)
	{
		TouchEvent touchEvent = touchEvents[i];
		if (touchEvent.released) // is this was released?
		{
			// TODO click menu?
		}
		else
		{
			int y = touchEvent.y;
			if (y > getMenuItemsStartY() && y < getMenuItemsEndY())
			{
				int viewportYNew = viewportY - touchEvent.dy;
				int viewportYMax = getViewportYMax();
				viewportYNew = constrain(viewportYNew, 0, viewportYMax);
				if (viewportYNew != viewportY)
				{
					viewportY = viewportYNew;
					menu->setDirty();
				}
			}
		}
	}
}

void MenuCenterSection::clear()
{
	int y = getMenuItemsStartY();
	int h = getCenterSectionHeight();
	M5.Display.fillRect(0, y, layout.SCREEN_WIDTH, h, layout.MENU_ITEM_BACKGROUND_COLOR);
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
	return  getMenuItemY(item) < getMenuItemsStartY();
}

bool MenuCenterSection::isBelowViewPort(MenuItem* item)
{
	return getMenuItemY(item) >= getMenuItemsEndY();
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
	int menuItemHeight = getMenuItemHeight();
	int remainingPixels = centerSectionHeight - (maxItemsInViewport * menuItemHeight);
	return menu->menuTopSection.getHeight() + (remainingPixels / 2);
}

int MenuCenterSection::getMenuItemsEndY()
{
	return getMenuItemsStartY() + getCenterSectionHeight();
}

int MenuCenterSection::getMaxMenuItemsInViewport()
{
	return getCenterSectionHeight() / getMenuItemHeight();
}

int MenuCenterSection::getMenuItemHeight()
{
	return M5.Display.fontHeight(layout.MENU_FONT);
}

int MenuCenterSection::getMenuItemY(MenuItem* item)
{
	return getMenuItemsStartY() + (item->getPosition() * getMenuItemHeight()) - viewportY;
}

int MenuCenterSection::getMenuItemPosForY(int y)
{
	return (y + viewportY) / getMenuItemHeight();
}

int MenuCenterSection::getViewportYMax()
{
	int viewportYMax = ((lastItem->getPosition() + 1) - getMaxMenuItemsInViewport()) * getMenuItemHeight();
	return (viewportYMax > 0) ? viewportYMax : 0;
}
