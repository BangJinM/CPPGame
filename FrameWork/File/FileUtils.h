#pragma once

#include "../Common/Config.h"
#include <string>
using namespace std;

GameEngineFileBegin class FileUtils
{
public:
    static std::string GetFileExtension(const std::string &filePath);

    static std::string GetFileName(const std::string &filePath);
};
GameEngineFileEnd