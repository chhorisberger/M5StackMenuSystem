#include "SubMenuItem.h"

#include "Menu.h"

SubMenuItem::SubMenuItem(Layout& layout_, Display& display_, String text_, Menu* subMenu_) : MenuItem(layout_, display_, text_)
{
	subMenu = subMenu_;
}

void SubMenuItem::loop() 
{
	if (subMenu->isDirty()) 
	{
		subMenu->enable();
	}
	subMenu->loop();
}

void SubMenuItem::onAdded()
{
	subMenu->addExitItem(getMenu());
}
