#include "Event.h"
#include "Subscriber.h"

#include <string>

map<EType, Event*> Event::s_events;


int Event::GetNumOfSubs() {
	return subscribers.size();
}

Event::Event(EType _type)
{	
	FunctionCallTracker debugFun(string("Event is being created TYPE=") + to_string(_type), "Event susscessfully created or already exists in 's_events'");
	this->type = _type;
	//if exists return ? //if not insert
	if (s_events.find(_type) != s_events.end()) 
	{

		cout << "Event already exists!" << endl;
		return;
	}
	else
	{
		s_events.insert(make_pair(type, this));
	}
	
}
Event::~Event()
{
	cout << "**LINE:"<< __LINE__ << "Deleting event" << this->type << endl;
	s_events.erase(this->type);
	cout << "**SUSCESS" << endl;

}
