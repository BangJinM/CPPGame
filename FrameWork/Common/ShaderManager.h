#pragma once
#include "IShaderManager.h"
#include <map>
class ShaderProgramBase;
GameEngineBegin class ShaderManager : public IShaderManager
{
public:
    virtual SharedShaderProgramBase GetShaderProgram(int index)
    {
        return m_DefaultShaders[index];
    };

    virtual int AddShaderByPath(std::string vspath, std::string fspath) = 0;
    virtual int AddShaderByString(std::string vspath, std::string fspath) = 0;

    virtual void RemoveShader(int index)
    {
        auto shaders = m_DefaultShaders.find(index);
        if (shaders != m_DefaultShaders.end())
            m_DefaultShaders.erase(index);
    }

    virtual int AddShader(SharedShaderProgramBase shader)
    {
        index++;
        m_DefaultShaders[index] = shader;
        return index;
    }

protected:
    std::map<const int, SharedShaderProgramBase> m_DefaultShaders;
    int index = 1;
};


GameEngineEnd