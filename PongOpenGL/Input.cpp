#include "Input.h"
#include "Game.h"

#include <iostream>
#include <string>
using namespace std;

map<SDL_Scancode, bool> Input::s_heldKeys;
map<SDL_Scancode, bool> Input::s_releaseKeys;

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
				int w = n_window::windowSize.w;			int h = n_window::windowSize.w;
				SDL_GetWindowSize(n_window::window, &w, &h);
				n_window::windowSize.w = w;				n_window::windowSize.h = h;				
			}
		}
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
