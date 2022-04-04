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
    const auto& cmdLine = Utility::CmdLine::GetInstance();

    auto& eventMgr = Event::EventMgr::GetInstance();
    FileService::OutputMgr outMgr{};

    if (not DEBUG)
    {
        FileService::FileDetector fileDetector{
            cmdLine->getOptionValues("-Path"sv),
            cmdLine->getOptionValues("-Ext"sv),
        };

        const auto duration = 10min;
        while (true)
        {
            fileDetector.detectFile(duration);
            std::this_thread::sleep_for(duration);
        }
    }
    else
    {   
        FileService::FileDetector fileDetector{
            { { "D:\\C++\\00_GitHub\\Daimler_TSS\\Build_and_Out\\Test" } },
            cmdLine->getOptionValues("-Ext"sv),
        };

        const auto duration = 10min;
        while (true)
        {
            fileDetector.detectFile(duration);
            std::this_thread::sleep_for(duration);
        }
    }
    return 0;
}

