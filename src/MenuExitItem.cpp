#include "MenuExitItem.h"

#include "Menu.h"

#ifdef M5_UNIFIED
#include <M5Unified.h>
#else
#include <M5Stack.h>
#endif

MenuExitItem::MenuExitItem(Layout& layout_, Menu* parentMenu_) : MenuItem(layout_, "..")
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

