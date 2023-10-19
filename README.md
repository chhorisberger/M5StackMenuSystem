# M5StackMenuSystem
A quick way to create nice menus for [M5 Stack](https://github.com/m5stack/m5stack) devices with just a few lines of code

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
  Serial.println(menuItem.getTetx() + " was clicked");
}
```
## Explanation of above code

Declare a new menu instance. Here it will show the title "Main Menu".
```c++
Menu myMenu("Main Menu");
```

In the Arduino "setup()" method, add multiple items to that menu.
```c++
myMenu.addMenuItem("Menu Item #1", testOneTimeCallback);
```
The first argument "Menu Item #1" is the text that will be displayed in the menu for this item.

The second argument "testOneTimeCallback" is the function that will be called when the user selects this item.

```c++
void testOneTimeCallback(CallbackMenuItem& menuItem) {
  Serial.println(menuItem.getTetx() + " menu item was clicked");
}
```
In this basic example all the menu items point to the same function, but in a real application you probably would want each item to point to its own designated funtion.

Don't forget to call "myMenu.loop()" in the Arduino "loop()" function, so that the menu is acutally rendered. 

Also make sure to call the "M5.update()" there. This is needed so that the button clicks can be detected.

```c++
myMenu.loop();
```



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

When adding a sub menu, a "exit item" (shown as "..") will be automatically added, so the user can get back to the main menu.

It is also possible to add such an "exit item" to the main menu, in order to leave the main menu completly.

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

When a user selects the menu item, this function will be then called automatically on every invocation of "mainMenu.loop()".

This is usefull if you want to display a designated screen on selection of the menu item, for example to allow for user input.

If you want the invocations of "loop callback" function to stop, just call the following inside the function: 

```c++
menuItem.deactivateCallbacks();
```

Check out the example "AdvancedMenu" that ships with the library to see how this all fits together.

### Custom Softkeys outside of menu

"Softkeys" are the virtual buttons displayed on the screen above the physical buttons of the M5 Stack device.

Inside a "loop callback" function, you can display custom soft keys by using the following code:

```c++
TextSoftKey exampleSoftKey(BtnASlot, "Foo");
exampleSoftKey.render(); 
```
The first argument "BtnASlot" determines above which of the three buttons the soft key should be displayed (BtnASlot, BtnDSlot or BtnCSlot).

The second argument "Foo" determines the text displayed in the soft key. Be aware that currently only about 3-4 character actually fit in the softkey.

Future updates with the possibility to change the font size might enable longer texts.

