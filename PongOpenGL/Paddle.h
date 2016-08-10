
#ifndef  PADDLE_H
#define  PADDLE_H

#include "GameObject.h"
#include "Controler.h"

class Paddle : public GameObject
{
public:
	float	horizontalSpeed;
	float	horizontalAcc;
	float	currentAcc;
	float	maxSpeed;
public:
	Controler controler;
public:
	void UpdateLogic(float deltaTime) override;
	void InitSettings() override;
	Paddle();
	Paddle(int _x, int _y, int _w, int _h);
	~Paddle();
};
#endif // ! PADDLE_H
