#include "AssetLoader.h"
#include <algorithm>
#include "easylogging++.h"
GameEngineFileBegin

    int
    AssetLoader::Initialize()
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

bool AssetLoader::AddSearchPath(const string path)
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

bool AssetLoader::RemoveSearchPath(const string path)
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

string AssetLoader::GetFileFullPath(const string path)
{
    return "";
}

bool AssetLoader::FileExists(const string fullPath)
{
    FilePtr fp = OpenFile(fullPath.c_str(), MY_OPEN_BINARY);
    if (fp != nullptr)
    {
        CloseFile(fp);
        return true;
    }
    return false;
}

FilePtr AssetLoader::OpenFile(const string name, FileOpenMode mode)
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
#ifdef _WINDOWS
            case MY_OPEN_TEXT:
                fopen_s(&fp, fullPath.c_str(), "r");
            case MY_OPEN_BINARY:
                fopen_s(&fp, fullPath.c_str(), "rb");
                break;
#else
            case MY_OPEN_TEXT:
                fp = fopen(fullPath.c_str(), "r");
                break;
            case MY_OPEN_BINARY:
                fp = fopen(fullPath.c_str(), "rb");
                break;
#endif
            }

            if (fp)
                return (FilePtr)fp;
        }

        upPath.append("../");
    }

    return nullptr;
}

Buffer AssetLoader::SyncOpenAndReadText(const string filePath)
{
    FilePtr fp = OpenFile(filePath, MY_OPEN_TEXT);
    Buffer *pBuff = nullptr;

    if (fp)
    {
        size_t length = GetFileSize(fp);

        pBuff = new Buffer(length + 1);
        length = fread(pBuff->m_pData, 1, length, static_cast<FILE *>(fp));
        pBuff->m_pData[length] = '\0';

        CloseFile(fp);
    }
    else
    {
        el::Loggers::getLogger("logger")->info("Error opening file '%s'\n", filePath);
        pBuff = new Buffer();
    }

#ifdef DEBUG
    fprintf(stderr, "Read file '%s', %d bytes\n", filePath, length);
#endif

    return *pBuff;
}

Buffer AssetLoader::SyncOpenAndReadBinary(const string filePath)
{
    FilePtr fp = OpenFile(filePath, MY_OPEN_BINARY);
    Buffer *pBuff = nullptr;

    if (fp)
    {
        size_t length = GetFileSize(fp);

        pBuff = new Buffer(length);
        fread(pBuff->m_pData, length, 1, static_cast<FILE *>(fp));

        CloseFile(fp);
    }
    else
    {
        el::Loggers::getLogger("logger")->info("Error opening file '%s'\n", filePath);
        pBuff = new Buffer();
    }

#ifdef DEBUG
    fprintf(stderr, "Read file '%s', %d bytes\n", filePath, length);
#endif

    return *pBuff;
}

void AssetLoader::CloseFile(FilePtr &fp)
{
    fclose((FILE *)fp);
    fp = nullptr;
}

size_t AssetLoader::GetFileSize(const FilePtr &fp)
{
    FILE *_fp = static_cast<FILE *>(fp);

    long pos = ftell(_fp);
    fseek(_fp, 0, SEEK_END);
    size_t length = ftell(_fp);
    fseek(_fp, pos, SEEK_SET);

    return length;
}

size_t AssetLoader::SyncRead(const FilePtr &fp, Buffer &buf)
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

void AssetLoader::WriteFile(const std::string &file, const std::string path)
{
    bool exist = FileExists(path.c_str());
    FILE *fp;
#ifdef _WINDOWS
    fopen_s(&fp, path.c_str(), "w");
#else
    fp = fopen(path.c_str(), "w");
#endif

    fwrite(file.c_str(), file.size(), 1, fp);
}
GameEngineFileEnd
