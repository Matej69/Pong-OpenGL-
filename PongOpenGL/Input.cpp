#include "Input.h"
#include "Game.h"
#include "GlobalStuff.h"
#include "GameObject.h"
#include "Paddle.h"
#include "Event.h"

#include <iostream>
#include <string>
using namespace std;

map<SDL_Scancode, bool> Input::s_heldKeys;
map<SDL_Scancode, bool> Input::s_releaseKeys;

void Input::OnInputEvent(/*Game *game*/) {
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{		
		//******************KEYBOARD********************	
		if (e.type == SDL_KEYDOWN)
		{
			OnKeyDown(e.key.keysym.scancode);
			
			if (e.key.keysym.scancode == SDL_SCANCODE_A || e.key.keysym.scancode == SDL_SCANCODE_LEFT)
			{
				
			}
			if (e.key.keysym.scancode == SDL_SCANCODE_D || e.key.keysym.scancode == SDL_SCANCODE_RIGHT)
			{
				//cout << "right was pressed" << endl;
			}
			if (e.key.keysym.scancode == SDL_SCANCODE_W || e.key.keysym.scancode == SDL_SCANCODE_UP)
			{
				//cout << "up was pressed" << endl;
			}
			if (e.key.keysym.scancode == SDL_SCANCODE_S || e.key.keysym.scancode == SDL_SCANCODE_DOWN)
			{
				//cout << "down was pressed" << endl;
			}
			if (e.key.keysym.scancode == SDL_SCANCODE_P)
			{
				//cout << "paused" << endl;
			}
			if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				//go to menu
			}		
		}

		if (e.type == SDL_KEYUP)
		{
			OnKeyUp(e.key.keysym.scancode);			
		}	
		//******************MOUSE********************	
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (e.button.button == SDL_BUTTON_LEFT)
			{						
				int x, y;
				SDL_GetMouseState(&x, &y);	
				cout << endl << x << " - " <<y << endl;
				Event::s_events[n_event::EType::MOUSE_CLICK]->CallEvent<int, int>(x, y);
			}
		}
		//******************WINDOW********************	
		if (e.type == SDL_WINDOWEVENT) 
		{
			if (e.window.event == SDL_WINDOWEVENT_RESIZED)
			{				
				int w = n_window::windowSize.w;			int h = n_window::windowSize.w;
				SDL_GetWindowSize(n_window::window, &w, &h);

				n_geometry::Size deltaSize(w - n_window::windowSize.w, h - n_window::windowSize.h);
				n_geometry::Size changedByFactor(w / n_window::windowSize.w, h / n_window::windowSize.h);
				
				n_window::windowSize.w = w;				n_window::windowSize.h = h;

				//loop through gameObject and reposition if necessary
				for (auto it = GameObject::s_gameObjects.begin(); it != GameObject::s_gameObjects.end(); ++it)
				{
					//update paddle stuff
					if ((*it)->type == n_gameObject::GObjType::PADDLE)
					{
						//resize paddles according ot new width
						Size &paddleSize = (*it)->GetAs<Paddle>().size;
						paddleSize.SetSize(paddleSize.w * changedByFactor.w, paddleSize.h);
						//reposition bottom paddle on Y-axis
						if ((*it)->GetAs<Paddle>().positionType == n_paddle::paddlePositionType::BOTTOM)
							(*it)->cord.y += deltaSize.h;
					}
					//update ball stuff
					//reposition ball
					if ((*it)->type == n_gameObject::GObjType::BALL)
						(*it)->cord.SetCord(w / 2, h / 2);
					//update button stuff
					//reposition button
					if ((*it)->type == n_gameObject::GObjType::BUTTON)
					{
						n_button::UpdateDefaultProperties();
						if((*it)->GetAs<Button>().buttonType == n_button::buttonType::NEW)
							(*it)->cord.SetCord(n_window::windowSize.w / 2 - n_button::size.w/2, n_window::windowSize.h / 2 - n_button::size.h/2 - n_button::vertDistance / 2);
						if ((*it)->GetAs<Button>().buttonType == n_button::buttonType::EXIT)
							(*it)->cord.SetCord(n_window::windowSize.w / 2 - n_button::size.w / 2, n_window::windowSize.h / 2 - n_button::size.h / 2 + n_button::vertDistance/2);
					}
				}				
			}			
		}
		//******************QUIT********************	
		if (e.type == SDL_QUIT)
			Game::isRunning = false;
	}
}
void Input::OnKeyDown(SDL_Scancode key) {
	s_heldKeys[key] = true;
	s_releaseKeys[key] = false;
}
void Input::OnKeyUp(SDL_Scancode key) {
	s_heldKeys[key] = false;
	s_releaseKeys[key] = true;
}
bool Input::IsKeyUp(SDL_Scancode key) {
	return s_releaseKeys[key];
}
bool Input::IsKeyDown(SDL_Scancode key) {
	return s_heldKeys[key];
}

Input::Input()
{	
}
Input::~Input()
{
}
