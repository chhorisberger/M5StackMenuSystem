#include <M5Stack.h>
#include "src/M5StackMenuSystem.h"  // TODO: revert to #include <M5StackMenuSystem.h> 

Menu myMenu("Main Menu");

void setup() {
  M5.begin();
  M5.Power.begin();
 
  myMenu.addItem(new CallbackMenuItem("Menu Item #1", testOneTimeCallback));
  myMenu.addItem(new CallbackMenuItem("Menu Item #2", testOneTimeCallback));
  myMenu.addItem(new CallbackMenuItem("Menu Item #3", testOneTimeCallback));
}

void loop() {
  M5.update();
  myMenu.loop();
}

void testOneTimeCallback(CallbackMenuItem& menuItem)
{
  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextDatum(MC_DATUM);
  M5.Lcd.drawString(menuItem.getText() + " selected", 160, 120);
  delay(1000);
}
