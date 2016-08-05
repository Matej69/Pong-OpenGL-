#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
class Game;

#include <map>
using namespace std;

class Input
{
private:
	map<SDL_Scancode, bool> heldKeys;
	map<SDL_Scancode, bool> releaseKeys;	
public:
	void OnInputEvent();
	void OnKeyDown(SDL_Scancode key);
	void OnKeyUp(SDL_Scancode key);
	bool IsKeyUp(SDL_Scancode key);
	bool IsKeyDown(SDL_Scancode key);
	Input();
	~Input();
};
#endif
