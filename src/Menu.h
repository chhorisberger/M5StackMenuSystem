#ifndef MENU_H
#define MENU_H

#include "MenuItem.h"
#include "CallbackMenuItem.h"
#include "TextSoftKey.h"
#include "UpSoftKey.h"
#include "DownSoftKey.h"

#include <Arduino.h>

#define TOP_BAR_TITLE_COLOR WHITE
#define TOP_BAR_BACKGROUND_COLOR RED

#define CENTER_BACKGROUND_COLOR LIGHTGREY

#define BOTTOM_BAR_BACKGROUND_COLOR RED

#define V_PADDING_TOP_SECTION 4
#define V_PADDING_BOTTOM_SECTION 4

#define NR_VISIBLE_MENU_ITEMS 5



class Menu
{
	typedef std::function<void(CallbackMenuItem &menuItem)> CallbackFunction;


public:
	Menu(String title_);
	~Menu();
	void loop();
	void addMenuItem(String text, CallbackFunction callbackOneTimeFunction, CallbackFunction callbackLoopFunction = NULL);
	void addExitItem(Menu* parentMenu);
	void addSubMenu(String text, Menu* subMenu);
	void resetActiveMenuItem();
	

private:
	void addItem(MenuItem* item);
	void checkMenuButtons();
	void checkUpButton();
	void checkDownButton();
	void checkOkButton();

	void render();
	void clearScreen();
	void renderTopSection();
	void renderCenterSection(bool force = false);
	void renderBottomSection();
	void renderSoftKeys(bool force = false);
	void setAllMenuItemsDirty();

	bool dirty;
	String title;
	MenuItem* firstItem;
	MenuItem* lastItem;
	MenuItem* highlightedItem;
	MenuItem* activeItem;
	int displayPosition;

	UpSoftKey softKeyUp;
	DownSoftKey softKeyDown;
	TextSoftKey softKeyOk;
};

#endif 

