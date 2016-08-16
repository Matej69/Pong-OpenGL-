
#ifndef SCREENMENU_H
#define SCREENMENU_H

#include "Screen.h"
class Button;

class ScreenMenu : public Screen
{
public:
	Button *buttonStart;
	Button *buttonExit;
public:
	 void Init() override;
	 void Update(float deltaTime) override;	
	 void Draw() override;
public:
	ScreenMenu();
	~ScreenMenu();
};
#endif
