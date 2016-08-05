#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Sprite.h"
#include "GlobalStuff.h"


class GameObject
{
public:
	int x, y, w, h;
public:
	Sprite sprite;
	//vector of all components
public:
	int Sum(int a, int b) { cout << a + b <<endl; return a + b; };
	//template<class objectType>
		//void Subscribe(/*Event e, f*/) { cout << "works \n"; };		
public:
	GameObject();
	GameObject(int _x, int _y, int _w, int _h);
	virtual ~GameObject();
};
#endif 

