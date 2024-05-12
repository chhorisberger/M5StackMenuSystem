#ifndef MENU_TOP_SECTION_H
#define MENU_TOP_SECTION_H

#include "Layout.h"

#include <Arduino.h>

class MenuTopSection
{

public:
	MenuTopSection(Layout& layout_, String title_);
	void render(bool force = false);
	void setTitle(String title_);
	int getHeight();
	void setDirty();

private:
	bool dirty;
	String title;
	Layout& layout;
};

#endif 

