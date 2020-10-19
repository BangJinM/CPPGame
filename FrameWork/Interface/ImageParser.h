#pragma once

#include "Buffer.h"
#include "Image.h"

namespace GameEngine
{
    class ImageParser
    {
    public:
        virtual Image Parse(const Buffer &buf) = 0;
    };
} // namespace GameEngine
