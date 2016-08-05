
class SDL_Window;
class SDL_Surface;
class SDL_Renderer;

namespace n_window {
	extern	int				w, h;
	extern	SDL_Window		*window;
	extern	SDL_Renderer	*renderer;
}

class Game
{
public:
	bool CreateWindow(int _w, int _h);
	void PaintBackground(int r, int g, int b, int a);
	void GameLoop();
	Game();
	~Game();
};

