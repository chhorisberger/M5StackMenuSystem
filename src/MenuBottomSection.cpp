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
	checkUpButton();
	checkDownButton();
	checkOkButton();
}

void MenuBottomSection::checkUpButton()
{
	if (control.buttonAPressed)
	{
		softKeyUp.setPressed(true);
	}
	else if (control.buttonAReleased)
	{
		softKeyUp.setPressed(false);
		menu->upButtonPressed();
	}
}

void MenuBottomSection::checkDownButton()
{
	if (control.buttonBPressed)
	{
		softKeyDown.setPressed(true);
	}
	else if (control.buttonBReleased)
	{
		softKeyDown.setPressed(false);
		menu->downButtonPressed();
	}
}

void MenuBottomSection::checkOkButton()
{
	if (control.buttonCPressed)
	{
		softKeyOk.setPressed(true);
	}
	else if (control.buttonCReleased)
	{
		softKeyOk.setPressed(false);
		menu->okButtonPressed();
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
