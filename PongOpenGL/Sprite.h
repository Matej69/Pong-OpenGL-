
#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include <string>
using namespace std;
class SDL_Texture;

namespace n_spriteFile {
	extern string root;
	enum spriteRotType { NORMAL, ROTATED_180};
}

class Sprite
{
public:
	//static map<,>
public:
	SDL_Texture	*texture;
	n_spriteFile::spriteRotType rotType;
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
