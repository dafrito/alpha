#include "SortedLoop.hpp"

namespace nt {

int SortedLoop::addReceiver(std::function<void(const double&)> receiver, const int order)
{
    int id = _idCount++;
    _receivers.insert(LoopEntry(id, receiver, order));
    return id;
}

void SortedLoop::removeReceiver(const int id)
{
    for (typename ReceiverList::const_iterator i = _receivers.begin(); i != _receivers.end(); ++i) {
        if (i->id == id) {
            _receivers.erase(i);
            return;
        }
    }
}

void SortedLoop::tick(const double& elapsed) const
{
    for (typename ReceiverList::const_iterator i = _receivers.begin(); i != _receivers.end(); ++i) {
        i->receiver(elapsed);
    }
}

int SortedLoop::numReceivers() const
{
    return _receivers.size();
}

bool LoopEntry::operator <(const LoopEntry& other) const
{
    return this->order < other.order;
}

} // namespace nt
