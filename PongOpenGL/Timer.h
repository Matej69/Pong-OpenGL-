#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
	float timeLeft;
	float startTime;
	float timePassed;
public:
	void Init(float _startTime);
	void Reset();
	bool IsFinished();
	void Tick(float deltaTime);
public:
	Timer(float _startTime);
	Timer();
	~Timer();
};
#endif
