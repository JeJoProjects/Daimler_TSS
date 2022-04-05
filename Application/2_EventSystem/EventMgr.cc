#include "EventMgr.hpp"
#include "EventObserver.hpp"

// name-space alias
namespace DE = DTSS::Event;

DE::UniqueEventMgr& DE::EventMgr::GetInstance()
{
    if (!instance)
    {
        std::cout << "Creating \"EventMgr\" singleton instance.\n";
        instance.reset(new DE::EventMgr{});
    }
    DTSS::Utility::Assert(instance != nullptr, "\"EventMgr\" singleton instance is nullptr!");
    return instance;
}

void DE::EventMgr::attach(const EventType eType, EventObserver* addObsvr)
{
    mEventObserverMap.emplace(eType, addObsvr);
}

void DE::EventMgr::detach(const EventType eType, EventObserver* removeObs)
{
    const auto erased = std::erase_if(mEventObserverMap, 
        [eType, removeObs](const auto& entry) noexcept 
        {
            const auto& [type, obsvr] = entry;
            return type == eType && obsvr == removeObs;
        });

    std::cout << "Total of " << erased << " Observers were erased.\n";
}

void DE::EventMgr::notify(const EventType eType, const std::any& para)
{
    auto range = mEventObserverMap.equal_range(eType);
    for (auto it = range.first; it != range.second; ++it)
    {
        auto& [type, obsvr] = *it;
        obsvr->handleEvent(type, para);
    }
}

