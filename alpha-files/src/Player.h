#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"

using namespace nt;

class Player : public Object
{


public:
	Player(const char* name): Object(), _name(name) {}

	void name(const char* name)
	{
	_name = name;
	}
	const char* name()
	{
		return _name;
	}

protected:
		const char* _name;
};

#endif // PLAYER_H
