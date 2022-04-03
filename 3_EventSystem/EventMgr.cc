#include "EventMgr.hpp"
#include "EventObserver.hpp"


std::unique_ptr<EventMgr>& EventMgr::GetInstance()
{
    if (!instance)
    {
        std::cout << "Creating EventMgr singleton instance.\n";
        instance.reset(new EventMgr{});
    }
    DTSS::Utility::Assert(instance != nullptr, "Singleton instance is nullptr!");
    return instance;
}

void EventMgr::attach(const EventType eType, EventObserver* addObsvr)
{
    mEventObserverMap.emplace(eType, addObsvr);
}

void EventMgr::detach(const EventType eType, EventObserver* removeObs)
{
    const auto erased = std::erase_if(mEventObserverMap,
        [eType, removeObs](const auto& entry) noexcept {
            const auto& [type, obsvr] = entry;
            return type == eType && obsvr == removeObs;
        });

    std::cout << "Total of " << erased << " Observers were erased.\n";
}

void EventMgr::notify(const EventType eType, const std::any& para)
{
    auto range = mEventObserverMap.equal_range(eType);
    for (auto it = range.first; it != range.second; ++it)
    {
        auto& [type, obsvr] = *it;
        obsvr->handleEvent(type, para);
    }
}