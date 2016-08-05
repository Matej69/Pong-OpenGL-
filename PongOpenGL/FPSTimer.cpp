#include "FPSTimer.h"
#include "SDL.h"

#include <iostream>
#include <string>
using namespace std;


bool FPSTimer::IsNewSec()
{
	return (int)(holdEndFrameTime / 1000) < (int)(currentFrameTime / 1000);
}
//*************************Delta time calculations*******************
void FPSTimer::UpdateDeltaTime()
{
	currentFrameTime	=	SDL_GetTicks();
	deltaTime			=	(currentFrameTime - endFrameTime) / 1000;
	deltaTime			=	deltaTime > MAX_FRAMETIME ? MAX_FRAMETIME : deltaTime;		
	holdEndFrameTime	=	(int)(endFrameTime);
	endFrameTime		=	SDL_GetTicks();	
		
}
void FPSTimer::PrintDeltaTime()
{
	cout << deltaTime << endl;
}
//*************************FPS calculations*******************
void FPSTimer::UpdateFramesPerSec()
{
	if (IsNewSec() == false)
		FPSCounter += 1;
	else {
		FPS			= FPSCounter;
		FPSCounter	= 0;
	}
	
}
void FPSTimer::PrintFramesPerSec()
{
	if(IsNewSec() == true)
		cout << FPS << endl;
}


FPSTimer::FPSTimer()
{
	endFrameTime		= SDL_GetTicks();
	currentFrameTime	= SDL_GetTicks();
	FPSCounter			= 1;				//avoiding 0 devision stuff -> inital value is not important
	FPS					= 1;
	holdEndFrameTime	= 1;
}
FPSTimer::~FPSTimer()
{
}
