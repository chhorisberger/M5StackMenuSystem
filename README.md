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
## Explanation of above code

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

Beside the basic functionality shown above, there are additional options that are showcased in the example "AdvancedMenu" that ships with the library.

### Sub Menus

To create a sub menu, just declare a second menu and then add it to the main menu using the "addSubMenu" function.

```c++
Menu subMenu("Sub Menu");
```

```c++
mainMenu.addSubMenu("Submenu", &subMenu);
```
Adding menu items to the sub menu works the same as adding menu items to the main menu

```c++
subMenu.addMenuItem("Sub Menu Item #1", testOneTimeCallback);
```

### Exit Items

When adding a sub menu, a "exit item" will be automatically added in order to be able to get back to the main menu.

It is also possible to add such an "exit item" to the main menu, in order to leave the main menu as completly.

```c++
mainMenu.addExitItem();
```
I you want to re-enter the main menu, just run 

```c++
mainMenu.enable();
```

Be aware this only works if "mainMenu.loop()" is still called in the Arduino "loop()" method.


### Loop Callbacks

When calling "myMenu.addMenuItem" you can pass a "loop callback" function as a third argument.

```c++
mainMenu.addMenuItem("Loop Callback", testLoopInitCallback, testLoopCallback);
```
This function will be then called automatically on every invocation of "mainMenu.loop()".

Be aware this only works if "mainMenu.loop()" is actually called in the Arduino "loop()" method.

If you want the invocations of "loop callback" function to stop, just call the following inside the function: 

```c++
menuItem.deactivateCallbacks();
```

Check out the example "AdvancedMenu" that ships with the library to see how this all fits together.

### Custom Softkeys outside of menu

Inside a "loop callback" function, you can display custom soft keys (the virtual buttons displayed on the screen above the physical buttons of the M5 Stack device) .

```c++
TextSoftKey exampleSoftKey(BtnASlot, "Foo");
exampleSoftKey.render(); 
```
The first argument "BtnASlot" determines in which of the 3 slots the soft key should be displayed (A, B or C).

The second argument "Foo" determines the text displayed in the soft key. Be aware that only about 3-4 character actually fit in the softkey.



