#include "MenuExitItem.h"

#include "Menu.h"

#include <M5Stack.h>

MenuExitItem::MenuExitItem(Menu* parentMenu_) : MenuItem(MENU_EXIT_ITEM_TEXT)
{
	parentMenu = parentMenu_;
}

void MenuExitItem::loop()
{
	getMenu()->reset();
	getMenu()->disable();

	if (parentMenu != NULL)
	{
		parentMenu->resetActiveMenuItem();
	}
}

