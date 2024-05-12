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
	void setDirty();

	void upButtonPressed();
	void downButtonPressed();
	void okButtonPressed();
	void resetActiveMenuItem();
	MenuItem* getActiveMenuItem();

private:
	void renderMenuItems(bool force);
	

	bool isAboveViewPort(MenuItem* item);
	bool isBelowViewPort(MenuItem* item);
	int getMaxMenuItemsInViewport();
	int getMenuItemsStartY();
	int getMenuItemsEndY();
	int getCenterSectionHeight();
	int getMenuItemHeight();
	int getMenuItemY(MenuItem* item);
	int getMenuItemPosForY(int y);


	Menu* menu;
	Layout& layout;
	Control& control;
	bool dirty;

	MenuItem* firstItem;
	MenuItem* lastItem;
	MenuItem* highlightedItem;
	MenuItem* activeItem;

	int viewportY;
	
};

#endif 

