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

	/* Menu loop function (should be regularly in order to render menu and handle button presses) */
	void loop();

	/* Enable the menu */
	void enable();
	
	/* Disable the menu*/
	void disable();
	
	/* Check if the menu is currently enabled*/
	bool isEnabled();

	/* Check if the menu is currently dirty */
	bool isDirty();
	
	/* Reset the highlighted menu item to the first one*/
	void reset();

	/* Add a new menu item. 
	   Once the user selected the menu item:
	    - the function specified in callbackOneTimeFunction will be called only one time.
	    - if set, the function specified in callbackLoopFunction will be called on every call of menu.loop().
	   In order to then de-select the menu item and stop the callbacks, call menuItem.deactivateCallbacks() inside the callback function.
	*/
	void addMenuItem(String text, CallbackFunction callbackOneTimeFunction, CallbackFunction callbackLoopFunction = NULL);

	/* Add a new sub menu to the menu */
	void addSubMenu(String text, Menu* subMenu);

	/* Add an exit menu item which allows you to leave the menu or submenu */
	void addExitItem(Menu* parentMenu = NULL);

	/* Displays a custom soft key. Argument "slot" determines which of the three buttons the soft key should be displayed (BtnASlot, BtnDSlot or BtnCSlot). */
	void displaySoftKey(SoftKeySlot slot, String text);

	/* Return a reference to the layout object, where you can tweak various display options */
	Layout& getLayout();

private:
	void init();
	void addItem(MenuItem* item);
	void render();
	void clearScreen();
	void renderCenterSection(bool force = false);
	void setAllMenuItemsDirty();
	bool isAboveViewPort(MenuItem* item);
	bool isBelowViewPort(MenuItem* item);
	int getCenterSectionHeight();
	int getMaxMenuItemsInViewport();
	int getMenuItemsStartY();
	void upButtonPressed();
	void downButtonPressed();
	void okButtonPressed();
	void resetActiveMenuItem();

	bool initialized;
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

