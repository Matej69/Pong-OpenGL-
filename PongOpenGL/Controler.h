#ifndef CONTROLER_H
#define CONTROLER_H

#include <SDL.h>
class Paddle;

class Controler
{
public:
	Paddle			*ownerPaddle;
	SDL_Scancode	leftScancode;
	SDL_Scancode	rightScancode;	
public:
	void SetControls(SDL_Scancode _leftScancode, SDL_Scancode _rightScancode);
	void UpdateOnInput(float deltaTime);
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
public:
	void ApplyMovement(float deltaTime);
	void LimitSpeedIfNescessary();
public:
	Controler();
	~Controler();
};
#endif
