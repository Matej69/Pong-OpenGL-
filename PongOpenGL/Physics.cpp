#include "Physics.h"

void Physics::ApplyForces(float deltaTime)
{
	if (active)
	{
		for (Force &force : forces)
		{
			force.ApplyForce(deltaTime);
		}
	}
}
void Physics::RemoveExpiredForces()
{
	for (auto it = forces.begin(); it != forces.end();)
	{
		if (it->duration <= 0)
			it = forces.erase(it);
		else
			++it;
	}
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
