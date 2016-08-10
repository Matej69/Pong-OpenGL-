#include "GameObject.h"
#include "FunctionCallTracker.h"
#include "Collider.h"
#include "Sprite.h"

#include "Collider.h"
#include "Event.h"
#include "ISubscriber.h"

vector<GameObject*> GameObject::s_gameObjects;


void GameObject::DrawSprite()
{
	sprite.Draw((int)cord.x, (int)cord.y, (int)size.w, (int)size.h);
}
void GameObject::UpdateGameObjectLogic(float deltaTime)
{
	collider.CollisionEffect();
	physics.ApplyForces(deltaTime);
	physics.RemoveExpiredForces();
}

GameObject::GameObject(int _x, int _y, int _w, int _h)
{		
	Event::s_events[n_event::EType::GAMEOBJECT_LIST_UPDATED]->Register<Collider, void>(this->collider, &Collider::CollisonListUpdate);
	cord.x = _x;		cord.y = _y;
	size.w = _w;		size.h = _h;
	collider.ownerObject = this;
	s_gameObjects.push_back(this);
}
GameObject::GameObject()
{	
	collider.ownerObject = this;
	s_gameObjects.push_back(this);
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
