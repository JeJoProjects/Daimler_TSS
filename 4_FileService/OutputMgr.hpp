#ifndef OUTPUT_MGR_HPP
#define OUTPUT_MGR_HPP

#include "EventObserver.hpp"

namespace DTSS::FileService {

class OutputMgr : public DTSS::Event::EventObserver
{
public:
    OutputMgr();
    virtual ~OutputMgr() override;
    void handleEvent(const DTSS::Event::EventType type, const std::any& para) override;

protected:
    void registerSelf() override;
    void de_registerSelf() override;
};

} // DTSS::Event

#endif // OUTPUT_MGR_HPP

