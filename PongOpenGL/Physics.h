
#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>
using namespace std;

#include "Force.h"

class Physics
{
public:
	vector<Force> forces;
	bool active;
public:
	void ApplyForces(float deltaTime);
	void RemoveExpiredForces();
	void RemoveAllForces();
	void AddForce(Force &force);
public:
	Physics();
	~Physics();
};
#endif