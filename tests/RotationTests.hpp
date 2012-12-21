#include <QtTest/QtTest>
#include <Vector3.hpp>
#include <QDebug>
#include <cmath>

using nt::Vector3;

class RotationTests : public QObject
{
	Q_OBJECT

private slots:
	void testNoopXRotation()
	{
		Vector3<double> rot(1, 0, 0);
		rot.rotateX(M_PI_2);
		QVERIFY(rot.equals(1, 0, 0));
	}

	void testNoopYRotation()
	{
		Vector3<double> rot(0, 1, 0);
		rot.rotateY(M_PI_2);
		QVERIFY(rot.equals(0, 1, 0));
	}

	void testNoopZRotation()
	{
		Vector3<double> rot(0, 0, 1);
		rot.rotateZ(M_PI_2);
		QVERIFY(rot.equals(0, 0, 1));
	}
};
