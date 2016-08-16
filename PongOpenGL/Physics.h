
#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>
using namespace std;

#include "Force.h"
#include "Timer.h"

class GameObject;

class Physics
{
public:
	GameObject *ownerObj;
public:
	float finalForceX;
	float finalForceY;
	vector<Force> forces;

	bool active;
	Timer addNewForceTimer;
public:
	void AddToFinalSpeed(Force &force);
	void ApplyForces(float deltaTime);
	void RemoveExpiredForces();
	void RemoveAllForces();
	void AddForce(Force &force);
public:
	Physics(GameObject &_ownerObj);
	Physics();
	~Physics();
};
#endif