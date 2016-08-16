#include "Timer.h"


void Timer::Reset()
{
	timeLeft = startTime;
}
void Timer::Tick(float deltaTime)
{	
	timeLeft -= deltaTime;
	timePassed = startTime - timeLeft;
}
bool Timer::IsFinished()
{
	return (timeLeft <= 0);
}

void Timer::Init(float _startTime)
{
	startTime = _startTime;
	timeLeft = _startTime;
}

Timer::Timer(float _startTime)
{
	Init(_startTime);
}
Timer::Timer()
{
}
Timer::~Timer()
{
}
