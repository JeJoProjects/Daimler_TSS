#ifndef FILE_NAME_HPP
#define FILE_NAME_HPP

#include "Utility.hpp"

namespace DTSS::FileService 
{
/*!
 * class "File" manages the file operations in the Application.
 */
class File
{
    // type aliases for the class.
    using PathType = std::filesystem::path;
    using DirType = std::filesystem::directory_entry;

public:
    explicit File(std::filesystem::directory_entry dir
        , std::vector<std::string> start
        , std::vector<std::string> end);

    // Special member functions
    File(const File&) = default;
    File& operator=(const File&) = default;
    File(File&&) = default;
    File& operator=(File&&) = default;


    /*!
     * Function vto check wehther the given File is created within
     * the given time period.
     *
     * @param time period/ interval - most likly in sec.
     * @return bool... true, if created with in the given time limit.
     */
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
    std::vector<std::string> mStartWith{};
    std::vector<std::string> mEndsWith{};
};

} // DTSS::FileService

#endif // FILE_NAME_HPP

