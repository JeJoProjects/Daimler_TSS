#ifndef FILE_DETECTOR_HPP
#define FILE_DETECTOR_HPP

#include "Utility.hpp"

namespace DTSS::FileService {

class FileDetector // Subject
{
public:
    explicit FileDetector(
        std::vector<std::string> const& paths, std::vector<std::string> const& exts);

    void detectFile(std::chrono::duration<double> const& duration);
    bool check(const PathType& ext) const noexcept;

private:
    std::vector<PathType> mFilePaths{};
    std::vector<PathType> mExtensions{};
    //PathType newFile{};

};


} // DTSS::FileService

#endif // #define FILE_DETECTOR_HPP

