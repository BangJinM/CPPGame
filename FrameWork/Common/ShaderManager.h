#pragma once
#include <map>

#include "IShaderManager.h"
class ShaderProgramBase;
namespace GameEngine
{
    class ShaderManager : public IShaderManager
    {
    public:
        virtual SharedShaderProgramBase GetShaderProgram(int index)
        {
            return m_DefaultShaders[index];
        };
        ///////////////////////////////
        // Add Shader
        // @param vspath
        // @param fspath
        //////////////////////////////
        virtual int AddShaderByPath(std::string vspath, std::string fspath) = 0;
        ///////////////////////////////
        // Add Shader
        // @param vsstring 
        // @param fsstring
        //////////////////////////////
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

}  // namespace GameEngine