#ifndef GLOBALSTUFF_H
#define GLOBALSTUFF_H

#include <iostream>
#include <string>
using namespace std;
#include <typeinfo>

class GameObject;

namespace n_globalStuff {
	template<class Type>
	string GetClassName(const Type &type) {
		return static_cast<string>(typeid(type).name()).substr(6, 20);
	}
}

namespace n_geometry {
	//***vector2 classes***
	class Cord {
	public:
		float x, y;
	public:
		void SetCord(float a, float b);
		Cord(float n1, float n2);
		Cord();
		~Cord();
	};
	class Size {
	public:
		float w,h;
	public:
		void SetSize(float a, float b);
		Size(float n1, float n2);
		Size();
		~Size();
	};
	//***Space geometry***
		//2 rect colliding, 2 circles colliding, rect and circle colliding
	extern bool AreRectsColliding		(const GameObject &thisObj, const GameObject &otherObj);
	extern bool AreCirclesColliding		(const GameObject &thisObj, const GameObject &otherObj);
	extern bool IsCircleAndRectColliding(GameObject &paddleObj, const GameObject &ballObj);
	extern bool IsCordInsideRect(GameObject &rectObj, const Cord &cord);
}

namespace n_effects {
	extern void ResizeByPercent(float f, GameObject &gameObject);
}
#endif