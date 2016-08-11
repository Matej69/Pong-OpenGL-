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

Timer::Timer(float _startTime)
{
	startTime = _startTime;
	timeLeft = _startTime;
}
Timer::Timer()
{
}
Timer::~Timer()
{
}
