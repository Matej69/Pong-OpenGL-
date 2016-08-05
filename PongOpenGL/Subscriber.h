#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include "ISubscriber.h"
#include "Event.h"

/*
***** "Subscriber" holds object and function pointer to one of the functions that is in object class
*/

template<class ObjectClass, class ReturnType, class ...Params>
class Subscriber : public ISubscriber
{
public:
	ObjectClass *gameObject;
	ReturnType(ObjectClass::*gameObjectFunction)(Params...);

public:		
	void CallFunction(Params... parameters) { 
			FunctionCallTracker debugF("Calling functioPointer function from 'Subscriber.h' ", "Sprite is created OR already exist");
			(gameObject->*gameObjectFunction)(parameters...);
		};

public:
	Subscriber(ObjectClass &passedObject, ReturnType(ObjectClass::*passedGameObjectFunction)(Params...)) {
		FunctionCallTracker debugF("Creating Subscriber pair", "Subscriber pair has been created");
		gameObject = &passedObject;
		gameObjectFunction = passedGameObjectFunction;
	};

	~Subscriber() {};
};
#endif
