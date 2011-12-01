#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <iostream>
#include "util.h"

struct NoWrapping
{
	template <class T>
	static void wrap(T&) {}
};

struct WrapRadians
{
	template <class T>
	static void wrap(T& value)
	{
		normalizeAngle(value);
	}
};

template <
	typename T,
	class WrappingPolicy = NoWrapping
>
class Vector3
{
protected:
	T _x;
	T _y;
	T _z;
public:
	Vector3() : _x(), _y(), _z() {}

	template <typename U, typename V>
	Vector3(const Vector3<U, V>& other) :
		_x(other.x()),
		_y(other.y()),
		_z(other.z())
	{}

	Vector3(const T& x, const T& y, const T& z) :
		_x(x),
		_y(y),
		_z(z)
	{}

	T x() const { return _x; };
	void setX(const T& x)
	{
		_x = x;
		WrappingPolicy::wrap(_x);
	}
	void addX(const T& x) { setX(_x + x); }
	void rotateX(const T& radians)
	{
		if (!radians)
			return;
		set(
			_x,
			_y * cos(radians) - _z * sin(radians),
			_y * sin(radians) + _z * cos(radians));
	}

	T y() const { return _y; };
	void setY(const T& y)
	{
		_y = y;
		WrappingPolicy::wrap(_y);
	}
	void addY(const T& y) { setY(_y + y); }
	void rotateY(const T& radians)
	{
		if (!radians)
			return;
		set(
			_x * cos(radians) + _z * sin(radians),
			_y,
			_z * cos(radians) - _x * sin(radians));
	}

	T z() const { return _z; };
	void setZ(const T& z)
	{
		_z = z;
		WrappingPolicy::wrap(_z);
	}
	void addZ(const T& z) { setZ(_z + z); }
	void rotateZ(const T& radians)
	{
		if (!radians)
			return;
		set(
			_x*cos(radians) - _y*sin(radians),
			_x*sin(radians) + _y*cos(radians));
	}

	void set(const T& x, const T& y)
	{
		set(x, y, _z);
	}

	void set(const T& x, const T& y, const T& z)
	{
		setX(x);
		setY(y);
		setZ(z);
	}

	template <class T, typename U>
	void rotate(const Vector3<T, U>& radians)
	{
		rotateX(radians.x());
		rotateY(radians.y());
		rotateZ(radians.z());
	}

	T length() const
	{
		return sqrt(
			_x * _x +
			_y * _y +
			_z * _z);
	}

	void normalize()
	{
		const T len = length();
		if (len == 0) {
			return;
		}
		set(
			_x / len,
			_y / len,
			_z / len);
	}

	void zero()
	{
		set(0, 0, 0);
	}

	void scale(const T& factor)
	{
		set(
			_x * factor,
			_y * factor,
			_z * factor);
	}

	void dump() const
	{
		std::cout << "(x: " << _x << ", y: " << _y << ", z: " << _z << ")" << std::endl;
	}
};

#endif // VECTOR_H
