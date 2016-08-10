#include "Ball.h"
#include "Event.h"
#include "Collider.h"
#include "Force.h"
#include "Game.h"

using namespace n_gameObject;

void Ball::UpdateLogic(float deltaTime)
{
	UpdateGameObjectLogic(deltaTime);
	BorderBounce();
}
void Ball::BorderBounce()
{
	int radius = this->size.w / 2;
	if (this->cord.x + radius * 2 > n_window::windowSize.w || this->cord.x < 0)
	{
		for (Force &force : this->physics.forces)
			force.dirX *= -1;
	}
	if (this->cord.y + radius * 2 > n_window::windowSize.h || this->cord.y < 0)
	{
		//if player goal is protected
			//for (Force &force : this->physics.forces)
				//force.dirY *= -1;
		//if player lost/won point
			//lastHitByObj.score++;
		this->cord.SetCord(n_window::windowSize.w/2, n_window::windowSize.h/2);
	}
		

}


void Ball::InitSettings()
{
	this->type = GObjType::BALL;
	sprite.InitSpriteTex("ball.png");	
	//collider.CollisonListUpdate(); //done by event not here...a.a.
	this->physics.AddForce(Force(300, 100, 0, 0, 99999, *this));
	Event::s_events[n_event::EType::GAMEOBJECT_LIST_UPDATED]->CallEvent<>();	
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
}
