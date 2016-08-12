#include "GameObject.h"
#include "Paddle.h"
#include "Ball.h"

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
			//::::::::::::::::::::::::::::::if this object is ball::::::::::::::::::::::::::::::
			if (ownerObject->type == GObjType::BALL)
			{
				if ((*it)->type == GObjType::PADDLE)
				{
					//if ball is colliding with paddle
					if (n_geometry::IsCircleAndRectColliding(*(*it),*ownerObject))
					{
						colliderTimer.Reset();
						//if ball is on left/right side of paddle just change x-axis movement dir, no need for cnage of y-axis dir
						if (ownerObject->GetMiddleCord().x < (*it)->cord.x || ownerObject->GetMiddleCord().x >(*it)->cord.x + (*it)->size.w)
						{
							bool ballIsOnLeft = ownerObject->GetMiddleCord().x < (*it)->cord.x;
							for (Force &force : ownerObject->physics.forces)
							{
								force.dirX = (ballIsOnLeft) ? -1 : 1;
								force.dirY = ((*it)->GetAs<Paddle>().positionType == n_paddle::paddlePositionType::TOP) ? 1 : -1;
							}
						}
						//if ball is NOT on left/right side of paddle just change y-axis movement dir, it depends is it TOP/BOTTOM paddle
						else
						{
							for (Force &force : ownerObject->physics.forces)
							{
								if ((*it)->GetAs<Paddle>().positionType == n_paddle::paddlePositionType::TOP)
								{
									force.dirY = (ownerObject->GetMiddleCord().y < (*it)->cord.y) ? -1 : 1;											
								}
								else if ((*it)->GetAs<Paddle>().positionType == n_paddle::paddlePositionType::BOTTOM)
								{
									force.dirY = (ownerObject->GetMiddleCord().y > (*it)->cord.y) ? 1 : -1;
								}																		
							}
						}								
					}
				}
			}

			//::::::::::::::::::::::::::::::if this object is paddle or effec/upgrade::::::::::::::::::::::::::::::
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
