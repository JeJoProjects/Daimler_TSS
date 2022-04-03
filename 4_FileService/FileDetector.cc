#include "FileDetector.hpp"
#include "EventMgr.hpp"
#include "FileName.hpp"

namespace DFS = DTSS::FileService;
namespace DE = DTSS::Event;

DFS::FileDetector::FileDetector(
    std::vector<std::string> const& paths, std::vector<std::string> const& exts)
{
    mFilePaths.reserve(paths.size());
    for (const auto& strPath : paths)
        mFilePaths.emplace_back(strPath);

    mExtensions.reserve(exts.size());
    for (const auto& strPath : exts)
        mExtensions.emplace_back(strPath);
}

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
                    DE::EventMgr::GetInstance()->notify(
                        DE::EventType::NEW_FILE, std::make_any<FileName>(fileObj)
                    );
                }               

            }
        }
    }
}

bool DFS::FileDetector::check(const PathType& ext) const noexcept
{
    if (mExtensions.empty()) // check all type of files
        return true;

    return std::ranges::any_of(mExtensions, [&ext](const auto& allowedExt) noexcept {
                return ext == allowedExt;
            });
}
