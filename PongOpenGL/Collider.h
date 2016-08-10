
#ifndef COLLIDER_H
#define COLLIDER_H

#include <vector>;
using namespace std;

class GameObject;

class Collider
{
public:
	GameObject *ownerObject;
	vector<GameObject*> collidableObjects;
public:
	void CollisonListUpdate();
	void CollisionEffect();
	Collider();
	Collider(GameObject &object);
	~Collider();
};
#endif
