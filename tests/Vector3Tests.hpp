#include <QtTest/QtTest>
#include <Vector3.hpp>
#include <gl/util.hpp>
#include <QDebug>

#include "init.hpp"

using nt::Vector3;

class Vector3Tests : public QObject
{
	Q_OBJECT

private slots:
	void testVectorIsTemplated()
	{
		Vector3<float> vec;
		QVERIFY(vec.x() == 0.0f);
	}

	void testVectorSupportsNestedValues()
	{
		Vector3<Vector3<int>> vec(
			Vector3<int>(1, 2, 3),
			Vector3<int>(4, 5, 6),
			Vector3<int>(7, 8, 9));
	}

	void testVectorCanCompareAgainstThreeValues()
	{
		Vector3<int> a(1, 2, 3);
		QVERIFY(!a.equals(0, 2, 3));
		QVERIFY(!a.equals(1, 0, 3));
		QVERIFY(!a.equals(1, 2, 0));
		QVERIFY(a.equals(1, 2, 3));
	}

	void testVectorCanCompareAgainstOtherVectors()
	{
		Vector3<int> a(1, 2, 3);
		Vector3<int> b(0, 2, 3);
		Vector3<int> c(1, 0, 3);
		Vector3<int> d(1, 2, 0);
		Vector3<int> e(1, 2, 3);
		QVERIFY(a != b);
		QVERIFY(a != c);
		QVERIFY(a != d);
		QVERIFY(a == e);
	}

	void testDefaultVectorStartsZeroedOut()
	{
		Vector3<int> a;
		QVERIFY(!a);
	}

	void testVectorHasSetMethods()
	{
		Vector3<int> a;
		a.setX(1);
		QVERIFY(a.x() == 1);
		QVERIFY(a.equals(1, 0, 0));
		a.setY(2);
		QVERIFY(a.y() == 2);
		QVERIFY(a.equals(1, 2, 0));
		a.setZ(3);
		QVERIFY(a.z() == 3);
		QVERIFY(a.equals(1, 2, 3));
	}

	void testVectorHasThreeArgSet()
	{
		Vector3<int> a;
		a.set(1, 2, 3);
		QVERIFY(a.equals(1, 2, 3));
	}

	void testTwoArgSetIgnoresZ()
	{
		Vector3<int> a(1, 2, 3);
		a.set(4, 5);
		QVERIFY(a.equals(4, 5, 3));
	}

	void testComponentsHaveAddMethods()
	{
		Vector3<int> a(1, 2, 3);
		a.addX(1);
		QVERIFY(a.equals(2, 2, 3));
		a.addY(2);
		QVERIFY(a.equals(2, 4, 3));
		a.addZ(3);
		QVERIFY(a.equals(2, 4, 6));
	}

	void testVectorCanBeCleared()
	{
		Vector3<int> a(1, 2, 3);
		a.clear();
		QVERIFY(a.equals(0, 0, 0));
	}

	void testVectorSupportsAssignmentOperator()
	{
		Vector3<int> a(1, 2, 3);
		Vector3<int> b = a;
		QVERIFY(b.equals(1, 2, 3));
	}

	void testVectorSupportsPlus()
	{
		Vector3<int> a(5, 4, 3);
		Vector3<int> b(1, 3, 5);
		Vector3<int> c = a + b;
		QVERIFY(c.x() == 6);
		QVERIFY(c.y() == 7);
		QVERIFY(c.z() == 8);
	}

	void testVectorSupportsPlusEquals()
	{
		Vector3<int> a(5, 4, 3);
		Vector3<int> b(1, 3, 5);
		a += b;
		QVERIFY(a.x() == 6);
		QVERIFY(a.y() == 7);
		QVERIFY(a.z() == 8);
	}

	void testVectorSupportsMinusOperator()
	{
		Vector3<int> a(5, 4, 3);
		Vector3<int> b(1, 2, 3);
		Vector3<int> c = a - b;
		QVERIFY(c.x() == 4);
		QVERIFY(c.y() == 2);
		QVERIFY(c.z() == 0);
	}

	void testVectorSupportsMinusEqualsOperator()
	{
		Vector3<int> a(5, 4, 3);
		Vector3<int> b(1, 2, 3);
		a -= b;
		QVERIFY(a.x() == 4);
		QVERIFY(a.y() == 2);
		QVERIFY(a.z() == 0);
	}

	void testVectorSupportsNegation()
	{
		Vector3<int> a(3, 4, 5);
		Vector3<int> b = -a;
		QVERIFY(b.equals(-3, -4, -5));
	}

	void testVectorSupportsMultiplyOperator()
	{
		Vector3<int> a(3, 4, 5);
		Vector3<int> r = a * 2;
		QVERIFY(r.x() == 6);
		QVERIFY(r.y() == 8);
		QVERIFY(r.z() == 10);
	}

	void testVectorSupportsMultiplyEqualsOperator()
	{
		Vector3<int> a(3, 4, 5);
		a *= 2;
		QVERIFY(a.x() == 6);
		QVERIFY(a.y() == 8);
		QVERIFY(a.z() == 10);
	}

