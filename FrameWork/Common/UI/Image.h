#pragma once

#include "Widget.h"
#include "Texture.h"
#include "MyMath.h"
namespace GameEngine
{
    class Image : public Widget
    {
    private:
        vecterFloat2 m_Size;
        Texture m_Texture;
    public:
        Image(/* args */);
        ~Image();
    };
} // namespace GameEngine