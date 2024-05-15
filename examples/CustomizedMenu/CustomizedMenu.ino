#include <M5Unified.h>
#include <M5StackMenuSystem.h> 

Menu myMenu("Customized Menu");

void setup() {
	M5.begin();
	M5.Power.begin();

	myMenu.addMenuItem("Menu Item #1", testOneTimeCallback);
	myMenu.addMenuItem("Menu Item #2", testOneTimeCallback);
	myMenu.addMenuItem("Menu Item #3", testOneTimeCallback);
	myMenu.addMenuItem("Menu Item #4", testOneTimeCallback);
	myMenu.addMenuItem("Menu Item #5", testOneTimeCallback);
	myMenu.addMenuItem("Menu Item #6", testOneTimeCallback);
	myMenu.addMenuItem("Menu Item #7", testOneTimeCallback);
	myMenu.addMenuItem("Menu Item #8", testOneTimeCallback);
	myMenu.addMenuItem("Menu Item #9", testOneTimeCallback);
	myMenu.addMenuItem("Menu Item #10", testOneTimeCallback);
	myMenu.addMenuItem("Menu Item #11", testOneTimeCallback);
	myMenu.addMenuItem("Menu Item #12", testOneTimeCallback);
	myMenu.addMenuItem("Menu Item #13", testOneTimeCallback);
	myMenu.addMenuItem("Menu Item #14", testOneTimeCallback);

	customizeLayout();
}

void loop() {
	M5.update();
	myMenu.loop();
}

void customizeLayout()
{
	// customize layout
	Layout& layout = myMenu.getLayout();

	// smaller font
	layout.MENU_FONT_SIZE = 1;

	// monochrome theme
	layout.TOP_BAR_TITLE_COLOR = WHITE;
	layout.TOP_BAR_BACKGROUND_COLOR = DARKGREY;

	layout.MENU_ITEM_TEXT_COLOR = WHITE;
	layout.MENU_ITEM_BACKGROUND_COLOR = BLACK;
	layout.MENU_ITEM_HIGHLIGHTED_TEXT_COLOR = BLACK;
	layout.MENU_ITEM_HIGHLIGHTED_BACKGROUND_COLOR = WHITE;
	layout.MENU_ITEM_HIGHLIGHTED_ICON_SIZE = 3;

	layout.BOTTOM_BAR_BACKGROUND_COLOR = DARKGREY;
	layout.BOTTOM_BAR_SOFTKEY_COLOR = WHITE;
	layout.BOTTOM_BAR_SOFTKEY_BACKGROUND_COLOR = DARKGREY;

	// adjust soft keys to smaller font size
	layout.BOTTOM_BAR_SOFTKEY_V_PADDING = 3;
	layout.BOTTOM_BAR_SOFTKEY_ICONS_SIZE = 3;
}

void testOneTimeCallback(CallbackMenuItem& menuItem) {
	M5.Display.clear(BLACK);
	M5.Display.setTextColor(WHITE);
	M5.Display.setTextDatum(MC_DATUM);
	M5.Display.drawString(menuItem.getText() + " selected", 160, 120);
	delay(1000);
}
