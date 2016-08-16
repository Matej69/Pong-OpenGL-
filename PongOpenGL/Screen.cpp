#include "Screen.h"
#include "ScreenMenu.h"
#include "ScreenGame.h"

#include <iostream>
using namespace std;

using namespace n_screen;

Screen*  Screen::currentScreen;
screenType  Screen::typeChangeHolder = screenType::NONE;

void Screen::ChangeTo(n_screen::screenType _type)
{
	delete Screen::currentScreen;
	switch (_type)
	{
	case screenType::MENU: currentScreen = new ScreenMenu(); break;
	case screenType::GAME: currentScreen = new ScreenGame(); break;
	default:break;
	}
	
}
void Screen::ChangeIfNeeded()
{
	if (Screen::DidTypeChange() && Screen::typeChangeHolder != screenType::NONE) {
		Screen::ChangeTo(typeChangeHolder);
	}
}



bool Screen::DidTypeChange()
{
	return (Screen::currentScreen->type != Screen::typeChangeHolder);
}

Screen::Screen()
{
}
Screen::~Screen()
{
}
