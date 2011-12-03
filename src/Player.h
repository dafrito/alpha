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
	float _baseAlpha;
	float _alpha;
public:
	Player(char* name) : _name(name), _baseAlpha(1), _alpha(_baseAlpha) {}

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
	void alpha(float alpha) {_alpha = alpha;}
	float alpha() {return _alpha;}
	void baseAlpha(float baseAlpha){_baseAlpha = baseAlpha;}
	float baseAlpha() {return _baseAlpha;}

};

#endif // PLAYER_H
