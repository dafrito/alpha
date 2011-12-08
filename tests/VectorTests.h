#include <QtTest/QtTest>
#include "Vector.h"
#include <QDebug>

class VectorTests : public QObject
{
	Q_OBJECT

private slots:
	void testVectorIsTemplated()
	{
		Vector3<float> vec;
		QVERIFY(vec.x() == 0.0f);
	}
};
