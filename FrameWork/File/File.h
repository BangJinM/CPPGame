#pragma once

#include "../Config.h"
#include "../Interface/IFile.h"
#include "../Buffer.h"

#include <string>
using namespace std;

GameEngineFileBegin
class File : public IFile
{
    virtual Buffer OpenFile(string path);
    virtual void WriteFile(string file, string path);
    virtual long long GetFileSize(string path);
    virtual bool IsFileExist(string path);
};
GameEngineFileEnd