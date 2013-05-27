#ifndef OBJECT_H
#define OBJECT_H

#include "Vector3.hpp"
#include "gl/util.hpp"

namespace nt {

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
	void velocity(double x, double y, double z)
	{
		_velocity.setX(x);
		_velocity.setY(y);
		_velocity.setZ(z);
	}
	void addVelocity(double x, double y, double z)
	{
		_velocity.addX(x);
		_velocity.addY(y);
		_velocity.addZ(z);
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

} // namespace nt

#endif // Object_H
