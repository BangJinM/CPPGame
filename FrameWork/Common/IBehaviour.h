#pragma once

#include "Config.h"

namespace GameEngine
{
    class IBehaviour
    {
    public:
        ///////////////////////////////////
        // Start 开始
        ///////////////////////////////////
        virtual void Start() = 0;

        ///////////////////////////////////
        // OnEnable
        ///////////////////////////////////
        virtual void OnEnable() = 0;

        ///////////////////////////////////
        // Update 更新
        ///////////////////////////////////
        virtual void Update() = 0;

        ///////////////////////////////////
        // Destory 销毁
        ///////////////////////////////////
        virtual void Destory() = 0;
    };

}  // namespace GameEngine