	void testVectorSupportsDivideOperator()
	{
		Vector3<int> a(6, 8, 10);
		Vector3<int> r = a / 2;
		QVERIFY(r.x() == 3);
		QVERIFY(r.y() == 4);
		QVERIFY(r.z() == 5);
	}

	void testVectorSupportsDivideEqualsOperator()
	{
		Vector3<int> a(6, 8, 10);
		a /= 2;
		QVERIFY(a.x() == 3);
		QVERIFY(a.y() == 4);
		QVERIFY(a.z() == 5);
	}

	void testVectorHasFalsyBooleanValueForZeroMagnitude()
	{
		Vector3<int> a;
		QVERIFY(!a);
		a.setX(1);
		QVERIFY(a);
	}

	void testVectorSupportsWrappingPolicies()
	{
        using nt::WrapRadians;
		Vector3<double, WrapRadians> vec;
		vec.set(PI * 3, 0, 0);
		QVERIFY(vec.equals(PI, 0, 0));
		vec.clear();
		vec.addX(PI * 3);
		QVERIFY(vec.equals(PI, 0, 0));
		vec.clear();
		vec.add(PI * 3, PI * 3, PI * 3);
		QVERIFY(vec.equals(PI, PI, PI));
		vec = -vec;
		QVERIFY(vec.equals(PI, PI, PI));
		Vector3<double> other(PI * 3, PI * 3, PI * 3);
		vec = other;
		QVERIFY(vec.equals(PI, PI, PI));
	}

	void testVectorSupportsDegreeWrapping()
	{
        using nt::WrapDegrees;
		Vector3<int, WrapDegrees> vec;
		vec.addX(360 + 180);
		QVERIFY(vec.x() == 180);
		vec.clear();
		vec.addX(-90);
		QVERIFY(vec.x() == 270);
	}

	void testVectorsCopyConstructorAbidesByPolicy()
	{
        using nt::WrapRadians;
		Vector3<double> first(PI * 3, PI * 3, PI * 3);
		Vector3<double, WrapRadians> vec(first);
		QVERIFY(vec.equals(PI, PI, PI));
	}

	void testVectorThreeArgCtorAbidesByPolicy()
	{
        using nt::WrapRadians;
		Vector3<double, WrapRadians> vec(PI * 3, PI * 3, PI * 3);
		QVERIFY(vec.equals(PI, PI, PI));
	}

	void testGetAxisHorizontalAngles()
	{
        using nt::gl::getAxisAngles;

		Vector3<double> Position(0,0,0);
		Vector3<double> Rotation = getAxisAngles(Position);
		QVERIFY(Rotation.equals(0,0,PI_2*0 + atan(0.0)));

		Position.set(0,3,0);
		Rotation = getAxisAngles(Position);
		QVERIFY(Rotation.equals(0,0,PI_2*0 + atan(0.0)));

		Position.set(-2,3,0);
		Rotation = getAxisAngles(Position);
		QVERIFY(Rotation.equals(0,0,PI_2*0 + atan(2.0/3.0)));

		Position.set(-2,0,0);
		Rotation = getAxisAngles(Position);
		QVERIFY(Rotation.equals(0,0,PI_2*1) + atan(0.0));

		Position.set(-2,-3,0);
		Rotation = getAxisAngles(Position);
		QVERIFY(Rotation.equals(0,0,PI_2*2 - atan(2.0/3.0)));

		Position.set(0,-3,0);
		Rotation = getAxisAngles(Position);
		QVERIFY(Rotation.equals(0,0,PI_2*2) + atan(0.0));

		Position.set(2,-3,0);
		Rotation = getAxisAngles(Position);
		QVERIFY(Rotation.equals(0,0,PI_2*2 + atan(2.0/3.0)));

		Position.set(2,0,0);
		Rotation = getAxisAngles(Position);
		QVERIFY(Rotation.equals(0,0,PI_2*3 + atan(0.0)));

		Position.set(2,3,0);
		Rotation = getAxisAngles(Position);
		QVERIFY(Rotation.equals(0,0,PI_2*4 - atan(2.0/3.0)));

	}
	void testGetAxisVerticalAngles()
	{
        using nt::gl::getAxisAngles;

		Vector3<double> Position(0,0,0);
		Vector3<double> Rotation = getAxisAngles(Position);
		QVERIFY( Rotation.x() == PI_2*0 + atan(0.0));

		Position.set(0,0,6);
		Rotation = getAxisAngles(Position);
		QVERIFY( Rotation.x() == PI_2*1 + atan(0.0));

		Position.set(3,0,6);
		Rotation = getAxisAngles(Position);
		QVERIFY( Rotation.x() == PI_2*1 - atan(3.0/6.0));

		Position.set(3,4,6);
		Rotation = getAxisAngles(Position);
		QVERIFY( Rotation.x() == PI_2*1 - atan(5.0/6.0));

		Position.set(0,0,-6);
		Rotation = getAxisAngles(Position);
		QVERIFY( Rotation.x() == PI_2*3 + atan(0.0));


	}


	void testFuzzyEqualsAllowsForErrors()
	{
		Vector3<double> a(0.01, 0, 0);
		Vector3<double> zero;
		QVERIFY(a.fuzzyEquals(zero, .1));
		QVERIFY(!a.fuzzyEquals(zero, .001));
	}

};
