#pragma once
#include "IRuntimeModule.h"
#include <memory>
#include "Config.h"
GameEngineBegin class IShaderManager : public IRuntimeModule
{
public:
    virtual ~IShaderManager() = default;

    virtual bool InitializeShaders() = 0;
    virtual void ClearShaders() = 0;
};

GameEngineEnd