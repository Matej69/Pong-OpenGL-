
#ifndef FCTracker_H
#define FCTracker_H

#include <string>
using namespace std;

class FunctionCallTracker
{
public:
	static int levelNum;
public:
	int level;
	string endMessage;
public:
	FunctionCallTracker(string _startMessage, string _endMessage);
	~FunctionCallTracker();
};
#endif
