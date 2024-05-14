#include "SoftKey.h"

#include <M5Unified.h>

SoftKey::SoftKey(SoftKeySlot slot_, Layout& layout_, Control& control_, Display& display_) : layout(layout_), control(control_), display(display_)
{
	slot = slot_;
	pressed = false;
}

SoftKeySlot SoftKey::getSlot()
{
	return slot;
}

bool SoftKey::wasReleased()
{
	return wasButtonReleased() || wasTouchReleased();
}

bool SoftKey::wasButtonReleased()
{
	ButtonEvent buttonEvent = getButtonEvent();
	if (buttonEvent.pressed)
	{
		setPressed(true);
	}
	else if (buttonEvent.released)
	{
		setPressed(false);
		return true;
	}
	
	return false;
}

ButtonEvent SoftKey::getButtonEvent()
{
	switch (getSlot())
	{
	case BtnASlot:
		return control.getAButtonEvent();
	case BtnBSlot:
		return control.getBButtonEvent();
	case BtnCSlot:
		return control.getCButtonEvent();
	}
}

bool SoftKey::wasTouchReleased()
{	
	int nrTouchEvents = control.getNrTouchEvents();
	TouchEvent* touchEvents = control.getTouchEvents();
	for (std::size_t i = 0; i < nrTouchEvents; i++)
	{
		TouchEvent touchEvent = touchEvents[i];
		if (wasTouchReleased(touchEvent))
		{
			return true;
		}
	}

	return false;
}

bool SoftKey::wasTouchReleased(TouchEvent& touchEvent)
{
	if (getRect().contains(touchEvent.x, touchEvent.y))
	{
		if (touchEvent.pressed)
		{
			setPressed(true);
		}
		else if (touchEvent.released)
		{
			setPressed(false);
			return true;
		}
	}
	
	return false;
}

void SoftKey::setPressed(bool pressed_)
{
	pressed = pressed_;
}

void SoftKey::render()
{
	int w = getWidth();
	int h = getHeight();
	int x = getXPosition();
	int y = getYPosition();

	renderInternal(x, y, w, h);
}

void SoftKey::renderRow(int x, int y, int w, int h)
{
	if (pressed)
	{
		display.fillRoundRect(x, y, w, h, 3, layout.BOTTOM_BAR_SOFTKEY_COLOR);
	}
	else
	{
		display.fillRoundRect(x, y, w, h, 3, layout.BOTTOM_BAR_SOFTKEY_BACKGROUND_COLOR);
		display.drawRoundRect(x, y, w, h, 3, layout.BOTTOM_BAR_SOFTKEY_COLOR);
	}
}

int SoftKey::getXPosition()
{
	switch (slot)
	{
	case BtnASlot:
		return getWidth() / 2;
	case BtnBSlot:
		return (layout.SCREEN_WIDTH / 2) - (getWidth() / 2);
	case BtnCSlot:
		return layout.SCREEN_WIDTH - (getWidth() + (getWidth() / 2));
	}

	return -1;
}

int SoftKey::getYPosition()
{
	int h = getHeight();
	return layout.SCREEN_HEIGHT - (h + layout.BOTTOM_BAR_SOFTKEY_V_SPACING);
}

int SoftKey::getWidth()
{
	return layout.SCREEN_WIDTH / layout.BOTTOM_BAR_SOFTKEY_WIDTH_AS_FRACTION_OF_SCREEN;
}

int SoftKey::getHeight()
{
	return  display.fontHeight(layout.MENU_FONT) + (2 * layout.BOTTOM_BAR_SOFTKEY_V_PADDING);
}

Rect SoftKey::getRect()
{
	Rect rect;
	rect.x = getXPosition();
	rect.y = getYPosition();
	rect.w = getWidth();
	rect.h = getHeight();
	return rect;
}
