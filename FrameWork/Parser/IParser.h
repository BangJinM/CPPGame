#pragma once

#include "Object.h"
#include "Buffer.h"
#include <string>

using namespace std;

UseGameEngine
GameEngineParserBegin 

class IParser
{
public:
	virtual SharedObject Parser(const std::string path) { return nullptr; }
};
GameEngineParserEnd