#ifndef GAME_H
#define GAME_H

#include <SDL.h>

#include "GlobalStuff.h"
using namespace n_geometry;

namespace n_window {
	extern	Size			windowSize	;
	extern	SDL_Window		*window		;
	extern	SDL_Renderer	*renderer	;
}

class Game
{
public:
	static bool isRunning;
public:
	bool CreateWindow(int _w, int _h);
	void PaintBackground(int r, int g, int b, int a);
	void GameLoop();
	Game();
	~Game();
};
#endif
