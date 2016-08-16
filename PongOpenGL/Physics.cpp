#include "Physics.h"
#include "GameObject.h"
#include "FunctionCallTracker.h"



using namespace n_force;

void Physics::ApplyForces(float deltaTime)
{
	finalForceX = 0;
	finalForceY = 0;

	addNewForceTimer.Tick(deltaTime);

	for (Force &force : forces)
	{
		AddToFinalSpeed(force);
		//if (finalForceX < 2000 && finalForceX > -2000)
			force.ApplyForce(deltaTime);
	}
}
void Physics::RemoveExpiredForces()
{
	for (auto it = forces.begin(); it != forces.end();)
	{
		if (it->duration <= 0 && it->type == forceType::REMOVE_AFTER_DURATION_END)
			it = forces.erase(it);
		else
			++it;			
	}
	
	
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
	//if its ball that force is applied to take timer in consideration, if not just add force (ball is the only object that usess 'Physics' as component)
	if (addNewForceTimer.IsFinished() && ownerObj->type == n_gameObject::BALL)
	{
		//FunctionCallTracker("Adding Force to Ball", "Force to ball is succesfuly added");
		forces.push_back(force);
		addNewForceTimer.Reset();
	}
	else if(ownerObj->type != n_gameObject::BALL)
	{		
		forces.push_back(force);
	}
	
}


Physics::Physics(GameObject &_ownerObj)
{
	ownerObj = &_ownerObj;
	active = true;	
}
Physics::Physics()
{
	active = true;	
}
Physics::~Physics()
{
}
