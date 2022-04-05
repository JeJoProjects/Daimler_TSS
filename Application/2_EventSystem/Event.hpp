#ifndef EVENT_HPP
#define EVENT_HPP

#include "Utility.hpp"

namespace DTSS::Event
{
// type of the event the File service application handles (in general).
enum struct EventType
{
    DEFAULT = 0,
    UPDATE,
    NEW_FILE
};

/*!
 * class "Event" is a pure abstract base class for all the Events.
 */
class Event
{
public:
    // constructor
    Event() = default;

    // virtual destructor 
    virtual ~Event() = default;

    virtual EventType GetEventType() const noexcept = 0;
    virtual std::string_view GetEventName() const noexcept = 0;
private:
};

} // DTSS::Event

#endif // EVENT_HPP

