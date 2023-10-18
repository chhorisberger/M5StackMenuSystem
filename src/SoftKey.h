#ifndef SOFT_KEY_H
#define SOFT_KEY_H

#include "Layout.h"

#include <Arduino.h>


enum SoftKeySlot { BtnASlot, BtnBSlot, BtnCSlot};

// TODO: make abstract and subclass TextSoftKey, UpSoftKey, DownSoftKey etc.

class SoftKey
{
public:
	SoftKey(SoftKeySlot slot_);

	void render(bool force = false);
	void setPressed(bool pressed_);
	int getWidth();
	int getHeight();

protected:
	virtual void renderInternal(int x, int y, int w, int h) = 0;
	void renderRow(int x, int y, int w, int h);

	SoftKeySlot slot;
	bool pressed;

private:
	int getXPosition();

	bool dirty;

};

#endif 

