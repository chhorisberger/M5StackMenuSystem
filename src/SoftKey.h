#ifndef SOFT_KEY_H
#define SOFT_KEY_H

#include "Layout.h"
#include "Rect.h"

#include <Arduino.h>


enum SoftKeySlot { BtnASlot, BtnBSlot, BtnCSlot};

class SoftKey
{
public:
	SoftKey(SoftKeySlot slot_, Layout& layout_);

	void render(bool force = false);
	void setPressed(bool pressed_);
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
	int getXPosition();
	int getYPosition();

	bool dirty;

};

#endif 

