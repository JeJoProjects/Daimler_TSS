#include "OutputMgr.hpp"
#include "EventMgr.hpp"
OutputMgr::OutputMgr()
    : EventObserver{}
{
    registerSelf();
}

OutputMgr::~OutputMgr()
{
    de_registerSelf();
}

void OutputMgr::handleEvent(const EventType type, const std::any& para)
{
    std::cout << "OutputMgr::update() --> \n";
    switch (type)
    {
    case EventType::NEW_FILE:
    {
        break;
    }
    default:
    {
        DTSS::Utility::Assert(false, "Shouldn't get a unknown event!");
        break;
    }
    }
}

void OutputMgr::registerSelf()
{
    EventMgr::GetInstance()->attach(EventType::NEW_FILE, this);
}

void OutputMgr::de_registerSelf()
{
    EventMgr::GetInstance()->detach(EventType::NEW_FILE, this);
}
