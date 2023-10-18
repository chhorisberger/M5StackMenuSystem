#ifndef MENU_BOTTOM_SECTION_H
#define MENU_BOTTOM_SECTION_H

#include "TextSoftKey.h"
#include "UpSoftKey.h"
#include "DownSoftKey.h"
#include "Layout.h"

#include <Arduino.h>


// foward declare class for backwards reference without cyclic dependency
class Menu;

class MenuBottomSection
{

public:
	MenuBottomSection(Menu* menu_);
	void render(bool force = false);
	void checkMenuButtons();

private:
	void checkUpButton();
	void checkDownButton();
	void checkOkButton();
	void renderBottomBar();
	void renderSoftKeys(bool force = false);

	bool dirty;
	Menu* menu;
	UpSoftKey softKeyUp;
	DownSoftKey softKeyDown;
	TextSoftKey softKeyOk;
};

#endif 

