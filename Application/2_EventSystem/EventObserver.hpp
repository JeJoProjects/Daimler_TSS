#ifndef EVENT_OBSERVER_HPP
#define EVENT_OBSERVER_HPP

#include "Event.hpp"

namespace DTSS::Event
{
/*!
 * class "EventObserver" is a pure abstract base class for all the observers.
 */
class EventObserver
{
public:
    // constructor
    EventObserver() = default;

    // virtual destructor 
    virtual ~EventObserver() = default;

    /*! 
     * Virtual function to handle the event and corresponding parameter received. 
     *
     * @param enum Event::EventType.. type of the event which has to be proceeded.
     * @param std::any parameter which has to be used for processing.
     */
    virtual void handleEvent(const EventType type, const std::any& para) = 0;

protected:
    /*!
     * The virtual function to (self) register the observer at the EventMgr.
     */
    virtual void registerSelf() = 0;

    /*!
     * The function to (self) de-register the observer from the EventMgr.
     */
    virtual void de_registerSelf() = 0;
};

} // DTSS::Event

#endif // EVENT_OBSERVER_HPP

