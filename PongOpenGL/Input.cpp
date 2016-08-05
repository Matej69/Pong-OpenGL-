#include "Input.h"
#include "Game.h"

#include <iostream>
#include <string>
using namespace std;

void Input::OnInputEvent() {
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
				//cout << "escape" << endl;
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
				//handle on gui button click event
			}
		}
		//******************WINDOW********************	
		if (e.type == SDL_WINDOWEVENT)
		{
			if (e.window.event == SDL_WINDOWEVENT_RESIZED)
			{
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% EXTERNAL PROBLEM, _> when external is used in Sprite.cpp it's fine %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
				//SDL_GetWindowSize(n_window::window, &n_window::w, &n_window::h);				
			}
		}
	}
}
void Input::OnKeyDown(SDL_Scancode key) {
	heldKeys[key] = true;
	releaseKeys[key] = false;
}
void Input::OnKeyUp(SDL_Scancode key) {
	heldKeys[key] = false;
	releaseKeys[key] = true;
}
bool Input::IsKeyUp(SDL_Scancode key) {
	return releaseKeys[key];
}
bool Input::IsKeyDown(SDL_Scancode key) {
	return heldKeys[key];
}

Input::Input()
{	
}


Input::~Input()
{
}
