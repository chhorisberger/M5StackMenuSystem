#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include "Layout.h"
#include "Display.h"

#include <Arduino.h>


// foward declare class for backwards reference without cyclic dependency
class Menu;

class MenuItem
{
public:
	MenuItem(Layout& layout_, String text_);
	virtual void loop() = 0;
	virtual void render(int x, int y, bool isHighlighted);
	virtual void onAdded();
	virtual void reset();

	MenuItem* getPrevious();
	void setPrevious(MenuItem* item);
	MenuItem* getNext();
	void setNext(MenuItem* item);
	String getText();
	void setMenu(Menu* menu_);
	Menu* getMenu();
	int getPosition();
	void setPosition(int position_);

protected:
	String text;
	Layout& layout;

private:
	Menu* menu;
	MenuItem* previousItem;
	MenuItem* nextItem;
	int position;
};

#endif 

