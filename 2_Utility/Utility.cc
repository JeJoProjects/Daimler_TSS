#include "Utility.hpp"

namespace DTSS::Utility
{
    void __M_Assert(const char* expr_str, bool expr, const char* file, int line, const char* msg)
    {
        if (!expr)
        {
            std::cerr << "Assert failed:\t" << msg << "\n"
                << "Expected:\t" << expr_str << "\n"
                << "Source:\t\t" << file << ", line " << line << "\n";
            // exit(0);
            abort();
        }
    }

}