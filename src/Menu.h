#ifndef MENU_H
#define MENU_H

#include "MenuTopSection.h"
#include "MenuBottomSection.h"
#include "MenuItem.h"
#include "CallbackMenuItem.h"

#include <Arduino.h>

#define CENTER_BACKGROUND_COLOR LIGHTGREY
#define NR_VISIBLE_MENU_ITEMS 5


class Menu
{
	typedef std::function<void(CallbackMenuItem &menuItem)> CallbackFunction;

public:
	Menu(String title_);
	~Menu();
	void loop();

	void addMenuItem(String text, CallbackFunction callbackOneTimeFunction, CallbackFunction callbackLoopFunction = NULL);
	void addSubMenu(String text, Menu* subMenu);
	void addExitItem(Menu* parentMenu);

	void resetActiveMenuItem();

	void upButtonPressed();
	void downButtonPressed();
	void okButtonPressed();

private:
	void addItem(MenuItem* item);
	void render();
	void clearScreen();
	void renderCenterSection(bool force = false);
	void setAllMenuItemsDirty();
	bool isAboveViewPort(MenuItem* item);
	bool isBelowViewPort(MenuItem* item);

	bool dirty;
	MenuItem* firstItem;
	MenuItem* lastItem;
	MenuItem* highlightedItem;
	MenuItem* activeItem;
	MenuItem* firstItemInViewport;
	MenuTopSection menuTopSection;
	MenuBottomSection menuBottomSection;
};

#endif 

