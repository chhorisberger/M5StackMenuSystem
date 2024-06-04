#ifndef SOFT_KEY_H
#define SOFT_KEY_H

#include "Display.h"
#include "Layout.h"
#include "Control.h"
#include "Rect.h"

#include <Arduino.h>


enum SoftKeySlot { BtnASlot, BtnBSlot, BtnCSlot};

class SoftKey
{
public:
	SoftKey(SoftKeySlot slot_, Layout& layout_, Control& control_);

	void render();
	bool wasPressed();
	bool wasReleased();

	Rect getRect();
	int getWidth();
	int getHeight();
	SoftKeySlot getSlot();

protected:
	virtual void renderInternal(int x, int y, int w, int h) = 0;
	void renderRow(int x, int y, int w, int h);

	SoftKeySlot slot;
	Layout& layout;
	bool pressed;

private:
	
	bool wasButtonPressed();
	bool wasButtonReleased();
	ButtonEvent getButtonEvent();
	bool wasTouchReleased();
	bool wasTouchReleased(TouchEvent& touchEvent);
	int getXPosition();
	int getYPosition();
	void setPressed(bool pressed_);

	Control& control;

};

#endif 

