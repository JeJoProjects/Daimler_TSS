#include "OutputMgr.hpp"
#include "Utility.hpp"
#include "CmdLine.hpp"
#include "EventMgr.hpp"
#include "File.hpp"

// name-space aliases
namespace DFS = DTSS::FileService;
namespace DE = DTSS::Event;

void spaceInfo(std::fstream& outFile, auto const& dir, int width = 14)
{
    using namespace DTSS::Utility;
    std::string c = "|";
    outFile << std::left;
    for (const auto s : { "Capacity", "Free", "Available", "Dir" })
        outFile << c << std::setw(width) << s << ' ';
    outFile << '\n';
    std::error_code ec;
    // @TODO: check spaces are correct
    const std::filesystem::space_info si = std::filesystem::space(dir, ec);
    outFile
        << c << std::setw(width) << Convert<std::intmax_t>::B2Mb(si.capacity) << ' '
        << c << std::setw(width) << Convert<std::intmax_t>::B2Mb(si.free) << ' '
        << c << std::setw(width) << Convert<std::intmax_t>::B2Mb(si.available) << ' '
        << c << dir << '\n';

}

auto creatAndWriteToFile(const DFS::File& file)
{
    std::filesystem::path path = []{
        const auto& outPaths 
            = DTSS::Utility::CmdLine::GetInstance()->getOptionValues<std::vector<std::string>>("-OutPath"sv);
        return outPaths[0];
    }();

    const auto folderName = file.fileName().string() + DTSS::Utility::generateRandomName();
    path /= (folderName + ".txt"s); // put something into there
    std::filesystem::create_directories(path.parent_path());

    std::fstream outFile{ path , std::ios::out };

    std::filesystem::path iterPath{ file.dir() };
    for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(iterPath.parent_path()))
    {
        if (std::filesystem::is_regular_file(dirEntry))
        {
            outFile << dirEntry << std::endl;
        }
        // @TODO: check the two booleans
        spaceInfo(outFile, dirEntry);
    }
    outFile.close();
}


DFS::OutputMgr::OutputMgr()
    : DE::EventObserver{}
{
    registerSelf();
}

DFS::OutputMgr::~OutputMgr()
{
    de_registerSelf();
}

void DFS::OutputMgr::handleEvent(const DE::EventType type, const std::any& para)
{
    switch (type)
    {
    case DE::EventType::NEW_FILE:
    {
        if (para.has_value())
        {
            try
            {
                const File& newFile = std::any_cast<File>(para);
                // @TDOD: FileArchiver class would have been nice
                creatAndWriteToFile(newFile);

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

void DFS::OutputMgr::registerSelf()
{
    DE::EventMgr::GetInstance()->attach(DE::EventType::NEW_FILE, this);
}

void DFS::OutputMgr::de_registerSelf()
{
    DE::EventMgr::GetInstance()->detach(DE::EventType::NEW_FILE, this);
}
