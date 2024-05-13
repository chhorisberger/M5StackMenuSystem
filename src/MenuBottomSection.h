#ifndef MENU_BOTTOM_SECTION_H
#define MENU_BOTTOM_SECTION_H

#include "TextSoftKey.h"
#include "UpSoftKey.h"
#include "DownSoftKey.h"
#include "Display.h"
#include "Layout.h"
#include "Control.h"

#include <Arduino.h>


// foward declare class for backwards reference without cyclic dependency
class Menu;

class MenuBottomSection
{

public:
	MenuBottomSection(Layout& layout_, Control& control_, Display& display_, Menu* menu_);
	void render(bool force = false);
	void loop();
	int getHeight();
	void setDirty();

private:
	void renderBottomBar();
	void renderSoftKeys(bool force = false);

	Layout& layout;
	Display& display;

	bool dirty;
	Menu* menu;
	UpSoftKey softKeyUp;
	DownSoftKey softKeyDown;
	TextSoftKey softKeyOk;
};

#endif 

