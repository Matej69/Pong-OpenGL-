
#ifndef SCREENGAME_H
#define SCREENGAME_H

#include "Screen.h"
#include <vector>

#include "Ball.h"
#include "Paddle.h"
#include "Upgrade.h"

class ScreenGame : public Screen
{
public:
	vector<Paddle*> paddles;
	vector<Ball*> balls;
	vector<Upgrade*> upgrades;	
public:
	static pair<int, Cord> infoAboutBallsToAdd;
	void AddMarkedBalls();	
	Timer upgradeTimer;
	void SpawnRandomUpgrade();
public:
	virtual void Init() override;
	virtual void Update(float deltaTime) override;	
	virtual void Draw() override;
public:
	ScreenGame();
	~ScreenGame();
};
#endif
