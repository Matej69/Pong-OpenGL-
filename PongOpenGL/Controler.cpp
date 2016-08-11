#include "Controler.h"
#include "Input.h"
#include "Paddle.h"



//***moving left/right will se if object is moving in opposite direction, if yes /1.007 until deltax>/< 0, 
//***else just change direction
void Controler::MoveLeft(float deltaTime)
{	
		ownerPaddle->currentAcc		=	-abs(ownerPaddle->horizontalAcc);	
}
void Controler::MoveRight(float deltaTime)
{
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
//********************************************

void Controler::UpdateOnInput(float deltaTime)
{		
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
		ownerPaddle->horizontalSpeed /= 1.0008;
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
