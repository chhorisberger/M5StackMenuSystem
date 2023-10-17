#ifndef MENU_TOP_SECTION_H
#define MENU_TOP_SECTION_H

#include <Arduino.h>


#define TOP_BAR_TITLE_COLOR WHITE
#define TOP_BAR_BACKGROUND_COLOR RED
#define V_PADDING_TOP_SECTION 4
#define MY_FONT 2


class MenuTopSection
{

public:
	MenuTopSection(String title_);
	void render(bool force = false);
	void setTitle(String title_);

private:

	bool dirty;
	String title;
};

#endif 

