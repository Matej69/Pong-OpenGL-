#include "Paddle.h"
#include "Collider.h"
#include "Event.h"

using namespace n_gameObject;

void Paddle::UpdateLogic(float deltaTime)
{
	UpdateGameObjectLogic(deltaTime);	
	controler.UpdateOnInput(deltaTime);
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

Paddle::Paddle(int _x, int _y, int _w, int _h) : GameObject(_x,_y,_w,_h)
{
	InitSettings();
}
Paddle::Paddle()
{
	InitSettings();
}
Paddle::~Paddle()
{
}
