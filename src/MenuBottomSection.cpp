#include "MenuBottomSection.h"

#include "Display.h"
#include "Menu.h"

#include <M5Unified.h>

MenuBottomSection::MenuBottomSection(Layout& layout_, Control& control_,  Menu* menu_) : layout(layout_), softKeyUp(BtnASlot, layout_, control_), softKeyDown(BtnBSlot, layout_, control_), softKeyOk(BtnCSlot, layout_, control_, "Ok")
{
	menu = menu_;
}

void MenuBottomSection::loop()
{
	if (softKeyUp.wasPressed())
	{
		menu->setDirty();
	}
	if (softKeyUp.wasReleased())
	{
		menu->moveUpSelection();
	}
	
	if (softKeyDown.wasPressed())
	{
		menu->setDirty();
	}
	if (softKeyDown.wasReleased())
	{
		menu->moveDownSelection();
	}
	
	if (softKeyOk.wasPressed())
	{
		menu->setDirty();
	}
	if (softKeyOk.wasReleased())
	{
		menu->confirmSelection();
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

	Display::getInstance()->fillRect(0, barY, layout.SCREEN_WIDTH, barH, layout.BOTTOM_BAR_BACKGROUND_COLOR);
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
