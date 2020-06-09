#ifndef GameEngine_Image_H
#define GameEngine_Image_H

#include <cstdint>
#include "MyMath.h"

namespace GameEngine{
    struct Image {
        uint32_t Width;
        uint32_t Height;
        R8G8B8A8Unorm* data;
        uint32_t bitcount;
        uint32_t pitch;
        size_t  data_size;
    };
}

#endif