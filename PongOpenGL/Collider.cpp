#include "GameObject.h"

using namespace n_gameObject;

void Collider::CollisonListUpdate() 
{	
	collidableObjects.clear();
	for (auto it = GameObject::s_gameObjects.begin(); it != GameObject::s_gameObjects.end(); ++it)
	{		
		if (ownerObject->type == GObjType::BALL)		
			{
				if ((*it)->type == GObjType::PADDLE || (*it)->type == GObjType::UPGRADE)
				{
					collidableObjects.push_back(*it);
					cout << (*it)->type << ">> (Ball,Paddle-Upgrade)" << endl;
				}				
			}
		else if (ownerObject->type == GObjType::PADDLE || ownerObject->type == GObjType::UPGRADE)
		{
			if ((*it)->type == GObjType::BALL)
			{
				collidableObjects.push_back(*it);
				cout << (*it)->type << ">> (Paddle-Upgrade,Ball)" << endl;
			}
			
		}
		cout << endl;
	}	
}
void Collider::CollisionEffect(float deltaTime)
{
	colliderTimer.Tick(deltaTime);
	if (this->colliderTimer.timePassed > deltaTime * 2)
	{
		for (auto it = collidableObjects.begin(); it != collidableObjects.end(); ++it)
		{
			//if this object is ball::::::::::::::::::::::::::::::
			if (ownerObject->type == GObjType::BALL)
			{
				if ((*it)->type == GObjType::PADDLE)
				{
					if (n_geometry::IsCircleAndRectColliding(*ownerObject, *(*it)))
					{
						colliderTimer.Reset();
						for (Force &force : ownerObject->physics.forces)
							force.dirY *= -1;
					}
				}
			}
			//if this object is paddle or upgrade::::::::::::::::::::::::::::::
			else if (ownerObject->type == GObjType::PADDLE || ownerObject->type == GObjType::UPGRADE)
			{
				if ((*it)->type == GObjType::BALL)
				{
					if (n_geometry::IsCircleAndRectColliding(*ownerObject, *(*it)))
					{

					}
				}
			}
		}
	}
}

Collider::Collider(GameObject &object)
{
	ownerObject = &object;
	this->colliderTimer.startTime = 0.5f;
}
Collider::Collider()
{
}
Collider::~Collider()
{
}
