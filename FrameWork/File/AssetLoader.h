#pragma once

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "Buffer.h"
#include "Config.h"
#include "IFile.h"
#include "IFileSystem.h"
#include "IRuntimeModule.h"

namespace GameEngine
{
    class AssetLoader : public IRuntimeModule,
                        public IFile,
                        public IFileSystem
    {
    public:
        virtual ~AssetLoader(){};

        virtual int Initialize();
        virtual void Finalize();

        virtual void Tick();

        //***************************************************IFileSystem
        virtual bool AddSearchPath(const string path) override;
        virtual bool RemoveSearchPath(const string path) override;
        virtual string GetFileFullPath(const string path) override;
        //***************************************************IFileSystem

        //***************************************************IFile
        virtual FilePtr OpenFile(const string fullPath, FileOpenMode mode) override;
        virtual void CloseFile(FilePtr &fp) override;
        virtual size_t GetFileSize(const FilePtr &fp) override;
        virtual size_t SyncRead(const FilePtr &fp, Buffer &buf) override;
        virtual void WriteFile(const std::string &file,
                               const std::string path) override;
        virtual bool FileExists(const string fullPath) override;

        virtual Buffer SyncOpenAndReadText(const string filePath) override;
        virtual Buffer SyncOpenAndReadBinary(const string filePath) override;
        //***************************************************IFile

        inline std::string SyncOpenAndReadTextFileToString(const char *fileName)
        {
            std::string result;
            Buffer buffer = SyncOpenAndReadText(fileName);
            char *content = reinterpret_cast<char *>(buffer.GetData());

            if (content)
            {
                result = std::string(std::move(content));
            }

            return result;
        }

    private:
        std::vector<std::string> m_strSearchPath;
    };

}  // namespace GameEngine
