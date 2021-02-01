#pragma once

#include "Buffer.h"
#include "Config.h"

using namespace GameEngine;

#include <string>
using namespace std;

namespace GameEngine
{
    typedef void *FilePtr;
    typedef int FileOpenMode;

    class IFile
    {
    public:
        virtual FilePtr OpenFile(const string fullPath, FileOpenMode mode) = 0;

        virtual void CloseFile(FilePtr &fp) = 0;

        virtual size_t SyncRead(const FilePtr &fp, Buffer &buf) = 0;

        virtual void WriteFile(const string &file, const string fullPath) = 0;

        virtual size_t GetFileSize(const FilePtr &fp) = 0;

        virtual bool FileExists(const string fullPath) = 0;

        virtual Buffer SyncOpenAndReadText(const string filePath) = 0;

        virtual Buffer SyncOpenAndReadBinary(const string filePath) = 0;
    };
}  // namespace GameEngine