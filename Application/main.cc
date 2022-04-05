#include "CmdLine.hpp"
#include "EventMgr.hpp"
#include "FileDetector.hpp"
#include "OutputMgr.hpp"

#include <thread> // sleep_for, sleep_until

#define DEBUG true

int main(int argc, char* argv[])
{
    using namespace DTSS;

    Utility::CmdLine::CreateInstance( argc, argv );
    const Utility::UniqueCmdLine& cmdLine = Utility::CmdLine::GetInstance();

    Event::UniqueEventMgr& eventMgr = Event::EventMgr::GetInstance();
    FileService::OutputMgr outMgr{};

    FileService::FileDetector fileDetector{
        cmdLine->getOptionValues<std::vector<std::string>>("-Path"sv),
        cmdLine->getOptionValues<std::vector<std::string>>("-Ext"sv),
    };

    if (not DEBUG)
    {
        const auto duration = cmdLine->getOptionValues<std::chrono::duration<double>>("-Duration"sv);
        while (true)
        {
            fileDetector.detectFile(duration);
            std::this_thread::sleep_for(duration);
        }
    }
    else
    {   
        const auto duration = 10min;
        while (true)
        {
            fileDetector.detectFile(duration);
            std::this_thread::sleep_for(duration);
        }
    }
    return 0;
}

