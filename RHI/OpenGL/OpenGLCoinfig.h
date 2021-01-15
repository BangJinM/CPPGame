#pragma once
#include "OpenGLShaderManager.h"

namespace GameEngine
{
    ShaderManager *g_pShaderManager = static_cast<ShaderManager *>(new OpenGLShaderManager);
}
