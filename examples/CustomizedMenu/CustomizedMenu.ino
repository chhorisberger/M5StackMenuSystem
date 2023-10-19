#include <M5Stack.h>
#include "src/M5StackMenuSystem.h"	// TODO: revert to #include <M5StackMenuSystem.h> 


Menu myMenu("Customized Menu");

/*
// smaller font
myMenu.layout.MENU_FONT_SIZE = 1;

// high contrast theme
myMenu.layout.TOP_BAR_TITLE_COLOR = WHITE;
myMenu.layout.TOP_BAR_BACKGROUND_COLOR = DARKGREY;

myMenu.layout.MENU_ITEM_TEXT_COLOR = WHITE;
myMenu.layout.MENU_ITEM_BACKGROUND_COLOR = BLACK;
myMenu.layout.MENU_ITEM_HIGHLIGHTED_TEXT_COLOR = BLACK;
myMenu.layout.MENU_ITEM_HIGHLIGHTED_BACKGROUND_COLOR = WHITE;

myMenu.layout.BOTTOM_BAR_BACKGROUND_COLOR = DARKGREY;
myMenu.layout.BOTTOM_BAR_SOFTKEY_COLOR = WHITE;
myMenu.layout.BOTTOM_BAR_SOFTKEY_BACKGROUND_COLOR = DARKGREY;

// larger soft keys
myMenu.layout.BOTTOM_BAR_SOFTKEY_V_PADDING = 4;
myMenu.layout.BOTTOM_BAR_SOFTKEY_WIDTH_AS_FRACTION_OF_SCREEN = 4;
*/

void setup() {
	M5.begin();
	M5.Power.begin();

	myMenu.addMenuItem("Menu Item #1", testOneTimeCallback);
	myMenu.addMenuItem("Menu Item #2", testOneTimeCallback);
	myMenu.addMenuItem("Menu Item #3", testOneTimeCallback);
}

void loop() {
	M5.update();
	myMenu.loop();
}

void testOneTimeCallback(CallbackMenuItem& menuItem) {
	M5.Lcd.clear(BLACK);
	M5.Lcd.setTextColor(WHITE);
	M5.Lcd.setTextDatum(MC_DATUM);
	M5.Lcd.drawString(menuItem.getText() + " selected", 160, 120);
	delay(1000);
}
