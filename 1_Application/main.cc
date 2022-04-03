#include "Utility.hpp"
#include "FileDetector.hpp"
#include "EventMgr.hpp"
#include "OutputMgr.hpp"

#include <thread> // sleep_for, sleep_until


int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        std::cout << "\nNot enough command line arguments has been passed.\n"
            << "Please add arguments as: Application.exe -path \"<directory-path>\" -ext \"<extension>\"\n\n";
        //return 0;
    }
    //else 
    {
        std::string directory{ "D:\\C++\\00_GitHub\\Daimler_TSS\\Build_and_Out\\Test" };
        std::string extension{};

        for (int index{ 0 }; index < argc; ++index)
        {
            if (std::string{ argv[index] } == "-path"s)
            {
                // get the path
                ++index;
                directory = std::string{ argv[index] };
            }
            else if (std::string{ argv[index] } == "-ext"s)
            {
                // get the user provided extension
                ++index;
                extension = std::string{ argv[index] };
            }

            std::cout << "Args[" << index << "] :" << argv[index] << "\n";
        }

        // validate the user input!
        if (!directory.empty())
        {

            std::vector<std::filesystem::path> exts;
            if (!extension.empty())
                exts.emplace_back(extension);


            auto& eventMgr = EventMgr::GetInstance();
            DTSS::FileService::OutputMgr outMgr{};

            DTSS::FileService::FileDetector fileDetector{ exts, directory };
            const auto duration = 10min;
            while (true)
            {
                fileDetector.detectFile(duration);
                std::this_thread::sleep_for(duration);
            }

        }
    }

    return 1;
}

