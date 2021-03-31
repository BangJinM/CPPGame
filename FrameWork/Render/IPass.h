﻿#pragma once
#include "Config.h"
#include "Camera.h"
namespace GameEngine
{
    class IPass
    {
    public:
        //////////////////////////////////////////
        // 初始化
        //////////////////////////////////////////
        virtual void Initialize() = 0;
        //////////////////////////////////////////
        // 开始渲染
        //////////////////////////////////////////
        virtual void BeginDraw() = 0;
        //////////////////////////////////////////
        // 渲染
        //////////////////////////////////////////
        virtual void Draw(SharedCamera) = 0;
        //////////////////////////////////////////
        // 结束渲染
        //////////////////////////////////////////
        virtual void EndDraw() = 0;
    };
}  // namespace GameEngine