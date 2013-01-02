#ifndef ALPHA_SORTEDLOOPTESTS_HEADER
#define ALPHA_SORTEDLOOPTESTS_HEADER

#include <QtTest/QtTest>
#include <SortedLoop.hpp>

namespace {

double ELAPSED_TEST = 15;
bool FIRST_FLAG = false;
bool SECOND_FLAG = false;
void firstReceiver(const double& elapsed)
{
    QCOMPARE(elapsed, ELAPSED_TEST);
    QCOMPARE(FIRST_FLAG, false);
    QCOMPARE(SECOND_FLAG, false);
    FIRST_FLAG = true;
}

void secondReceiver(const double& elapsed)
{
    QCOMPARE(FIRST_FLAG, true);
    QCOMPARE(SECOND_FLAG, false);
    SECOND_FLAG = true;
}

void thirdReceiver(const double& elapsed)
{
    QCOMPARE(FIRST_FLAG, true);
    QCOMPARE(SECOND_FLAG, true);
}

} // namespace anonymous

class SortedLoopTests : public QObject
{
    Q_OBJECT
private slots:
    void testSortedLoopCanAddAndRemoveReceivers()
    {
        nt::SortedLoop loop;
        QCOMPARE(loop.numReceivers(), 0);
        loop.addReceiver(firstReceiver, 0);
        QCOMPARE(loop.numReceivers(), 1);
        loop.removeReceiver(firstReceiver, 0);
        QCOMPARE(loop.numReceivers(), 0);
    }

    void testSortedLoopCallsReceiversBasedOnOrdering()
    {
        FIRST_FLAG = false;
        SECOND_FLAG = false;

        nt::SortedLoop loop;

        loop.addReceiver(firstReceiver, 1);
        loop.addReceiver(secondReceiver, 2);
        loop.addReceiver(thirdReceiver, 3);

        loop.tick(15);

        QCOMPARE(FIRST_FLAG, true);
        QCOMPARE(SECOND_FLAG, true);
    }
};

#endif // ALPHA_SORTEDLOOPTESTS_HEADER
