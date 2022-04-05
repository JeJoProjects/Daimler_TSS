#ifndef EVENT_MGR_HPP
#define EVENT_MGR_HPP

#include "Event.hpp"

namespace DTSS::Event
{
// forward declarations
class EventObserver;
class EventMgr;

// type alias
using UniqueEventMgr = std::unique_ptr<EventMgr>;

/*!
 * class "EventMgr" manages the Events and notify the changes to observers.
 */
class EventMgr final
{
public:
    // static functions to access the singleton instance.
    static UniqueEventMgr& GetInstance();

    // copy-move are not available
    EventMgr(const EventMgr&) = delete;
    EventMgr& operator=(const EventMgr&) = delete;
    EventMgr(EventMgr&&) = delete;
    EventMgr& operator=(EventMgr&&) = delete;

    // destructor 
    ~EventMgr() = default;

    /*!
     * The function to add the observer(i.e. register the observer them self) in the
     * event-type <-> observers map.
     *
     * @param enum Event::EventType.. type of the event which has to be proceeded.
     * @param pointer to the observer to be added.
     */
    void attach(const EventType eType, EventObserver* addObsvr);

    /*!
     * The function to remove the observer(i.e. de-register the observer them self) in the
     * event-type <-> observers map.
     *
     * @param enum Event::EventType.. type of the event which has to be proceeded.
     * @param pointer to the observer to be removed.
     */
    void detach(const EventType eType, EventObserver* removeObsvr);

    /*!
     * The function to notify the observer regarding the event receive.
     *
     * @param enum Event::EventType.. type of the event which has to be proceeded.
     * @param std::any parameter which has to be used for processing.
     */
    void notify(const EventType eType, const std::any& para);

private:
    // constructor is for private use
    EventMgr() = default;

private:
    inline static UniqueEventMgr instance{ nullptr };
    std::unordered_multimap<EventType, EventObserver*> mEventObserverMap;
};

} // DTSS::Event

#endif // EVENT_MGR_HPP

