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


#include <iostream>
#include <string>
using namespace std;

namespace n_window {
	Size			windowSize;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
}
using namespace n_window;

bool Game::CreateWindow(int _w, int _h) {
	windowSize.w	=	_w;
	windowSize.h	=	_h;
	//sdl init
	if(SDL_Init(SDL_INIT_VIDEO) < 0)	 { cout << "sdl could not been initialised" << endl;	return false; }
	//window init
	window	=	SDL_CreateWindow("El Pong dell Consago", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSize.w, windowSize.h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window == NULL)					{ cout << "window could not been created" << endl;		return false;	 }
	//renderer init
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)				{ cout << "renderer could not been created" << endl;	return false;	 }
}
void Game::PaintBackground(int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_Rect w_rect = { 0,0,windowSize.w,windowSize.h };
	SDL_RenderFillRect(renderer, &w_rect);
}

#include "Paddle.h"
#include "Ball.h"
#include "Physics.h"


void Game::GameLoop() {
	int isRunning = true;
	Input input;
	FPSTimer fpsTimer;

	//all events are crated before and accesed over Event::s_events[eventID]....
	Event keyup(n_event::KEY_UP); 
	Event mouseclick(n_event::MOUSE_CLICK);
	Event keydown(n_event::KEY_DOWN);
	Event GOlistUpdated(n_event::GAMEOBJECT_LIST_UPDATED);

	Paddle o1(10, 10, 150, 30);	
	Ball o2(10, 160, 81, 81);

	o1.controler.SetControls(SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT);
		
	while (isRunning) 
	{
		fpsTimer.UpdateDeltaTime();
		fpsTimer.UpdateFramesPerSec();

		PaintBackground(1, 10, 40, 160);		
		
		input.OnInputEvent();

		o1.DrawSprite();
		o2.DrawSprite();
				
		o1.UpdateLogic(fpsTimer.deltaTime);
		o2.UpdateLogic(fpsTimer.deltaTime);
					

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
