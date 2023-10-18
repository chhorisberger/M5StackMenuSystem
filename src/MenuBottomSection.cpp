#include "MenuBottomSection.h"

#include "Menu.h"

#include <M5Stack.h>

MenuBottomSection::MenuBottomSection(Menu* menu_) : softKeyUp(BtnASlot), softKeyDown(BtnBSlot), softKeyOk(BtnCSlot, "Ok")
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
	if (M5.BtnA.wasPressed())
	{
		softKeyUp.setPressed(true);
	}
	else if (M5.BtnA.wasReleased())
	{
		softKeyUp.setPressed(false);
		menu->upButtonPressed();
	}
}

void MenuBottomSection::checkDownButton()
{
	if (M5.BtnB.wasPressed())
	{
		softKeyDown.setPressed(true);
	}
	else if (M5.BtnB.wasReleased())
	{
		softKeyDown.setPressed(false);
		menu->downButtonPressed();
	}
}

void MenuBottomSection::checkOkButton()
{
	if (M5.BtnC.wasPressed())
	{
		softKeyOk.setPressed(true);
	}
	else if (M5.BtnC.wasReleased())
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
	int barW = SCREEN_WIDTH / 5;
	int barH = MENU_FONT_HEIGHT + (2 * V_PADDING_BOTTOM_SECTION);
	int barY = SCREEN_HEIGHT - barH;
	int paddingSide = barW / 2;

	M5.Lcd.fillRoundRect(0, barY, SCREEN_WIDTH, barH, 3, BOTTOM_BAR_BACKGROUND_COLOR);
}

void MenuBottomSection::renderSoftKeys(bool force)
{
	softKeyUp.render(force);
	softKeyDown.render(force);
	softKeyOk.render(force);
}
