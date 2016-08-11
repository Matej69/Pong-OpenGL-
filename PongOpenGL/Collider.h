
#ifndef COLLIDER_H
#define COLLIDER_H

#include <vector>
using namespace std;

#include "Timer.h"
class GameObject;


class Collider
{
public:
	GameObject			*ownerObject;
	vector<GameObject*>	collidableObjects;
	Timer				colliderTimer;
public:
	void CollisonListUpdate();
	void CollisionEffect(float deltaTime);
	Collider();
	Collider(GameObject &object);
	~Collider();
};
#endif
