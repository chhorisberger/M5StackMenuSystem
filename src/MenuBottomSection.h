#ifndef MENU_BOTTOM_SECTION_H
#define MENU_BOTTOM_SECTION_H

#include "TextSoftKey.h"
#include "UpSoftKey.h"
#include "DownSoftKey.h"
#include "Layout.h"
#include "Control.h"

#include <Arduino.h>


// foward declare class for backwards reference without cyclic dependency
class Menu;

class MenuBottomSection
{

public:
	MenuBottomSection(Layout& layout_, Control& control_, Menu* menu_);
	void render(bool force = false);
	void checkMenuButtons();
	int getHeight();
	void setDirty();

private:
	void renderBottomBar();
	void renderSoftKeys(bool force = false);

	Layout& layout;
	bool dirty;
	Menu* menu;
	UpSoftKey softKeyUp;
	DownSoftKey softKeyDown;
	TextSoftKey softKeyOk;
};

#endif 

