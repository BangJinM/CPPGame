#include "FileUtils.h"

#include <algorithm>
namespace GameEngine
{
    std::string
    GetFileExtension(const std::string &filePath)
    {
        std::string fileExtension;
        size_t pos = filePath.find_last_of('.');
        if (pos != std::string::npos)
        {
            fileExtension = filePath.substr(pos, filePath.length());

            std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower);
        }

        return fileExtension;
    }

    std::string GetFileName(const std::string &filePath)
    {
        char drive[_MAX_DRIVE];
        char dir[_MAX_DIR];
        char fname[_MAX_FNAME];
        char ext[_MAX_EXT];

        _splitpath(filePath.data(), drive, dir, fname, ext);
        std::string result = fname;
        return result;
    }

}  // namespace GameEngine