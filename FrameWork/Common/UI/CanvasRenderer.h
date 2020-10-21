#pragma once

#include "Config.h"
#include "MeshRenderer.h"

GameEngineBegin 

class Widget;
class CanvasRenderer : public MeshRenderer
{
private:
    /* data */
    std::vector<SharePtr<Widget>> m_Widgets;

public:
    CanvasRenderer(/* args */);
    ~CanvasRenderer();

    virtual void Start();
    virtual void Update();
    virtual void Render(SharePtr<Camera> camera);
    void addWidget(SharePtr<Widget> widget);
    void getWidget();
};
GameEngineEnd