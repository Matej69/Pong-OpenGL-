#include "ScreenGame.h"
#include "FunctionCallTracker.h"
#include "Event.h"
#include "Game.h"

#include <stdlib.h> 
#include <time.h>

using namespace n_screen;

pair<int, Cord> ScreenGame::infoAboutBallsToAdd = make_pair(0, Cord(200, 200));

void ScreenGame::AddMarkedBalls()
{	
	int &num = ScreenGame::infoAboutBallsToAdd.first;
	Cord &cord = ScreenGame::infoAboutBallsToAdd.second;		
	while (ScreenGame::infoAboutBallsToAdd.first > 0)
	{			
		
		float randX = (float)(rand() % 30 + 1) / 10;	

		balls.push_back(new Ball(cord.x, cord.y, 80, 80));
		balls[balls.size() - 1]->physics.forces.push_back(Force(randX, 0, randX/10, 0, 0.2f, n_force::forceType::KEEP_AFTER_DURATION_END, *balls[balls.size() - 1]));

		ScreenGame::infoAboutBallsToAdd.first--;
	}
}
void ScreenGame::SpawnRandomUpgrade()
{
	int w = n_window::windowSize.w;
	int h = n_window::windowSize.h;
	Cord cord(rand() % (w - 300) + 150, rand() % (h - 300) + 150);

	int upgradeID = rand() % 4;	
	upgrades.push_back(new Upgrade(cord.x, cord.y, 80, 80, static_cast<n_upgrade::upgradeType>(upgradeID)));
}



void ScreenGame::Init()
{
	srand(time(NULL));
	upgradeTimer.Init(6);

	type = screenType::GAME;
	Screen::typeChangeHolder = type;

	infoAboutBallsToAdd = make_pair(0, Cord(200, 200));

	paddles.push_back(new Paddle(250, 30, n_paddle::paddlePositionType::TOP));
	paddles.push_back(new Paddle(250, 30, n_paddle::paddlePositionType::BOTTOM));
	paddles[0]->controler.SetControls(SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT);
	paddles[1]->controler.SetControls(SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT);

	balls.push_back(new Ball(390, 390, 40, 40));	
	
}
void ScreenGame::Update(float deltaTime)
{	
	//for (GameObject *gameObject : GameObject::s_gameObjects) {
	//	gameObject->UpdateLogic(deltaTime);
	//}	
	for (auto it = GameObject::s_gameObjects.begin(); it != GameObject::s_gameObjects.end();)
	{
		(*it)->UpdateLogic(deltaTime);
		if ((*it)->sizeState == n_gameObject::sizeStateType::RESIZING_END)
			it = GameObject::s_gameObjects.erase(it);
		else
			++it;
	}
	//add new balls if needed, must be outside for loop that use gameObject*
	AddMarkedBalls();

	if (upgradeTimer.IsFinished()) {
		SpawnRandomUpgrade();
		upgradeTimer.Reset();
	}
	upgradeTimer.Tick(deltaTime);
}
void ScreenGame::Draw()
{	
	for (GameObject *gameObject : GameObject::s_gameObjects)
		gameObject->DrawSprite();
}



ScreenGame::ScreenGame() 
{
	FunctionCallTracker debugF("Constructor for 'ScreenGame' is being called", "construction is completed");
	Init();
}
ScreenGame::~ScreenGame()
{
	FunctionCallTracker debugF("Constructor for 'ScreenGame' is being destroyed", "construction is destroyed");
}