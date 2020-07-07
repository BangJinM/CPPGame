#ifndef CPPGAME_COMMON_AssetLoader_H
#define CPPGAME_COMMON_AssetLoader_H
#include "IRuntimeModule.h"
#include "Buffer.h"
#include <string>
#include <vector>
#include <map>
#include <utility>
namespace GameEngine
{
    class AssetLoader : public IRuntimeModule
    {
    public:
        virtual ~AssetLoader(){};

        virtual int Initialize();
        virtual void Finalize();

        virtual void Tick();

        typedef void *AssetFilePtr;

        enum AssetOpenMode
        {
            MY_OPEN_TEXT = 0,   /// Open In Text Mode
            MY_OPEN_BINARY = 1, /// Open In Binary Mode
        };

        enum AssetSeekBase
        {
            MY_SEEK_SET = 0, /// SEEK_SET
            MY_SEEK_CUR = 1, /// SEEK_CUR
            MY_SEEK_END = 2  /// SEEK_END
        };

        bool AddSearchPath(const char *path);

        bool RemoveSearchPath(const char *path);

        bool FileExists(const char *filePath);

        AssetFilePtr OpenFile(const char *name, AssetOpenMode mode);

        Buffer SyncOpenAndReadText(const char *filePath);

        Buffer SyncOpenAndReadBinary(const char *filePath);

        size_t SyncRead(const AssetFilePtr &fp, Buffer &buf);

        void CloseFile(AssetFilePtr &fp);

        size_t GetSize(const AssetFilePtr &fp);

        int32_t Seek(AssetFilePtr fp, long offset, AssetSeekBase where);

        inline std::string SyncOpenAndReadTextFileToString(const char *fileName)
        {
            auto fBegin = m_Assets.find(fileName);
            if (fBegin != m_Assets.end())
                return fBegin->second;
            std::string result;
            Buffer buffer = SyncOpenAndReadText(fileName);
            char *content = reinterpret_cast<char *>(buffer.m_pData);

            if (content)
            {
                m_Assets.insert(std::pair<std::string, std::string>(fileName, content));
                result = std::string(std::move(content));
            }

            return result;
        }

        std::string getFileExtension(const std::string &filePath) const;

		std::string GetFileName(const std::string &filePath)const;

        void WriteFile(const std::string &file, const std::string path);

        void getFullPath(std::string path);

    private:

        std::vector<std::string> m_strSearchPath;
        std::map<std::string, std::string> m_Assets;
    };

} // namespace GameEngine

#endif