#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <Arduino.h>




// foward declare class for backwards reference without cyclic dependency
class Menu;

class MenuItem
{
public:
	MenuItem(String text_);
	virtual void loop() = 0;
	virtual void render(int x, int y, bool isHighlighted, bool force = false);
	virtual void onAdded();

	MenuItem* getPrevious();
	void setPrevious(MenuItem* item);
	MenuItem* getNext();
	void setNext(MenuItem* item);
	void setDirty();
	String getText();
	void setMenu(Menu* menu_);
	Menu* getMenu();
	int getPosition();
	void setPosition(int position_);

protected:
	String text;
	bool dirty;

private:
	Menu* menu;
	MenuItem* previousItem;
	MenuItem* nextItem;
	int position;
};

#endif 

