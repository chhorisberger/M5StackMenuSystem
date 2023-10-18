# M5StackMenuSystem
A quick way to create nice menus for the neat [M5 Stack](https://github.com/m5stack/m5stack) devices with just a few lines of code

<img src="https://github.com/chhorisberger/M5StackMenuSystem/blob/main/docs/picture.jpg" width="256">

## Getting Started
Install the library using either the .zip file from the latest release or by searching for "M5StackMenuSystem" in the libraries manager of the Arduino IDE

Here's a simple sketch that shows the basic functionality:

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
## Explenation of above code

Declare a new menu instance, which will have the title "Main Menu".
```c++
Menu myMenu("Main Menu");
```

In the setup() method, add multiple items to that menu.
```c++
myMenu.addMenuItem("Menu Item #1", testOneTimeCallback);
```
The first argument "Menu Item #1" is the text that will be displayed in the menu for this item.
The second argument "testOneTimeCallback" is the function further down that will be called once when the user selects this item.

```c++
void testOneTimeCallback(CallbackMenuItem& menuItem) {
```

In this basic example all the menu items point to the same function, but in a real application you probably would want each item to point to its own designated funtion.

## Advanced Usage

WIP
