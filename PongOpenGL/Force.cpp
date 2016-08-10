#include "Force.h"
#include "GameObject.h"



void Force::ApplyForce(float deltaTime)
{
	if (duration <= 0) return;
	forceX			+=	accX;
	forceY			+=	accY;
	ownerGO->cord.x	+=	forceX * dirX * deltaTime;
	ownerGO->cord.y	+=	forceY * dirY * deltaTime;
	duration		-=	deltaTime;
}

Force::Force(float _forceX, float _forceY, float _accX, float _accY, float _duration, GameObject &_ownerGO)
{
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
