#include <QtTest/QtTest>

using namespace std;

class BasicTests : public QObject
{
    Q_OBJECT
private slots:

    void testMathWorks()
    {
        QCOMPARE(4, 2+2);
    }
};
