#pragma once

#include "Buffer.h"
#include "Config.h"

using namespace GameEngine;

#include <string>

namespace GameEngine
{
    typedef void *FilePtr;
    typedef int FileOpenMode;

    class IFile
    {
    public:
        virtual FilePtr OpenFile(const std::string fullPath, FileOpenMode mode) = 0;

        virtual void CloseFile(FilePtr &fp) = 0;

        virtual size_t SyncRead(const FilePtr &fp, Buffer &buf) = 0;

        virtual void WriteFile(const std::string &file, const std::string fullPath) = 0;

        virtual size_t GetFileSize(const FilePtr &fp) = 0;

        virtual bool FileExists(const std::string fullPath) = 0;

        virtual Buffer SyncOpenAndReadText(const std::string filePath) = 0;

        virtual Buffer SyncOpenAndReadBinary(const std::string filePath) = 0;
    };
}  // namespace GameEngine