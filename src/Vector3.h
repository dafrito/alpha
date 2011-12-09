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
		nt::normalizeAngle(value);
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
		_x(other._x),
		_y(other._y),
		_z(other._z)
	{}

	Vector3(const T& x, const T& y, const T& z) :
		_x(x),
		_y(y),
		_z(z)
	{}

	const T& x() const { return _x; };
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

	const T& y() const { return _y; };
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

	const T& z() const { return _z; };
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
		setX(x);
		setY(y);
	}

	void set(const T& x, const T& y, const T& z)
	{
		setX(x);
		setY(y);
		setZ(z);
	}

	template <class U>
	void add(const U x, const U y, const U z)
	{
		addX(x);
		addY(y);
		addZ(z);
	}

	template <class U, class V>
	Vector3<T, WrappingPolicy> operator +(const Vector3<U, V>& other) const
	{
		Vector3<T, WrappingPolicy> vec(*this);
		vec += other;
		return vec;
	}

	template <class U, class V>
	Vector3<T, WrappingPolicy>& operator +=(const Vector3<U, V>& other)
	{
		add(other._x, other._y, other._z);
		return *this;
	}

	template <class U, class V>
	Vector3<T, WrappingPolicy> operator -(const Vector3<U, V>& other) const
	{
		Vector3<T, WrappingPolicy> vec(*this);
		vec.add(-other._x, -other._y, -other._z);
		return vec;
	}

	template <class U, class V>
	Vector3<T, WrappingPolicy>& operator -=(const Vector3<U, V>& other)
	{
		this->add(-other._x, -other._y, -other._z);
		return *this;
	}

	template <class U, class V>
	void rotate(const Vector3<U, V>& radians)
	{
		rotateX(radians._x);
		rotateY(radians._y);
		rotateZ(radians._z);
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

	void clear()
	{
		_x = _y = _z = 0;
	}

	template<typename U>
	Vector3<T, WrappingPolicy> operator*(const U& factor)
	{
		Vector3<T, WrappingPolicy> result(*this);
		result *= factor;
		return result;
	}

	template<typename U>
	Vector3<T, WrappingPolicy>& operator*=(const U& factor)
	{
		set(
			_x * factor,
			_y * factor,
			_z * factor);
		return *this;
	}

	template<typename U>
	Vector3<T, WrappingPolicy> operator/(const U& factor)
	{
		Vector3<T, WrappingPolicy> result(*this);
		result /= factor;
		return result;
	}

	template<typename U>
	Vector3<T, WrappingPolicy>& operator/=(const U& factor)
	{
		set(
			_x / factor,
			_y / factor,
			_z / factor);
		return *this;
	}

	void dump() const
	{
		std::cout << "(x: " << _x << ", y: " << _y << ", z: " << _z << ")" << std::endl;
	}

	template<typename U>
	bool equals(U x, U y, U z) const
	{
		return _x == x && _y == y && _z == z;
	}

	template<typename U, class V>
	bool operator ==(const Vector3<U, V>& other) const
	{
		return equals(other._x, other._y, other._z);
	}

	template <typename U, class V>
	bool operator !=(const Vector3<U, V>& other) const
	{
		return !(*this == other);
	}

	Vector3<T, WrappingPolicy> operator-() const
	{
		return Vector3<T, WrappingPolicy>(-_x, -_y, -_z);
	}

	operator bool() const
	{
		return _x || _y || _z;
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
