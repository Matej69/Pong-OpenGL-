
#ifndef BUTTON_H
#define BUTTON_H

#include "GameObject.h"

namespace n_button {
	enum buttonType {
		NEW,
		EXIT
	};
	extern Cord cord;
	extern Size size;
	extern int vertDistance;
	extern void UpdateDefaultProperties();
}

class Button : public GameObject
{
public:
	void OnButtonClick(int _x, int _y);
	n_button::buttonType buttonType;
public:
	void	UpdateLogic(float deltaTime) override;
	void	InitSettings() override;
public:
	Button(int _x, int _y, int _w, int _h, n_button::buttonType _type);
	Button();
	~Button();
};
#endif
