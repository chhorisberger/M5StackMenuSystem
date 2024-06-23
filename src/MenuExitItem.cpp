#include "MenuExitItem.h"

#include "Menu.h"


MenuExitItem::MenuExitItem(Layout& layout_, Menu* parentMenu_, String text) : MenuItem(layout_, text)
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

