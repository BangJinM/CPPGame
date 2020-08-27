#pragma once

#include "MeshRenderer.h"

namespace GameEngine
{
	class Widget;
    class CanvasRenderer : public MeshRenderer
    {
    private:
        /* data */
        std::vector<std::shared_ptr<Widget>> m_Widgets;

    public:
        CanvasRenderer(/* args */);
        ~CanvasRenderer();

        virtual void Start();
        virtual void Update();
        virtual void Render(std::shared_ptr<Camera> camera);
        void addWidget(std::shared_ptr<Widget> widget);
        void getWidget();
    };
} // namespace GameEngine