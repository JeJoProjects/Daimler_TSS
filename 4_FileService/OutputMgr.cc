#include "OutputMgr.hpp"
#include "EventMgr.hpp"
#include "Utility.hpp"

void print_space_info(std::fstream& outFile, auto const& dir, int width = 14)
{
    using namespace DTSS::Utility;
    std::string c = "|";
    outFile << std::left;
    for (const auto s : { "Capacity", "Free", "Available", "Dir" })
        outFile << c << std::setw(width) << s << ' ';
    outFile << '\n';
    std::error_code ec;
    const std::filesystem::space_info si = std::filesystem::space(dir, ec);
    outFile
        << c << std::setw(width) << Convert<std::intmax_t>::B2Mb(si.capacity) << ' '
        << c << std::setw(width) << Convert<std::intmax_t>::B2Mb(si.free) << ' '
        << c << std::setw(width) << Convert<std::intmax_t>::B2Mb(si.available) << ' '
        << c << dir << '\n';

}

auto creatFile(const FileName& file)
{
    std::filesystem::path path{ "D:\\C++\\00_GitHub\\Daimler_TSS\\Build_and_Out" };
    const auto folderName = file.fileName().string() + DTSS::Utility::generateRandomName();
    path /= (folderName + ".txt"s); //put something into there
    std::filesystem::create_directories(path.parent_path());

    std::fstream outFile{ path , std::ios::out };

    std::filesystem::path iterPath{ file.dir() };
    for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(iterPath.parent_path()))
    {
        if (std::filesystem::is_regular_file(dirEntry))
        {
            outFile << dirEntry << std::endl;
        }
        print_space_info(outFile, dirEntry);
    }
    outFile.close();
}


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
        if (para.has_value())
        {
            try
            {
                const auto& newFile = std::any_cast<FileName>(para);
                creatFile(newFile);

            }
            catch (const std::bad_any_cast& error)
            {
                std::cout << error.what() << '\n';
            }
        }

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
