#include "MenuBottomSection.h"

#include "Menu.h"

#include <M5Unified.h>

MenuBottomSection::MenuBottomSection(Layout& layout_, Control& control_, Menu* menu_) : layout(layout_), control(control_), softKeyUp(BtnASlot, layout_), softKeyDown(BtnBSlot, layout_), softKeyOk(BtnCSlot, layout_, "Ok")
{
	menu = menu_;
	dirty = true;
}

void MenuBottomSection::checkMenuButtons()
{
	checkButtonEvent(softKeyUp, control.getAButtonEvent());
	checkButtonEvent(softKeyDown, control.getBButtonEvent());
	checkButtonEvent(softKeyOk, control.getCButtonEvent());
	checkTouchEvents(control.getNrTouchEvents(), control.getTouchEvents());
}


void MenuBottomSection::checkButtonEvent(SoftKey& softKey, ButtonEvent buttonEvent)
{
	if (buttonEvent.pressed)
	{
		softKey.setPressed(true);
	}
	else if (buttonEvent.released)
	{
		softKey.setPressed(false);
		handleButtonPress(softKey);
	}
}

void MenuBottomSection::checkTouchEvents(int nrTouchEvents, TouchEvent* touchEvents)
{
	for (std::size_t i = 0; i < nrTouchEvents; i++)
	{
		TouchEvent touchEvent = touchEvents[i];
		checkTouchEvent(touchEvent, softKeyUp);
		checkTouchEvent(touchEvent, softKeyDown);
		checkTouchEvent(touchEvent, softKeyOk);
	}
}

void MenuBottomSection::checkTouchEvent(TouchEvent& touchEvent, SoftKey& softKey)
{
	if (softKey.getRect().contains(touchEvent.x, touchEvent.y))
	{
		if (touchEvent.pressed)
		{
			softKey.setPressed(true);
		}
		else if (touchEvent.released)
		{
			softKey.setPressed(false);
			handleButtonPress(softKey);
		}
	}
}

void MenuBottomSection::handleButtonPress(SoftKey& softKey)
{
	switch (softKey.getSlot())
	{
	case BtnASlot:
		menu->upButtonPressed();
		break;
	case BtnBSlot:
		menu->downButtonPressed();
		break;
	case BtnCSlot:
		menu->okButtonPressed();
		break;
	}
}

void MenuBottomSection::render(bool force)
{
	if (dirty || force)
	{
		renderBottomBar();
		dirty = false;
	}

	renderSoftKeys(force);
}

void MenuBottomSection::renderBottomBar()
{
	int barW = layout.SCREEN_WIDTH;
	int barH = getHeight();
	int barY = layout.SCREEN_HEIGHT - barH;
	int paddingSide = barW / 2;

	M5.Lcd.fillRoundRect(0, barY, layout.SCREEN_WIDTH, barH, 3, layout.BOTTOM_BAR_BACKGROUND_COLOR);
}

void MenuBottomSection::renderSoftKeys(bool force)
{
	softKeyUp.render(force);
	softKeyDown.render(force);
	softKeyOk.render(force);
}

int MenuBottomSection::getHeight()
{
	return softKeyOk.getHeight() + (2 * layout.BOTTOM_BAR_SOFTKEY_V_SPACING);
}
