#ifndef CMD_LINE_HPP
#define CMD_LINE_HPP

#include "Utility.hpp"

namespace DTSS::Utility
{
// forward declaration(s)
class CmdLine;

// type alias(es)
using CharPtr = char*;
using UniqueCmdLine = std::unique_ptr<CmdLine>;

/*!
 * Singleton class "CmdLine" parse and stores the command line arguments. It also provide
 * access to the cmd line arguments through out the application.
 * If no cmd line arguments have been provided it uses the default ones.
 */
class CmdLine final
{
public:
    // static functions to create the Singleton class instance. 
    static void CreateInstance(const int argc, CharPtr* argv);

    // static functions to access the singleton instance.
    static UniqueCmdLine& GetInstance();

    // disable copy-move by default!
    CmdLine(const CmdLine&) = delete;
    CmdLine& operator=(const CmdLine&) = delete;
    CmdLine(CmdLine&&) = delete;
    CmdLine& operator=(CmdLine&&) = delete;

    // destructor 
    ~CmdLine() = default;

    /*!
     * Returns the values of a valid option provided.
     * 
     * @param option whose values should be retrieved.
     * @return values to the given cmd line option.
     * 
     * @TODO: Implement that caller doesn't know all the options and makes no typos!!!
     */
    template<typename ReType>
    ReType getOptionValues(std::string_view&& option) const noexcept;


    /*!
     * Function validate whether provided cmd options is valid as per the list.
     *
     * @param option which has to be validated.
     * @return bool... true, if valid option.
     */
    constexpr bool isValidOption(std::string_view option) const noexcept;

private:
    // constructor is for private use
    explicit CmdLine(const int argc, CharPtr* argv);

    /*!
     * Function to parse the cmd line arguments, as well as adding default values
     * to the options, when there is no cmd line arguments have been not provided.
     *
     * @param argc and argv.
     */
    void parseArguments(const int argc, CharPtr* argv);

    /*!
     * Function to the available options for the cmd line.
     */
    void printCmdOptions() const noexcept;

private:
    inline static UniqueCmdLine instance{ nullptr };
    std::unordered_map<std::string_view, std::vector<std::string>> mCmdOptionArgMap
    {
        { "-Path"sv,            {{"D:\\C++\\00_GitHub\\Daimler_TSS\\Build_and_Out\\Test"s}} },
        { "-Ext"sv,             {}                                                        },
        { "-Duration"sv,        {{"10s"s}}                                                  },

        { "-NameStart"sv,       {{"core"s}}                                                 },
        { "-NameEnd"sv,         {{"lz4"s}}                                                  },

        { "-OutPath"sv,         {{"D:\\C++\\00_GitHub\\Daimler_TSS\\Build_and_Out"s}}       },
        { "-OutFileFormat"sv,   {{".tar"s}}                                                 },

        { "-bOutFileOnly"sv,    {{"false"s}}  },
        { "-bOutFileAndDirs"sv, {{"true"s}} }
    };
};

template<typename ReType>
ReType CmdLine::getOptionValues(std::string_view&& option) const noexcept
{
    const auto iter = mCmdOptionArgMap.find(option);
    // @TODO: iter != std::cend(mCmdOptionArgMap)

    if constexpr (std::is_same_v<ReType, bool>)
    {
        const std::vector<std::string>& flagVec = iter->second;
        // @TODO: more error checks!
        return !flagVec.empty() && flagVec[0] == "true"s;
    } 
    else if constexpr (std::is_same_v<ReType, std::chrono::duration<double>>)
    {
        // @TODO: more error checks and convert correct time unit(h, min, sec etc.)!
        const std::vector<std::string>& timeStrs = iter->second;
        const std::chrono::duration<double> duration 
            = timeStrs.empty() ? 100s // default duration
            : static_cast<std::chrono::duration<double>>(std::stoul(timeStrs[0]));
        return duration;
    }
    else if constexpr (std::is_same_v<ReType, std::vector<std::string>>)
    {
        return iter->second;
    }
}

}// DTSS::Utility

#endif // CMD_LINE_HPP

