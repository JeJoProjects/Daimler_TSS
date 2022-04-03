#include "FileDetector.hpp"

#include <iostream>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

int main(int argc, char* argv[])
{
    std::string directory{ "D:\\C++\\00_GitHub\\Daimler_TSS\\Build_and_Out\\Test" };
    if (!directory.empty())
    {
        std::vector<std::filesystem::path> exts;

        FileDetector fileDetector{ exts, directory };
        const auto duration = 10s;
        while (true)
        {
            fileDetector.detectFile(duration);
            std::this_thread::sleep_for(duration);
        }

    }
}