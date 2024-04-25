#include "CallbackMenuItem.h"

#include "Menu.h"

#ifdef M5_UNIFIED
#include <M5Unified.h>
#else
#include <M5Stack.h>
#endif

CallbackMenuItem::CallbackMenuItem(Layout& layout_, String text_, CallbackFunction callbackOneTimeFunction_, CallbackFunction callbackLoopFunction_) : MenuItem(layout_, text_)
{
	text = text_;
	callbackOneTimeFunction = callbackOneTimeFunction_;
	callbackLoopFunction = callbackLoopFunction_;
	firstLoop = true;
}

void CallbackMenuItem::loop() 
{
	if (firstLoop)
	{
		callbackOneTimeFunction(*this);
		firstLoop = false;

		if (callbackLoopFunction == NULL)
		{
			deactivateCallbacks();
		}
	}	

	if (callbackLoopFunction != NULL)
	{
		callbackLoopFunction(*this);
	}
}

void CallbackMenuItem::deactivateCallbacks()
{
	firstLoop = true;
	getMenu()->resetActiveMenuItem();
}
