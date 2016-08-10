#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Sprite.h"
#include "Collider.h"
#include "Physics.h"

#include "GlobalStuff.h"
using namespace n_geometry;

#include <vector>
using namespace std;

namespace n_gameObject {
	enum GObjType {
		PADDLE,
		BALL,
		UPGRADE
	};
}

class GameObject
{
public:
	n_gameObject::GObjType		type;
	static vector<GameObject*>	s_gameObjects;
public:
	Cord cord;
	Size size;
public:
	Sprite sprite;
	Collider collider;
	Physics physics;
public:	
			void	DrawSprite();
			void	UpdateGameObjectLogic(float deltaTime);
	virtual	void	UpdateLogic(float deltaTime) = 0;
	virtual	void	InitSettings() = 0;
	GameObject();
	GameObject(int _x, int _y, int _w, int _h);
	virtual ~GameObject();
};
#endif 

