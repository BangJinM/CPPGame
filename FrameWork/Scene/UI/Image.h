#pragma once

#include "Config.h"
#include "MyMath.h"
#include "Widget.h"

namespace GameEngine
{
    class Texture;
    class Image : public Widget
    {
    private:
        vecterFloat2 m_Size;
        SharedTexture m_Texture;

    public:
        Image(/* args */);
        ~Image();
        virtual void Start();
        void setTexture(SharedTexture texture);
    };
}  // namespace GameEngine