#include "MenuExitItem.h"

#include "Menu.h"

#include <M5Stack.h>

MenuExitItem::MenuExitItem(Menu* parentMenu_) : MenuItem("..")
{
	parentMenu = parentMenu_;
}

void MenuExitItem::loop()
{
	getMenu()->resetActiveMenuItem();
	getMenu()->disable();

	if (parentMenu != NULL)
	{
		parentMenu->resetActiveMenuItem();
	}
}

