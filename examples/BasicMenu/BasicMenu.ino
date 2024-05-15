#include <M5Unified.h>
#include <M5StackMenuSystem.h> 

Menu myMenu("Main Menu");

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
  M5.Display.clear(BLACK);
  M5.Display.setTextColor(WHITE);
  M5.Display.setTextFont(2);
  M5.Display.setTextSize(2);
  M5.Display.setTextDatum(MC_DATUM);
  M5.Display.drawString(menuItem.getText() + " selected", 160, 120);
  delay(1000);
}
