#include "Menu.h"
#include "SubMenuItem.h"
#include "MenuExitItem.h"

#include <M5Unified.h>

Menu::Menu(String title_) : display(), control(), menuTopSection(layout, display, title_), menuCenterSection(layout, control, display, this), menuBottomSection(layout, control, display, this)
{
	enabled = true;
	dirty = true;
	parentMenu = NULL;
}

void Menu::init()
{
	display.init();
	control.init();
	layout.SCREEN_WIDTH = display.width();
	layout.SCREEN_HEIGHT = display.height();
	display.setTextFont(layout.MENU_FONT);
	display.setTextSize(layout.MENU_FONT_SIZE);
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
	menuCenterSection.addItem(new CallbackMenuItem(layout, display, text, callbackOneTimeFunction, callbackLoopFunction));
}

void Menu::addSubMenu(String text, Menu* subMenu)
{
	subMenu->setParentMenu(this);
	menuCenterSection.addItem(new SubMenuItem(layout, display, text, subMenu));
}

void Menu::addExitItem(Menu* parentMenu)
{
	menuCenterSection.addItem(new MenuExitItem(layout, display, parentMenu));
}

Layout& Menu::getLayout()
{
	return layout;
}

void Menu::displaySoftKey(SoftKeySlot slot, String text)
{
	TextSoftKey softKey(slot, layout, control, display, text);
	display.drawStart();
	softKey.render();
	display.drawEnd();
}

bool Menu::wasSoftKeyReleased(SoftKeySlot slot)
{
	TextSoftKey softKey(slot, layout, control, display, "");
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
		display.drawStart();
		menuCenterSection.render();
		menuTopSection.render();
		menuBottomSection.render();
		display.drawEnd();
		dirty = false;
	}
}

