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
};
