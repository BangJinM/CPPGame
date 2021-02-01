#include "OpenGLShaderManager.h"

#include "Shader.h"

namespace GameEngine
{
    bool
    OpenGLShaderManager::InitializeShaders()
    {
        return false;
    }

    void OpenGLShaderManager::ClearShaders()
    {
    }

    int OpenGLShaderManager::AddShaderByPath(std::string vspath, std::string fspath)
    {
        SharedShaderProgramBase shader = make_shared<ShaderProgram>();
        shader->AddShaderFromSourceCode(Shader::ShaderType::Vertex, vspath.c_str());
        shader->AddShaderFromSourceCode(Shader::ShaderType::Fragment, fspath.c_str());
        shader->Link();
        return AddShader(shader);
    }

    int OpenGLShaderManager::AddShaderByString(std::string vspath, std::string fspath)
    {
        return 0;
    }
}  // namespace GameEngine
