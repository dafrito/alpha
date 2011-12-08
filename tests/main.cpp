#include <QTest>
#include "Vector3Tests.h"

int main(int argc, char *argv[])
{
	int rv = 0;
	Vector3Tests vector3Tests;
	rv += QTest::qExec(&vector3Tests, argc, argv);
	return rv;
}
