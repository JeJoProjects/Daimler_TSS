#ifndef EVENT_OBSERVER_HPP
#define EVENT_OBSERVER_HPP

#include "Event.hpp"


class EventObserver
{
public:
    EventObserver() = default;
    virtual ~EventObserver() = default;

    virtual void handleEvent(const EventType type, const std::any& para) = 0;

protected:
    virtual void registerSelf() = 0;
    virtual void de_registerSelf() = 0;
};

#endif // EVENT_OBSERVER_HPP