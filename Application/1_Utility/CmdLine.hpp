#ifndef CMD_LINE_HPP
#define CMD_LINE_HPP

#include "Utility.hpp"

namespace DTSS::Utility
{
// type alias
using CharPtr = char*;

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
    static std::unique_ptr<CmdLine>& GetInstance();

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
     */
    const std::vector<std::string>& getOptionValues(std::string_view option) const noexcept;


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
    inline static std::unique_ptr<CmdLine> instance{ nullptr };
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

}// DTSS::Utility

#endif // CMD_LINE_HPP

