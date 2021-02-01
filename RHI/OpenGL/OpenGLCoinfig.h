#pragma once
#include "GraphicsManager.h"
#include "OpenGLShaderManager.h"
namespace GameEngine
{
    BaseGraphicsManager *g_pGraphicsManager = static_cast<GraphicsManager *>(new GraphicsManager);
    ShaderManager *g_pShaderManager = static_cast<ShaderManager *>(new OpenGLShaderManager);
}  // namespace GameEngine
