#include "SubMenuItem.h"

#include "Menu.h"

#include <M5Stack.h>

SubMenuItem::SubMenuItem(String text_, Menu* subMenu_) : MenuItem(text_)
{
	subMenu = subMenu_;
}

void SubMenuItem::loop() 
{
	subMenu->loop();
}

void SubMenuItem::onAdded()
{
	subMenu->addExitItem(getMenu());
}
