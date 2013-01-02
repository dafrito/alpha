#include "SystemLoop.hpp"

namespace nt {

int SystemLoop::addSystem(const std::function<void(const double&)> system, const int order)
{
    int id = _idCount++;
    _systems.insert(SystemEntry(id, system, order));
    return id;
}

int SystemLoop::addTimelessSystem(const std::function<void()> system, const int order)
{
    return addSystem([=](const double&) { system(); }, order);
}

void SystemLoop::removeSystem(const int id)
{
    for (typename SystemList::const_iterator i = _systems.begin(); i != _systems.end(); ++i) {
        if (i->id == id) {
            _systems.erase(i);
            return;
        }
    }
}

void SystemLoop::tick(const double& elapsed) const
{
    for (typename SystemList::const_iterator i = _systems.begin(); i != _systems.end(); ++i) {
        i->system(elapsed);
    }
}

int SystemLoop::numSystems() const
{
    return _systems.size();
}

bool SystemEntry::operator <(const SystemEntry& other) const
{
    return this->order < other.order;
}

} // namespace nt
