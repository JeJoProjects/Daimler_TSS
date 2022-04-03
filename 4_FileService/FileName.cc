#include "FileName.hpp"



FileName::FileName(std::filesystem::directory_entry dir, std::string startStr, std::string endStr)
    : mPath{ std::move(dir) }
    , mStartWith { std::move(startStr) }
    , mEndsWith{ std::move(endStr) }
{}

bool FileName::isCreatedWithIn(std::chrono::duration<double> const& duration) const noexcept
{
    return false;
}

bool FileName::isGoodFile() const
{
    if (!mPath.is_regular_file())
        return false;

    const std::string fileNameStr = this->fileName().string();

    return fileNameStr.starts_with(mStartWith) || fileNameStr.ends_with(mEndsWith) || hasHexadecimal(fileNameStr);
}

bool FileName::hasHexadecimal(const std::string& str) const
{
    return false;
}

