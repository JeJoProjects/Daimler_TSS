#include "FileName.hpp"

#include <iostream>


    template<typename TimeType>
    constexpr auto toSysTime(TimeType&& time) noexcept
    {
        if constexpr (std::is_same_v<std::chrono::system_clock::time_point, TimeType>)
        {
            return std::chrono::system_clock::to_time_t(
                std::forward<TimeType>(time)
            );
        }
        else if constexpr (std::is_same_v<std::filesystem::file_time_type, TimeType>)
        {
            return std::chrono::system_clock::to_time_t(
                std::chrono::clock_cast<std::chrono::system_clock>(
                    std::forward<TimeType>(time)
                    )
            );
        }
    }

    template<typename Rep, typename Period = std::ratio<1>>
    constexpr auto timeTo_h_min_sec_ms(
        const std::chrono::duration<Rep, Period>& duration) noexcept
    {
        const auto hrs = duration_cast<std::chrono::hours>(duration);
        const auto mins = duration_cast<std::chrono::minutes>(duration - hrs);
        const auto secs = duration_cast<std::chrono::seconds>(duration - hrs - mins);
        const auto ms = duration_cast<std::chrono::milliseconds>(duration - hrs - secs);

        return std::make_tuple(hrs, mins, secs, ms);
    }


FileName::FileName(std::filesystem::directory_entry dir, std::string startStr, std::string endStr)
    : mPath{ std::move(dir) }
    , mStartWith { std::move(startStr) }
    , mEndsWith{ std::move(endStr) }
{}

bool FileName::isCreatedWithIn(std::chrono::duration<double> const& duration) const noexcept
{
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

    const auto [hrsCheck, minsCheck, secsCheck, msCheck] = timeTo_h_min_sec_ms(
        duration
    );
    return hrs <= hrsCheck && mins <= minsCheck && secs <= secsCheck && ms <= msCheck;
}

bool FileName::isGoodFile() const
{
    if (!mPath.is_regular_file())
        return false;

    const std::string fileNameStr = this->fileName().string();

    return fileNameStr.starts_with(mStartWith) || fileNameStr.ends_with(mEndsWith) || hasHexadecimal(fileNameStr);
}

bool FileName::hasHexadecimal(const std::string& str) const
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

