#include "FunctionCallTracker.h"

#include <iostream>


int FunctionCallTracker::levelNum = 0;


FunctionCallTracker::FunctionCallTracker(string _startMessage, string _endMessage)
	: endMessage(_endMessage)
{
	level = FunctionCallTracker::levelNum++;
	cout << "**" << level << "**" << _startMessage << endl;
}


FunctionCallTracker::~FunctionCallTracker()
{
	cout << "**" << level << "**" << endMessage << endl;
	if (this->level == 0)
		FunctionCallTracker::levelNum = 0;
}
