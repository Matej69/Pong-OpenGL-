#include "EffectOnPickup.h"
#include "GlobalStuff.h"

namespace n_effectOnPickup {
	int w = 150;
	int h = 150;
	int maxSize = 5000;
	float sizeIncreaseSpeed = 1.00075f;
}


void EffectOnPickup::UpdateLogic(float deltaTime)
{
	n_effects::IncreaseByPercent(n_effectOnPickup::sizeIncreaseSpeed,*this);
}
void EffectOnPickup::InitSettings()
{
	this->sprite.InitSpriteTex("UpgradePickupEffect.png");
	this->size.SetSize(n_effectOnPickup::w, n_effectOnPickup::h);
	this->type = n_gameObject::GObjType::PICKUP_EFFECT;
}


EffectOnPickup::EffectOnPickup(int _x, int _y) : GameObject(_x,_y,n_effectOnPickup::w, n_effectOnPickup::h)
{
	InitSettings();
}
EffectOnPickup::~EffectOnPickup()
{
}
