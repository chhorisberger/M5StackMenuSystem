#include "SubMenuItem.h"

#include "Menu.h"

SubMenuItem::SubMenuItem(Layout& layout_, Display& display_, String text_, Menu* subMenu_) : MenuItem(layout_, display_, text_)
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
