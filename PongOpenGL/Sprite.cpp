#include "Sprite.h"
#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>
#include "FunctionCallTracker.h"

namespace n_spriteFile {
	string root = "Images/";
}

void Sprite::Draw(int x, int y, int w, int h)
{	
	SDL_Rect destination = { x,y,w,h };
	if (rotType == n_spriteFile::spriteRotType::NORMAL) {		
		SDL_RenderCopy(n_window::renderer, texture, NULL, &destination);
	}
	else if (rotType == n_spriteFile::spriteRotType::ROTATED_180) {
		SDL_Point pivot = { w / 2,h / 2 };
		SDL_RenderCopyEx(n_window::renderer, texture, NULL, &destination, 180, &pivot, SDL_FLIP_NONE);
	}
}


void Sprite::InitSpriteTex(string imgName)
{
	FunctionCallTracker debugF(string("Sprite is being created NAME=") + imgName, "Sprite is created SUSSCESSFULY or doesnt exist");
	//loads but ong rgb error is here, but works soo..... heh 
	src = n_spriteFile::root + imgName;
	SDL_Surface *surface = IMG_Load(src.c_str());
	texture = SDL_CreateTextureFromSurface(n_window::renderer, surface);
	SDL_FreeSurface(surface);
}

Sprite::Sprite(string imgName)
{
	//sprite type is always normal at first, later can be changed depending which class it is asigned to
	rotType = n_spriteFile::spriteRotType::NORMAL;
	InitSpriteTex(imgName);
}
Sprite::Sprite()
{
}
Sprite::~Sprite()
{
	FunctionCallTracker debugF(string("Sprite is being destroied NAME=") + this->src, "Sprite is destroyed SUSSCESSFULY");
	SDL_DestroyTexture(texture);
}
