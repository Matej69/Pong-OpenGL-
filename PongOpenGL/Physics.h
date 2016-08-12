
#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>
using namespace std;

#include "Force.h"

class Physics
{
public:
	float finalForceX;
	float finalForceY;
	vector<Force> forces;
	bool active;
public:
	void AddToFinalSpeed(Force &force);
	void ApplyForces(float deltaTime);
	void RemoveExpiredForces();
	void RemoveAllForces();
	void AddForce(Force &force);
public:
	Physics();
	~Physics();
};
#endif