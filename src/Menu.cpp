#include "Menu.h"


#include "SubMenuItem.h"
#include "MenuExitItem.h"

#include <M5Stack.h>

Menu::Menu(String title_) : softKeyUp(BtnASlot), softKeyDown(BtnBSlot), softKeyOk(BtnCSlot, "Ok")
{
	title = title_;

	dirty = true;
	firstItem = NULL;
	lastItem = NULL;
	highlightedItem = NULL;
	activeItem = NULL;
	firstItemInViewport = NULL;
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

void Menu::loop() 
{
	if (activeItem == NULL)
	{
		checkMenuButtons();
		render();
	}
	else
	{
		activeItem->loop();
	}
}

void Menu::resetActiveMenuItem()
{
	activeItem = NULL;
	dirty = true;
}

void Menu::addMenuItem(String text, CallbackFunction callbackOneTimeFunction, CallbackFunction callbackLoopFunction)
{
	addItem(new CallbackMenuItem(text, callbackOneTimeFunction, callbackLoopFunction));
}

void Menu::addSubMenu(String text, Menu* subMenu)
{
	addItem(new SubMenuItem(text, subMenu));
}

void Menu::addExitItem(Menu* parentMenu)
{
	addItem(new MenuExitItem(parentMenu));
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

void Menu::checkMenuButtons()
{
	checkUpButton();
	checkDownButton();
	checkOkButton();
}

void Menu::checkUpButton()
{
	if (M5.BtnA.wasPressed())
	{
		softKeyUp.setPressed(true);
	}
	else if (M5.BtnA.wasReleased())
	{
		softKeyUp.setPressed(false);

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
}

void Menu::checkDownButton()
{
	if (M5.BtnB.wasPressed())
	{
		softKeyDown.setPressed(true);
	}
	else if (M5.BtnB.wasReleased())
	{
		softKeyDown.setPressed(false);

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
}

void Menu::checkOkButton()
{
	if (M5.BtnC.wasPressed())
	{
		softKeyOk.setPressed(true);
	}
	else if (M5.BtnC.wasReleased())
	{
		softKeyOk.setPressed(false);
		activeItem = highlightedItem;
	}
}

void Menu::render()
{
	if (dirty)
	{
		clearScreen();

		renderTopSection();
		renderBottomSection();

		renderCenterSection(true);
		renderSoftKeys(true);
		dirty = false;
	}

	renderCenterSection();
	renderSoftKeys();
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

void Menu::clearScreen()
{
	M5.Lcd.clear(CENTER_BACKGROUND_COLOR);
	M5.Lcd.setTextSize(2);
	M5.Lcd.setTextFont(MY_FONT);
}

void Menu::renderTopSection()
{
	int barW = M5.Lcd.width();
	int barH = M5.Lcd.fontHeight(MY_FONT) + (2 * V_PADDING_TOP_SECTION);
	M5.Lcd.fillRect(0, 0, barW, barH, TOP_BAR_BACKGROUND_COLOR);

	M5.Lcd.setTextColor(TOP_BAR_TITLE_COLOR);
	M5.Lcd.setTextDatum(TC_DATUM);
	M5.Lcd.drawString((title).c_str(), M5.Lcd.width() / 2, V_PADDING_TOP_SECTION);
}

void Menu::renderCenterSection(bool force)
{
	int fontHeight = M5.Lcd.fontHeight(MY_FONT);
	int titleHeight = fontHeight + (2 * V_PADDING_TOP_SECTION);

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

bool Menu::isAboveViewPort(MenuItem* item)
{
	return item->getPosition() < firstItemInViewport->getPosition();
}

bool Menu::isBelowViewPort(MenuItem* item)
{
	return item->getPosition() >= firstItemInViewport->getPosition() + NR_VISIBLE_MENU_ITEMS;
}

void Menu::renderBottomSection()
{
	int barW = M5.Lcd.width() / 5;
	int barH = M5.Lcd.fontHeight(MY_FONT) + (2 * V_PADDING_BOTTOM_SECTION);
	int barY = M5.Lcd.height() - barH;
	int paddingSide = barW / 2;

	M5.Lcd.fillRoundRect(0, barY, M5.Lcd.width(), barH, 3, BOTTOM_BAR_BACKGROUND_COLOR);

	renderSoftKeys();
}

void Menu::renderSoftKeys( bool force)
{
	softKeyUp.render(force);
	softKeyDown.render(force);
	softKeyOk.render(force);
}
