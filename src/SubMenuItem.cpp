#include "SubMenuItem.h"

#include "Menu.h"

#include <M5Stack.h>

SubMenuItem::SubMenuItem(Layout& layout_, String text_, Menu* subMenu_) : MenuItem(layout_, text_)
{
	subMenu = subMenu_;
}

void SubMenuItem::loop() 
{
	subMenu->enable();
	subMenu->loop();
}

void SubMenuItem::onAdded()
{
	subMenu->addExitItem(getMenu());
}
