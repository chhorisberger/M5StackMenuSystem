#include "SubMenuItem.h"

#include "Menu.h"

#ifdef M5_UNIFIED
#include <M5Unified.h>
#else
#include <M5Stack.h>
#endif

SubMenuItem::SubMenuItem(Layout& layout_, String text_, Menu* subMenu_) : MenuItem(layout_, text_)
{
	subMenu = subMenu_;
}

void SubMenuItem::loop() 
{
	if (subMenu->isDirty()) {
		subMenu->enable();
	}
	subMenu->loop();
}

void SubMenuItem::onAdded()
{
	subMenu->addExitItem(getMenu());
}
