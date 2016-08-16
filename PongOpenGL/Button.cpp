#include "Button.h"
#include "Event.h"
#include "Screen.h"
#include "Game.h"

namespace n_button {
	Size size(180,60);
	int vertDistance = size.h * 1.4;
	Cord cord(n_window::windowSize.w / 2 - size.w/2, n_window::windowSize.h / 2 - size.h/2 - vertDistance/2);
	void UpdateDefaultProperties()
	{
		size.SetSize(180, 60);
		cord.SetCord(n_window::windowSize.w / 2 - size.w/2, n_window::windowSize.h / 2 - size.h/2 - vertDistance/2);
	}
}


void Button::OnButtonClick(int _x, int _y)
{
	FunctionCallTracker debug("start", "done");
	Cord cord(_x, _y);
	if (n_geometry::IsCordInsideRect(*this, cord))
	{
		switch (buttonType)
		{
			case n_button::buttonType::NEW :	Screen::typeChangeHolder = n_screen::screenType::GAME;	 break;
			case n_button::buttonType::EXIT:	Game::isRunning = false;	break;
		}
	}
}


void Button::UpdateLogic(float deltaTime)
{
	UpdateGameObjectLogic(deltaTime);
}
void Button::InitSettings()
{
	Event::s_events[n_event::EType::MOUSE_CLICK]->Register<Button, void, int, int>(*this, &Button::OnButtonClick);
	switch (buttonType)
	{
		case n_button::buttonType::NEW:	this->sprite.InitSpriteTex("BUTTON_NEW.png"); break;
		case n_button::buttonType::EXIT:this->sprite.InitSpriteTex("BUTTON_EXIT.png"); break;
	}
}


Button::Button(int _x, int _y, int _w, int _h, n_button::buttonType _type) : GameObject(_x,_y,_w,_h)
{
	buttonType = _type;
	this->type = n_gameObject::GObjType::BUTTON;
	InitSettings();
}
Button::Button()
{
	InitSettings();
}
Button::~Button()
{
	Event::s_events[n_event::EType::MOUSE_CLICK]->RemoveSubscriber<Button, void, int, int>(this);
}
