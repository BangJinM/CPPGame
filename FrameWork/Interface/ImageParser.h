#ifndef CPPGAME_INTERFACE_ImageParser_H
#define CPPGAME_INTERFACE_ImageParser_H
#include "Image.hpp"
#include "Buffer.hpp"

namespace GameEngine {
    class ImageParser
    {
    public:
        virtual Image Parse(const Buffer& buf) = 0;
    };
}

#endif