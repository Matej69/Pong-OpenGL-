#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
class Game;

#include <map>
using namespace std;

class Input
{
public:
	static map<SDL_Scancode, bool> s_heldKeys;
	static map<SDL_Scancode, bool> s_releaseKeys;
public:
	void OnInputEvent(Game *game);
	void OnKeyDown(SDL_Scancode key);
	void OnKeyUp(SDL_Scancode key);
	bool IsKeyUp(SDL_Scancode key);
	bool IsKeyDown(SDL_Scancode key);
	Input();
	~Input();
};
#endif
