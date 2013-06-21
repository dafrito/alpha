#include <QtTest/QtTest>
#include <Vector3.hpp>

#include "init.hpp"

using nt::Vector3;

class RotationTests : public QObject
{
	Q_OBJECT

private slots:
	void testNoopXRotation()
	{
		Vector3<double> rot(1, 0, 0);
		rot.rotateX(PI_2);
		QVERIFY(rot.equals(1, 0, 0));
	}

	void testNoopYRotation()
	{
		Vector3<double> rot(0, 1, 0);
		rot.rotateY(PI_2);
		QVERIFY(rot.equals(0, 1, 0));
	}

	void testNoopZRotation()
	{
		Vector3<double> rot(0, 0, 1);
		rot.rotateZ(PI_2);
		QVERIFY(rot.equals(0, 0, 1));
	}
};
