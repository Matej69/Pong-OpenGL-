
#ifndef SCREEN_H
#define SCREEN_H

namespace n_screen {
	enum screenType {
		MENU,
		GAME,
		NONE
	};
}

class Screen
{
public:
	static void ChangeTo(n_screen::screenType _type);
	static void ChangeIfNeeded();
	static bool DidTypeChange();
	static Screen *currentScreen;
	static n_screen::screenType typeChangeHolder;
public:
	n_screen::screenType type;
public:	
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;	
	virtual void Draw() = 0;
public:
	Screen();
	virtual ~Screen() = 0;
};
#endif
