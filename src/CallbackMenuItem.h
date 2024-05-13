#ifndef CALLBACK_MENU_ITEM_H
#define CALLBACK_MENU_ITEM_H

#include "MenuItem.h"


class CallbackMenuItem : virtual public MenuItem
{
	typedef std::function<void(CallbackMenuItem &menuItem)> CallbackFunction;

public:
	CallbackMenuItem(Layout& layout_, Display& display_, String text_, CallbackFunction callbackOneTimeFunction_, CallbackFunction callbackLoopFunction_ = NULL);
	virtual ~CallbackMenuItem() {}

	virtual void loop();
	void deactivateCallbacks();

protected:
	String text;
	CallbackFunction callbackOneTimeFunction;
	CallbackFunction callbackLoopFunction;

private:
	bool firstLoop;
};

#endif 

