#ifndef FILE_DETECTOR_HPP
#define FILE_DETECTOR_HPP

#include "Utility.hpp"

namespace DTSS::FileService
{
/*!
 * class "FileDetector" provides the functionalities for the checking each
 * files in the given directory or set of directories, whether it satisfies the
 * condition of the file service application.
 */
class FileDetector final
{
public:
    // constructor
    explicit FileDetector(
        std::vector<std::string> const& paths, std::vector<std::string> const& exts);

    // disable copy-move by default!
    FileDetector(const FileDetector&) = delete;
    FileDetector& operator=(const FileDetector&) = delete;
    FileDetector(FileDetector&&) = delete;
    FileDetector& operator=(FileDetector&&) = delete;

    // destructor 
    ~FileDetector() = default;

    /*!
     * Function to detect a file; whether it is created within the given time period
     * and satisfies all the conditions specified by the file service.
     *
     * @param time period/ interval - most likely in sec.
     */
    void detectFile(std::chrono::duration<double> const& duration);

    /*!
     * Function to check whether the passed file has desired extension(s).
     *
     * @param Extension of the current file in check.
     * @return bool... true, if the file has desired extension.
     */
    bool hasAllowedExtension(const PathType& ext) const noexcept;

private:
    std::vector<PathType> mFilePaths{};
    std::vector<PathType> mExtensions{};
};


} // DTSS::FileService

#endif // #define FILE_DETECTOR_HPP

