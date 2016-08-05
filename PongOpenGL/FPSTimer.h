
#define MIN_FPS 30
#define MAX_FRAMETIME (float)1/MIN_FPS

class FPSTimer
{
private:
	float	endFrameTime;
	float	currentFrameTime;	
	int		FPSCounter;				//resets to 0 on start of every new second
	float	holdEndFrameTime;		//used for displaying FPS for LAST frame
public:
	float	deltaTime;
	float	 FPS;					//holds frame number before FPSCounter resets
public:
	void	UpdateDeltaTime();
	void	PrintDeltaTime();

	void	UpdateFramesPerSec();
	void	PrintFramesPerSec();

	bool	IsNewSec();
	
	FPSTimer();
	~FPSTimer();
};

