#include "ScreenGame.h"
#include "FunctionCallTracker.h"
#include "Event.h"
#include "Game.h"
#include "EffectOnPickup.h"


#include <stdlib.h> 
#include <time.h>

using namespace std;
using namespace n_screen;

pair<int, Cord> ScreenGame::infoAboutBallsToAdd = make_pair(0, Cord(200, 200));
vector<Cord> ScreenGame::CordsForEffects;


void ScreenGame::UpdateEffectsIfNeeded()
{
	//checking if effec should be removed
	for (auto it = GameObject::s_gameObjects.begin(); it != GameObject::s_gameObjects.end();)
	{
		if ((*it)->type == n_gameObject::GObjType::PICKUP_EFFECT && (*it)->size.w > n_effectOnPickup::maxSize)
			it = GameObject::s_gameObjects.erase(it);
		else
			++it;
	}
	//if there is no effects to be added just skip adding part
	if (ScreenGame::CordsForEffects.size() == 0)
		return;
	for (Cord &cord : ScreenGame::CordsForEffects)
	{
		effects.push_back(new EffectOnPickup(cord.x, cord.y));
	}
	CordsForEffects.clear();
}
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
	gameEnded = false;

	type = screenType::GAME;
	Screen::typeChangeHolder = type;

	infoAboutBallsToAdd = make_pair(0, Cord(200, 200));

	paddles.push_back(new Paddle(250, 30, n_paddle::paddlePositionType::TOP));
	paddles.push_back(new Paddle(250, 30, n_paddle::paddlePositionType::BOTTOM));
	paddles[0]->controler.SetControls(SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT);
	paddles[1]->controler.SetControls(SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT);
	paddles[0]->health = PADDLE_HEALTH;
	paddles[1]->health = PADDLE_HEALTH;



	balls.push_back(new Ball(390, 390, 40, 40));	

	pointsLayer = new n_pointsLayer::PointsLayer(PADDLE_HEALTH);
	
}
void ScreenGame::Update(float deltaTime)
{	
	for (auto it = GameObject::s_gameObjects.begin(); it != GameObject::s_gameObjects.end();)
	{
		(*it)->UpdateLogic(deltaTime);
		if ((*it)->sizeState == n_gameObject::sizeStateType::RESIZING_END)
			it = GameObject::s_gameObjects.erase(it);
		else
			++it;
	}
	//add new balls, add/remove Effects if needed, must be outside for loop that use gameObject*
	AddMarkedBalls();
	UpdateEffectsIfNeeded();

	if (upgradeTimer.IsFinished()) {
		SpawnRandomUpgrade();
		upgradeTimer.Reset();
	}
	
	pointsLayer->Update(deltaTime);
	upgradeTimer.Tick(deltaTime);	

	if (this->gameEnded)
		Screen::currentScreen->ChangeTo(n_screen::screenType::MENU);
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
	paddles.clear();
	balls.clear();
	upgrades.clear();
	effects.clear();
	GameObject::s_gameObjects.clear();
}
