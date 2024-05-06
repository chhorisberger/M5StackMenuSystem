#ifndef CONTROL_H
#define CONTROL_H

#include <cstdint>

#include "ButtonEvent.h"
#include "TouchEvent.h"

#define MAX_TOUCH_EVENTS 5

class Control
{
	public:
		Control();

		void init();
		void loop();

		ButtonEvent getAButtonEvent();
		ButtonEvent getBButtonEvent();
		ButtonEvent getCButtonEvent();

		std::uint8_t getNrTouchEvents();
		TouchEvent* getTouchEvents();

	private:
		void checkButtons();
		void checkTouch();

		ButtonEvent aButtonEvent;
		ButtonEvent bButtonEvent;
		ButtonEvent cButtonEvent;

		std::uint8_t nrTouchEvents;
		TouchEvent touchEvents[MAX_TOUCH_EVENTS];

};

#endif 

