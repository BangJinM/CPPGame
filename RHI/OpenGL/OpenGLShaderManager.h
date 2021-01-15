#pragma once

#include "ShaderManager.h"
GameEngineBegin

    class OpenGLShaderManager : public ShaderManager
{
private:
    /* data */
public:
	virtual int Initialize() override { return 0; }
	virtual void Finalize() override{}
	virtual void Tick() override{}

    virtual bool InitializeShaders() override;
    virtual void ClearShaders() override;

    virtual int AddShaderByPath(std::string vspath, std::string fspath) override;
    virtual int AddShaderByString(std::string vspath, std::string fspath) override;
};
GameEngineEnd
