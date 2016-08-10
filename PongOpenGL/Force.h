#ifndef FORCE_H
#define FORCE_H

class GameObject;

class Force
{
public:
	GameObject *ownerGO;
public:
	float forceX, forceY;
	float accX, accY;
	float duration;
	int dirX, dirY;
public:
	void ApplyForce(float deltaTime);
	Force(float _forceX, float _forceY, float accX, float accY, float _duration, GameObject &_ownerGO);
	Force();
	~Force();
};
#endif
