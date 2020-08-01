#include "AssetLoader.h"
#include <algorithm>
namespace GameEngine
{
    int AssetLoader::Initialize()
    {
        return 0;
    }

    void AssetLoader::Finalize()
    {
        m_strSearchPath.clear();
    }

    void AssetLoader::Tick()
    {
    }

    bool AssetLoader::AddSearchPath(const char *path)
    {
        std::vector<std::string>::iterator src = m_strSearchPath.begin();

        while (src != m_strSearchPath.end())
        {
            if (!(*src).compare(path))
                return true;
            src++;
        }

        m_strSearchPath.push_back(path);
        return true;
    }

    bool AssetLoader::RemoveSearchPath(const char *path)
    {
        std::vector<std::string>::iterator src = m_strSearchPath.begin();

        while (src != m_strSearchPath.end())
        {
            if (!(*src).compare(path))
            {
                m_strSearchPath.erase(src);
                return true;
            }
            src++;
        }

        return true;
    }

    bool AssetLoader::FileExists(const char *filePath)
    {
        AssetFilePtr fp = OpenFile(filePath, MY_OPEN_BINARY);
        if (fp != nullptr)
        {
            CloseFile(fp);
            return true;
        }
        return false;
    }

    AssetLoader::AssetFilePtr AssetLoader::OpenFile(const char *name, AssetOpenMode mode)
    {
        FILE *fp = nullptr;
        // loop N times up the hierarchy, testing at each level
        std::string upPath;
        std::string fullPath;
        for (int32_t i = 0; i < 10; i++)
        {
            std::vector<std::string>::iterator src = m_strSearchPath.begin();
            bool looping = true;
            while (looping)
            {
                fullPath.assign(upPath); // reset to current upPath.
                if (src != m_strSearchPath.end())
                {
                    fullPath.append(*src);
                    fullPath.append("/Asset/");
                    src++;
                }
                else
                {
                    fullPath.append("Asset/");
                    looping = false;
                }
                fullPath.append(name);
#ifdef DEBUG
                fprintf(stderr, "Trying to open %s\n", fullPath.c_str());
#endif
                switch (mode)
                {
                case MY_OPEN_TEXT:
                    fp = fopen(fullPath.c_str(), "r");
                    break;
                case MY_OPEN_BINARY:
                    fp = fopen(fullPath.c_str(), "rb");
                    break;
                }

                if (fp)
                    return (AssetFilePtr)fp;
            }

            upPath.append("../");
        }

        return nullptr;
    }

    Buffer AssetLoader::SyncOpenAndReadText(const char *filePath)
    {
        AssetFilePtr fp = OpenFile(filePath, MY_OPEN_TEXT);
        Buffer *pBuff = nullptr;

        if (fp)
        {
            size_t length = GetSize(fp);

            pBuff = new Buffer(length + 1);
            length = fread(pBuff->m_pData, 1, length, static_cast<FILE *>(fp));
            pBuff->m_pData[length] = '\0';

            CloseFile(fp);
        }
        else
        {
            fprintf(stderr, "Error opening file '%s'\n", filePath);
            pBuff = new Buffer();
        }

#ifdef DEBUG
        fprintf(stderr, "Read file '%s', %d bytes\n", filePath, length);
#endif

        return *pBuff;
    }

    Buffer AssetLoader::SyncOpenAndReadBinary(const char *filePath)
    {
        AssetFilePtr fp = OpenFile(filePath, MY_OPEN_BINARY);
        Buffer *pBuff = nullptr;

        if (fp)
        {
            size_t length = GetSize(fp);

            pBuff = new Buffer(length);
            fread(pBuff->m_pData, length, 1, static_cast<FILE *>(fp));

            CloseFile(fp);
        }
        else
        {
            fprintf(stderr, "Error opening file '%s'\n", filePath);
            pBuff = new Buffer();
        }

#ifdef DEBUG
        fprintf(stderr, "Read file '%s', %d bytes\n", filePath, length);
#endif

        return *pBuff;
    }

    void AssetLoader::CloseFile(AssetFilePtr &fp)
    {
        fclose((FILE *)fp);
        fp = nullptr;
    }

    size_t AssetLoader::GetSize(const AssetFilePtr &fp)
    {
        FILE *_fp = static_cast<FILE *>(fp);

        long pos = ftell(_fp);
        fseek(_fp, 0, SEEK_END);
        size_t length = ftell(_fp);
        fseek(_fp, pos, SEEK_SET);

        return length;
    }

    size_t AssetLoader::SyncRead(const AssetFilePtr &fp, Buffer &buf)
    {
        size_t sz;

        if (!fp)
        {
            fprintf(stderr, "null file discriptor\n");
            return 0;
        }

        sz = fread(buf.m_pData, buf.m_szSize, 1, static_cast<FILE *>(fp));

        return sz;
    }

    int32_t AssetLoader::Seek(AssetFilePtr fp, long offset, AssetSeekBase where)
    {
        return fseek(static_cast<FILE *>(fp), offset, static_cast<int>(where));
    }

    std::string AssetLoader::getFileExtension(const std::string &filePath) const
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

    std::string AssetLoader::GetFileName(const std::string &filePath) const
    {
        char drive[_MAX_DRIVE];
        char dir[_MAX_DIR];
        char fname[_MAX_FNAME];
        char ext[_MAX_EXT];

        _splitpath(filePath.data(), drive, dir, fname, ext);
        std::string result = fname;
        delete drive;
        delete dir;
        delete fname;
        delete ext;
        return result;
    }

    void AssetLoader::WriteFile(const std::string &file, const std::string path)
    {
        bool exist = FileExists(path.c_str());
        FILE *fp;
        fp = fopen(path.c_str(), "w");
        fwrite(file.c_str(), file.size(), 1, fp);
    }
} // namespace GameEngine