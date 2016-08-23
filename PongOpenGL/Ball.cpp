#include "Ball.h"
#include "Event.h"
#include "Collider.h"
#include "Physics.h"
#include "Force.h"
#include "Game.h"
#include "Paddle.h"
#include "Screen.h"
#include "ScreenGame.h"

using namespace n_gameObject;
using namespace n_force;

void Ball::UpdateLogic(float deltaTime)
{
	UpdateGameObjectLogic(deltaTime);
	//if can bounce call BorderBounce, if it actually bounced->ResetTime
	this->borderBounceTimer.Tick(deltaTime);
	if (this->collider.colliderTimer.timePassed > deltaTime && this->borderBounceTimer.IsFinished())
		if (BorderBounce() == true) {
			this->collider.colliderTimer.Reset();
			this->borderBounceTimer.Reset();
		}
	
}

bool Ball::BorderBounce()
{	
	int radius = this->size.w / 2;

	//.......if collided with left/right bound.......
	if (this->cord.x + radius * 2 > n_window::windowSize.w || this->cord.x < 0)
	{
		for (Force &force : this->physics.forces) {			
			force.dirX *= -1;
		}

		//making sure direction is not change infinitly
		if (this->cord.x > n_window::windowSize.w / 2)
			this->cord.x -= 4;
		if (this->cord.x < n_window::windowSize.w / 2)
			this->cord.x += 4;
	}

	//.........if collided with top/bot bound.......
	if (this->cord.y + radius * 2 > n_window::windowSize.h || this->cord.y < 0)
	{
		for (Force &force : this->physics.forces) {
			force.dirY *= -1;
		}

		//making sure direction is not change infinitly
		if(this->cord.y > n_window::windowSize.h/2)
			this->cord.y -= 4;
		if (this->cord.y < n_window::windowSize.h / 2)
			this->cord.y += 4;		

		//lose health depending
		for (GameObject *obj : GameObject::s_gameObjects)
		{
			if (obj->type == n_gameObject::GObjType::PADDLE)
			{
				//IF BALL HIT TOP, REDUCE HEALTH OF TOP PADDLE AND GAIN HEALTH TO bOTTOM ONE
				if (this->cord.y < n_window::windowSize.h / 2 && obj->GetAs<Paddle>().positionType == n_paddle::TOP && this->lastHitByObj != NULL) {
					(obj)->GetAs<Paddle>().TakeDamage(1);
					static_cast<ScreenGame*>(Screen::currentScreen)->pointsLayer->MovePointer(n_pointsLayer::pointerDirType::UP);					
				}
				else if (this->cord.y < n_window::windowSize.h / 2 && obj->GetAs<Paddle>().positionType == n_paddle::BOTTOM && this->lastHitByObj != NULL) {
					(obj)->GetAs<Paddle>().TakeDamage(-1);
				}
				//IF BALL HIT BOTTOM, REDUCE HEALTH OF BOTTOM PADDLE AND GAIN HEALTH TO TOP	ONE 
				if (this->cord.y > n_window::windowSize.h / 2 && obj->GetAs<Paddle>().positionType == n_paddle::BOTTOM && this->lastHitByObj != NULL) {
					(obj)->GetAs<Paddle>().TakeDamage(1);
					static_cast<ScreenGame*>(Screen::currentScreen)->pointsLayer->MovePointer(n_pointsLayer::pointerDirType::DOWN);					
				}
				else if (this->cord.y > n_window::windowSize.h / 2 && obj->GetAs<Paddle>().positionType == n_paddle::TOP && this->lastHitByObj != NULL) {
					(obj)->GetAs<Paddle>().TakeDamage(-1);
				}
			}
		}
	}

	return true;
}


void Ball::InitSettings()
{
	maxSpeed = 2000;
	this->type = GObjType::BALL;
	sprite.InitSpriteTex("ball.png");	
	physics.ownerObj = this;

	this->physics.AddForce(Force(100, 600 /*300*/, 0, 0, 99999, forceType::KEEP_AFTER_DURATION_END, *this));

	Event::s_events[n_event::EType::GAMEOBJECT_LIST_UPDATED]->Register<Collider, void>(this->collider, &Collider::CollisonListUpdate);
	Event::s_events[n_event::EType::GAMEOBJECT_LIST_UPDATED]->CallEvent<>();

	this->physics.addNewForceTimer.Init(0.6f);	//timer is here after we added 1 Force for ball nitial movement		
	this->borderBounceTimer.Init(0.05f);
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
