#ifndef MENU_CENTER_SECTION_H
#define MENU_CENTER_SECTION_H

#include "Layout.h"
#include "Control.h"
#include "MenuItem.h"

// foward declare class for backwards reference without cyclic dependency
class Menu;

class MenuCenterSection
{

public:
	MenuCenterSection(Layout& layout_, Control& control_, Menu* menu_);
	~MenuCenterSection();

	void render(bool force = false);
	void addItem(MenuItem* item);
	void reset();

	void upButtonPressed();
	void downButtonPressed();
	void okButtonPressed();
	void resetActiveMenuItem();
	MenuItem* getActiveMenuItem();

private:
	void renderMenuItems(bool force);
	void setAllMenuItemsDirty();

	bool isAboveViewPort(MenuItem* item);
	bool isBelowViewPort(MenuItem* item);

	int getMenuItemsStartY();
	int getCenterSectionHeight();
	int getMaxMenuItemsInViewport();

	Menu* menu;
	Layout& layout;
	Control& control;
	bool dirty;

	MenuItem* firstItem;
	MenuItem* lastItem;
	MenuItem* highlightedItem;
	MenuItem* activeItem;
	MenuItem* firstItemInViewport;

	int height;
	
};

#endif 

