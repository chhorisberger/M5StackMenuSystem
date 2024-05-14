#include "MenuBottomSection.h"

#include "Menu.h"

#include <M5Unified.h>

MenuBottomSection::MenuBottomSection(Layout& layout_, Control& control_, Display& display_, Menu* menu_) : layout(layout_), display(display_), softKeyUp(BtnASlot, layout_, control_, display_), softKeyDown(BtnBSlot, layout_, control_, display_), softKeyOk(BtnCSlot, layout_, control_, display_, "Ok")
{
	menu = menu_;
}

void MenuBottomSection::loop()
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

void MenuBottomSection::render()
{
	renderBottomBar();
	renderSoftKeys();
}

void MenuBottomSection::renderBottomBar()
{
	int barW = layout.SCREEN_WIDTH;
	int barH = getHeight();
	int barY = layout.SCREEN_HEIGHT - barH;
	int paddingSide = barW / 2;

	display.fillRoundRect(0, barY, layout.SCREEN_WIDTH, barH, 3, layout.BOTTOM_BAR_BACKGROUND_COLOR);
}

void MenuBottomSection::renderSoftKeys()
{
	softKeyUp.render();
	softKeyDown.render();
	softKeyOk.render();
}

int MenuBottomSection::getHeight()
{
	return softKeyOk.getHeight() + (2 * layout.BOTTOM_BAR_SOFTKEY_V_SPACING);
}
