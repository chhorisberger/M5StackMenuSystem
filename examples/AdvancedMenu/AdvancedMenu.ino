#include <M5Unified.h>
#include <M5StackMenuSystem.h> 

Menu mainMenu("Main Menu");
Menu subMenu("Sub Menu");

void setup() {
	M5.begin();
	M5.Power.begin();

	mainMenu.addMenuItem("One Time Callback", testOneTimeCallback);
	mainMenu.addMenuItem("Loop Callback", testLoopInitCallback, testLoopCallback);
	mainMenu.addSubMenu("Submenu", &subMenu);
	mainMenu.addExitItem("Exit");

	subMenu.addMenuItem("Sub Menu Item #1", testOneTimeCallback);
	subMenu.addMenuItem("Sub Menu Item #2", testOneTimeCallback);
	subMenu.addMenuItem("Sub Menu Item #3", testOneTimeCallback);
	subMenu.addMenuItem("Sub Menu Item #4", testOneTimeCallback);
	subMenu.addMenuItem("Sub Menu Item #5", testOneTimeCallback);
	subMenu.addMenuItem("Sub Menu Item #6", testOneTimeCallback);
}

void loop() {
	M5.update();

	if (mainMenu.isEnabled()) {
		mainMenu.loop(); 
	} else {
		M5.Display.clear(BLACK);
		if (M5.BtnA.wasReleased() || M5.BtnB.wasReleased() || M5.BtnC.wasReleased() || M5.Touch.getCount() > 0) {
			M5.update();
			mainMenu.enable();
		}
	}
}

void testOneTimeCallback(CallbackMenuItem& menuItem) {
	M5.Display.clear(BLACK);
	drawText("One Time Callback");
	delay(1500);
}

void testLoopInitCallback(CallbackMenuItem& menuItem) {
	M5.Display.clear(BLACK);
	drawText("Loop Callback");
	menuItem.getMenu()->displaySoftKey(BtnASlot, "Esc");
}

void testLoopCallback(CallbackMenuItem& menuItem) {
	String time = "sec: " + String(millis() / 1000);
	drawText(time);

	if (menuItem.getMenu()->wasSoftKeyReleased(BtnASlot)) 
	{
		menuItem.deactivateCallbacks();
	}
}

void drawText(String text)
{
	M5.Display.setTextColor(WHITE, BLACK);
	M5.Display.setTextFont(2);
	M5.Display.setTextSize(2);
	M5.Display.setTextDatum(MC_DATUM);
	M5.Display.drawString(text, M5.Display.width() / 2, (3 * M5.Display.height()) / 6);
}
