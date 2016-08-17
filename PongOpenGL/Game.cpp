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
#include "Timer.h"

#include "Screen.h"
#include "ScreenGame.h"
#include "ScreenMenu.h"
#include "Button.h"
#include "EffectOnPickup.h"

bool Game::isRunning = true;

void Game::GameLoop() {
	isRunning = true;
	Input input;
	FPSTimer fpsTimer;

	FunctionCallTracker::isPrinting = true;

	//all events are crated before and accesed over Event::s_events[eventID]....
	Event keyup(n_event::KEY_UP); 
	Event mouseclick(n_event::MOUSE_CLICK);
	Event keydown(n_event::KEY_DOWN);
	Event GOlistUpdated(n_event::GAMEOBJECT_LIST_UPDATED);

	FunctionCallTracker::isPrinting = false;

	n_button::UpdateDefaultProperties();			
	Screen::currentScreen = new ScreenMenu();	

	//EffectOnPickup effect(300, 300, 1.00035);
	
	while (isRunning) 
	{
		fpsTimer.UpdateDeltaTime();
		fpsTimer.UpdateFramesPerSec();

		PaintBackground(1, 10, 40, 160);		
		
		input.OnInputEvent();

		Screen::currentScreen->ChangeIfNeeded();
		Screen::currentScreen->Update(fpsTimer.deltaTime);
		Screen::currentScreen->Draw();	

		//effect.UpdateLogic(fpsTimer.deltaTime);
		//effect.DrawSprite();

		//Sprite s("UpgradePickupEffect.png");
		
		SDL_RenderPresent(renderer);		
		//SDL_UpdateWindowSurface(window);			cout << GameObject::s_gameObjects.size() << endl;
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
