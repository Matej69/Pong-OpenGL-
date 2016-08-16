
#ifndef UPGRADE_H
#define UPGRADE_H

#include "GameObject.h"
class Timer;

namespace n_upgrade {
	enum upgradeType {
		PADDLE_INCREASE,
		PADDLE_DECREASE,
		BALL_SPEEDUP,
		BALL_NUMx2
	};
}

class Upgrade : public GameObject
{
public:
	n_upgrade::upgradeType typeOfUpgrade;	
	bool isCollidable;
public:
	virtual	void UpdateLogic(float deltaTime) override;
	virtual	void InitSettings() override;
	void ChoseSprite();
public:
	Upgrade(int _x, int _y, int _w, int _h, n_upgrade::upgradeType _type);
	Upgrade();
	~Upgrade();
};
#endif
