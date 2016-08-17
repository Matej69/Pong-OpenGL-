#include "GameObject.h"
#include "Paddle.h"
#include "Ball.h"
#include "Upgrade.h"
#include "Screen.h"
#include "ScreenGame.h"
#include "FunctionCallTracker.h"
#include "EffectOnPickup.h"

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
				}				
			}
		else if (ownerObject->type == GObjType::PADDLE || ownerObject->type == GObjType::UPGRADE)
		{			
			if ((*it)->type == GObjType::BALL)
			{
				collidableObjects.push_back(*it);
			}
			
		}	
	}		
}
void Collider::CollisionEffect(float deltaTime)
{
	//FunctionCallTracker cc("start","funsuh");
	colliderTimer.Tick(deltaTime);
	if (this->colliderTimer.timePassed > deltaTime * 3)
	{
		for (auto it = collidableObjects.begin(); it != collidableObjects.end(); ++it)
		{
	//::::::::::::::::::::::::::::::if THIS object is ball::::::::::::::::::::::::::::::
			if (ownerObject->type == GObjType::BALL)
			{
				Ball &ball = ownerObject->GetAs<Ball>();
		//>>>>>>>>>>>>>>>>>>>>>>>.if ball is colliding with paddle<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				if ((*it)->type == GObjType::PADDLE)
				{			
					if (n_geometry::IsCircleAndRectColliding(*(*it), *ownerObject))
					{
						Paddle &paddle = (*it)->GetAs<Paddle>();
						colliderTimer.Reset();
						ball.lastHitByObj = &paddle;
						//if ball is on left/right side of paddle just change x-axis movement dir, no need for cnage of y-axis dir
						if (ownerObject->GetMiddleCord().x < paddle.cord.x || ownerObject->GetMiddleCord().x >paddle.cord.x + paddle.size.w)
						{
							bool ballIsOnLeft = ownerObject->GetMiddleCord().x < paddle.cord.x;
							for (Force &force : ownerObject->physics.forces)
							{
								force.dirX = (ballIsOnLeft) ? -1 : 1;
								force.dirY = (paddle.positionType == n_paddle::paddlePositionType::TOP) ? 1 : -1;
							}
						}
						//if ball is NOT on left/right side of paddle just change y-axis movement dir, it depends is it TOP/BOTTOM paddle
						else
						{
							bool paddleMovingLeft = (paddle.horizontalSpeed < 0) ? true : false;

							for (Force &force : ownerObject->physics.forces)
							{
								//change y directio based on what paddle it collided with
								if (paddle.positionType == n_paddle::paddlePositionType::TOP)
								{
									force.dirY = (ownerObject->GetMiddleCord().y < paddle.cord.y) ? -1 : 1;
								}
								else if (paddle.positionType == n_paddle::paddlePositionType::BOTTOM)
								{
									force.dirY = (ownerObject->GetMiddleCord().y > paddle.cord.y) ? 1 : -1;
								}
								//change X direction based on is paddle moving left or right	
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
							//depends when ball hit paddle curving will be bigger/smaller
							float amountOfCurving = 0.15;
							float distanceFromLeft_percent;
							if (paddle.horizontalSpeed < 0)
								distanceFromLeft_percent = 1 - ((ownerObject->GetMiddleCord().x - paddle.cord.x) / paddle.size.w);
							else
								distanceFromLeft_percent = ((ownerObject->GetMiddleCord().x - paddle.cord.x) / paddle.size.w);
							amountOfCurving *= distanceFromLeft_percent;

							if (paddleMovingLeft) {
								ownerObject->physics.AddForce(Force(1, 0, amountOfCurving, 0, 0.5f, forceType::KEEP_AFTER_DURATION_END, *ownerObject));
								ownerObject->physics.forces[ownerObject->physics.forces.size() - 1].dirX = -1;
							}
							else
								ownerObject->physics.AddForce(Force(1, 0, amountOfCurving, 0, 0.5, forceType::KEEP_AFTER_DURATION_END, *ownerObject));

						}
					}
				}
		//>>>>>>>>>>>>>>>>>>>>>>>.if ball is colliding with upgrade<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				if ((*it)->type == GObjType::UPGRADE)
				{
					Upgrade &upgrade = (*it)->GetAs<Upgrade>();
					if (ownerObject->GetAs<Ball>().lastHitByObj == NULL)	//if nobody touched it just skip everything
						continue;

					if (n_geometry::IsCircleAndRectColliding(*ownerObject, *(*it)) && upgrade.isCollidable)
					{		
						
						ScreenGame::CordsForEffects.push_back(Cord(upgrade.GetMiddleCord().x - n_effectOnPickup::w/2, upgrade.GetMiddleCord().y - n_effectOnPickup::h/2));
						upgrade.sizeState = n_gameObject::sizeStateType::RESIZING;
						upgrade.isCollidable = false;

						switch (upgrade.typeOfUpgrade)
						{
							case n_upgrade::upgradeType::PADDLE_INCREASE: 
							{
								ball.lastHitByObj->size.w *= 1.4f;
							} break;
							case n_upgrade::upgradeType::PADDLE_DECREASE:
							{
								for(GameObject *gameObject : GameObject::s_gameObjects)
									if (gameObject != ball.lastHitByObj) 
									{
										ball.lastHitByObj->size.w /= 1.4;
										break;
									}
							} break;
							case n_upgrade::upgradeType::BALL_SPEEDUP:
							{
								for (Force &force : ball.physics.forces)
									force.forceY *= 1.5f;
							} break;
							case n_upgrade::upgradeType::BALL_NUMx2:
							{
								ScreenGame::infoAboutBallsToAdd = make_pair(1, Cord(ball.cord.x, ball.cord.y));
							} break;
						}
						
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
