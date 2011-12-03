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
// XXX: Y-axis rotation is commented out until we figure out how to handle it
// Object rotations needs to rotate Z-axis first then X, the opposite of the way we handle the camera
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

	template <class U, class V>
	void add(const Vector3<U, V>& other)
	{
		addX(other.x());
		addY(other.y());
		addZ(other.z());
	}

	template <class U, class V>
	void rotate(const Vector3<U, V>& radians)
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

namespace nt
{
	template <class U>
	void glTranslate(const Vector3<float, U>& vec)
	{
		glTranslatef(vec.x(), vec.y(), vec.z());
	}

	template <class U>
	void glTranslate(const Vector3<double, U>& vec)
	{
		glTranslated(vec.x(), vec.y(), vec.z());
	}

	template <class T, class U>
	void glRotateRadians(const Vector3<T, U>& vec)
	{
		glRotated(vec.z() * TO_DEGREES, 0, 0, 1);
		glRotated(vec.x() * TO_DEGREES, 1, 0, 0);
		//glRotated(vec.y() * TO_DEGREES, 0, 1, 0);

	}

	template <class T, class U>
	void glRotateDegrees(const Vector3<T, U>& vec)
	{
		glRotated(vec.z(), 0, 0, 1);
		glRotated(vec.x(), 1, 0, 0);
		// glRotated(vec.y(), 0, 1, 0);

	}

	template <class U>
	void glRotateRadians(const Vector3<float, U>& vec)
	{
		glRotatef(vec.z() * TO_DEGREES, 0, 0, 1);
		glRotatef(vec.x() * TO_DEGREES, 1, 0, 0);
		//glRotatef(vec.y() * TO_DEGREES, 0, 1, 0);

	}

	template <class U>
	void glRotateDegrees(const Vector3<float, U>& vec)
	{
		glRotatef(vec.z(), 0, 0, 1);
		glRotatef(vec.x(), 1, 0, 0);
		// glRotatef(vec.y(), 0, 1, 0);

	}
	// these 2 functions are for the camera
	// backwards means everything flipped!
	// values are negative and x is rotated before z
	template <class U>
	void glRotateRadiansBackwards(const Vector3<float, U>& vec)
	{
		glRotatef(-vec.x() * TO_DEGREES, 1, 0, 0);
		glRotatef(-vec.z() * TO_DEGREES, 0, 0, 1);
	}
	template <class T, class U>
	void glRotateRadiansBackwards(const Vector3<T, U>& vec)
	{
		glRotated(-vec.x() * TO_DEGREES, 1, 0, 0);
		glRotated(-vec.z() * TO_DEGREES, 0, 0, 1);
	}

};

#endif // VECTOR_H
