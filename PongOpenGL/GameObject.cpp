#include "GameObject.h"
#include "FunctionCallTracker.h"




GameObject::GameObject(int _x, int _y, int _w, int _h)
{
	x = _x;		y = _y;
	w = _w;		h = _h;
}
GameObject::GameObject()
{
}
GameObject::~GameObject()
{
	FunctionCallTracker debugF("GameObject is being destroyed", "GameObject is destroyed susscesfully");
}
