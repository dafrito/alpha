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

	void testVectorSupportsPlus()
	{
		Vector3<int> a(1, 0, 0);
		Vector3<int> b(0, 1, 0);
		Vector3<int> c = a + b;
		QVERIFY(c.x() == 1);
		QVERIFY(c.y() == 1);
		QVERIFY(c.z() == 0);
	}

	void testVectorSupportsPlusEquals()
	{
		Vector3<int> a(1, 0, 0);
		Vector3<int> b(0, 1, 0);
		a += b;
		QVERIFY(a.x() == 1);
		QVERIFY(a.y() == 1);
		QVERIFY(a.z() == 0);
	}
};
