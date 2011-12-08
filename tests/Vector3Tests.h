#include <QtTest/QtTest>
#include "Vector3.h"
#include <QDebug>

class Vector3Tests : public QObject
{
	Q_OBJECT

private slots:
	void testVectorIsTemplated()
	{
		Vector3<float> vec;
		QVERIFY(vec.x() == 0.0f);
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

};
