#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <iostream>
#include <type_traits>
#include <filesystem>
#include <algorithm>
#include <string_view>
#include <iterator>
#include <utility>
#include <vector>
#include <array>
#include <string>
#include <unordered_map>
#include <map>
#include <random>
#include <ranges>
#include <chrono>
#include <any>
#include <fstream>
#include <iomanip>

#include <cassert>
#include <cctype>
#include <ctime>

using namespace std::string_view_literals;
using namespace std::string_literals;
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.


using StrSizeType = std::string::size_type;
using PathType = std::filesystem::path;

namespace // constants
{
    inline static constexpr char allChars[]{ '0','1','2','3','4','5','6','7', '8','9',
    'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };

    template<typename T> inline static constexpr T BYTE     = static_cast<T>(1);
    template<typename T> inline static constexpr T KILOBYTE = static_cast<T>(1024);
    template<typename T> inline static constexpr T MEGABYTE = static_cast<T>(1024 * 1024);
    template<typename T> inline static constexpr T GIGABYTE = static_cast<T>(1024 * 1024 * 1024);
}

namespace DTSS::Utility
{
#ifndef NDEBUG
#   define Assert(Expr, Msg) \
    __M_Assert(#Expr, Expr, __FILE__, __LINE__, Msg)
#else
#   define Assert(Expr, Msg) ;
#endif
    void __M_Assert(const char* expr_str, bool expr, const char* file, int line, const char* msg);

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
    
    template<std::size_t N = std::size(allChars)>
    std::string generateRandomName(const char (&charArray)[N] = allChars, StrSizeType nameLength = 8u)
    {        
        std::mt19937 prng(std::random_device{}());
        std::uniform_int_distribution<StrSizeType> randIdx(0u, std::size(charArray) - 1u);

        std::string name;
        name.reserve(nameLength);

        while (nameLength--)
            name.push_back(charArray[ randIdx(prng) ]);

        return name;
    }

    template<typename T> struct Convert final
    {
        inline static constexpr T B2Kb(T bytes) noexcept { return bytes / KILOBYTE<T>; }
        inline static constexpr T B2Mb(T bytes) noexcept { return bytes / MEGABYTE<T>; }
    };
}

#endif // UTILITY_HPP

