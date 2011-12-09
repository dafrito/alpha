#include <QTest>
#include "Vector3Tests.h"
#include "RotationTests.h"

int main(int argc, char *argv[])
{
	int rv = 0;
	RotationTests rotTests;
	rv += QTest::qExec(&rotTests, argc, argv);
	Vector3Tests vector3Tests;
	rv += QTest::qExec(&vector3Tests, argc, argv);
	return rv;
}
