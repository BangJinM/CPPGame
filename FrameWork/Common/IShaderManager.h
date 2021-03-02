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
    };

}  // namespace GameEngine