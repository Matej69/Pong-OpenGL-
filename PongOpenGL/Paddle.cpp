#include "Paddle.h"
#include "Collider.h"
#include "Event.h"
#include "Game.h"

using namespace n_gameObject;
using namespace n_paddle;

void Paddle::UpdateLogic(float deltaTime)
{
		//******************************if pointer is not setup here it passes wrong values**************************************
	//controler.ownerPaddle = this;
	
	UpdateGameObjectLogic(deltaTime);		
	controler.UpdateOnInput(deltaTime);	
	RepositionIfOutOfBounds();	

	//cout << "Is it number : " << controler.ownerPaddle->cord.x << endl;
}
void Paddle::InitSettings()
{	
	this->type = GObjType::PADDLE; 
	sprite.InitSpriteTex("paddle.png");	

	horizontalSpeed = 200;
	maxSpeed		= 400;
	horizontalAcc	= 0.5f;
	currentAcc		= horizontalAcc;
	health			= 10;

	controler.ownerPaddle = this;
	Event::s_events[n_event::EType::GAMEOBJECT_LIST_UPDATED]->Register<Collider, void>(this->collider, &Collider::CollisonListUpdate);
	Event::s_events[n_event::EType::GAMEOBJECT_LIST_UPDATED]->CallEvent<>();
}

void Paddle::RepositionIfOutOfBounds()
{
	if(this->cord.x > n_window::windowSize.w)
		this->cord.x = 0 - this->size.w;
	if (this->cord.x < 0 - this->size.w)
		this->cord.x = n_window::windowSize.w;
		
}
void Paddle::TakeDamage(int amount)
{
	this->health -= amount;
}


Paddle::Paddle(int _x, int _y, int _w, int _h, paddlePositionType _type) : GameObject(_x,_y,_w,_h)
{
	this->positionType = _type;
	InitSettings();
}
Paddle::Paddle(int _w, int _h, paddlePositionType _type) : GameObject()
{
	this->size.SetSize(_w, _h);
	int spawnVerOffset = 35;
	if(_type == paddlePositionType::TOP)		this->cord.SetCord(n_window::windowSize.w / 2, spawnVerOffset);
	if (_type == paddlePositionType::BOTTOM)	this->cord.SetCord(n_window::windowSize.w / 2, n_window::windowSize.h - this->size.h - spawnVerOffset);
	this->positionType = _type;
	InitSettings();
}
Paddle::Paddle()
{
	InitSettings();
}
Paddle::~Paddle()
{
	Event::s_events[n_event::EType::GAMEOBJECT_LIST_UPDATED]->RemoveSubscriberFromAll<Paddle>(this);
	Event::s_events[n_event::EType::GAMEOBJECT_LIST_UPDATED]->CallEvent<>();
}
