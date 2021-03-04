#pragma once

#include <string>

#include "../Common/Config.h"

namespace GameEngine
{
    class FileUtils
    {
    public:
        static std::string GetFileExtension(const std::string &filePath);

        static std::string GetFileName(const std::string &filePath);
    };
}  // namespace GameEngine