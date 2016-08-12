#include "Force.h"
#include "GameObject.h"



void Force::ApplyForce(float deltaTime)
{
	if (this->duration <= 0)
	{
		accX = 0;
		accY = 0;
	}
	forceX += accX;
	forceY += accY;
	ownerGO->cord.x += forceX * dirX * deltaTime;
	ownerGO->cord.y += forceY * dirY * deltaTime;
	duration -= deltaTime;
}

Force::Force(float _forceX, float _forceY, float _accX, float _accY, float _duration, n_force::forceType _type, GameObject &_ownerGO)
{
	this->type = _type;
	dirX	= 1;
	dirY	= 1;
	forceX	= _forceX;	forceY = _forceY;
	accX	= _accX;		accY = _accY;
	duration= _duration;
	ownerGO	= &_ownerGO;
}
Force::Force()
{
}
Force::~Force()
{
}
