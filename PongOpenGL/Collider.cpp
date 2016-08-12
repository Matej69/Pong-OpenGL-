#include "GameObject.h"
#include "Paddle.h"
#include "Ball.h"

using namespace n_gameObject;
using namespace n_force;

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
	if (this->colliderTimer.timePassed > deltaTime * 3)
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
							bool paddleMovingLeft = ((*it)->GetAs<Paddle>().horizontalSpeed < 0) ? true : false;
								
							for (Force &force : ownerObject->physics.forces)
							{
								//change y directio based on what paddle it collided with
								if ((*it)->GetAs<Paddle>().positionType == n_paddle::paddlePositionType::TOP)
								{
									force.dirY = (ownerObject->GetMiddleCord().y < (*it)->cord.y) ? -1 : 1;
								}
								else if ((*it)->GetAs<Paddle>().positionType == n_paddle::paddlePositionType::BOTTOM)
								{
									force.dirY = (ownerObject->GetMiddleCord().y > (*it)->cord.y) ? 1 : -1;
								}
								//change X direction based on is paddle moving left or right	
								//*****************************************weird physics problem might be here**********************************************
								if (paddleMovingLeft) {
									if (force.dirX < 0)
									{
										force.dirX = force.dirX;
									}
									else
										force.dirX = -force.dirX;
								}

								else {
									if (force.dirX > 0)
									{
										force.dirX = force.dirX;
									}
									else
										force.dirX = -force.dirX;
								}								
								force.forceX /= 2.5;
							}
							//*****************************************weird physics problem might be here**********************************************
							//depends when ball hit paddle curving will be bigger/smaller
							float amountOfCurving = 0.15;
							float distanceFromLeft_percent;
							if ((*it)->GetAs<Paddle>().horizontalSpeed < 0)							
								distanceFromLeft_percent = 1 - ((ownerObject->GetMiddleCord().x - (*it)->GetAs<Paddle>().cord.x) / (*it)->GetAs<Paddle>().size.w);	
							else
								distanceFromLeft_percent = ((ownerObject->GetMiddleCord().x - (*it)->GetAs<Paddle>().cord.x) / (*it)->GetAs<Paddle>().size.w);
							amountOfCurving *= distanceFromLeft_percent;
							
							if (paddleMovingLeft) {
								ownerObject->physics.forces.push_back(Force(1, 0, amountOfCurving, 0, 0.5f, forceType::KEEP_AFTER_DURATION_END, *ownerObject));
								ownerObject->physics.forces[ownerObject->physics.forces.size() - 1].dirX = -1;
							}
							else
								ownerObject->physics.forces.push_back(Force(1, 0, amountOfCurving, 0, 0.5, forceType::KEEP_AFTER_DURATION_END, *ownerObject));
							
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
