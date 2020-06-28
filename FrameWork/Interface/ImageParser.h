#ifndef CPPGAME_INTERFACE_ImageParser_H
#define CPPGAME_INTERFACE_ImageParser_H

#include "Buffer.h"
#include "Image.h"

namespace GameEngine {
    class ImageParser
    {
    public:
        virtual Image Parse(const Buffer& buf) = 0;
    };
}

#endif