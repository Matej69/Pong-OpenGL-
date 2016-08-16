#include "GlobalStuff.h"
#include "GameObject.h"
#include "Paddle.h"
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
	//****************	works for ball-object collider of paddle -> paddle can be TOP OR BOTTOM	*********************
	bool IsCircleAndRectColliding(GameObject &paddleObj, const GameObject &ballObj) {	
		Paddle &PaddleObj = paddleObj.GetAs<Paddle>();
		bool ballIsOnRightSide;
		//apply collision only if TOP/BOTTOM of paddle is touched by ball, 'ballIsOnRightSide' turnes		
		
		Cord topLeft(paddleObj.cord.x - ballObj.size.w / 2, paddleObj.cord.y - ballObj.size.h / 2);
		Cord botRight(paddleObj.cord.x + paddleObj.size.w + ballObj.size.w / 2, paddleObj.cord.y + paddleObj.size.h + ballObj.size.h / 2);
		//const Cord &ballMiddleCord = Cord(ballObj.cord.x + ballObj.size.w / 2, ballObj.cord.y + ballObj.size.h / 2);
		Cord &ballMiddleCord = ballObj.GetMiddleCord();
		
		bool thereIsCollision = (ballMiddleCord.x >= topLeft.x && ballMiddleCord.x <= botRight.x && ballMiddleCord.y <= botRight.y && ballMiddleCord.y >= topLeft.y);
		return thereIsCollision;
	}

	bool IsCordInsideRect(GameObject &rect, const Cord &cord) {
		if (cord.x > rect.cord.x && cord.y > rect.cord.y && cord.x < rect.cord.x + rect.size.w && cord.y > rect.cord.y &&
			cord.x > rect.cord.x && cord.y < rect.cord.y + rect.size.h && cord.x < rect.cord.x + rect.size.w && rect.cord.y + rect.size.h)
			return true;
		return false;
	}
}

namespace n_effects {
	void ResizeByPercent(float f, GameObject &obj)
	{
		Size reduceToSize(obj.size.w * f, obj.size.h * f);
		Cord moveToCord(obj.cord.x + (obj.size.w - reduceToSize.w)/2, obj.cord.y + (obj.size.h - reduceToSize.h) / 2);
		obj.size.SetSize(reduceToSize.w, reduceToSize.h);
		obj.cord.SetCord(moveToCord.x, moveToCord.y);
	}
}