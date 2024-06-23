#ifndef MENU_EXIT_ITEM_H
#define MENU_EXIT_ITEM_H

#include "MenuItem.h"
#include "Layout.h"

// foward declare class for backwards reference without cyclic dependency
class Menu;

class MenuExitItem : virtual public MenuItem
{

public:
	MenuExitItem(Layout& layout_, Menu* parentMenu_, String text);
	virtual ~MenuExitItem() {}

	virtual void loop();

private:
	Menu* parentMenu;
};

#endif 

