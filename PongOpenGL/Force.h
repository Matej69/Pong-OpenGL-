#ifndef FORCE_H
#define FORCE_H

class GameObject;

namespace n_force {
	enum forceType {
		KEEP_AFTER_DURATION_END,
		REMOVE_AFTER_DURATION_END
	};
}

class Force
{
public:
	GameObject *ownerGO;
	n_force::forceType type;
public:
	float forceX, forceY;
	float accX, accY;
	float duration;
	int dirX, dirY;
public:
	void ApplyForce(float deltaTime);
	Force(float _forceX, float _forceY, float accX, float accY, float _duration, n_force::forceType _type, GameObject &_ownerGO);
	Force();
	~Force();
};
#endif
