#include "Controler.h"
#include "Input.h"
#include "Paddle.h"

namespace n_controler {
	float lastX		= 0;
	float newX		= 0;
	float deltaX	= 0;
}
using namespace n_controler;

//***moving left/right will se if object is moving in opposite direction, if yes /1.007 until deltax>/< 0, 
//***else just change direction
void Controler::MoveLeft(float deltaTime)
{	
	if (deltaX > 0)
		ownerPaddle->horizontalSpeed /= 1.007;
	else
		ownerPaddle->currentAcc		=	-abs(ownerPaddle->horizontalAcc);
}
void Controler::MoveRight(float deltaTime)
{
	if (deltaX < 0)
		ownerPaddle->horizontalSpeed /= 1.007;
	else
		ownerPaddle->currentAcc		=	abs(ownerPaddle->horizontalAcc);
}

void Controler::SetControls(SDL_Scancode _leftScancode, SDL_Scancode _rightScancode)
{
	leftScancode = _leftScancode;
	rightScancode = _rightScancode;
}
//********************************************
//***Speed stuff that should not be here******
//********************************************
void Controler::ApplyMovement(float deltaTime)
{
	ownerPaddle->horizontalSpeed += ownerPaddle->currentAcc;
	ownerPaddle->cord.x += ownerPaddle->horizontalSpeed * deltaTime;
}
void Controler::LimitSpeedIfNescessary()
{
	if (ownerPaddle->horizontalSpeed > ownerPaddle->maxSpeed)
		ownerPaddle->horizontalSpeed = ownerPaddle->maxSpeed;
	if (ownerPaddle->horizontalSpeed < -ownerPaddle->maxSpeed)
		ownerPaddle->horizontalSpeed = -ownerPaddle->maxSpeed;
}
void Controler::UpdateDeltaX()
{
	newX = this->ownerPaddle->cord.x;
	deltaX = (lastX - newX) *-1;
	lastX = newX;
}
//********************************************

void Controler::UpdateOnInput(float deltaTime)
{	
	UpdateDeltaX();

	if (Input::s_heldKeys[leftScancode])
	{
		MoveLeft(deltaTime);
	}
	else if (Input::s_heldKeys[rightScancode])
	{
		MoveRight(deltaTime);
	}
	else
	{		
		SDL_Delay(1);			//needed when getting deltaX -> to small values become 0 so we wait slow framerate
		if (deltaX > 0)
			ownerPaddle->horizontalSpeed /= 1.007;
		if(deltaX < 0)
			ownerPaddle->horizontalSpeed /= 1.007;
		ownerPaddle->currentAcc = 0;
	}

	LimitSpeedIfNescessary();
	ApplyMovement(deltaTime);
}

Controler::Controler()
{
}
Controler::~Controler()
{
}
