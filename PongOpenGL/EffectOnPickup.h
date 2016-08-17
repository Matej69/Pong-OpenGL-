
#ifndef EFFECTONPICKUP_H
#define EFFECTONPICKUP_H

#include "GameObject.h"

namespace n_effectOnPickup {
	extern int w, h;
	extern int maxSize;
	extern float sizeIncreaseSpeed;
}

class EffectOnPickup :  public GameObject
{
public:
	virtual	void	UpdateLogic(float deltaTime) ;
	virtual	void	InitSettings() ;
public:
	EffectOnPickup(int _x, int _y);
	~EffectOnPickup();
};
#endif

