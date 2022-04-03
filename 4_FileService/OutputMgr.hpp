#ifndef OUTPUT_MGR_HPP
#define OUTPUT_MGR_HPP

#include "EventObserver.hpp"

class OutputMgr : public EventObserver
{
public:
    OutputMgr();
    virtual ~OutputMgr() override;
    void handleEvent(const EventType type, const std::any& para) override;

protected:
    void registerSelf() override;
    void de_registerSelf() override;
};


#endif // OUTPUT_MGR_HPP
