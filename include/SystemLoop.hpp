#ifndef ALPHA_SYSTEMLOOP_HEADER
#define ALPHA_SYSTEMLOOP_HEADER

#include <set>
#include <functional>
#include "MeasuredTimer.hpp"

namespace nt {

struct SystemEntry;

/**
 * An ordered list of systems.
 *
 * This class can be used to represent any sort of game or rendering loop that
 * consists of a number of invoked systems. The systems are ordered based on a
 * specified integer, so you can have various levels of systems that are executed
 * in a specific order.
 *
 * The loop is assumed to be called at timed intervals, though for simplicitiy and
 * flexibility, timing functionality is not included in this class. Each system, when
 * invoked, will received a time parameter, as given to tick(). Systems that do not
 * depend on a timing parameter should use addTimelessSystem().
 *
 * Multiple systems are allowed to have the same ordering. This lets a grouping
 * of systems that perform the same category of behavior use the same ordering
 * number, such as AI, PHYSICS, or RENDERING.
 */
class SystemLoop
{
    typedef std::multiset<SystemEntry> SystemList;
    SystemList _systems;

    int _idCount;
public:
    SystemLoop() :
        _systems(),
        _idCount(0)
    {}

    void tick(const double& elapsed) const;

    int addSystem(const std::function<void(const double&)> system, const int order);
    int addTimelessSystem(const std::function<void()> system, const int order);

    void removeSystem(const int id);

    int numSystems() const;
};

struct SystemEntry
{
    int id;
    std::function<void(const double&)> system;
    int order;

    SystemEntry(const int id, std::function<void(const double&)> system, const int order) :
        id(id),
        system(system),
        order(order)
    {}

    bool operator <(const SystemEntry& other) const;
};

} // namespace nt

#endif // ALPHA_SYSTEMLOOP_HEADER
