
#ifndef SCREENGAME_H
#define SCREENGAME_H

#include "Screen.h"
#include <vector>

#include "Ball.h"
#include "Paddle.h"
#include "Upgrade.h"
#include "PointsLayer.h"
class EffectOnPickup;

#define PADDLE_HEALTH 4

class ScreenGame : public Screen
{

public:
	n_pointsLayer::PointsLayer *pointsLayer;
	bool gameEnded;
public:
	vector<Paddle*> paddles;
	vector<Ball*> balls;
	vector<Upgrade*> upgrades;	
	vector<EffectOnPickup*> effects;
public:
	static pair<int, Cord> infoAboutBallsToAdd;
	static vector<Cord> CordsForEffects;
	void AddMarkedBalls();	
	void UpdateEffectsIfNeeded();
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
