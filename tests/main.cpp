#include <QTest>
#include "VectorTests.h"

int main(int argc, char *argv[])
{
	int rv = 0;
	VectorTests vectorTests;
	rv += QTest::qExec(&vectorTests, argc, argv);
	return rv;
}
