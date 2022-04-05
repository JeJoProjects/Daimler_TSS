#ifndef OUTPUT_MGR_HPP
#define OUTPUT_MGR_HPP

#include "EventObserver.hpp"

namespace DTSS::FileService 
{
/*!
 * class "OutputMgr" is a Event observer, which observer the event changes and,
 * act on the file or directory creating and managing the output/ file exports.
 */
class OutputMgr : public DTSS::Event::EventObserver
{
public:
    // default constructor
    OutputMgr();

    // disable copy - move by default!
    // @TODO: Singleton class ??
    OutputMgr(const OutputMgr&) = delete;
    OutputMgr& operator=(const OutputMgr&) = delete;
    OutputMgr(OutputMgr&&) = delete;
    OutputMgr& operator=(OutputMgr&&) = delete;

    // virtual destructor 
    virtual ~OutputMgr() override;

    /*!
     * Overridden function from base class. 
     * The function handles the event revived for which it has been observed to. 
     *
     * @param enum Event::EventType.. type of the event which has to be proceeded.
     * @param std::any parameter which has to be used for processing.
     */
    void handleEvent(const DTSS::Event::EventType type, const std::any& para) override;

protected:
    /*!
     * Overridden function from base class.
     * The function to (self) register this class as observer at the EventMgr.
     */
    void registerSelf() override;

    /*!
     * Overridden function from base class.
     * The function to (self) de-register this class from the observers list.
     */
    void de_registerSelf() override;
};

} // DTSS::Event

#endif // OUTPUT_MGR_HPP

