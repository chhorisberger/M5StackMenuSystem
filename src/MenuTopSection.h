#ifndef MENU_TOP_SECTION_H
#define MENU_TOP_SECTION_H

#include "Layout.h"
#include <Arduino.h>

class MenuTopSection
{

public:
	MenuTopSection(Layout& layout_, String title_);
	void render();
	void setTitle(String title_);
	int getHeight();

private:
	String title;
	Layout& layout;
};

#endif 

