#ifndef ALPHA_SORTEDLOOP_HEADER
#define ALPHA_SORTEDLOOP_HEADER

#include <set>
#include <functional>
#include "MeasuredTimer.hpp"

namespace nt {

struct LoopEntry;

/**
 * A sorted list of receivers that receive a provided elapsed time.
 *
 * This class can be used to represent any sort of game or rendering loop, where the
 * order of invoked receivers is significant. It is recommended to specify constants or
 * an enumeration for the ordering of a receiver (e.g., AI, PHYSICS, RENDERING) to make
 * the code clearer.
 *
 * Multiple receivers can have the same ordering. In this case, the relative order of
 * execution is undefined.
 */
class SortedLoop
{
    typedef std::multiset<LoopEntry> ReceiverList;
    ReceiverList _receivers;

    int _idCount;
public:
    SortedLoop() :
        _receivers(),
        _idCount(0)
    {}

    void tick(const double& elapsed) const;

    int addReceiver(const std::function<void(const double&)> receiver, const int order);

    void removeReceiver(const int id);

    int numReceivers() const;
};

struct LoopEntry
{
    int id;
    std::function<void(const double&)> receiver;
    int order;

    LoopEntry(const int id, std::function<void(const double&)> receiver, const int order) :
        id(id),
        receiver(receiver),
        order(order)
    {}

    bool operator <(const LoopEntry& other) const;
};

} // namespace nt

#endif // ALPHA_SORTEDLOOP_HEADER
