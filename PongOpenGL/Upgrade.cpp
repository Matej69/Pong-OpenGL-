#include "Upgrade.h"
#include "Event.h"
#include "Timer.h"

using namespace n_upgrade;



void Upgrade::ChoseSprite()
{
	switch (typeOfUpgrade)
	{
		case upgradeType::PADDLE_INCREASE : this->sprite.InitSpriteTex("PADDLE_INCREASE.png"); break;
		case upgradeType::PADDLE_DECREASE: this->sprite.InitSpriteTex("PADDLE_DECREASE.png"); break;
		case upgradeType::BALL_SPEEDUP: this->sprite.InitSpriteTex("BALL_SPEEDUP.png"); break;
		case upgradeType::BALL_NUMx2: this->sprite.InitSpriteTex("BALL_NUMx2.png"); break;
	}
}

void Upgrade::UpdateLogic(float deltaTime)
{
	UpdateGameObjectLogic(deltaTime);
}
void Upgrade::InitSettings()
{
	this->type = n_gameObject::GObjType::UPGRADE;


	isCollidable = true;
	Event::s_events[n_event::EType::GAMEOBJECT_LIST_UPDATED]->Register<Collider, void>(this->collider, &Collider::CollisonListUpdate);
	Event::s_events[n_event::EType::GAMEOBJECT_LIST_UPDATED]->CallEvent<>();
}

Upgrade::Upgrade(int _x, int _y, int _w, int _h, upgradeType _type) : GameObject(_x,_y,_w,_h)
{
	typeOfUpgrade = _type;
	ChoseSprite();
	InitSettings();
}
Upgrade::Upgrade()
{
}
Upgrade::~Upgrade()
{
	Event::s_events[n_event::EType::GAMEOBJECT_LIST_UPDATED]->RemoveSubscriberFromAll<Upgrade>(this);
	Event::s_events[n_event::EType::GAMEOBJECT_LIST_UPDATED]->CallEvent<>();
}
