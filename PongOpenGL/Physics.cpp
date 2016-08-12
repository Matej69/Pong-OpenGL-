#include "Physics.h"

using namespace n_force;

void Physics::ApplyForces(float deltaTime)
{
	finalForceX = 0;
	finalForceY = 0;

	for (Force &force : forces)
	{
		AddToFinalSpeed(force);
		//if (finalForceX < 2000 && finalForceX > -2000)
			force.ApplyForce(deltaTime);
	}
}
void Physics::RemoveExpiredForces()
{
	/*for (auto it = forces.begin(); it != forces.end();)
	{
		if (it->duration <= 0 && it->type == forceType::REMOVE_AFTER_DURATION_END)
			it = forces.erase(it);
		else
			++it;			
	}
	*/
	
}

void Physics::AddToFinalSpeed(Force &force)
{
		finalForceX += force.forceX;
		finalForceY += force.forceY;
}


void Physics::RemoveAllForces()
{
	forces.erase(forces.begin(), forces.end());
}
void Physics::AddForce(Force &force)
{
	forces.push_back(force);
}


Physics::Physics()
{
	active = true;
}
Physics::~Physics()
{
}
