#ifndef MENU_H
#define MENU_H

#include "Layout.h"
#include "Control.h"
#include "MenuTopSection.h"
#include "MenuCenterSection.h"
#include "MenuBottomSection.h"
#include "MenuItem.h"
#include "CallbackMenuItem.h"

#include <Arduino.h>

class Menu
{
	typedef std::function<void(CallbackMenuItem &menuItem)> CallbackFunction;

public:
	Menu(String title_);

	/* Menu loop function (should be regularly in order to render menu and handle button presses) */
	void loop();

	/* Enable the menu */
	void enable();
	
	/* Disable the menu*/
	void disable();
	
	/* Check if the menu is currently enabled*/
	bool isEnabled();

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
	void addExitItem(String text = "..");

	/* Displays a custom soft key. Argument "slot" determines which of the three buttons the soft key should be displayed (BtnASlot, BtnDSlot or BtnCSlot). */
	void displaySoftKey(SoftKeySlot slot, String text);
	
	/* Check if the softkey at this slot was just released. Argument "slot" determines which of the three buttons the soft key should be displayed (BtnASlot, BtnDSlot or BtnCSlot).*/
	bool wasSoftKeyReleased(SoftKeySlot slot);

	/* Return a reference to the layout object, where you can tweak various display options */
	Layout& getLayout();
	
	/* Move the current menu selection up */
	void moveUpSelection();

	/* Move the current menu selection down */
	void moveDownSelection();

	/* Confirm the current menu selection */
	void confirmSelection();


private:
	void init();
	void render();

	void setParentMenu(Menu* menu);
	void resetActiveMenuItem();
	bool isDirty();
	void setDirty();

	bool initialized;
	bool enabled;
	bool dirty;
	
	MenuTopSection menuTopSection;
	MenuCenterSection menuCenterSection;
	MenuBottomSection menuBottomSection;

	Control control;
	Menu* parentMenu;
	Layout layout;

	friend class MenuBottomSection;
	friend class MenuCenterSection;
	friend class CallbackMenuItem;
	friend class MenuExitItem;
	friend class SubMenuItem;
};

#endif 

