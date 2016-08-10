
#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include <string>
using namespace std;
class SDL_Texture;

namespace n_spriteFile {
	extern string root;
}

class Sprite
{
public:
	//static map<,>
public:
	SDL_Texture	*texture;
private:
	string		src;
public:
	void Draw(int x, int y, int w, int h);
	void InitSpriteTex(string imgName);
	Sprite(string imgName);
	Sprite();
	~Sprite();
};
#endif 
