#ifndef EVENT_MGR_HPP
#define EVENT_MGR_HPP

#include "Event.hpp"

class EventObserver;

class EventMgr final // Subject
{
public:
    static std::unique_ptr<EventMgr>& GetInstance();

    // copy-move are not available
    EventMgr(const EventMgr&) = delete;
    EventMgr& operator=(const EventMgr&) = delete;
    EventMgr(EventMgr&&) = delete;
    EventMgr& operator=(EventMgr&&) = delete;
    ~EventMgr() = default;

    void attach(const EventType eType, EventObserver* addObsvr);
    void detach(const EventType eType, EventObserver* removeObsvr);

    void notify(const EventType eType, const std::any& para);

private:
    // constructor is for private use
    EventMgr() = default;

private:
    inline static std::unique_ptr<EventMgr> instance{ nullptr };
    std::unordered_multimap<EventType, EventObserver*> mEventObserverMap;

};

#endif // EVENT_MGR_HPP