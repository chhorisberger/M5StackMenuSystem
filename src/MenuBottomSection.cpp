#include "MenuBottomSection.h"

#include "Menu.h"

#include <M5Unified.h>

MenuBottomSection::MenuBottomSection(Layout& layout_, Control& control_, Menu* menu_) : layout(layout_), softKeyUp(BtnASlot, layout_, control_), softKeyDown(BtnBSlot, layout_, control_), softKeyOk(BtnCSlot, layout_, control_, "Ok")
{
	menu = menu_;
	dirty = true;
}

void MenuBottomSection::checkMenuButtons()
{
	if (softKeyUp.wasReleased())
	{
		menu->upButtonPressed();
	}
	
	if (softKeyDown.wasReleased())
	{
		menu->downButtonPressed();
	}
	
	if (softKeyOk.wasReleased())
	{
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

void MenuBottomSection::setDirty()
{
	dirty = true;
}
