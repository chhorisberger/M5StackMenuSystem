#include "Layout.h"

#include <M5Unified.h> 


Layout::Layout()
{
	// General
	MENU_FONT = 2;
	MENU_FONT_SIZE = 2;

	// Top bar
	TOP_BAR_TITLE_COLOR = WHITE;
	TOP_BAR_BACKGROUND_COLOR = RED;
	TOP_BAR_V_PADDING = 4;

	// Center section
	MENU_ITEM_TEXT_COLOR = DARKGREY;
	MENU_ITEM_BACKGROUND_COLOR = LIGHTGREY;
	MENU_ITEM_HIGHLIGHTED_TEXT_COLOR = BLACK;
	MENU_ITEM_HIGHLIGHTED_BACKGROUND_COLOR = WHITE;
	MENU_ITEM_HIGHLIGHTED_ICON_SIZE = 6;

	// Bottom bar
	BOTTOM_BAR_BACKGROUND_COLOR = RED;
	BOTTOM_BAR_SOFTKEY_V_SPACING = 4;
	BOTTOM_BAR_SOFTKEY_V_PADDING = 0;
	BOTTOM_BAR_SOFTKEY_WIDTH_AS_FRACTION_OF_SCREEN = 5;
	BOTTOM_BAR_SOFTKEY_COLOR = WHITE;
	BOTTOM_BAR_SOFTKEY_BACKGROUND_COLOR = RED;
	BOTTOM_BAR_SOFTKEY_ICONS_SIZE = 6;
}
