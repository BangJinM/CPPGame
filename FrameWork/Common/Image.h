#ifndef GameEngine_Image_H
#define GameEngine_Image_H

#include <cstdint>
#include "MyMath.h"

namespace GameEngine
{
    struct Image
    {
        int id;
        uint32_t Width;
        uint32_t Height;
        char *data;
        size_t data_size;
    };
} // namespace GameEngine

#endif