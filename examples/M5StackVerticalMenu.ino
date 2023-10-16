#include <M5Stack.h>

#include "M5StackMenuSystem.h"

Menu mainMenu("Main Menu");
Menu subMenu("Sub Menu");

void setup() {
	M5.begin();
	M5.Power.begin();

	mainMenu.addItem(new CallbackMenuItem("One Time Callback", testOneTimeCallback));
	mainMenu.addItem(new CallbackMenuItem("Loop Callback", testLoopInitCallback, testLoopCallback));
	mainMenu.addItem(new SubMenuItem("Submenu", &subMenu));

	subMenu.addItem(new CallbackMenuItem("Sub Menu Item #1", testOneTimeCallback));
	subMenu.addItem(new CallbackMenuItem("Sub Menu Item #2", testOneTimeCallback));
	subMenu.addItem(new CallbackMenuItem("Sub Menu Item #3", testOneTimeCallback));
}

void loop() {
	M5.update();
	mainMenu.loop();
}

void testOneTimeCallback(CallbackMenuItem& menuItem)
{
	M5.Lcd.clear(BLACK);
	M5.Lcd.setTextColor(WHITE);
	M5.Lcd.setTextDatum(MC_DATUM);
	M5.Lcd.drawString("One Time Callback", M5.Lcd.width() / 2, (2 * M5.Lcd.height()) / 6);

	delay(1500);
}

void testLoopInitCallback(CallbackMenuItem& menuItem)
{
	M5.Lcd.clear(BLACK);
	M5.Lcd.setTextColor(WHITE);
	M5.Lcd.setTextDatum(MC_DATUM);
	M5.Lcd.drawString("Loop Callback", M5.Lcd.width() / 2, (2 * M5.Lcd.height()) / 6);

	TextSoftKey escapeSoftKey(BtnASlot, "Esc");
	escapeSoftKey.render(); 
}

void testLoopCallback(CallbackMenuItem& menuItem)
{
	String time = "sec: " + String(millis() / 1000);

	M5.Lcd.setTextColor(WHITE, BLACK);
	M5.Lcd.setTextDatum(MC_DATUM);
	M5.Lcd.drawString(time.c_str(), M5.Lcd.width() / 2, (3 * M5.Lcd.height()) / 6);

	if (M5.BtnA.wasReleased())
	{
		menuItem.deactivateCallbacks();
	}
}