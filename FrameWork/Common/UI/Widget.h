#pragma once

#include "Component.h"
namespace GameEngine
{
    class CanvasRenderer;
    class Widget : public Component
    {
    private:
        /* data */
        std::weak_ptr<CanvasRenderer> m_CanvasRenderer;
    public:
        Widget(/* args */);
        ~Widget();

        std::shared_ptr<CanvasRenderer> getCanvasRenderer();
        void setCanvasRenderer(std::shared_ptr<CanvasRenderer> canvasRenderer);
    };
} // namespace GameEngine