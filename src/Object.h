#ifndef OBJECT_H
#define OBJECT_H

#include "Vector.h"
#include "util.h"

using namespace nt;

class Object
{

	typedef Vector3<double> Position;
	typedef Vector3<double> Velocity;
	typedef Vector3<float, WrapRadians> Rotation;
public:
	Object() :  _baseAlpha(1), _alpha(_baseAlpha) {}

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

	void alpha(float alpha) {_alpha = alpha;}
	float alpha() {return _alpha;}
	void baseAlpha(float baseAlpha){_baseAlpha = baseAlpha;}
	float baseAlpha() {return _baseAlpha;}
protected:

	Position _position;
	Velocity _velocity;
	Rotation _rotation;
	float _baseAlpha;
	float _alpha;

};

#endif // Object_H
