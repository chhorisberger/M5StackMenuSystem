#ifndef MENU_H
#define MENU_H

#include "Layout.h"
#include "MenuTopSection.h"
#include "MenuBottomSection.h"
#include "MenuItem.h"
#include "CallbackMenuItem.h"

#include <Arduino.h>

class Menu
{
	typedef std::function<void(CallbackMenuItem &menuItem)> CallbackFunction;

public:
	Menu(String title_);
	~Menu();

	void loop();
	void enable();
	void disable();
	bool isEnabled();
	void reset();

	void addMenuItem(String text, CallbackFunction callbackOneTimeFunction, CallbackFunction callbackLoopFunction = NULL);
	void addSubMenu(String text, Menu* subMenu);
	void addExitItem(Menu* parentMenu = NULL);

private:
	void addItem(MenuItem* item);
	void render();
	void clearScreen();
	void renderCenterSection(bool force = false);
	void setAllMenuItemsDirty();
	bool isAboveViewPort(MenuItem* item);
	bool isBelowViewPort(MenuItem* item);
	void upButtonPressed();
	void downButtonPressed();
	void okButtonPressed();
	void resetActiveMenuItem();
	void setDefaultLayout();

	bool enabled;
	bool dirty;
	MenuItem* firstItem;
	MenuItem* lastItem;
	MenuItem* highlightedItem;
	MenuItem* activeItem;
	MenuItem* firstItemInViewport;
	MenuTopSection menuTopSection;
	MenuBottomSection menuBottomSection;
	Layout layout;

	friend class MenuBottomSection;
	friend class CallbackMenuItem;
	friend class MenuExitItem;
};

#endif 

