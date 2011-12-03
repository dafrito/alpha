#ifndef PLAYER_H
#define PLAYER_H

#include "Vector.h"
#include "util.h"

using namespace nt;

class Player
{
	typedef Vector3<double> Position;
	typedef Vector3<double> Velocity;
	typedef Vector3<float, WrapRadians> Rotation;

	Position _position;
	Velocity _velocity;
	Rotation _rotation;
	char* _name;
public:
	Player(char* name) : _name(name), defaultAlpha(1), alpha(defaultAlpha) {}

	Position& position()
	{
		return _position;
	}

	Velocity& velocity()
	{
		return _velocity;
	}

	Rotation& rotation()
	{
		return _rotation;
	}

	void name(char* name)
	{
	_name = name;
	}
	char* name()
	{
		return _name;
	}
	float defaultAlpha;
	float alpha;
};

#endif // PLAYER_H
