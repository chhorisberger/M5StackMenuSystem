#include "MenuExitItem.h"

#include "Menu.h"


MenuExitItem::MenuExitItem(Layout& layout_, Display& display_, Menu* parentMenu_) : MenuItem(layout_, display_, "..")
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

