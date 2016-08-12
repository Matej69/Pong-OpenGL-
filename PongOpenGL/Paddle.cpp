#include "Paddle.h"
#include "Collider.h"
#include "Event.h"
#include "Game.h"

using namespace n_gameObject;
using namespace n_paddle;

void Paddle::UpdateLogic(float deltaTime)
{
	UpdateGameObjectLogic(deltaTime);	
	controler.UpdateOnInput(deltaTime);
	RepositionIfOutOfBounds();
}
void Paddle::InitSettings()
{
	this->type = GObjType::PADDLE;
	sprite.InitSpriteTex("paddle.png");	
	horizontalSpeed = 200;
	maxSpeed		= 400;
	horizontalAcc	= 0.5f;
	currentAcc		= horizontalAcc;
	//collider.CollisonListUpdate(); //done by event not here...a.a.
	controler.ownerPaddle = this;
	Event::s_events[n_event::EType::GAMEOBJECT_LIST_UPDATED]->CallEvent<>();
}

void Paddle::RepositionIfOutOfBounds()
{
	if(this->cord.x > n_window::windowSize.w)
		this->cord.x = 0 - this->size.w;
	if (this->cord.x < 0 - this->size.w)
		this->cord.x = n_window::windowSize.w;
		
}

Paddle::Paddle(int _x, int _y, int _w, int _h, paddlePositionType _type) : GameObject(_x,_y,_w,_h)
{
	this->positionType = _type;
	InitSettings();
}
Paddle::Paddle(int _w, int _h, paddlePositionType _type) : GameObject()
{
	this->size.SetSize(_w, _h);
	int spawnVerOffset = 25;
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
}
