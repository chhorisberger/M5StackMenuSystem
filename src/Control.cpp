#include "Control.h"

#include <M5Unified.h> 

Control::Control()
{	
}

void Control::init()
{
	clearState();
}

void Control::loop()
{
	clearState();
	checkButtons();
	checkTouch();
}

void Control::clearState()
{
	buttonAPressed = false;
	buttonAReleased = false;
	buttonBPressed = false;
	buttonBReleased = false;
	buttonCPressed = false;
	buttonCReleased = false;
}

void Control::checkButtons()
{
	if (M5.BtnA.wasPressed())
	{
		buttonAPressed = true;
	}

	if (M5.BtnA.wasReleased())
	{
		buttonAReleased = true;
	}

	if (M5.BtnB.wasPressed())
	{
		buttonBPressed = true;
	}

	if (M5.BtnB.wasReleased())
	{
		buttonBReleased = true;
	}

	if (M5.BtnC.wasPressed())
	{
		buttonCPressed = true;
	}

	if (M5.BtnC.wasReleased())
	{
		buttonCReleased = true;
	}
}

void Control::checkTouch()
{
	// TODO: store touch events
	// TODO: provide getters, so they can be evaluated later in MenuButtonSection and in Menu
}