#pragma once

#include "Config.h"

UseGameEngine

#include <string>
    using namespace std;
enum AssetOpenMode
{
    MY_OPEN_TEXT = 0,   /// Open In Text Mode
    MY_OPEN_BINARY = 1, /// Open In Binary Mode
};
GameEngineFileBegin

    class IFileSystem
{
public:
    virtual bool AddSearchPath(const string path) = 0;

    virtual bool RemoveSearchPath(const string path) = 0;

    virtual string GetFileFullPath(const string path) = 0;
};
GameEngineFileEnd