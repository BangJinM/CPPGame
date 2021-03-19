#pragma once

#include "ShaderManager.h"
namespace GameEngine
{
    class OpenGLShaderManager : public ShaderManager
    {
    private:
        /* data */
    public:
        virtual int Initialize() override { return 0; }
        virtual void Finalize() override {}
        virtual void Tick(float deltaTime) override {}

        virtual int AddShaderByPath(std::string vspath, std::string fspath) override;
        virtual int AddShaderByString(std::string vspath, std::string fspath) override;
    };
}  // namespace GameEngine
