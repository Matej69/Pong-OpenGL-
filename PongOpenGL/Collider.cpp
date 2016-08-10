#include "GameObject.h"

using namespace n_gameObject;

void Collider::CollisonListUpdate() 
{	
	collidableObjects.clear();
	for (auto it = GameObject::s_gameObjects.begin(); it != GameObject::s_gameObjects.end(); ++it)
	{
		cout << "owner TYPE : " << ownerObject->type << " it Type : "<< (*it)->type << " >>>  ";
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
void Collider::CollisionEffect() 
{
	 //cout << "++++++ " << collidableObjects.size() << " +++++++"<< endl;
	for (auto it = collidableObjects.begin(); it != collidableObjects.end(); ++it)
	{	
		if (ownerObject->type == GObjType::BALL)
		{
			if ((*it)->type == GObjType::PADDLE)
			{
				if (n_geometry::IsCircleAndRectColliding(*ownerObject, *(*it)))
				{
					cout << "BALL AND BALL are colliding" << endl;
				}
			}
		}
		else if (ownerObject->type == GObjType::PADDLE || ownerObject->type == GObjType::UPGRADE)
		{
			if ((*it)->type == GObjType::BALL)
			{
				if (n_geometry::IsCircleAndRectColliding(*ownerObject, *(*it)))
				{
					cout << "PADDLE AND BALL are colliding" << endl;
				}
			}
		}
		
	}
}

Collider::Collider(GameObject &object)
{
	ownerObject = &object;
}
Collider::Collider()
{
}
Collider::~Collider()
{
}
