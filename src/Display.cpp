#include "Display.h"
#include "BufferedDisplay.h"

Display* Display::singleton = nullptr;


Display::Display()
{	
}

void Display::init()
{
}

void Display::drawStart()
{
}

void Display::drawEnd()
{
}

Display* Display::getInstance()
{
	if (singleton == nullptr)
	{
		singleton = new BufferedDisplay();
		singleton->init();
	}
	return singleton;
}

