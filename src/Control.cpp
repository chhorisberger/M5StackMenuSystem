#include "Control.h"

#include <M5Unified.h> 

Control::Control()
{	
}

void Control::init()
{
}

void Control::loop()
{
	checkButtons();
	checkTouch();
}

void Control::checkButtons()
{
	aButtonEvent.pressed = M5.BtnA.wasPressed();
	aButtonEvent.released = M5.BtnA.wasReleased();

	bButtonEvent.pressed = M5.BtnB.wasPressed();
	bButtonEvent.released = M5.BtnB.wasReleased();

	cButtonEvent.pressed = M5.BtnC.wasPressed();
	cButtonEvent.released = M5.BtnC.wasReleased();
}

void Control::checkTouch()
{
	nrTouchEvents = M5.Touch.getCount();

	for (std::size_t i = 0; (i < nrTouchEvents) && (i < MAX_TOUCH_EVENTS); i++)
	{
		auto touch = M5.Touch.getDetail(i);
		touchEvents[i].x = touch.x;
		touchEvents[i].y = touch.y;
		touchEvents[i].dx = touch.deltaX();
		touchEvents[i].dy = touch.deltaY();
		touchEvents[i].state = touch.state;
		touchEvents[i].clicked = touch.wasClicked();
		touchEvents[i].pressed = touch.wasPressed();
		touchEvents[i].released = touch.wasReleased();
		touchEvents[i].dragStart = touch.wasDragStart();
		touchEvents[i].drag = touch.wasDragged();
		touchEvents[i].dragging = touch.isDragging();
		touchEvents[i].flickStart = touch.wasFlickStart();
		touchEvents[i].flick = touch.wasFlicked();
		touchEvents[i].hold = touch.wasHold();
	}
}

ButtonEvent Control::getAButtonEvent()
{
	return aButtonEvent;
}

ButtonEvent Control::getBButtonEvent()
{
	return bButtonEvent;
}

ButtonEvent Control::getCButtonEvent()
{
	return cButtonEvent;
}

std::uint8_t Control::getNrTouchEvents()
{
	return nrTouchEvents;
}

TouchEvent* Control::getTouchEvents()
{
	return touchEvents;
}