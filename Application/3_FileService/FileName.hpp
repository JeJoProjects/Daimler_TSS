#ifndef FILE_NAME_HPP
#define FILE_NAME_HPP

#include "Utility.hpp"

namespace DTSS::FileService {

class FileName
{
    using PathType = std::filesystem::path;
    using DirType = std::filesystem::directory_entry;
public:
    explicit FileName(std::filesystem::directory_entry dir,
        std::string startStr = "core"s, std::string endStr = "lz4"s);

    // @TODO Special member functions

    bool isCreatedWithIn(std::chrono::duration<double> const& sec) const noexcept;
    bool isGoodFile() const;

    const DirType& dir() const { return mPath; }

    PathType file() const { return mPath.path().filename(); }

    PathType fileName() const { return file().stem(); }

    PathType ext() const { return mPath.path().extension(); }

private:
    bool hasHexadecimal(const std::string& str) const;


private:
    DirType mPath{};
    std::string mStartWith{};
    std::string mEndsWith{};
};

} // DTSS::FileService

#endif // FILE_NAME_HPP

