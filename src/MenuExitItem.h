#ifndef MENU_EXIT_ITEM_H
#define MENU_EXIT_ITEM_H

#include "MenuItem.h"

// foward declare class for backwards reference without cyclic dependency
class Menu;

class MenuExitItem : virtual public MenuItem
{

public:
	MenuExitItem(Menu* subMenu_);
	virtual ~MenuExitItem() {}

	virtual void loop();

private:
	Menu* subMenu;
};

#endif 

