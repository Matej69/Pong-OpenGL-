#include "ScreenMenu.h"
#include "FunctionCallTracker.h"
#include "Button.h"

using namespace n_screen;

void ScreenMenu::Init()
{	
	type = screenType::MENU;
	Screen::typeChangeHolder = type;

	buttonStart = new Button(n_button::cord.x, n_button::cord.y, n_button::size.w, n_button::size.h, n_button::buttonType::NEW);
	buttonExit = new Button(n_button::cord.x, n_button::cord.y + n_button::vertDistance, n_button::size.w, n_button::size.h, n_button::buttonType::EXIT);

}
void ScreenMenu::Update(float deltaTime)
{
	buttonStart->UpdateLogic(deltaTime);
	buttonExit->UpdateLogic(deltaTime);	
}
void ScreenMenu::Draw()
{	
	buttonStart->DrawSprite();
	buttonExit->DrawSprite();
}	

ScreenMenu::ScreenMenu()
{
	FunctionCallTracker debugF("Constructor for 'ScreenMenu' is being called", "construction is completed");
	Init();
}
ScreenMenu::~ScreenMenu()
{
	delete buttonStart;
	delete buttonExit;
}
