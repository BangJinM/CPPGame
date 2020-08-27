#pragma once

#include "Widget.h"
#include "MyMath.h"
namespace GameEngine
{
    class Texture;
    class Image : public Widget
    {
    private:
        vecterFloat2 m_Size;
        std::shared_ptr<Texture> m_Texture;

    public:
        Image(/* args */);
        ~Image();
        virtual void Start();
        void setTexture(std::shared_ptr<Texture> texture);
    };
} // namespace GameEngine