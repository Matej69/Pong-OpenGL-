#ifndef  POINTSLAYER_H
#define  POINTSLAYER_H

#include "GameObject.h"
#include <memory>

namespace n_pointsLayer {

	#define SMILE_SIZE 80
	#define POINTER_SIZE 40
	#define SPLITTER_SIZE 30	

	//explosion class
	//creates object that can be drawn,moved by position, rotated (NonSpecificObject = GameObject - virtual)	
	namespace n_nonSpecObj {
		enum nonSpecObjType { POINTER, SPLITTER, SMILEY };
	}
	
	class NonSpecificObject : public GameObject {		
	public:
		n_nonSpecObj::nonSpecObjType nonsSpecType;
	public:
		void	UpdateLogic(float deltaTime)override;
		void	InitSettings()				override;
	public:
		NonSpecificObject(int _x, int _y, int _w, int _h, n_nonSpecObj::nonSpecObjType specType);
		~NonSpecificObject();
	};

	class Explosion : public GameObject {
	public:
		int currentSpriteID;
		vector<string> expSpritePaths;
		Timer nextSpriteTimer;
		bool isFinished;
	public:
		void AdvanceAnimation(float deltaTime);
	public:
		void	UpdateLogic(float deltaTime)override;
		void	InitSettings()				override;
	public:
		Explosion(int _x, int _y, int _w, int _h);
		~Explosion();
	};

	//PointsLayer holds NonSpecificObjects and updates score visualy
	enum pointerDirType { UP, DOWN };

	class PointsLayer
	{
	typedef shared_ptr<NonSpecificObject> ObjPtr;	
	public:
		int numOfSplitters;
		int trackHeight;
		bool explosionSpawned;
		int numOfExplosions;
	public:
		vector<ObjPtr> smiles;
		vector<ObjPtr> pointers;
		vector<ObjPtr> splitters;
		vector<Explosion*> explosions;
	public:
		void Init(int _health);
		void Update(float deltaTime);
		void MovePointer(pointerDirType dir);
		void SetSplittersNum(int _health);		//we get num of splitters from health
	public:
		PointsLayer(int _health);
		~PointsLayer();
	};
}
#endif
