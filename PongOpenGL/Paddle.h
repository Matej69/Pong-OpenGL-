
#ifndef  PADDLE_H
#define  PADDLE_H

#include "GameObject.h"
#include "Controler.h"

namespace n_paddle {
	enum paddlePositionType {
		TOP,
		BOTTOM
	};	
}


class Paddle : public GameObject
{
public:								
	float	horizontalSpeed;
	float	horizontalAcc;
	float	currentAcc;
	float	maxSpeed;
public:
	n_paddle::paddlePositionType positionType;
public:
	Controler controler;
public:
	void RepositionIfOutOfBounds();
	void UpdateLogic(float deltaTime) override;
	void InitSettings() override;
	Paddle(int _x, int _y, int _w, int _h, n_paddle::paddlePositionType _type);
	Paddle(int _w, int _h, n_paddle::paddlePositionType _type);
	Paddle();	
	~Paddle();
};
#endif // ! PADDLE_H
