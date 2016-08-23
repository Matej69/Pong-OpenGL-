#include "PointsLayer.h"
#include "Game.h"
#include "Screen.h"
#include "ScreenGame.h"

using namespace n_pointsLayer::n_nonSpecObj;

namespace n_pointsLayer {

	//...............................NonSpecific.................................
	void NonSpecificObject::UpdateLogic(float deltaTime)
	{
		this->UpdateGameObjectLogic(deltaTime);
		this->DrawSprite();
	}
	void NonSpecificObject::InitSettings()
	{
		this->type = n_gameObject::GObjType::NON_SPECIFIC;
		switch (nonsSpecType)
		{
		case nonSpecObjType::POINTER:	this->sprite.InitSpriteTex("POINTER.png");	break;
		case nonSpecObjType::SMILEY:	this->sprite.InitSpriteTex("SMILEY.png");	break;
		case nonSpecObjType::SPLITTER:	this->sprite.InitSpriteTex("SPLITTER.png");	break;
		}
	}

	NonSpecificObject::NonSpecificObject(int _x, int _y, int _w, int _h, nonSpecObjType specType)
		: GameObject(_x,_y,_w,_h)
	{
		nonsSpecType = specType;
		InitSettings();
	}
	NonSpecificObject::~NonSpecificObject()
	{
	}

	//...............................Explosion.................................
	void Explosion::AdvanceAnimation(float deltaTime)
	{
		if (nextSpriteTimer.IsFinished() && isFinished == false) {
			this->sprite.InitSpriteTex(expSpritePaths[currentSpriteID]);
			currentSpriteID++;
			nextSpriteTimer.Reset();

			if (currentSpriteID == expSpritePaths.size() - 1) {
				isFinished = true;
				static_cast<ScreenGame*>(Screen::currentScreen)->gameEnded = true;
			}
		}
		//if animation ended,,,,,, do something
	}

	void Explosion::UpdateLogic(float deltaTime)
	{			
		this->UpdateGameObjectLogic(deltaTime);
		AdvanceAnimation(deltaTime);
		this->DrawSprite();	
		cout << nextSpriteTimer.timePassed << endl;
		nextSpriteTimer.Tick(deltaTime);
		
	}
	void Explosion::InitSettings()
	{			
		nextSpriteTimer.Init(0.08f);
		isFinished = false;		
		currentSpriteID = 0;

		for (int i = 1; i < 16; ++i) {
			string path = "explosion/"+ to_string(i) + ".png";
			expSpritePaths.push_back(path);
		}
	}	

	Explosion::Explosion(int _x, int _y, int _w, int _h)
		: GameObject(_x, _y, _w, _h)
	{
		InitSettings();
	}
	Explosion::~Explosion()
	{
	}

	//................................PointsLayer.................................
	void PointsLayer::MovePointer(pointerDirType dir)
	{
		int direction = (dir == pointerDirType::DOWN) ? 1 : -1;
		for (ObjPtr pointer : pointers)
			pointer->cord.y += trackHeight * direction;
	}	
	void PointsLayer::SetSplittersNum(int _health)
	{
		numOfSplitters = (2 * _health) + 2;
	}


	void PointsLayer::Init(int _health)
	{
		Size winSize = n_window::windowSize;

		pointers.push_back( ObjPtr(new NonSpecificObject(0, winSize.h / 2 - POINTER_SIZE/2, POINTER_SIZE, POINTER_SIZE, nonSpecObjType::POINTER)));
		pointers.push_back(ObjPtr(new NonSpecificObject(winSize.w - POINTER_SIZE, winSize.h / 2 - POINTER_SIZE / 2, POINTER_SIZE, POINTER_SIZE, nonSpecObjType::POINTER)));
		pointers[1]->sprite.rotType = n_spriteFile::spriteRotType::ROTATED_180;

		SetSplittersNum(_health);
		this->trackHeight = n_window::windowSize.h / numOfSplitters;
		for (int i = 0; i < numOfSplitters; ++i) {
			if (i == 0 || i == numOfSplitters - 1)
				continue;
			splitters.push_back(ObjPtr(new NonSpecificObject(0, trackHeight * i + trackHeight / 2 - SPLITTER_SIZE/2, SPLITTER_SIZE, SPLITTER_SIZE, nonSpecObjType::SPLITTER)));
			splitters.push_back(ObjPtr(new NonSpecificObject(winSize.w - SPLITTER_SIZE, trackHeight * i + trackHeight / 2 - SPLITTER_SIZE / 2, SPLITTER_SIZE, SPLITTER_SIZE, nonSpecObjType::SPLITTER)));
			splitters[splitters.size() - 1]->sprite.rotType = n_spriteFile::spriteRotType::ROTATED_180;
		}

		numOfExplosions = 15;
		explosionSpawned = false;
	}
	void PointsLayer::Update(float deltaTime)
	{

		for (ObjPtr obj : pointers) {
			obj->UpdateLogic(deltaTime);
		}
		for (ObjPtr obj : splitters) {
			obj->UpdateLogic(deltaTime);
		}
				

		//spawn explosions
		if (!explosionSpawned)	{
			for (Paddle *paddle : static_cast<ScreenGame*>(Screen::currentScreen)->paddles) {
				if (paddle->health <= 0) {
					int explosionWidth = n_window::windowSize.w / numOfExplosions;
					if (paddle->positionType == n_paddle::TOP) {						
						for (int i = 0; i < numOfExplosions; ++i)
							explosions.push_back(new Explosion(i * explosionWidth - 90, -explosionWidth * 1.4f, explosionWidth*4, explosionWidth*4));
					}
					if (paddle->positionType == n_paddle::BOTTOM) {
						for (int i = 0; i < numOfExplosions; ++i)
							explosions.push_back(new Explosion(i * explosionWidth - 90, n_window::windowSize.h - explosionWidth*2.4f, explosionWidth*4, explosionWidth*4));
					}
					explosionSpawned = true;
				}				
			}
		}	

	}

	PointsLayer::PointsLayer(int _health)
	{
		Init(_health);
	}
	PointsLayer::~PointsLayer()
	{
	}

}