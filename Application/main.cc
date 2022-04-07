#include "CmdLine.hpp"
#include "EventMgr.hpp"
#include "FileDetector.hpp"
#include "OutputMgr.hpp"

#include <thread> // sleep_for, sleep_until

#define DEBUG false

int main(int argc, char* argv[])
{
    using namespace DTSS;

    Utility::CmdLine::CreateInstance( argc, argv );

    if (argc == 1) return 0;

    const Utility::UniqueCmdLine& cmdLine = Utility::CmdLine::GetInstance();

    Event::UniqueEventMgr& eventMgr = Event::EventMgr::GetInstance();
    FileService::OutputMgr outMgr{};

    FileService::FileDetector fileDetector{
        cmdLine->getOptionValues<std::vector<std::string>>("-Path"sv),
        cmdLine->getOptionValues<std::vector<std::string>>("-Ext"sv),
    };

    const auto duration = cmdLine->getOptionValues<std::chrono::duration<double>>("-Duration"sv);
    while (true)
    {
        fileDetector.detectFile(duration);
        std::this_thread::sleep_for(duration);
    }
    return 0;
}

