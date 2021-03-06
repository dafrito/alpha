#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <iostream>
#include "math.hpp"

namespace nt {

/**
 * A no-op wrapping policy
 */
struct NoWrapping
{
	template <class T>
	static void wrap(T&) {}
};

/**
 * Treat the vector as a radian rotation during wrapping
 */
struct WrapRadians
{
	template <class T>
	static void wrap(T& angle)
	{
		nt::normalizeRadians(angle);
	}
};

/**
 * Treat the vector as a degree rotation during wrapping
 */
struct WrapDegrees
{
	template <class T>
	static void wrap(T& angle)
	{
		nt::normalizeDegrees(angle);
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

	void rewrapAll()
	{
		WrappingPolicy::wrap(_x);
		WrappingPolicy::wrap(_y);
		WrappingPolicy::wrap(_z);
	}

protected:
	T _x;
	T _y;
	T _z;
public:
	Vector3() :
		_x(), _y(), _z()
	{
		rewrapAll();
	}

	template <typename U, typename V>
	Vector3(const Vector3<U, V>& other) :
		_x(other.x()),
		_y(other.y()),
		_z(other.z())
	{
		rewrapAll();
	}

	Vector3(const T& x, const T& y, const T& z) :
		_x(x), _y(y), _z(z)
	{
		rewrapAll();
	}

	const T& x() const { return _x; };
	void setX(const T& x)
	{
		_x = x;
		WrappingPolicy::wrap(_x);
	}
	void addX(const T& magnitude) { setX(x() + magnitude); }
	void rotateX(const T& radians)
	{
		if (!radians)
			return;
		set(
			x(),
			y() * cos(radians) - z() * sin(radians),
			y() * sin(radians) + z() * cos(radians));
	}

	const T& y() const { return _y; };
	void setY(const T& y)
	{
		_y = y;
		WrappingPolicy::wrap(_y);
	}
	void addY(const T& magnitude) { setY(y() + magnitude); }
	void rotateY(const T& radians)
	{
		if (!radians)
			return;
		set(
			x() * cos(radians) + z() * sin(radians),
			y(),
			z() * cos(radians) - x() * sin(radians));
	}

	const T& z() const { return _z; };
	void setZ(const T& z)
	{
		_z = z;
		WrappingPolicy::wrap(_z);
	}
	void addZ(const T& magnitude) { setZ(z() + magnitude); }
	void rotateZ(const T& radians)
	{
		if (!radians)
			return;
		set(
			x()*cos(radians) - y()*sin(radians),
			x()*sin(radians) + y()*cos(radians));
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

	void add(const T& x, const T& y, const T& z)
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
		add(other.x(), other.y(), other.z());
		return *this;
	}

	template <class U, class V>
	Vector3<T, WrappingPolicy> operator -(const Vector3<U, V>& other) const
	{
		Vector3<T, WrappingPolicy> vec(*this);
		vec.add(-other.x(), -other.y(), -other.z());
		return vec;
	}

	template <class U, class V>
	Vector3<T, WrappingPolicy>& operator -=(const Vector3<U, V>& other)
	{
		this->add(-other.x(), -other.y(), -other.z());
		return *this;
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
			x() * x() +
			y() * y() +
			z() * z());
	}

	void normalize()
	{
		const T len = length();
		if (len == 0) {
			return;
		}
		set(
			x() / len,
			y() / len,
			z() / len);
	}

	void clear()
	{
		const T nil = T();
		set(nil, nil, nil);
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
			x() * factor,
			y() * factor,
			z() * factor);
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
			x() / factor,
			y() / factor,
			z() / factor);
		return *this;
	}

	void dump() const
	{
		std::cout << "(x: " << x() << ", y: " << y() << ", z: " << z() << ")" << std::endl;
	}

	bool equals(const T& otherX, const T& otherY, const T& otherZ) const
	{
		return x() == otherX && y() == otherY && z() == otherZ;
	}

	bool fuzzyEquals(const T& otherX, const T& otherY, const T& otherZ, const T& fuzz) const
	{
		return std::abs(otherX - x()) < fuzz &&
			std::abs(otherY - y()) < fuzz &&
			std::abs(otherZ - z()) < fuzz;
	}

	template<typename U, class V>
	bool fuzzyEquals(const Vector3<U, V>& other, const T& fuzz) const
	{
		return fuzzyEquals(other.x(), other.y(), other.z(), fuzz);
	}

	template<typename U, class V>
	bool operator ==(const Vector3<U, V>& other) const
	{
		return equals(other.x(), other.y(), other.z());
	}

	template <typename U, class V>
	bool operator !=(const Vector3<U, V>& other) const
	{
		return !(*this == other);
	}

	Vector3<T, WrappingPolicy> operator-() const
	{
		return Vector3<T, WrappingPolicy>(-x(), -y(), -z());
	}

	operator bool() const
	{
		return x() || y() || z();
	}

	Vector3<T, WrappingPolicy>& operator=(const Vector3<T, WrappingPolicy>& other)
	{
		if (this == &other)
			return *this;
		return assign(other);
	}

	template <typename U, class V>
	Vector3<T, WrappingPolicy>& operator=(const Vector3<U, V>& other)
	{
		return assign(other);
	}

private:
	template <typename U, class V>
	Vector3<T, WrappingPolicy>& assign(const Vector3<U, V> other)
	{
		set(other.x(), other.y(), other.z());
		return *this;
	}
};

} // namespace nt

#endif // VECTOR_H
