#ifndef GLOBALSTUFF_H
#define GLOBALSTUFF_H

#include <iostream>
#include <string>
using namespace std;
#include <typeinfo>

namespace n_globalStuff {
	template<class Type>
	string GetClassName(Type type) {
		return static_cast<string>(typeid(type).name()).substr(6, 20);
	}



}

#endif