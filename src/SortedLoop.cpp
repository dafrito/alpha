#include "SortedLoop.hpp"

namespace nt {

void SortedLoop::addReceiver(const std::function<void(const double&)> receiver, const int order)
{
    _receivers.insert(LoopEntry(receiver, order));
}

void SortedLoop::removeReceiver(const std::function<void(const double&)> receiver, const int order)
{
    _receivers.erase(LoopEntry(receiver, order));
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

LoopEntry::LoopEntry(const std::function<void(const double&)>& receiver, const int order) :
    order(order),
    receiver(receiver)
{}

bool LoopEntry::operator <(const LoopEntry& other) const
{
    return this->order < other.order;
}

} // namespace nt
