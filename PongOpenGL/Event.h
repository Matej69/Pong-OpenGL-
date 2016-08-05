#ifndef EVENT_H
#define EVENT_H

/*****************Every event when called(CallEvent) is passing given arguments to every subscribed object of that event
****************whick means that all (ISubscriber*) must point to "Subscriber" that has pointer function that accepts given arguments
***** EXAMPLE.........
	GameObject o;
	Event mouseCLICK(n_event::EType::KEY_DOWN);
	mouseCLICK.Register<GameObject, int, int, int>(o, &GameObject::Sum);
	mouseCLICK.CallEvent<int, int>(3, 7);
*/

#include <map>
#include <vector>
using namespace std;

#include "GlobalStuff.h"
#include "FunctionCallTracker.h"

class ISubscriber;

namespace n_event {
	enum EType {
		KEY_DOWN,
		KEY_UP,
		MOUSE_CLICK
	};
}
using namespace n_event;


class Event
{
public:
	static map<EType, Event*> s_events;
public:
	vector<ISubscriber*> subscribers;
	EType type;
public:
	template<class Object, class Return, class ...Params>
		void Register(Object &object, Return(Object::*objectFun)(Params...)) {
			FunctionCallTracker debugFun(string("Registering object to event" + to_string(type)), "Registration was suscessfull");
			ISubscriber *pointerToSub = new Subscriber<Object, Return, Params...>(object, objectFun);
			pointerToSub->subscriberObjType = n_globalStuff::GetClassName(object);
			subscribers.push_back(pointerToSub);
		}
	template<class ...Params>
		void CallEvent(Params ...params) {
			FunctionCallTracker debugFun(string("Event is being called TYPE=" + to_string(type)), "Call was suscessfull");
			int counter = 0;
			for (ISubscriber *sub : subscribers) {
				cout << "("<< counter++ <<") ..." ;
				if (sub->subscriberObjType == "GameObject") { static_cast<Subscriber<GameObject, void, Params...>*>(sub)->CallFunction(params...); }				
			}
		}
	template<class Object,class Return, class ...Params >
		void RemoveSubscriber(Object *subToRemove) {
			FunctionCallTracker debugFun(string("Trying to find object to remove from event" + to_string(type)), "Trying to remove was suscessfull");
			int index = 0;
			for (ISubscriber *sub : subscribers) {
				if(static_cast<Subscriber<Object,Return,Params...>*>(sub)->gameObject == subToRemove){ 
					FunctionCallTracker debugFun2(string("Removing object from event TYPE=" + to_string(type)), "Removal was suscessfull");
					subscribers.erase(subscribers.begin() + index);
					return;
				}
				++index;
			}
		}
public:
		template<class Object, class Return, class ...Params >
			static void RemoveSubscriberFromAll(Object *subToRemove) {			
				FunctionCallTracker debugFun("Trying to remove object from all events", "Trying to remove was suscessfull");
				for (auto it = s_events.begin(); it != s_events.end(); ++it)
				{			
					int index = 0;
					for (ISubscriber *sub : it->second->subscribers) {
						if (static_cast<Subscriber<Object, Return, Params...>*>(sub)->gameObject == subToRemove) {
							FunctionCallTracker debugFun(string("Removing object from from event TYPE=" + to_string(it->second->type)), string("Object removed from event TYPE=" + to_string(it->second->type)));
							it->second->subscribers.erase(it->second->subscribers.begin() + index);
							break;
						}
						++index;
					}					
				}			
			}
	

public:
	int GetNumOfSubs();
	Event(EType _type);
	~Event();
};
#endif

