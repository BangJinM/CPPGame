#ifndef GameEngine_Image_H
#define GameEngine_Image_H

#include <cstdint>
#include "MyMath.h"
#include "Object.h"
namespace GameEngine
{
    class Image :public Object
    {
        public:
        int id;
        uint32_t Width;
        uint32_t Height;
        char *data;
        size_t data_size;
    };
} // namespace GameEngine

#endif