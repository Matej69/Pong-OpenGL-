
#ifndef  BALL_H
#define  BALL_H

#include "GameObject.h"

class Ball : public GameObject
{
public:
	GameObject *lastHitByObj;
public:
	void UpdateLogic(float deltaTime) override;
	void InitSettings() override;
	void BorderBounce();
public:
	Ball();
	Ball(int _x, int _y, int _w, int _h);
	~Ball();
};
#endif
