#include "SubMenuItem.h"

#include "Menu.h"

SubMenuItem::SubMenuItem(Layout& layout_, String text_, Menu* subMenu_) : MenuItem(layout_, text_)
{
	subMenu = subMenu_;
	firstLoop = true;
}

void SubMenuItem::loop() 
{
	if (firstLoop)
	{
		subMenu->enable();
		firstLoop = false;
	}

	subMenu->loop();
}

void SubMenuItem::onAdded()
{
	subMenu->addExitItem(getMenu());
}

void SubMenuItem::reset()
{
	firstLoop = true;
}
