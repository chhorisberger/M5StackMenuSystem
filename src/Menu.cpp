#include "Menu.h"

#include "SubMenuItem.h"
#include "MenuExitItem.h"

#include <M5Unified.h>

Menu::Menu(String title_) : control(), menuTopSection(layout, title_), menuCenterSection(layout, control, this), menuBottomSection(layout, control, this)
{
	enabled = true;
	dirty = true;
	parentMenu = NULL;
}

void Menu::init()
{
	control.init();
	layout.SCREEN_WIDTH = M5.Display.width();
	layout.SCREEN_HEIGHT = M5.Display.height();
	M5.Display.setTextFont(layout.MENU_FONT);
	M5.Display.setTextSize(layout.MENU_FONT_SIZE);
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

void Menu::setDirty()
{
	dirty = true;
	menuTopSection.setDirty();
	menuCenterSection.setDirty();
	menuBottomSection.setDirty();
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
	softKey.render();
}

bool Menu::wasSoftKeyReleased(SoftKeySlot slot)
{
	TextSoftKey softKey(slot, layout, control, "");
	return softKey.wasReleased();
}

void Menu::resetActiveMenuItem()
{
	menuCenterSection.resetActiveMenuItem();
	dirty = true;
}

void Menu::upButtonPressed()
{
	menuCenterSection.upButtonPressed();
}

void Menu::downButtonPressed()
{
	menuCenterSection.downButtonPressed();
}

void Menu::okButtonPressed()
{
	menuCenterSection.okButtonPressed();
}

void Menu::render()
{
	M5.Display.waitDisplay();

	// TODO: clean this up, only delegate to sub components 
	if (dirty)
	{
		menuCenterSection.render(true);
		menuTopSection.render(true);
		menuBottomSection.render(true);

		dirty = false;
	}
	else
	{
		menuCenterSection.render();
		menuTopSection.render();
		menuBottomSection.render();
	}

	M5.Display.display();
}

