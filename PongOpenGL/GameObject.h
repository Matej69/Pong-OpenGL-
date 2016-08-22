#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Sprite.h"
#include "Collider.h"
#include "Physics.h"

#include "GlobalStuff.h"
using namespace n_geometry;

#include <vector>
#include <utility>
using namespace std;

namespace n_gameObject {
	enum GObjType {
		PADDLE,
		BALL,
		UPGRADE,
		BUTTON,
		PICKUP_EFFECT,
		NON_SPECIFIC
	};
	enum sizeStateType
	{
		NOT_RESIZING,
		RESIZING,
		RESIZING_END
	};
}


class GameObject
{
public:
	void ResizeAndDestroyIfToSmall(float num);
public:
	n_gameObject::GObjType		type;
	n_gameObject::sizeStateType sizeState;
	static vector<GameObject*>	s_gameObjects;	
public:
	Cord cord;
	Size size;
public:
	Sprite sprite;
	Collider collider;
	Physics physics;
public:
	template<class ClassToReturn>
	ClassToReturn& GetAs() {
		return static_cast<ClassToReturn&>(*this);
	}

public:				
			Cord	GetMiddleCord() const;
			void	DrawSprite();
			void	UpdateGameObjectLogic(float deltaTime);
	virtual	void	UpdateLogic(float deltaTime) = 0;
	virtual	void	InitSettings() = 0;
	GameObject();
	GameObject(int _x, int _y, int _w, int _h);
	virtual ~GameObject();
};
#endif 

