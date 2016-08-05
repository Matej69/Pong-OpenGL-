#include "Game.h" 
#include "Input.h"
#include "FPSTimer.h"
#include "Sprite.h"
#include "GameObject.h"

#include "ISubscriber.h"
#include "Subscriber.h"
//#include "Subscriber.cpp"	//template stuff

#include "Event.h"
//#include "Event.cpp"

#include <SDL.h>

#include <iostream>
#include <string>
using namespace std;

namespace n_window {
	int				w, h;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
}
using namespace n_window;

bool Game::CreateWindow(int _w, int _h) {
	n_window::w	=	_w;
	n_window::h	=	_h;
	//sdl init
	if(SDL_Init(SDL_INIT_VIDEO) < 0)	 { cout << "sdl could not been initialised" << endl;	return false; }
	//window init
	window	=	SDL_CreateWindow("El Pong dell Consago", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window == NULL)					{ cout << "window could not been created" << endl;		return false;	 }
	//renderer init
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)				{ cout << "renderer could not been created" << endl;	return false;	 }
}
void Game::PaintBackground(int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_Rect w_rect = { 0,0,w,h };
	SDL_RenderFillRect(renderer, &w_rect);
}


void Game::GameLoop() {
	int isRunning = true;
	Input input;
	FPSTimer fpsTimer;

	//all events are crated before and accesed over Event::s_events[eventID]....
	Event ev(n_event::KEY_UP); 
	Event ev1(n_event::MOUSE_CLICK);
	Event ev3(n_event::KEY_UP);

	GameObject o,o2;
	ev.Register<GameObject, int, int, int>(o, &GameObject::Sum);
	ev1.Register<GameObject, int, int, int>(o, &GameObject::Sum);

	Event::RemoveSubscriberFromAll<GameObject, int, int, int>(&o);
	//Event::RemoveSubscriberFromAll<GameObject, int, int, int>(&o);

	while (isRunning) 
	{
		fpsTimer.UpdateDeltaTime();
		fpsTimer.UpdateFramesPerSec();

		PaintBackground(1, 60, 40, 160);		
		
		input.OnInputEvent();
				
		

		SDL_RenderPresent(renderer);		
		//SDL_UpdateWindowSurface(window);	
	}


	
}

Game::Game()
{
	CreateWindow(800,600);
	GameLoop();
}


Game::~Game()
{
}
