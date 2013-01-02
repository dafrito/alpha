#ifndef ALPHA_SYSTEMLOOPTESTS_HEADER
#define ALPHA_SYSTEMLOOPTESTS_HEADER

#include <QtTest/QtTest>
#include <SystemLoop.hpp>

namespace {

double ELAPSED_TEST = 15;
bool FIRST_FLAG = false;
bool SECOND_FLAG = false;
void firstSystem(const double& elapsed)
{
    QCOMPARE(elapsed, ELAPSED_TEST);
    QCOMPARE(FIRST_FLAG, false);
    QCOMPARE(SECOND_FLAG, false);
    FIRST_FLAG = true;
}

void secondSystem(const double& elapsed)
{
    QCOMPARE(FIRST_FLAG, true);
    QCOMPARE(SECOND_FLAG, false);
    SECOND_FLAG = true;
}

void thirdSystem(const double& elapsed)
{
    QCOMPARE(FIRST_FLAG, true);
    QCOMPARE(SECOND_FLAG, true);
}


bool TIMELESS = false;
void timelessSystem()
{
    TIMELESS = true;
}

} // namespace anonymous

class SystemLoopTests : public QObject
{
    Q_OBJECT
private slots:
    void testSystemLoopCanAddAndRemoveSystems()
    {
        nt::SystemLoop loop;
        QCOMPARE(loop.numSystems(), 0);
        int systemId = loop.addSystem(firstSystem, 0);
        QCOMPARE(loop.numSystems(), 1);
        loop.removeSystem(systemId);
        QCOMPARE(loop.numSystems(), 0);
    }

    void testSystemLoopCallsSystemsBasedOnOrdering()
    {
        FIRST_FLAG = false;
        SECOND_FLAG = false;

        nt::SystemLoop loop;

        loop.addSystem(firstSystem, 1);
        loop.addSystem(secondSystem, 2);
        loop.addSystem(thirdSystem, 3);

        loop.tick(15);

        QCOMPARE(FIRST_FLAG, true);
        QCOMPARE(SECOND_FLAG, true);
    }

    void testSystemLoopIsSpecificWhenRemovingElements()
    {
        FIRST_FLAG = false;
        SECOND_FLAG = false;

        nt::SystemLoop loop;

        int id = loop.addSystem(firstSystem, 1);
        loop.addSystem(secondSystem, 1);
        QCOMPARE(loop.numSystems(), 2);
        loop.removeSystem(id);
        QCOMPARE(loop.numSystems(), 1);
    }

    void testAddingATimelessSystem()
    {
        TIMELESS = false;

        nt::SystemLoop loop;
        loop.addTimelessSystem(timelessSystem, 1);
        loop.tick(1);

        QCOMPARE(TIMELESS, true);
    }
};

#endif // ALPHA_SYSTEMLOOPTESTS_HEADER
