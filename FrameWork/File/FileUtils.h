#pragma once

#include "../Config.h"
#include <string>
using namespace std;

GameEngineFileBegin
class FileUtils{
    string getFileExtension(string path);
    string GetFileName(string path);
};
GameEngineFileEnd