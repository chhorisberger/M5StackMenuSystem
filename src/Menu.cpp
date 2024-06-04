#include "Menu.h"
#include "SubMenuItem.h"
#include "MenuExitItem.h"
#include "BufferedDisplay.h"

#include <M5Unified.h>

Menu::Menu(String title_) : control(), menuTopSection(layout, title_), menuCenterSection(layout, control, this), menuBottomSection(layout, control, this)
{
	enabled = true;
	dirty = true;
	initialized = false;
	parentMenu = NULL;
}

void Menu::init()
{
	control.init();

	layout.SCREEN_WIDTH = Display::getInstance()->width();
	layout.SCREEN_HEIGHT = Display::getInstance()->height();

	Display::getInstance()->setTextFont(layout.MENU_FONT);
	Display::getInstance()->setTextSize(layout.MENU_FONT_SIZE);
	initialized = true;
}

void Menu::enable()
{
	enabled = true;
	setDirty();
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

void Menu::setDirty()
{
	dirty = true;
}

bool Menu::isDirty()
{
	return dirty;
}

void Menu::reset()
{
	menuCenterSection.reset();
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

		MenuItem* activeItem = menuCenterSection.getActiveMenuItem();

		if (activeItem == NULL)
		{
			menuCenterSection.loop();
			menuBottomSection.loop();
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

void Menu::addMenuItem(String text, CallbackFunction callbackOneTimeFunction, CallbackFunction callbackLoopFunction)
{
	menuCenterSection.addItem(new CallbackMenuItem(layout, text, callbackOneTimeFunction, callbackLoopFunction));
}

void Menu::addSubMenu(String text, Menu* subMenu)
{
	subMenu->setParentMenu(this);
	menuCenterSection.addItem(new SubMenuItem(layout, text, subMenu));
}

void Menu::addExitItem(Menu* parentMenu)
{
	menuCenterSection.addItem(new MenuExitItem(layout, parentMenu));
}

Layout& Menu::getLayout()
{
	return layout;
}

void Menu::displaySoftKey(SoftKeySlot slot, String text)
{
	TextSoftKey softKey(slot, layout, control, text);
	Display::getInstance()->drawStart();
	softKey.render();
	Display::getInstance()->drawEnd();
}

bool Menu::wasSoftKeyReleased(SoftKeySlot slot)
{
	TextSoftKey softKey(slot, layout, control, "");
	return softKey.wasReleased();
}

void Menu::resetActiveMenuItem()
{
	menuCenterSection.resetActiveMenuItem();
	setDirty();
}

void Menu::upButtonPressed()
{
	menuCenterSection.upButtonPressed();
	setDirty();
}

void Menu::downButtonPressed()
{
	menuCenterSection.downButtonPressed();
	setDirty();
}

void Menu::okButtonPressed()
{
	menuCenterSection.okButtonPressed();
	setDirty();
}

void Menu::render()
{
	if (isDirty())
	{
		Display::getInstance()->drawStart();
		menuCenterSection.render();
		menuTopSection.render();
		menuBottomSection.render();
		Display::getInstance()->drawEnd();
		dirty = false;
	}
}

