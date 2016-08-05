#ifndef ISUBSCRIBER_H
#define ISUBSCRIBER_H

#include <iostream>
#include <string>
using namespace std;

/*****	"ISubscriber" will be casted to "Subscriber" so we can call "Subscriber->ObjectFun"
 *****	"ISubscriber" needs "subscriberObjType" because we need information what is the type of 
		"Subscriber->Object" so we can pass his class type as template when casting
 ***** Only reason we have "ISubscriber" is because we can't have template class in vector or list
*/
class ISubscriber
{
public:
	string subscriberObjType;
public:
	ISubscriber();
	~ISubscriber();
};
#endif
