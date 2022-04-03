#include "FileDetector.hpp"
#include "EventMgr.hpp"
#include "FileName.hpp"

namespace DFS = DTSS::FileService;

void DFS::FileDetector::detectFile(std::chrono::duration<double> const& duration)
{

    for(const auto& currPath: mFilePaths)
    {
        for (auto dirEntry : std::filesystem::recursive_directory_iterator(currPath))
        {
            if (std::filesystem::is_regular_file(dirEntry)
                && check(dirEntry.path().extension()))
            {
                FileName fileObj{ std::move(dirEntry) };
                std::cout << "File : " << fileObj.fileName().string() << "\n\n";
                if (fileObj.isCreatedWithIn(duration) && fileObj.isGoodFile())
                {
#if 1
                    std::cout << fileObj.dir()
                        << " | File: " << fileObj.fileName().string()
                        << " | ext: " << fileObj.ext().string() << "\n";
#endif
                    EventMgr::GetInstance()->notify(EventType::NEW_FILE, std::make_any<FileName>(fileObj));
                   

                }               

            }
        }
    }
}

bool DFS::FileDetector::check(const PathType& ext)
{
    if (mExtensions.empty()) // check all type of files
        return true;

    return std::ranges::any_of(mExtensions, [&ext](const auto& allowedExt) noexcept {
                return ext == allowedExt;
            });
}
