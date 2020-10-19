#pragma once

#include "Config.h"
#include "Buffer.h"
#include "Image.h"

GameEngineBegin

class ImageParser
{
public:
    virtual Image Parse(const Buffer &buf) = 0;
};

GameEngineEnd
