#include "GameObject.h"
#include "FunctionCallTracker.h"
#include "Collider.h"
#include "Sprite.h"

#include "Collider.h"
#include "Event.h"
#include "ISubscriber.h"

vector<GameObject*> GameObject::s_gameObjects;

void GameObject::ResizeAndDestroyIfToSmall(float num)
{
	if (this->sizeState == n_gameObject::sizeStateType::RESIZING)
		n_effects::ResizeByPercent(num, *this);
	if (this->size.w < 5 || this->size.h < 5)
		this->sizeState = n_gameObject::sizeStateType::RESIZING_END;
}

void GameObject::DrawSprite()
{	
	sprite.Draw((int)cord.x, (int)cord.y, (int)size.w, (int)size.h);
}
void GameObject::UpdateGameObjectLogic(float deltaTime)
{
	collider.CollisionEffect(deltaTime);
	physics.ApplyForces(deltaTime);
	physics.RemoveExpiredForces();	

	float resizeFactor = 0.9992f;
	ResizeAndDestroyIfToSmall(resizeFactor);
	
}
Cord GameObject::GetMiddleCord() const
{
	return Cord(cord.x + size.w / 2, cord.y + size.h / 2);
}

GameObject::GameObject(int _x, int _y, int _w, int _h)
{		
	cord.x = _x;		cord.y = _y;
	size.w = _w;		size.h = _h;
	collider.ownerObject = this;
	s_gameObjects.push_back(this);
	sizeState = n_gameObject::sizeStateType::NOT_RESIZING;
}
GameObject::GameObject()
{	
	collider.ownerObject = this;	
	s_gameObjects.push_back(this);
	sizeState = n_gameObject::sizeStateType::NOT_RESIZING;
}
GameObject::~GameObject()
{
	FunctionCallTracker debugF("GameObject Destructor is being called", "GameObject is destroyed susscesfully");	
	//removing this gameObject from list of gameObjects	
	for (auto it = s_gameObjects.begin(); it != s_gameObjects.end(); ++it)
	{
		if (*it == this) {
			s_gameObjects.erase(it);
			break;
		}
	}	
	//********** GameObjectListUpdated event is being called that will inform PADDLE,BALL,UPGRADE... to refresh
	//********** their local gameObjectList(erase everithing, go through every object and deside will it be in local
	//********** list or not depending on type)


	
}
