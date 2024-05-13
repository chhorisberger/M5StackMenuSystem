#ifndef MENU_CENTER_SECTION_H
#define MENU_CENTER_SECTION_H

#include "Display.h"
#include "Layout.h"
#include "Control.h"
#include "MenuItem.h"

// foward declare class for backwards reference without cyclic dependency
class Menu;

class MenuCenterSection
{

public:
	MenuCenterSection(Layout& layout_, Control& control_, Display& display_, Menu* menu_);
	~MenuCenterSection();

	void render(bool force = false);
	void addItem(MenuItem* item);
	void reset();
	void setDirty();
	void loop();

	void upButtonPressed();
	void downButtonPressed();
	void okButtonPressed();
	void resetActiveMenuItem();
	MenuItem* getActiveMenuItem();

private:
	void renderMenuItems(bool force);
	
	void clear();
	void checkTouch();
	bool isAboveViewPort(MenuItem* item);
	bool isBelowViewPort(MenuItem* item);
	int getMaxMenuItemsInViewport();
	int getViewportYMax();
	int getMenuItemsStartY();
	int getMenuItemsEndY();
	int getCenterSectionHeight();
	int getMenuItemHeight();
	int getMenuItemY(MenuItem* item);
	MenuItem* getMenuItemForY(int y);
	MenuItem* getMenuItemByPos(int pos);
	int getMenuItemPosForY(int y);

	Menu* menu;
	Layout& layout;
	Display& display;
	Control& control;

	bool dirty;

	MenuItem* firstItem;
	MenuItem* lastItem;
	MenuItem* highlightedItem;
	MenuItem* activeItem;

	int viewportY;
	
};

#endif 

