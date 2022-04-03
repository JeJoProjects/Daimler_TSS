#ifndef EVENT_HPP
#define EVENT_HPP

#include "Utility.hpp"

enum struct EventType
{
    DEFAULT = 0,
    UPDATE,
    NEW_FILE
};

class Event
{
public:
    // constructor
    Event() = default;
    virtual ~Event() = default;

    virtual EventType GetEventType() const noexcept = 0;
    virtual std::string_view GetEventName() const noexcept = 0;
private:

};

#endif // EVENT_HPP