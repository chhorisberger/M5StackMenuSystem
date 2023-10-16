#include "MenuExitItem.h"

#include "Menu.h"

#include <M5Stack.h>

MenuExitItem::MenuExitItem(Menu* subMenu_) : MenuItem("..")
{
	subMenu = subMenu_;
}

void MenuExitItem::loop()
{
	subMenu->resetActiveMenuItem();
	getMenu()->resetActiveMenuItem();
}

