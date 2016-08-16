#include "FunctionCallTracker.h"

#include <iostream>


int FunctionCallTracker::levelNum = 0;
bool FunctionCallTracker::isPrinting = false;


FunctionCallTracker::FunctionCallTracker(string _startMessage, string _endMessage)
	: endMessage(_endMessage)
{	
	if (isPrinting) 
	{
		level = FunctionCallTracker::levelNum++;
		cout << "**" << level << "**" << _startMessage << endl;
	}
}


FunctionCallTracker::~FunctionCallTracker()
{
	if (isPrinting)
	{
		cout << "**" << level << "**" << endMessage << endl;
		if (this->level == 0)
			FunctionCallTracker::levelNum = 0;
	}
}
