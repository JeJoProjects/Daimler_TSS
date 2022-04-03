#ifndef FILE_DETECTOR_HPP
#define FILE_DETECTOR_HPP

#include "Utility.hpp"

class FileDetector // Subject
{
public:
    template<typename... Paths>
    explicit FileDetector(std::vector<PathType> const& exts, Paths&&... paths);

    void detectFile(std::chrono::duration<double> const& duration);
    bool check(const PathType& ext);

private:
    std::vector<PathType> mFilePaths{};
    std::vector<PathType> mExtensions{};
    //PathType newFile{};

};

template<typename... Args>
FileDetector::FileDetector(std::vector<PathType> const& exts, Args&&... paths)
    : mExtensions{ exts }
{
    static_assert((std::is_constructible_v<PathType, Args> && ...));
    mFilePaths.reserve(sizeof...(Args));
    (mFilePaths.emplace_back(std::forward<Args>(paths)), ...);
}


#endif // #define FILE_DETECTOR_HPP
