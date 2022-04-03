#ifndef CMD_LINE_HPP
#define CMD_LINE_HPP

#include "Utility.hpp"

namespace DTSS
{
// type alias
using CharPtr = char*;

class CmdLine final
{
public:
    static void CreateInstance(const int argc, CharPtr* argv);
    static std::unique_ptr<CmdLine>& GetInstance();

    // disable copy-move by default!
    CmdLine(const CmdLine&) = delete;
    CmdLine& operator=(const CmdLine&) = delete;
    CmdLine(CmdLine&&) = delete;
    CmdLine& operator=(CmdLine&&) = delete;
    ~CmdLine() = default;

    const std::vector<std::string>& getOptionValues(std::string_view option) const noexcept;

    std::size_t optionsRecived() const noexcept;


    constexpr bool isValidOption(std::string_view option) const noexcept;

private:
    explicit CmdLine(const int argc, CharPtr* argv) noexcept;

    void parseArguments(const int argc, CharPtr* argv);

    void printCmdOptions() const noexcept;

private:
    inline static std::unique_ptr<CmdLine> instance{ nullptr };
    std::unordered_map<std::string_view, std::vector<std::string>> mCmdOptionArgMap;
};

}// DTSS

#endif // CMD_LINE_HPP

