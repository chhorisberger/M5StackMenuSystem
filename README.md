# M5StackMenuSystem
A quick way to create nice menus for the neat [M5 Stack](https://github.com/m5stack/m5stack) devices with just a few lines of code

<img src="https://github.com/chhorisberger/M5StackMenuSystem/blob/main/docs/picture.jpg" width="256">

#### Code Example

```c++
#include <M5Stack.h>
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
  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextDatum(MC_DATUM);
  M5.Lcd.drawString(menuItem.getText() + " selected", 160, 120);
  delay(1000);
}

```
