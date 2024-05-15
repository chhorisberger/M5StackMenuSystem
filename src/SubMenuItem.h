#ifndef SUB_MENU_ITEM_H
#define SUB_MENU_ITEM_H

#include "MenuItem.h"

// foward declare class for backwards reference without cyclic dependency
class Menu;

class SubMenuItem : virtual public MenuItem
{

public:
	SubMenuItem(Layout& layout_, Display& display_, String text_, Menu* subMenu_);
	virtual ~SubMenuItem() {}
	virtual void loop();
	virtual void onAdded();
	virtual void reset();

protected:
	Menu* subMenu;

private:
	bool firstLoop;
};

#endif 

