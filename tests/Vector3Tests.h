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

};
