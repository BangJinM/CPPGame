#pragma once

#include "../Config.h"
#include "../Buffer.h"

#include <string>
using namespace std;
UseGameEngine
GameEngineFileBegin
class IFile
{
    virtual Buffer OpenFile(string path) = 0;
    virtual void WriteFile(string file, string path) = 0;
    virtual long long GetFileSize(string path) = 0;
    virtual bool IsFileExist(string path) = 0;
};
GameEngineFileEnd