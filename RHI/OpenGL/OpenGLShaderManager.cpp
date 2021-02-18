#include "OpenGLShaderManager.h"

#include "AssetLoader.h"
#include "Shader.h"

namespace GameEngine
{
    extern AssetLoader *g_pAssetLoader;

    bool OpenGLShaderManager::InitializeShaders()
    {
        return false;
    }

    void OpenGLShaderManager::ClearShaders()
    {
    }

    int OpenGLShaderManager::AddShaderByPath(std::string vspath, std::string fspath)
    {
        std::string vertStr = g_pAssetLoader->SyncOpenAndReadTextFileToString(vspath.c_str());
        std::string fragStr = g_pAssetLoader->SyncOpenAndReadTextFileToString(fspath.c_str());

        SharedShaderProgramBase shader = make_shared<ShaderProgram>();
        shader->AddShaderFromSourceCode(Shader::ShaderType::Vertex, vertStr.c_str());
        shader->AddShaderFromSourceCode(Shader::ShaderType::Fragment, fragStr.c_str());
        shader->Link();
        return AddShader(shader);
    }

    int OpenGLShaderManager::AddShaderByString(std::string vspath, std::string fspath)
    {
        SharedShaderProgramBase shader = make_shared<ShaderProgram>();
        shader->AddShaderFromSourceCode(Shader::ShaderType::Vertex, vspath.c_str());
        shader->AddShaderFromSourceCode(Shader::ShaderType::Fragment, fspath.c_str());
        shader->Link();
        return AddShader(shader);
    }
}  // namespace GameEngine
