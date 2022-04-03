#include "CmdLine.hpp"

namespace
{
    inline static constexpr std::array<std::pair<std::string_view, std::string_view>, 8> cmdOptions
    {
        {
            { "-Path"sv,           " Specify the directory(s) to be observed."sv },
            { "-Ext"sv,             " Specify the file extension(s) to be checked."sv },
            { "-NameStart"sv,       " Specify the desired file name start(s), for check."sv },
            { "-NameEnd"sv,         " Specify the desired file name end(s), for check."sv },

            { "-OutPath"sv,         " Specify the directory where the output archive should be stored. Default: Dir/user/"sv },
            { "-OutFileFormat"sv,   " Specify the output file archiver format. By default it is .tar format."sv },

            { "-bOutFileOnly"sv,    " Specify whether the output archive should contain only new file. Default: 0 ... false"sv },
            { "-bOutFileAndDirs"sv, " Specify whether the output archive should contain new file and whole directories and their contents. Default: 1 ... true"sv }
        }
    };
}

void DTSS::CmdLine::CreateInstance(const int argc, CharPtr* argv)
{
    if (!instance)
    {
        std::cout << "Creating CmdLine singleton instance.\n";
        instance.reset(new CmdLine{ argc, argv });
    }
}

std::unique_ptr<DTSS::CmdLine>& DTSS::CmdLine::GetInstance()
{
    DTSS::Utility::Assert(instance != nullptr, "Singleton instance is nullptr!");
    return instance;
}

DTSS::CmdLine::CmdLine(const int argc, CharPtr* argv) noexcept
{
    if (argc == 1)
    {
        printCmdOptions(); // nothing to parse!
    }
    else if(1 < argc && argv)
    {
        parseArguments(argc, argv);
    }
}

const std::vector<std::string>& DTSS::CmdLine::getOptionValues(
    std::string_view option) const noexcept
{
    if (const auto iter = mCmdArgumentMap.find(option);
        iter != std::cend(mCmdArgumentMap))
    {
        return iter->second;
    }
    
    static const std::vector<std::string> dummy;
    return dummy;
}

constexpr bool DTSS::CmdLine::isValidOption(std::string_view option) const noexcept
{
    return std::find_if(std::cbegin(cmdOptions), std::cend(cmdOptions),
        [&option](const auto& pair) constexpr noexcept {
            return pair.first == option;
        }) != std::cend(cmdOptions);
}

void DTSS::CmdLine::parseArguments(const int argc, CharPtr* const argv)
{
    for (int i = 1; i < argc; )
    {
        std::string_view currArg{ argv[i] };

        // if arg is a validate cmd option!
        if (!currArg.empty()
            && currArg.starts_with("-")
            && isValidOption(currArg))
        {
            // collect the values for this option
            std::vector<std::string> values;
            while (i + 1 < argc
                && std::string_view{ argv[i + 1] }.starts_with("-") == false)
            {
                ++i;
                values.emplace_back(argv[i]);
            }

            // add cmd option entry with values.
            mCmdArgumentMap.emplace(std::move(currArg), std::move(values));
        }
        else
        {
            std::cout << "WARNING: CmdLine parsing: "
                      << " [ " << currArg << " ]  is a wrong option!\n";
            while (i + 1 < argc
                && std::string_view{ argv[i + 1] }.starts_with("-") == false)
            {
                ++i; // increment until next valid option
            }
        }

        // otherwise 
        ++i;
    }

    // DEBUG: print commands revived
    for (const auto& [option, values] : mCmdArgumentMap)
    {
        std::cout << option << " : ";
        for (const auto& val : values) std::cout << val << " ";
        std::cout << "\n";
    }
}


void DTSS::CmdLine::printCmdOptions() const noexcept
{
    for (const auto& [option, description] : cmdOptions)
    {
        std::cout <<  option << "\t\t" << description << std::endl;
    }
}

