#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"

using namespace nt;

class Player : public Object
{


public:
	Player(char* name): Object(), _name(name) {}

	void name(char* name)
	{
	_name = name;
	}
	char* name()
	{
		return _name;
	}

protected:
		char* _name;
};

#endif // PLAYER_H
