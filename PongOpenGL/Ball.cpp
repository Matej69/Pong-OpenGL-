#include "Ball.h"
#include "Event.h"
#include "Collider.h"
#include "Physics.h"
#include "Force.h"
#include "Game.h"

using namespace n_gameObject;
using namespace n_force;

void Ball::UpdateLogic(float deltaTime)
{
	UpdateGameObjectLogic(deltaTime);
	//if can bounce call BorderBounce, if it actually bounced->ResetTime
	if (this->collider.colliderTimer.timePassed > deltaTime)
		if(BorderBounce() == true)
			this->collider.colliderTimer.Reset();	
}

bool Ball::BorderBounce()
{
	int radius = this->size.w / 2;
	if (this->cord.x + radius * 2 > n_window::windowSize.w || this->cord.x < 0)
	{
		for (Force &force : this->physics.forces)
			force.dirX *= -1;
		return true;
	}
	if (this->cord.y + radius * 2 > n_window::windowSize.h || this->cord.y < 0)
	{
		for (Force &force : this->physics.forces)
				force.dirY *= -1;
		return true;
	}
	return false;
		

}


void Ball::InitSettings()
{
	maxSpeed = 2000;
	this->type = GObjType::BALL;
	sprite.InitSpriteTex("ball.png");	
	physics.ownerObj = this;

	this->physics.AddForce(Force(100, 300, 0, 0, 99999, forceType::KEEP_AFTER_DURATION_END, *this));

	Event::s_events[n_event::EType::GAMEOBJECT_LIST_UPDATED]->Register<Collider, void>(this->collider, &Collider::CollisonListUpdate);
	Event::s_events[n_event::EType::GAMEOBJECT_LIST_UPDATED]->CallEvent<>();

	this->physics.addNewForceTimer.Init(0.6f);	//timer is here after we added 1 Force for ball nitial movement		
}

Ball::Ball(int _x, int _y, int _w, int _h) : GameObject(_x, _y, _w, _h)
{
	InitSettings();
}
Ball::Ball()
{
	InitSettings();
}
Ball::~Ball()
{
	Event::s_events[n_event::EType::GAMEOBJECT_LIST_UPDATED]->RemoveSubscriberFromAll<Ball>(this);
	Event::s_events[n_event::EType::GAMEOBJECT_LIST_UPDATED]->CallEvent<>();
}
