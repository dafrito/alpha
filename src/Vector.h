#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <iostream>

template <typename T>
class Vector3
{
	T _x;
	T _y;
	T _z;
public:
	Vector3() : _x(), _y(), _z() {}

	template <typename U>
	Vector3(const Vector3<U>& other) :
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
	void setX(const T& x) { _x = x; }
	void addX(const T& x) { setX(_x + x); }
	void rotateX(const T& radians)
	{
		// TODO The math here is very likely incorrect.
		setY(yzLength() * cos(radians));
		setZ(yzLength() * sin(radians));
	}

	T y() const { return _y; };
	void setY(const T& y) { _y = y; }
	void addY(const T& y) { setY(_y + y); }
	void rotateY(const T& radians)
	{
		// TODO The math here is very likely incorrect.
		setX(xzLength() * cos(radians));
		setZ(xzLength() * sin(radians));
	}

	T z() const { return _z; };
	void setZ(const T& z) { _z = z; }
	void addZ(const T& z) { setZ(_z + z); }
	void rotateZ(const T& radians)
	{
		// TODO The math here is very likely incorrect.
		setX(xyLength() * cos(radians));
		setY(xyLength() * sin(radians));
	}

	void set(const T& x, const T& y, const T& z)
	{
		setX(x);
		setY(y);
		setZ(z);
	}

	T xyLength() const
	{
		return sqrt(
			_x * _x +
			_y * _y);
	}

	T xzLength() const
	{
		return sqrt(
			_x * _x +
			_z * _z);
	}

	T yzLength() const
	{
		return sqrt(
			_y * _y +
			_z * _z);
	}

	T length() const
	{
		return pow(
			_x * _x +
			_y * _y +
			_z * _z,
			(T)1/3);
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
