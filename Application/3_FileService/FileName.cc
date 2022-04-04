#include "FileName.hpp"
#include "Utility.hpp"

// name-space alias
namespace DFS = DTSS::FileService;

DFS::File::File(std::filesystem::directory_entry dir
    , std::vector<std::string> startStrs
    , std::vector<std::string> endStrs
)
    : mPath{ std::move(dir) }
    , mStartWith { std::move(startStrs) }
    , mEndsWith{ std::move(endStrs) }
{}

bool DFS::File::isCreatedWithIn(std::chrono::duration<double> const& duration) const noexcept
{
    using namespace DTSS::Utility;
    // current time.
    const auto now = toSysTime(std::chrono::system_clock::now());
    // std::cout << "Current time      : " << std::ctime(&now) << "\n";

    // file creation time.
    const auto fileTime = toSysTime(std::filesystem::last_write_time(mPath));
    // std::cout << "File creation time: " << std::ctime(&fileTime) << "\n";

    // how long has been the file is crested after.
    const auto [hrs, mins, secs, ms] = timeTo_h_min_sec_ms(
        static_cast<std::chrono::duration<double>>(now - fileTime)
    );
    
    std::cout << "It has been " << hrs <<
        ":" << mins <<
        ":" << secs <<
        "." << ms << " after the file creation!\n\n\n";

    const auto [hrsCheck, minsCheck, secsCheck, msCheck] = timeTo_h_min_sec_ms(duration);


    if (hrsCheck == 0h) [[likely]]
    {
        if (minsCheck == 0min) [[likely]]
        {
            if (secsCheck == 0s) [[unlikely]]
            {
                // @TODO: Do we need ms check ??
                std::cout << "Unknown scenario!\n";
            }
            else [[likely]]
            {
                return secs <= secsCheck;
            }
        }
        else [[unlikely]]
        {
            return mins <= minsCheck;
        }
    }

    return hrs <= hrsCheck;
}

bool DFS::File::isGoodFile() const
{
    if (!mPath.is_regular_file())
        return false;

    const std::string fileNameStr = this->fileName().string();

    return std::ranges::any_of(mStartWith, [&fileNameStr](const auto& startStr) noexcept { return fileNameStr.starts_with(startStr); })
        || std::ranges::any_of(mEndsWith, [&fileNameStr](const auto& endStr) noexcept { return fileNameStr.ends_with(endStr); })
        || hasHexadecimal(fileNameStr);
}

bool DFS::File::hasHexadecimal(const std::string& str) const
{
    static const auto is_hex_digit = [](unsigned char c) { return std::isxdigit(c); };

    std::istringstream iss{ str };
    std::string possibleNum{};
    while (std::getline(iss, possibleNum, '.'))
    {
        std::cout << "possibleNum : " << possibleNum << '\n';
        if (!possibleNum.empty()
            && std::ranges::all_of(possibleNum, is_hex_digit))
            return true;
    }
    return false;
}

