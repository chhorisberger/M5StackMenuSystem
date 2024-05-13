#ifndef TOUCH_EVENT_H
#define TOUCH_EVENT_H

struct TouchEvent
{
	int state;

	int x;
	int y;
	int dx;
	int dy;

	bool clicked;
	bool pressed;
	bool released;
	bool hold;
	bool dragStart;
	bool drag;
	bool dragging;
	bool flickStart;
	bool flick;
};


#endif 

