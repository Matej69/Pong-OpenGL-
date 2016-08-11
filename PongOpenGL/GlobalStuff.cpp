#include "GlobalStuff.h"
#include "GameObject.h"
#include "Sprite.h"

namespace n_geometry {
	void Cord::SetCord(float a, float b) { x = a; y = b; }
	Cord::Cord(float n1, float n2) : x(n1), y(n2) {};
	Cord::Cord	()	{};
	Cord::~Cord	()	{};

	void Size::SetSize(float a, float b) { w = a; h = b; }
	Size::Size(float n1, float n2) : w(n1), h(n2) {};
	Size::Size() {};
	Size::~Size() {};

	bool AreRectsColliding(const GameObject &thisObj, const GameObject &otherObj) {
		Cord topLeft(thisObj.cord.x - otherObj.size.w / 2						,thisObj.cord.y + otherObj.size.h / 2);
		Cord botRight(thisObj.cord.x + thisObj.size.w + otherObj.size.w / 2		,thisObj.cord.y - thisObj.size.h - otherObj.size.h / 2);
		const Cord &otherCord = Cord(otherObj.cord.x + otherObj.size.w/2, otherObj.cord.y - otherObj.size.h / 2);

		return (otherCord.x >= topLeft.x && otherCord.x <= botRight.x && otherCord.y >= botRight.y && otherCord.y <= topLeft.y);
	}
	bool AreCirclesColliding(const GameObject &thisObj, const GameObject &otherObj) {
		Cord midCordOf1Circle(thisObj.cord.x + thisObj.size.w / 2, thisObj.cord.y - thisObj.size.h / 2);
		Cord midCordOf2Circle(otherObj.cord.x + otherObj.size.w / 2, otherObj.cord.y - otherObj.size.h / 2);
		float distance = abs(sqrt(pow(midCordOf2Circle.x - midCordOf1Circle.x, 2) + pow(midCordOf2Circle.y - midCordOf1Circle.y, 2)));

		return (distance < thisObj.size.w / 2 + otherObj.size.w / 2);	
	}
	//Change later to actuall  circle-rect collision if you want, for now since circles are gonna be small, this will work as well
	bool IsCircleAndRectColliding(const GameObject &thisObj, const GameObject &otherObj) {
		Cord topLeft(thisObj.cord.x - otherObj.size.w / 2, thisObj.cord.y - otherObj.size.h / 2);
		Cord botRight(thisObj.cord.x + thisObj.size.w + otherObj.size.w / 2, thisObj.cord.y + thisObj.size.h + otherObj.size.h / 2);
		const Cord &otherCord = Cord(otherObj.cord.x + otherObj.size.w / 2, otherObj.cord.y + otherObj.size.h / 2);

		return (otherCord.x >= topLeft.x && otherCord.x <= botRight.x && otherCord.y <= botRight.y && otherCord.y >= topLeft.y);
	}
}