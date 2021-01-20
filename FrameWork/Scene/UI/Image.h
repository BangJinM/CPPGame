#pragma once

#include "Widget.h"
#include "MyMath.h"
#include "Config.h"

GameEngineBegin 

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
GameEngineEnd