#include "FileDetector.hpp"
#include "EventMgr.hpp"
#include "File.hpp"
#include "CmdLine.hpp"

// name-space aliases
namespace DFS = DTSS::FileService;
namespace DE = DTSS::Event;
namespace DTSSU = DTSS::Utility;

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
            // std::cout << dirEntry << "\n";
            if (std::filesystem::is_regular_file(dirEntry)
                && hasAllowedExtension(dirEntry.path().extension()))
            {
                File fileObj{ std::move(dirEntry)
                    , DTSSU::CmdLine::GetInstance()->getOptionValues<std::vector<std::string>>("-NameStart"sv)
                    , DTSSU::CmdLine::GetInstance()->getOptionValues<std::vector<std::string>>("-NameEnd"sv)
                };

                // @TODO: Test the files check!
                std::cout << "File : " << fileObj.file().string() << "\n\n";
                if (fileObj.isCreatedWithIn(duration) && fileObj.isGoodFile())
                {
#if 0
                    std::cout << fileObj.dir()
                        << " | File: " << fileObj.fileName().string()
                        << " | ext: " << fileObj.ext().string() << "\n";
#endif
                    DE::EventMgr::GetInstance()->notify(DE::EventType::NEW_FILE
                        , std::make_any<File>(std::move(fileObj))
                    );
                }               

            }
        }
    }
}

bool DFS::FileDetector::hasAllowedExtension(const PathType& ext) const noexcept
{
    if (mExtensions.empty()) // if no specific ext is not provided.
        return true;

    return std::ranges::any_of(mExtensions, [&ext](const auto& allowedExt) noexcept {
                return ext == allowedExt;
    });
}
