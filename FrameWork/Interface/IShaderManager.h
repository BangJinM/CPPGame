#pragma once
#include <memory>

#include "Config.h"
#include "IRuntimeModule.h"
namespace GameEngine
{
    class IShaderManager : public IRuntimeModule
    {
    public:
        virtual ~IShaderManager() = default;

        virtual bool InitializeShaders() = 0;
        virtual void ClearShaders() = 0;
    };

}  // namespace GameEngine