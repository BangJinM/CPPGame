#pragma once

#include "Config.h"

using namespace GameEngine;

#include <string>

enum AssetOpenMode
{
    MY_OPEN_TEXT = 0,    /// Open In Text Mode
    MY_OPEN_BINARY = 1,  /// Open In Binary Mode
};
namespace GameEngine
{
    class IFileSystem
    {
    public:
        virtual bool AddSearchPath(const std::string path) = 0;

        virtual bool RemoveSearchPath(const std::string path) = 0;

        virtual std::string GetFileFullPath(const std::string path) = 0;
    };
}  // namespace GameEngine